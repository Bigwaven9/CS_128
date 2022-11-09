extern crate dummy_project;
mod runner;

use crate::dummy_project::{mappers::*, reduce::*, map::*};
use std::collections::HashMap;

fn main() {
    //
    //
    //
    // If you would like to run this code, you will need to unzip the .txt file 
    // in /rust_mp_2/data/ and save it in `/rust_mp_2/data/cleaned.txt`.
    //
    //                   !!! WARNING: this file is 83mb !!! 
    //
    // This file contains text from all 7 Harry Potter books. The code below 
    // will use your code to count the number of words by word length and graph 
    // a histogram of the distribution of words by word length.
    // 
    // You do not need to unzip this file. You may complete the MP without it. 
    // It is here only if you want to see your code in action :)
    // 
    //
    //

    let results: HashMap<usize, usize> = runner::run("data/cleaned.txt");
    println!("---------------------------------------------------------------");
    runner::graph_results(results.clone());
}
