extern crate hw4;

fn main() {
    // Feel free to change these to test your formulas
    let mut words: Vec<String> = vec!["fish".to_string(), "cat".to_string(), "ardvaark".to_string(), "dog".to_string(), "bird".to_string(), "ant".to_string()];
    let tuple = hw4::vector_iter(&mut words);
    println!("This prints the modified vector: {:?}", words);
    println!("Returned tuple: {:?}", tuple);
}
