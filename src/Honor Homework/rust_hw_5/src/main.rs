extern crate hw5;

fn main() {
    // Feel free to change these to test your formulas
    let cards: &mut Vec<String> = &mut vec!["A".to_string(), "A".to_string(), "A".to_string(), "A".to_string(), 
    "B".to_string(), "B".to_string(), "B".to_string(), "B".to_string(),
    "C".to_string(), "C".to_string(), "C".to_string(), "C".to_string(),
    "D".to_string(), "D".to_string(), "D".to_string(), "D".to_string()];
    let runner_cards: &mut Vec<String> = &mut cards.clone();
    println!("Regular Deck -> {:?}", cards);
    println!("Perfect Bridge -> {:?}", hw5::perfect_bridge(cards));
    println!("Runner -> {:?}", hw5::runner(runner_cards));
}
