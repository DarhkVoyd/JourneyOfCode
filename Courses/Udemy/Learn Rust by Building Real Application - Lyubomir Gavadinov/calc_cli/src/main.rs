use std::io;

fn main() {
    println!("Enter you weight on Earth: ");
    let mut weight = String::new();
    io::stdin().read_line(&mut weight).unwrap();
    let weight: f32 = weight.trim().parse().unwrap();
    println!("{}", weight_on_mars(&weight));
}

fn weight_on_mars(weight: &f32) -> f32 {
    (weight / 9.81) * 3.711
}
