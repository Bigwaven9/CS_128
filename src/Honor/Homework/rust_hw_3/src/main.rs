extern crate hw3;

fn main() {
    // Feel free to change these to test your formulas
    let num: i32 = 888;
    println!("Formula 1: {}", hw3::math_formula_one(num));

    let mun: &mut i32 = &mut 333;
    hw3::math_formula_two(mun);
    println!("Formula 2: {:?}", mun);
    
    // You will need to write this function first
    // println!("Runner: {}", hw3::runner());
}
