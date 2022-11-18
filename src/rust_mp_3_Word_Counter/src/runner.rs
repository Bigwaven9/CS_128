use textplots::{Chart, Plot, Shape};
use std::time::{Duration, Instant};
use std::collections::HashMap;
use std::fs;

use crate::dummy_project::{mappers::*, reduce::*, map::*};

// [COMPLETED FUNCTION - DO NOT EDIT - USE THIS AS YOU SEE FIT]
pub fn run(filepath: &str) -> HashMap<usize, usize> {
    // This function is only here so that main() is not cluttered.
    // Feel free to delete this function or change it to play around and experiment :)

    let start: Instant = Instant::now();
    let cleaned_contents: String = load_file(filepath);

    let words: Vec<String> = cleaned_contents.split(" ")
        .into_iter()
        .map(|s: &str| s.to_owned())
        .collect();

    println!("Num words: {}", words.len());

    // Run and print the duration of a single function by passing a function pointer.
    let _word_counts: HashMap<usize, usize> = 
        run_and_print_duration("word_length_mapper()", &words, word_length_mapper);

    // Run and print the duration of multiple functions by passing a closure.
    let word_counts_mt: HashMap<usize, usize> = 
        run_and_print_duration(
            &format!("multi_threaded_generics for {} at {} threads", "word_length_mapper()", 10)[..],
            &words,
            move |w: &Vec<String>| {
                // you must pass in literals (unless you are borrowing) inside 
                // this closure so the closure will be interpreted as a function pointer
                // NOTE: compare the word vector borrow above ("&words") 
                // to the number of threads literal and function pointer that are consumed.
                let results = multi_threaded_mapper_generic(&w, 10, word_length_mapper.clone());
                thread_reducer(results)
            }
        );

    // assert!(word_counts_mt == _word_counts); // if you want a sanity check :)

    // Print the duration of the runtime.
    let duration: Duration = start.elapsed();
    println!("Time elapsed was: {:?}", duration);

    word_counts_mt
}

// [COMPLETED FUNCTION - DO NOT EDIT - USE THIS AS YOU SEE FIT]
pub fn load_file(filepath: &str) -> String {
    // Reads a file from the specified path to a String.
    // This function has already been implemented. You can use this in your own testing.
    fs::read_to_string(filepath).expect("Something went wrong reading the file")
}

// [COMPLETED FUNCTION - DO NOT EDIT - USE THIS AS YOU SEE FIT]
pub fn graph_results(results: HashMap<usize, usize>) {
    // Graph a histogram depicting the relative frequency of words by word length.
    // This function has already been implemented. You can use this in your own testing.
    let word_count = results.iter().fold(0f32, |sum, (_key, val)| sum + *val as f32);

    let mut points: Vec<(f32, f32)> = results.into_iter()
        .map(|(a, b): (usize, usize)| (a as f32, 100.0 * (b as f32 / word_count)))
        .collect();

    points.sort_by_key(|k| k.0 as i32);

    let (min, max): (f32, f32) = (0.0, 15.0);
    println!("Relative Frequency of Words by Word Length");
    println!("\ny = percent occurence of word length, x = word length");
    Chart::new(180, 100, min, max)
        .lineplot(&Shape::Bars(&points))
        .nice();
}

// [COMPLETED FUNCTION - DO NOT EDIT - USE THIS AS YOU SEE FIT]
pub fn run_and_print_duration<InputType, OutputType>(func_name: &str, input: InputType, func: fn(InputType) -> OutputType) -> OutputType {
    // This function prints the time taken by a a function and returns the result of that function.
    // The function that is run must take in an input parameter and return some output parameter.
    // HINT: Use this function to find the duration of your implementations of 
    //          1. word_count_mapper
    //          2. word_length_mapper
    //          3. multi_threaded_mapper
    //          4. multi_threaded_mapper_generic using the "word_count_mapper" function
    //          5. multi_threaded_mapper_generic using the "word_length_mapper" function
    // This function has already been implemented. You can use this in your own testing.
    
    let start: Instant = Instant::now();
    let result: OutputType = func(input);
    let duration: Duration = start.elapsed();

    println!("Time elapsed in implementation of {} was: {:?}", func_name, duration);

    result
}
