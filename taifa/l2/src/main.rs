use std::env::args;

fn check_input(input: &str) -> (char, bool) {
    let mut state = '0';
    for c in input.chars() {
        match c {
            '0' => match state {
                '0' => state = '1',
                '1' => state = '2',
                '2' => state = '2',
                '3' => state = '3',
                _ => (),
            },
            '1' => match state {
                '0' => state = '3',
                '1' => state = '3',
                '2' => state = '2',
                '3' => state = '3',
                _ => (),
            },
            _ => (),
        }
    }

    if state == '2' {
        (state, true)
    } else {
        (state, false)
    }
}

fn main() {
    let input = args().nth(1).expect("Не введено проверямое слово");
    let (state, success) = check_input(&input);

    println!("ЛР№2, 2 вариант. КА завершил работу в состоянии \"{state}\"");
    if success {
        println!("Слово соответствует языку");
    } else {
        println!("Слово не соответствует языку");
    }
}
