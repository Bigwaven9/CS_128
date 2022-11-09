extern crate hw10;
use hw10::*;

fn main()
{
    // Feel free to change this to test your code
    let val = (0..500000).collect::<Vec<i32>>();
    let num_chunks = 200;
    println!("{:?}", runner(num_chunks, val));
}