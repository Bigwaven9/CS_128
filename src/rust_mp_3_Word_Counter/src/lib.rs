// discussed with chaoqil2

/// This module contains code that takes in a dataset and maps each piece of 
/// data to some value. These functions are used in the MAP stage in MapReduce. 
/// These functions can stand alone and map an entire dataset. They may also be 
/// on a number of distinct distributed nodes to map pieces of an entire dataset. 
/// The mapped data on each node will then be combined to produce a result 
/// equivalent to that of mapping an entire dataset on a single node.
pub mod mappers {
    use std::{collections::HashMap, hash::Hash};

    // STEP 1: COMPLETE THIS FUNCTION FIRST

    /// [COMPLETE THIS FUNCTION]
    /// Takes a `Vec` of words and creates a map from the word (the key) to the 
    /// number of occurrences (the value) of that word in the given `Vec`.
    /// 
    /// @param `words` - a `Vec` of `String`s. You can assume that all `String`s 
    ///                  have been formatted and stripped of whitespace, 
    ///                  punctutation, etc.
    /// 
    /// @return a `HashMap` with distinct words as keys and the number of 
    ///         occurrences of the key in given `Vec` of `String`s.
    pub fn word_count_mapper(words: &Vec<String>) -> HashMap<String, usize> {
        // [YOUR CODE HERE]
        let mut ret:HashMap<String, usize> = HashMap::new();
        for i in words {
            if ret.contains_key(i) {
                ret.insert(i.clone(), ret[i] + 1);
            } else {
                ret.insert(i.clone(), 1 as usize);
            }
        }
        return ret;
    }

    // STEP 2: COMPLETE THIS FUNCTION SECOND

    /// [COMPLETE THIS FUNCTION]
    /// Takes a `Vec` of words and creates a map from the length of a word (the
    /// key) to the number of occurrences of words with that length (the value) 
    /// in the given `Vec`.
    /// 
    /// @param `words` - a `Vec` of `String`s. You can assume that all `String`s 
    ///                  have been formatted and stripped of whitespace, 
    ///                  punctutation, etc.
    /// 
    /// @return a `HashMap` with distinct word *LENGTHS* as keys and the number of 
    ///         occurrences of the key in given `Vec` of `String`s.
    pub fn word_length_mapper(words: &Vec<String>) -> HashMap<usize, usize> {
        // [YOUR CODE HERE]
        let mut ret:HashMap<usize, usize> = HashMap::new();
        for i in words {
            if ret.contains_key(&i.len()) {
                ret.insert(i.len(), ret[&i.len()] + 1);
            } else {
                ret.insert(i.len(), 1 as usize);
            }
        }
        return ret;
    }
}

/// This module contains code that assigns work to multiple nodes (threads) and 
/// manages the data mapping on each node. This is the MAP stage of MapReduce. 
pub mod map {
    use std::sync::{mpsc, mpsc::Receiver};
    use std::collections::HashMap;
    use std::thread::JoinHandle;
    use std::hash::Hash;
    use std::thread;

    use crate::mappers;

    use super::mappers::word_length_mapper;
    use super::mappers::word_count_mapper;

    // STEP 3: COMPLETE THIS FUNCTION NEXT

