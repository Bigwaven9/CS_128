/// This struct represents a student at UIUC
/// It stores their name and netid
/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug, Clone, PartialEq)]
pub struct Student {
    pub name: String,
    pub netid: String,
}

/// This struct represents a class at UIUC
/// It stores the name of the class and the list of students enrolled
/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug)]
pub struct Class {
    pub name: String,
    pub attendance: Vec<Student>,
}

/// This function initializes a student with the given name and netid
pub fn student_init(name: String, netid: String) -> Student {
    Student {
        name: name,
        netid: netid,
    }
}

/// This function initializes a class with the given name and an empty list of students
/// It should set the class name to the given String and the list of students to a new empty vector
pub fn class_init(name: String) -> Class {
    return Class {
        name: name,
        attendance: Vec::new(),
    };
}

/// This function returns information about the given student
/// It returns a tuple of the student's name and netid
pub fn student_info(student: &Student) -> (String, String) {
    (student.name.clone(), student.netid.clone())
}

/// This function returns information about the given class
/// It returns the name of the class and the number of students enrolled
pub fn class_info(class: &Class) -> (String, usize) {
    return (class.name.clone(), class.attendance.len());
}

/// This function enrolls the given student in the given class
/// It then returns the full attendance list for the class
pub fn class_enrollment(student: &Student, class: &mut Class) -> Vec<Student> {
    class.attendance.push(student.clone());
    return class.attendance.clone();
}

/// This function returns some vector of the given students 
/// and whether they are enrolled in the given class
/// If their are no students enrolled then return None
pub fn get_attendance(students: Vec<&Student>, class: &Class) -> Option<Vec<(Student, bool)>> {
    let mut x : Vec<(Student, bool)> = Vec::new();
    let mut y = false;
    for i in students.iter() {
        if class.attendance.contains(i) {
            x.push(((*i).clone(), true));
            y = true;
        } else {
            x.push(((*i).clone(), false));
        }
    }
    if y {
        return Some(x);
    }
    return None;
}