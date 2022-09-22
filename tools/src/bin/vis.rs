#![allow(non_snake_case)]

use tools::*;

fn main() {
    if std::env::args().len() != 2 {
        eprintln!(
            "Usage: {} <input> <output>",
            std::env::args().nth(0).unwrap()
        );
        return;
    }
    let seed = std::env::args().nth(1).unwrap();
    let in_file = format!("./input/{seed:0>4}.txt");
    let out_file = format!("./output/{seed:0>4}.txt");
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
        Ok(out) => vis(&input, &out, true),
        Err(err) => (0, err, String::new()),
    };
    println!("Score = {}", score);
    if err.len() > 0 {
        println!("{}", err);
    }
    let vis = format!("<html><body>{}</body></html>", svg);
    std::fs::write(format!("./tools/images/{seed:0>4}.html"), &vis).unwrap();
}
