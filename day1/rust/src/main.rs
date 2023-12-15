use std::collections::HashMap;
use std::fs::{metadata, File};
use std::io::{self, BufRead};

fn part1(line: &String) -> i64 {
    let mut first: char = ' ';
    let mut last: char = ' ';
    for ch in line.chars() {
        if ch.is_digit(10) {
            first = ch;
            break;
        }
    }

    for ch in line.chars().rev() {
        if ch.is_digit(10) {
            last = ch;
            break;
        }
    }

    let digits: String = format!("{}{}", first, last);

    match digits.parse::<i64>() {
        Ok(parsed_value) => {
            return parsed_value;
        }
        Err(err) => {
            eprintln!("Error parsing the string: {}", err);
            return -1;
        }
    }
}

fn part2(line: &String) -> i64 {
    let mut lookup_table: HashMap<String, char> = HashMap::new();
    lookup_table.insert("one".to_string(), '1');
    lookup_table.insert("two".to_string(), '2');
    lookup_table.insert("three".to_string(), '3');
    lookup_table.insert("four".to_string(), '4');
    lookup_table.insert("five".to_string(), '5');
    lookup_table.insert("six".to_string(), '6');
    lookup_table.insert("seven".to_string(), '7');
    lookup_table.insert("eight".to_string(), '8');
    lookup_table.insert("nine".to_string(), '9');

    let mut first: char = ' ';
    let mut last: char = ' ';
    let mut first_index: usize = line.len();
    let mut last_index: usize = 0;

    // first digit
    for (index, ch) in line.char_indices() {
        if ch.is_digit(10) {
            first = ch;
            first_index = index;
            break;
        }
    }

    // first word
    for (key, value) in lookup_table.iter() {
        let index = line.find(key);
        match index {
            Some(index) => {
                if index < first_index {
                    first_index = index;
                    first = *value;
                }
            }
            None => {
                continue;
            }
        }
    }

    // last digit
    for (index, ch) in line.char_indices().rev() {
        if ch.is_digit(10) {
            last = ch;
            last_index = index;
            break;
        }
    }

    // last word
    for (key, value) in lookup_table.iter() {
        let index = line.rfind(key);
        match index {
            Some(index) => {
                if index > last_index {
                    last_index = index;
                    last = *value;
                }
            }
            None => {
                continue;
            }
        }
    }

    let digits: String = format!("{}{}", first, last);

    match digits.parse::<i64>() {
        Ok(parsed_value) => {
            return parsed_value;
        }
        Err(err) => {
            eprintln!("Error parsing the string: {}", err);
            return -1;
        }
    }
}

fn main() -> io::Result<()> {
    let f_name = "./../input";

    let file = File::open(f_name)?;
    if metadata(f_name).is_ok() {
        let reader = io::BufReader::new(file);
        let mut result1: i64 = 0;
        let mut result2: i64 = 0;

        for line in reader.lines() {
            match line {
                Ok(line_content) => {
                    result1 += part1(&line_content);
                    result2 += part2(&line_content);
                }
                Err(err) => {
                    eprintln!("Error reading line: {}", err);
                }
            }
        }
        println!("Solution part1: {}", result1);
        println!("Solution part2: {}", result2);
    } else {
        println!("File does not exist.\n");
    }
    Ok(())
}