    /// [COMPLETE THIS FUNCTION]
    /// Splits a vector of strings (`items`) into the specified number of 
    /// sub-vectors (`num_chunks`) such that the difference in lengths of each 
    /// sub-vector (chunk) is no more or no less than 1 word.
    /// 
    /// This function helps to distribute the workload of mapping a dataset
    /// to multiple nodes by dividing up the work into chunks. You will use this
    /// function to help assigning work to multiple nodes. 
    /// 
    /// It is up to you how you distribute the workload. You can sequentially 
    /// assign words at an index offset to a chunk of the same index (modulo). 
    /// You could also choose to assign the first `k` pieces of data to the 1st
    /// chunk. We will only be checking the length of each of the chunks you 
    /// form. Make sure that you do not discard any pieces of data. If you do 
    /// discard any data, your final results will differ from what we expect. 
    /// 
    ///     -> abs ( length( result[0] ) - length( result[1] ) ) <= 1
    ///     -> abs ( length( result[1] ) - length( result[2] ) ) <= 1
    ///     -> abs ( length( result[2] ) - length( result[3] ) ) <= 1
    ///     -> abs ( length( result[3] ) - length( result[0] ) ) <= 1
    ///     etc...
    /// 
    /// @param `items` - a `Vec` of `String`s (the dataset) that must be split 
    ///                  into smaller chunks of data. 
    /// 
    /// @param `num_chunks` - an unsigned integer indicating the number of 
    ///                       chunks to split the data into. You can assume that 
    ///                       this parameter will be non-zero.
    /// 
    /// @return a `Vec` of `Vec`s of `String`s. The returned `Vec` should 
    ///         contain `num_chunks` `Vec`s of `String`s. Each `Vec` of 
    ///         `String`s should contain similar numbers of words. Refer to the 
    ///         description above for more details. 
    pub fn split_into_chunks(items: &Vec<String>, num_chunks: usize) 
            -> Vec<Vec<String>> {
        // [YOUR CODE HERE]
        let mut ret:Vec<Vec<String>> = Vec::new();
        let mut cnt = items.len() % num_chunks;
        let n = items.len() / num_chunks;
        for i in 0..num_chunks {
            let start = i * n;
            let end = start + n;
            let mut v:Vec<String> = items[start..end].to_vec().clone();
            if cnt != 0 {
                v.push(items[items.len() - cnt].clone());
                cnt -= 1;
            }
            ret.push(v.clone());
        }
        return ret;
    }

    // STEP 4: COMPLETE THIS FUNCTION NEXT

    /// [COMPLETE THIS FUNCTION]
    /// Takes a `Vec` of `String`s and spawns the specified number of threads 
    /// (`num_chunks`). Each thread will call the `word_length_mapper mapper` 
    /// function using chunks of data of roughly-equal length (see the 
    /// description of `split_into_chunks`).
    /// 
    /// This is the MAP stage in MapReduce. This function will break up the 
    /// dataset into smaller chunks, distribute each chunk to a node, and 
    /// monitor the progress of each node.
    /// 
    /// HINT: use the `split_into_chunks` function!
    /// 
    /// @param `words` - a `Vec` of `String`s. You can assume that all `String`s 
    ///                  have been formatted and stripped of whitespace, 
    ///                  punctutation, etc.
    /// 
    /// @param `num_chunks` - an unsigned integer indicating the number nodes 
    ///                       that will be working in parallel to map the given 
    ///                       dataset. You can assume that this parameter will 
    ///                       be non-zero.
    /// 
    /// @return a tuple containing a `Vec` of the JoinHandle of each thread spawned 
    ///         and the mpsc::Receiver created by the main thread channel.

    pub fn multi_threaded_mapper(words: &Vec<String>, num_chunks: usize) 
                    -> (Vec<JoinHandle<()>>, Receiver<HashMap<usize, usize>>) {
        // [YOUR CODE HERE]
        let mut ret:Vec<JoinHandle<()>> = Vec::new();
        let (tx, rx) = mpsc::channel();

        for i in split_into_chunks(words, num_chunks) {
            let tx_clone = tx.clone();
            ret.push(thread::spawn(move || {
                tx_clone.send(word_length_mapper(&i)).unwrap();
            }));
        }
        return (ret, rx);
    }

    // STEP 5: COMPLETE THIS FUNCTION NEXT
    //         COMPLETE THIS FUNCTION ONLY AFTER HAVING COMPLETED STEP 4
    //         THIS IMPLEMENTATION WILL BE SIMILAR TO THAT IN STEP 4

