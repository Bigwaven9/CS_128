extern crate hw2;

fn main() {

    println!("School Colors! {:#?} and {:#?}", hw2::color_string_to_enum(Some(String::from("blue"))).unwrap(), hw2::color_string_to_enum(Some(String::from("orange"))).unwrap());
    println!("Fibbonaci numbers not exceeding: {:?}", hw2::fibonacci_odd_sum(1111111111));
}
