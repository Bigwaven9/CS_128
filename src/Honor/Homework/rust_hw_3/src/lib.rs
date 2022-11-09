/// TODO: Implement this function that passes a parameter by value
/// Multiply the input by 6, add 8 if the number is even and 9 if it is odd,
/// divide by 4, subtract 4, then subtract 1 if the number is odd, and multiply by 9
/// return the result
pub fn math_formula_one(mut target: i32) -> i32 {
    target *= 6;
    if target % 2 == 0 {
        target += 8
    } else {
        target += 9;
    }
    target /= 4;
    target -= 4;
    if target % 2 == 1 {
        target -=1;
    }
    target *= 9;
    return target;
}

/// TODO: Implement this function that passes a parameter by reference
/// Divide by 2, multiply by 3, add 5, subtract 8, divide by 10
/// Subtract 10 from the input until the input is less than 200
/// Multiply the input by 15   
pub fn math_formula_two(target: &mut i32) {
    *target /= 2;
    *target *= 3;
    *target += -3;
    *target /= 10;
    while *target >= 200 {
        *target -= 10;
    }
    *target *= 15;
}

/// TODO: Create a function called "runner" with no input that returns an i32. 
/// Create a variable holding the year
/// Call math_formula_one and pass the variable as a parameter
/// Is the value of the variable holding the year still the same?
/// Call math_formula_two and pass the variable as a parameter
/// Is the value of the variable holding the year still the same now? Did anything change? Why?
/// Return the value returned by the function minus the variable holding the year
  
pub fn runner() -> i32 {
    let mut year = 2022;
    let ret = math_formula_one(year);
    math_formula_two(&mut year);
    return ret - year;
}


// You can test your code with the test cases we've provided by running `cargo test`
// We also encourage you to add more assert statements to test out your code further!
#[cfg(test)]
mod test {
    use super::*;
    
    #[test]
    fn test_math_formula_one() {
        assert_eq!(math_formula_one(10), 108);
        assert_eq!(math_formula_one(2022), 27270);
    }

    #[test]
    fn test_math_formula_two() {
        let a: &mut i32 = &mut 10;
        math_formula_two(a);
        assert_eq!(*a, 15);
    }

    #[test]
    fn test_runner() {
        // [Your test here...]
    }

}
