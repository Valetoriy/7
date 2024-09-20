use rand::prelude::*;
use std::collections::HashMap;

fn gen_word(production_rules: &HashMap<char, &[&str]>, start: char) -> String {
    let Some(rule_variants) = production_rules.get(&start) else {
        return String::from(start);
    };
    let mut rng = thread_rng();
    let rule = rule_variants[rng.gen_range(0..rule_variants.len())];

    let mut res = String::new();
    for c in rule.chars() {
        res.push_str(&gen_word(&production_rules, c));
    }
    return res;
}

fn main() {
    let mut production_rules: HashMap<char, &[&str]> = HashMap::new();
    production_rules.insert('S', &["aSb", "cFc"]);
    production_rules.insert('F', &["cFc", ""]);
    let res = gen_word(&production_rules, 'S');
    println!("ЛР№1, 2 вариант. Случайное слово: {res}");
}
