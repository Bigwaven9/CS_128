extern crate dummy_project;
use dummy_project::*;

fn main() {
    let students = vec![
        Student::new("Eustis".to_string()),
        Student::new("Neil".to_string()),
        Student::new("Welby".to_string()),
        Student::new("Cooper".to_string()),
        Student::new("Arul".to_string()),
    ];

    let handles = study_progress(students);
}
