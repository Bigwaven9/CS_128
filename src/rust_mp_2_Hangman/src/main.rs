pub mod runner;
pub mod opt;
pub mod hangman;
use structopt::StructOpt;

/// main function for the hangman program
/// reads command line input and starts the game.
fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Welcome to Hangman!\nInstructions: enter a command (e.g., !new, !guess, !exit, !status), \
                    or use !help for usage instructions.\n");
    // read command line args
    let cmd = opt::HangmanOpt::from_args();
    // start the hangman runner
    let mut hangman_runner = runner::HangmanRunner::new(cmd.word, cmd.verbose);
    // run the game
    hangman_runner.run()?;
    Ok(())
}