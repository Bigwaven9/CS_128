extern crate csv;
extern crate dummy_project;

use csv::Reader;
use std::vec::Vec;

use crate::dummy_project::*;

fn main() {
    let dataset: Dataset = init();
    let random_cereal: Vec<f64> = vec![110.0f64, 1.0f64, 0.0f64, 14.0f64];

    let prediction = dataset.predict(&random_cereal); // SHOULD BE K (aka KELLOGGS)

    println!("A cereal with {} calories, {} grams of protein, {} grams of fat, and {} grams of carbs per serving is most likely manufactured by {}.", 
            random_cereal[0], random_cereal[1], random_cereal[2], random_cereal[3],
            match_manufacturer(&prediction));
}

fn match_manufacturer(initial: &String) -> &str {
    match initial.as_str() {
        "A" => "American Hoem Food Products",
        "G" => "General Mills",
        "K" => "Kelloggs",
        "N" => "Nabisco",
        "P" => "Post",
        "Q" => "Quaker Oats",
        "R" => "Ralston Purina",
        _ => "Unknown manufacturer",
    }
}

fn init() -> Dataset {
    let mut matrix: Vec<Vec<f64>> = Vec::new();
    let mut labels: Vec<String> = Vec::new();

    let mut rdr = Reader::from_path("data/cereal.csv").unwrap();
    for result in rdr.records() {
        let record = result.unwrap();
        let data = vec![
            record[3].parse::<f64>().unwrap(), // get calories quantity
            record[4].parse::<f64>().unwrap(), // get protein quantity
            record[5].parse::<f64>().unwrap(), // get fat quantity
            record[8].parse::<f64>().unwrap(), // get carbs quantity
        ];
        matrix.push(data);
        labels.push(record[1].to_string()); // get associated manufacterer
    }

    let means = dummy_project::mean(&matrix);
    let stds = dummy_project::std(&matrix, &means);
    dummy_project::normalize(&mut matrix, &means, &stds);

    dummy_project::Dataset { matrix, labels }
}
