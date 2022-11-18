extern crate hw7;
use hw7::*;

fn main() {
    // Feel free to change these to test your code
    // Initialize a bunch of students
    let mut welby = Student::new("Welby".to_string(), "welby2".to_string());
    let mut eustis = Student::new("Eustis".to_string(), "weustis2".to_string());
    let mut neil = Student::new("Neil".to_string(), "neilk3".to_string());
    let mut arul = Student::new("Arul".to_string(), "arulhv2".to_string());
    let mut cooper = Student::new("Cooper".to_string(), "kcm3".to_string());

    // Initialize some classes
    let cs128h = Class::new("CS128H".to_string(), 1);
    let cs124h = Class::new("CS124H".to_string(), 1);
    let cs199 = Class::new("CS199".to_string(), 1);
    let cs173 = Class::new("CS173".to_string(), 3);
    let cs240 = Class::new("CS240".to_string(), 3);
    let phil223 = Class::new("PHIL223".to_string(), 3);

    // Initialize some schedules
    let schedule0 = Schedule::new(vec![cs128h.clone(), cs173.clone()]);
    let schedule1 = Schedule::new(vec![cs124h.clone(), cs199.clone()]);
    let schedule2 = Schedule::new(vec![cs173.clone(), phil223.clone()]);
    let schedule3 = Schedule::new(vec![cs128h.clone(), cs173.clone()]);
    let schedule4 = Schedule::new(vec![cs240.clone(), phil223.clone()]);

    // Enroll some students
    neil.schedule_enrollment(schedule0.clone());
    eustis.schedule_enrollment(schedule1.clone());
    arul.schedule_enrollment(schedule2.clone());
    cooper.schedule_enrollment(schedule3.clone());
    welby.schedule_enrollment(schedule4.clone());

    // Print attendance
    let students = vec![eustis, arul, cooper, welby];
    for student in students {
        println!("{} schedule -> {:?}\n", student.name, student.schedule);
        println!("{} is {} with Neil\n", student.name, if neil.is_classmate(&student) { "classmate" } else { "not a classmate" });
    }
}
