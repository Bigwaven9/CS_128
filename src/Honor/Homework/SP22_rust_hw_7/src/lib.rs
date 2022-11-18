/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug, Clone, PartialEq)]
pub struct Student {
    pub name: String,
    pub netid: String,
    pub schedule: Schedule,
}

/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug, Clone, PartialEq)]
pub struct Class {
    pub name: String,
    pub credit_hours: u8,
}

/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug, Clone, PartialEq)]
pub struct Schedule {
    pub classes: Vec<Class>,
    pub credit_hours: u8,
}

impl Student {
    // TODO: Implement this function
    /// Initialize a new student
    /// Set the students schedule with a new empty schedule
    pub fn new(name: String, netid: String) -> Student {
        Self {
            name : name,
            netid : netid,
            schedule : Schedule::new(Vec::new())
        }
    }

    // TODO: Implement this function
    /// Enroll a student in a schedule
    pub fn schedule_enrollment(&mut self, schedule: Schedule) {
        self.schedule = schedule;
    }

    // TODO: Implement this function
    /// Check if a student is a classmate of another student
    pub fn is_classmate(&self, other: &Student) -> bool {
        for i in self.schedule.classes.clone() {
            if other.schedule.classes.contains(&i) {
                return true;
            }
        }
        return false;
    }
}

impl Class {
    // TODO: Implement this function
    /// Initialize a new class
    pub fn new(name: String, credit_hours: u8) -> Class {
        Self {
            name : name,
            credit_hours : credit_hours
        }
    }
}

impl Schedule {
    // TODO: Implement this function
    /// Initialize a new schedule
    /// Credit hours should be total up from the classes
    pub fn new(classes: Vec<Class>) -> Schedule {
        let mut c = 0;
        for i in classes.clone() {
            c += i.credit_hours;
        }
        Self {
            classes : classes,
            credit_hours : c
        }
    }
}