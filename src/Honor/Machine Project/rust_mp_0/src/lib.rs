use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;
use std::io::{self, BufRead};
use std::path::Path;

#[derive(Debug, Copy, Clone)]
pub enum Operation {
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo
}

impl Operation {
    // [COMPLETE THIS FUNCTION]
    pub fn from_char(symbol: char) -> Option<Operation> {
        match symbol {
            '+' => Option::Some(Operation::Add),
            '-' => Option::Some(Operation::Subtract),
            '/' => Option::Some(Operation::Divide),
            '%' => Option::Some(Operation::Modulo),
            '*' | 'x' => Option::Some(Operation::Multiply),
            _ => Option::None,
        }
    }
}

// [HELPER FUNCTION - DO NOT EDIT]
pub fn get_equation_tuple(line: &String) -> (Option<&str>, Option<&str>) {
    let v: Vec<&str> = line.split(&['-', '+', 'x', '*', '/', '%'][..]).collect();
    
    (v.get(0).cloned(), v.get(1).cloned())
}

// [COMPLETE THIS HELPER FUNCTION]
pub fn parse_equation(line: &String) -> Result<(f32, f32, Operation), ()> {
    if let (Some(x), Some(y)) =  get_equation_tuple(&line) {
        if let (Ok(x), Ok(y)) = (x.trim().parse::<f32>(), y.trim().parse::<f32>()) {
            for op in line.chars() {
                if let Some(op) = Operation::from_char(op) {
                    match op {
                        Operation::Add => return Ok((x, y, op)),
                        Operation::Subtract => return Ok((x, y, op)),
                        Operation::Divide => return Ok((x, y, op)),
                        Operation::Modulo => return Ok((x, y, op)),
                        Operation::Multiply => return Ok((x, y, op)),
                    }
                }
            }
        }
    }
    return Err(());
}

// [COMPLETE THIS FUNCTION]
pub fn solve(equation: &String) -> Result<f32, ()> {
    let tup = parse_equation(equation);

    if let Ok(t) = tup {
        let (a, b, op) = t;
        match op {
            Operation::Add => return Ok(a + b),
            Operation::Subtract => return Ok(a - b),
            Operation::Multiply => return Ok(a * b),
            Operation::Divide => return Ok(a / b),
            Operation::Modulo => return Ok(a % b),
        }
    }
    return Err(());    
}


fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

// [COMPLETE THIS FUNCTION]
pub fn solve_all(file_path: &str) -> Result<f32, ()> {
    let mut sum:f32 = 0.0;
    if let Ok(lines) = read_lines(file_path) {
        for line in lines {
            if let Ok(mut ip) = line {
                if let Ok(x) = solve(&mut ip) {
                    sum += x;
                }
            }
        }
        return Ok(sum);
    }
    return Err(());
}