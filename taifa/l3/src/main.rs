use clap::Parser;

#[derive(Parser)]
struct CliArgs {
    coins: Vec<u8>,
}

fn main() {
    println!("ЛР№3, 2 вариант.");
    let args = CliArgs::parse();

    let mut state = 0;
    let coin_vals = [1, 2, 5];
    for c in args.coins {
        if !coin_vals.contains(&c) {
            println!("Неверная монета ({c}). Попробуйте снова.");
            continue;
        }

        // Переход в другое состояние
        match c {
            1 => match state {
                0 => state = 1,
                1 => state = 2,
                2 => state = 3,
                3 => state = 4,
                4 => state = 5,
                _ => (),
            },
            2 => match state {
                0 => state = 2,
                1 => state = 3,
                2 => state = 4,
                3 => state = 5,
                4 => state = 6,
                _ => (),
            },
            5 => match state {
                0 => state = 5,
                1 => state = 6,
                2 => state = 7,
                3 => state = 8,
                4 => state = 9,
                _ => (),
            },
            _ => (),
        }

        // Действия
        match state {
            0..5 => println!("Получено {state}р. Ничего не происходит."),
            5 => {
                println!("Выдаётся товар без сдачи.");
                state = 0;
            }
            6..10 => {
                println!("Выдаётся товар со сдачей {}р.", state - 5);
                state = 0;
            }
            _ => (),
        }
    }
}
