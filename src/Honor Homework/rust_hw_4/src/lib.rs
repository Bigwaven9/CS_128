use std::ops::{IndexMut, Index};

/// TODO: Implement this function that passes a mutable Vector of Strings
/// You must iterate through the vector. 
/// If the word has an even number of characters, reverse the word by using the reverse function.
/// If the word has an odd number of characters, count the number of vowels in the word.
/// You should return a tuple containg a Vector of the reversed words 
/// and the total number of vowels from odd lengthed words.
pub fn vector_iter(words: &mut Vec<String>) -> (Vec<String>, i32) {
    let mut v : Vec<String> = Vec::new();
    let mut cnt = 0;
    for i in words.iter_mut() {
        if i.len() % 2 == 0 {
            reverse_word(i);
            v.push(i.clone());
        } else {
            cnt += count_vowels(i);
        }
    }
    return (v, cnt);
}

/// TODO: Implement this function that takes a String and reverses it.
/// This should directly modify the contents of the passed String.
pub fn reverse_word(word: &mut String) {
    for i in 0..word.len() / 2 {
        let temp = word.chars().nth(i).unwrap();
        word.replace_range(i..i + 1, word.chars().nth(word.len() - i - 1).unwrap().to_string().as_str());
        word.replace_range(word.len() - 1 - i..word.len() - i, temp.to_string().as_str());
    }
}

/// TODO: Implement this function that takes a String and counts the number of vowels in it.
/// In this instance, we mean the vowels a, e, i, o, and u. Do not worry about y.
/// You will need to handle words with upper and lower case vowels.
/// You should not modify the contents of the passed String.
/// You should return the vowel count.
pub fn count_vowels(word: &str) -> i32 {
    let mut cnt = 0;
    for i in word.chars() {
        if i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u' || i == 'A' || i == 'E' || i == 'O' || i == 'U' || i == 'I' {
            cnt += 1;
        }
    }
    return cnt;
}


// You can test your code with the test cases we've provided by running `cargo test`
// We also encourage you to add more assert statements to test out your code further!
#[cfg(test)]
mod test {
    use super::*;
    
    #[test]
    fn test_vector_iter() {
        let words: &mut Vec<String> = &mut vec!["fish".to_string(), "cat".to_string(), "ardvaark".to_string(), "dog".to_string(), "bird".to_string(), "ant".to_string()];
        let (reversed_words, count) = vector_iter(words);
        assert_eq!(reversed_words, vec!["hsif".to_string(), "kraavdra".to_string() ,"drib".to_string()]);
        assert_eq!(count, 3);
    }

}
