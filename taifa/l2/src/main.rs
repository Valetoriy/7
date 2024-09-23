use std::env::args;

#[derive(Debug)]
enum State {
    Zero,
    One,
    Two,
    Three,
}

/*
 * /--\
 * V  |(0, 1)
 * 2 -/
 * ^           /--\
 * |(0)        V  |(0, 1)
 * 1 --------> 3 -/
 * ^  (1)      ^
 * |(0)        |
 * 0 ----------/
 * ^  (1)
 * |(start)
*/
fn check_input(input: &str) -> (State, bool) {
    let mut state = State::Zero;
    for c in input.chars() {
        use State::*;
        match c {
            '0' => match state {
                Zero => state = One,
                One => state = Two,
                Two => state = Two,
                Three => state = Three,
            },
            '1' => match state {
                Zero => state = Three,
                One => state = Three,
                Two => state = Two,
                Three => state = Three,
            },
            _ => (),
        }
    }

    if let State::Two = state {
        (state, true)
    } else {
        (state, false)
    }
}

fn main() {
    let input = args().nth(1).expect("Не введено проверямое слово");
    let (state, success) = check_input(&input);

    println!("ЛР№2, 2 вариант. КА завершил работу в состоянии \"{state:?}\"");
    if success {
        println!("Слово соответствует языку");
    } else {
        println!("Слово не соответствует языку");
    }
}
