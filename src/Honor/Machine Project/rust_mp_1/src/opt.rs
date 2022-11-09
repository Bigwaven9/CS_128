use structopt::StructOpt;

#[derive(Debug, StructOpt)]
#[structopt(name="Hangman", about="Hangman Game for CS 196-28 MP2.", author="CS 196-28")]
/// Handles command line arguments for a Hangman game.
pub struct HangmanOpt {
    /// The word for the hangman game.
    #[structopt(short, long)]
    pub word: Option<String>,
    /// Displays the game status after every guess when verbose is True.
    /// Displays the game status only after the !status command is used when False.
    #[structopt(short, long)]
    pub verbose: bool,
}