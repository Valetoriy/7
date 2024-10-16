use regex::Regex;

fn main() {
    let content = std::fs::read_to_string("sut_phones.html").unwrap();
    Regex::new(r"(\+7|8)?\s?\(?\d{3}\)?\s\d{3}[-\s]\d{2}[-\s]\d{2}")
        .unwrap()
        .find_iter(&content)
        .for_each(|m| println!("{}", m.as_str().trim()));
}
