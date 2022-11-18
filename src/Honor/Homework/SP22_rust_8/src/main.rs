extern crate hw8;
use hw8::*;

fn main() {
    // Feel free to change these to test your code
    let mut linked_list: LinkedList<String> = LinkedList::new();
    linked_list.add_front("fast".to_string());
    linked_list.add_front("is".to_string());
    linked_list.add_front("Rust".to_string());
    linked_list.add_back("C++".to_string());
    linked_list.add_back("is".to_string());
    linked_list.add_back("slow".to_string());
    println!("linked_list generated -> {:?}", linked_list.to_vec());

    let mut linked_list: LinkedList<i32> = LinkedList::new();
    linked_list.add_back(4);
    linked_list.add_back(5);
    linked_list.add_back(6);
    linked_list.add_front(3);
    linked_list.add_front(2);
    linked_list.add_front(1);
    println!("linked_list generated -> {:?}", linked_list.to_vec());
}