    /// [COMPLETE THIS FUNCTION]
    /// This function is a `GENERIC` version of the `multi_threaded_mapper`
    /// function. It is identical to the function above apart from the fact that
    /// there is an additional parameter that takes in a `function pointer`. The 
    /// function pointer is, well, a pointer to a function. The thing to note is 
    /// that this  function pointer is a pointer to a generic function (more on 
    /// this in a bit). 
    /// 
    /// This function takes in a `Vec` of `String`s and returns a `HashMap` with 
    /// keys of *ALMOST* any type and values of type `usize`. The key values are 
    /// bounded by certain parameters, as indicated here in the function 
    /// signature: (`<KeyType: 'static + Eq + Hash + Send>`). The first bound is 
    /// a `LIFETIME`. The `'static` lifetime indicates that the variable will 
    /// last the *ENTIRE* runtime of the *FUNCTION*. The remaining bounds are 
    /// `Trait`s that `KeyType` must implement. 
    /// 
    ///     -> `Eq`: `KeyType` can be compared for equality
    ///     -> `Hash`: `KeyType` can be hashed 
    ///     -> `Send`: `KeyType` can be sent safely between threads 
    /// 
    /// Refer to the description of `multi_threaded_mapper` for a detailed 
    /// explanation of the functionality of this method. The only difference is 
    /// that this function will call the function passed in by the parameter 
    /// `func` (a function pointer) in each thread on the chunk of data assigned
    /// to the corresponding thread. 
    /// 
    /// @param `words` - a `Vec` of `String`s. You can assume that all `String`s 
    ///                  have been formatted and stripped of whitespace, 
    ///                  punctutation, etc.
    /// 
    /// @param `num_chunks` - an unsigned integer indicating the number nodes 
    ///                       that will be working in parallel to map the given 
    ///                       dataset. You can assume that this parameter will 
    ///                       be non-zero.
    /// 
    /// @param `func` - a function pointer to a function that takes in a 
    ///                 borrowed `Vec` of `String`s and returns a `HashMap` with 
    ///                 generic keys and values of type `usize`. Refer to the 
    ///                 description above for more information on generics. 
    /// 
    /// @return a tuple containing a `Vec` of the JoinHandle of each thread spawned 
    ///         and the mpsc::Receiver created by the main thread channel.
    pub fn multi_threaded_mapper_generic<KeyType: 'static + Eq + Hash + Send>(
                words: &Vec<String>, 
                num_chunks: usize, 
                func: fn(&Vec<String>) -> HashMap<KeyType, usize>) 
            -> (Vec<JoinHandle<()>>, Receiver<HashMap<KeyType, usize>>) {
        // [YOUR CODE HERE]
        let mut ret:Vec<JoinHandle<()>> = Vec::new();
        let (tx, rx) = mpsc::channel();

        for i in split_into_chunks(words, num_chunks) {
            let tx_clone = tx.clone();
            ret.push(thread::spawn(move || {
                tx_clone.send(func(&i)).unwrap();
            }));
        }
        return (ret, rx);
    }
}

/// This module contains code that combines the results generated by all of the 
/// nodes (threads). This is the REDUCE stage of MapReduce. 
pub mod reduce {
    use std::collections::HashMap;
    use std::sync::mpsc::Receiver;
    use std::thread::JoinHandle;
    use std::hash::Hash;

    // STEP 6: COMPLETE THIS FUNCTION NEXT

    /// [COMPLETE THIS FUNCTION]
    /// Receives the results contained in the `Vec` of tuples of `JoinHandle`s 
    /// and `mpsc::Receiver`s and then combines the received results into a 
    /// single `HashMap` from `KeyType` to a `usize` such that the values mapped 
    /// to the same key in different received `HashMaps` will be added to each 
    /// other and stored under that same key in the resulting `HashMap`.
    /// 
    /// This function will be able to consume the `Vec` returned by either the 
    /// `multi_threaded_mapper_generic` function or the `multi_threaded_mapper`
    /// function. 
    /// 
    /// Refer to the description of the `multi_threaded_mapper_generic` function
    /// for more information on `GENERICS`. Refer to the `map` module and its
    /// functions for more information on how the given `Vec` is generated.
    /// 
    /// @param `receivers` - a tuple containing the `Vec` of a JoinHandle for each 
    ///         thread spawned and the mpsc::Receiver created by the main thread channel.
    /// 
    /// @return a `HashMap` from `KeyType` to a `usize` that is the result of 
    ///         combining the received `HashMaps` by adding values with the 
    ///         same key and storing under the same key.
    pub fn thread_reducer<KeyType: Eq + Hash>(
                receivers: (Vec<JoinHandle<()>>, Receiver<HashMap<KeyType, usize>>)) 
            -> HashMap<KeyType, usize> {
        // [YOUR CODE HERE]
        let mut ret:HashMap<KeyType, usize> = HashMap::new();
        let (a, b) = receivers;
        for i in a {
            i.join().unwrap();
        }
        while let Ok(x) = b.recv() {
            for (k, v) in x {
                if ret.contains_key(&k) {
                    *ret.get_mut(&k).unwrap() += v;
                } else {
                    ret.insert(k, v);
                }
            }
        }
        return ret;
    }
}
