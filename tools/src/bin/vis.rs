#![allow(non_snake_case)]

use tools::*;

fn main() {
    if std::env::args().len() != 5 {
        eprintln!(
            "Usage: {} <seed> <input> <output> <mode>",
            std::env::args().nth(0).unwrap()
        );
        return;
    }

    let seed = std::env::args().nth(1).unwrap();
    let in_file = std::env::args().nth(2).unwrap();
    let out_file = std::env::args().nth(3).unwrap();
    let mode = std::env::args().nth(4).unwrap().parse::<i32>().unwrap();
    assert!(mode == 0 || mode == 1);

    let input = std::fs::read_to_string(&in_file).unwrap_or_else(|_| {
        eprintln!("no such file: {}", in_file);
        std::process::exit(1)
    });
    let output = std::fs::read_to_string(&out_file).unwrap_or_else(|_| {
        eprintln!("no such file: {}", out_file);
        std::process::exit(1)
    });
    let input = parse_input(&input);
    let out = parse_output(&input, &output);
    let (score, err, svg) = match out {
        Ok(out) => vis(&input, &out, true, mode),
        Err(err) => (0, err, String::new()),
    };
    println!("Score = {}", score);
    if err.len() > 0 {
        println!("{}", err);
    }
    let vis = format!("<html><body>{}</body></html>", svg);
    std::fs::write(format!("./tools/images/{seed:0>4}.html"), &vis).unwrap();
}
