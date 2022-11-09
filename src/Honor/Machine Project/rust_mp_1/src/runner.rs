use dialoguer::Input;
use crate::hangman::game::{Hangman, NUM_GUESSES_TOTAL};
use crate::hangman::error::{HangmanError, HangmanErrorKind};

/// Hangman ASCII drawings to display in the command line.
const HANGMAN_DRAWINGS : [&str; NUM_GUESSES_TOTAL + 1] = [
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n", 
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n"
];

/// Runs a hangman game on the command line.
#[derive(Debug, Default)]
pub struct HangmanRunner {
    game: Option<Hangman>,
    verbose: bool
}

/// Implementation block for HangmanRunner
impl HangmanRunner {
    /// Constructs a new HangmanRunner with a Hangman game from the given word.
    pub fn new(word: Option<String>, verbose: bool) -> HangmanRunner {
        let mut output = HangmanRunner { game: None, verbose };
        match word {
            Some(w) => output.handle_new(w),
            _ => {}
        };
        output
    }

    /// Handles I/O for guessing a character. (!guess)
    fn handle_guess(&mut self, c: char) {
        match &mut self.game {
            Some(g) => {
                match g.guess(c) {
                    Ok(true) => println!("[{}] was a correct guess!\n", c),
                    Ok(false) => println!("[{}] was an incorrect guess.\n", c),
                    Err(e) => println!("{}", e)
                }
            },
            _ => {
                println!("{}", HangmanError::new(HangmanErrorKind::GameNotStarted, c.to_string()))
            }

        };
    }

    /// Handles I/O for starting a new game with a new word. (!new)
    fn handle_new(&mut self, word: String) {
        let count = word.len();
        self.game = match Hangman::new(word) {
            Ok(h) => {
                println!("Starting game with new word: {}\n", 
                    (0..count).map(|_| "_").collect::<String>());
                Some(h)
            },
            Err(e) => {
                println!("{}", e);
                None
            }
        };
    }

    /// Displays the game status including the word status, incorrect guesses,
    /// correct guesses, number of guesses remaining, and a drawing of the hangman. (!status)
    fn display_status(&self) {
        match &self.game {
            Some(g) => {
                let mut status : String = String::new();
                for c in g.get_word().chars() {
                    if g.get_correct_guesses().contains(&c) {
                        status.push(c)
                    } else {
                        status.push('_');
                    }
                }
                println!("Word Status: {}", status);
                println!("Incorrect Guesses: {:?}", g.get_incorrect_guesses());
                println!("Correct Guesses: {:?}", g.get_correct_guesses());
                println!("You have [{}] guesses left. Guess a letter with !guess.\n", 
                    g.get_num_guesses_left());
                println!("{}", HANGMAN_DRAWINGS[g.get_num_guesses_left()]);
            },
            _ => {}
        }
    }

    /// Outputs the help screen (!help)
    fn display_help(&self) {
        println!("!new [word]: starts a new game with the given word.\n!guess [char]: \
            guesses the character in the current game.\n!status: \
            outputs the current game status.\n!help: displays this help message.\n!exit: exits the game.\n")
    }

    /// Runs a game of hangman on the command line
    pub fn run(&mut self) -> Result<(), Box<dyn std::error::Error>> {
        // display the status once at the very start.
        if self.verbose {
            self.display_status();
        }
        loop {
            // Get input from the user
            let input : String = Input::new()
                .with_prompt(">")
                .interact_text()?;

            // Split the command line input by spaces
            let args : Vec<&str> = input.trim().split(' ').collect();

            // If there are 0 arguments, return an error
            if args.len() == 0 {
                println!("{}", HangmanError::new(HangmanErrorKind::ArgError, format!{"{:?}", args}));
                continue;
            }
            // match the first word in the command line input (the command)
            match args[0] {
                "!guess" => {
                    if args.len() == 2 {
                        match args[1].chars().next() {
                            Some(x) if x.is_ascii_alphabetic() && args[1].len() == 1 => self.handle_guess(x.to_ascii_lowercase()),
                            _  => println!("{}", HangmanError::new(HangmanErrorKind::InvalidCharacter, format!("{:?}", args)))
                        };
                    } else {
                        println!("{}", HangmanError::new(HangmanErrorKind::ArgError, format!("{:?}", args)));
                    }
                },
                "!status" => {
                    self.display_status();
                    continue;
                },
                "!exit" => {
                    return Ok(());
                },
                "!help" => {
                    self.display_help();
                    continue;
                },
                "!new" => {
                    if args.len() == 2 {
                        self.handle_new(args[1].to_string());
                        
                    } else {
                        println!("{}", HangmanError::new(HangmanErrorKind::ArgError, format!("{:?}", args)));
                    }
                }
                _ => {
                    println!("{}", HangmanError::new(HangmanErrorKind::CommandNotRecognized, format!("{:?}", args)));
                    continue;
                }
            };
            match &self.game {
                Some(g) => {
                    match g.get_game_result() {
                        Some(true) => {
                            println!("Game Over. The guesser wins.\n");
                        },
                        Some(false) => {
                            println!("Game Over. The guesser loses.\n");
                        }
                        _ => {
                            if self.verbose {
                                self.display_status();
                            }
                        }
                    }
                },
                _ => {}
            };
        }
    }
}