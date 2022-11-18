extern crate hw6;
use hw6::*;

fn main() {
    // Feel free to change these to test your code
    // Initialize a bunch of students
    let welby: Student = student_init("Welby".to_string(), "welby2".to_string());
    let eustis: Student = student_init("Eustis".to_string(), "weustis2".to_string());
    let neil: Student = student_init("Neil".to_string(), "neilk3".to_string());
    let arul: Student = student_init("Arul".to_string(), "arulhv2".to_string());
    let cooper: Student = student_init("Cooper".to_string(), "kcm3".to_string());

    // Initialize a super cool class
    let mut cs128h: Class = class_init("CS128H".to_string());
    // Enroll some students
    class_enrollment(&welby, &mut cs128h);
    class_enrollment(&eustis, &mut cs128h);
    class_enrollment(&neil, &mut cs128h);
    let students: Vec<&Student> = vec![&welby, &eustis, &neil, &arul, &cooper];
    // Print attendance
    println!("Class attendance -> {:?}", get_attendance((*students).to_vec(), &cs128h));
}
