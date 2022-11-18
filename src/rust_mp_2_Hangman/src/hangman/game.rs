use crate::hangman::error::{HangmanError, HangmanErrorKind};

/// DO NOT CHANGE THIS, you may use this as you see fit
/// The number of guesses allowed before the game ends.
pub const NUM_GUESSES_TOTAL : usize = 6;

/// Struct to handle a Hangman game and store all necessary game state.
/// Feel free to design this struct however you like, as long as you don't
/// modify any of the function signatures in the impl block.
/// TODO: design the Hangman struct.
#[derive(Debug, Default)]
pub struct Hangman {
    s:String,
    chances:usize,
    guessed:std::collections::HashSet<char>,
    correct:std::collections::HashSet<char>,
    incorrect:std::collections::HashSet<char>
}

/// Hangman impl block.
/// Your task is to finish all the functions in this block. You may add any
/// helper functions as you need. After you have finished all the functionality
/// below, feel free to run the program and play with the command line interface which should be 
/// fully functional assuming that your code passes all tests. See the README for instructions.
/// Note: Make sure not to change the function signatures below!!!
/// TODO: finish all the functions in the impl block.
impl Hangman {
    /// Instantiates a new Hangman game object for the given word.
    /// Returns an Ok(Hangman) if the word was valid.
    /// Returns an Err(HangmanError) if the word was an empty string or contained non-alpha chars.
    pub fn new(word: String) -> Result<Self, HangmanError> {
        if word.len() == 0 {
            return Err(HangmanError {
                error_type : HangmanErrorKind::InvalidWord,
                error_msg : "Invalid Character".to_string(),
                user_input : word.to_string()
            });
        }
        for i in word.to_lowercase().to_string().chars() {
            if !i.is_alphabetic() {
                return Err(HangmanError {
                    error_type : HangmanErrorKind::InvalidWord,
                    error_msg : "Invalid Character".to_string(),
                    user_input : word.to_string()
                });
            }
        }
        return Ok(Self {
            s : word.to_lowercase().to_string(),
            chances : 0,
            guessed : std::collections::HashSet::new(),
            correct : std::collections::HashSet::new(),
            incorrect : std::collections::HashSet::new()
        });
    }

    /// Guesses a character in the hangman game and updates the game state
    /// Note: the guess is case INSENSITIVE (e.g., if the word is "abc," both 'A' and 'a' are correct guesses).
    /// Returns Ok(true) if the guess was valid and correct
    /// Returns Ok(false) if the guess was valid, but incorrect
    /// Returns a GameAlreadyOver error if the game was already finished before the guess
    /// Returns an InvalidCharacter error if the character is not alphabetic
    /// Returns an AlreadyGuessedCharacter error if the character was already guessed 
    /// (either correctly or incorrectly) in the game.
    pub fn guess(&mut self, mut c: char) -> Result<bool, HangmanError> {
        c = c.to_ascii_lowercase();
        if self.get_game_result().is_some() {
            return Err(HangmanError {
                error_type : HangmanErrorKind::GameAlreadyOver,
                error_msg : "Chance out".to_string(),
                user_input : c.to_string()
            });
        }
        if !c.is_alphabetic() {
            return Err(HangmanError {
                error_type : HangmanErrorKind::InvalidCharacter,
                error_msg : "Invalid Character".to_string(),
                user_input : "".to_string()
            });
        }
        if self.guessed.contains(&c) {
            return Err(HangmanError {
                error_type : HangmanErrorKind::AlreadyGuessedCharacter,
                error_msg : "Guessed Already".to_string(),
                user_input : "".to_string()
            });
        }
        
        self.guessed.insert(c);
        if self.s.contains(c) {
            self.correct.insert(c);
            return Ok(true);
        } else {
            self.incorrect.insert(c);
            self.chances += 1;
            return Ok(false);
        }
    }

    /// Returns a reference to the game word converted to lowercase.
    pub fn get_word(&self) -> &String {
        return &self.s;
    }

    /// Returns the number of guesses left before the guesser loses.
    pub fn get_num_guesses_left(&self) -> usize {
        return NUM_GUESSES_TOTAL - self.chances;
    }

    /// Returns a reference to a HashSet of all correct guessed characters.
    pub fn get_correct_guesses(&self) -> &std::collections::HashSet<char> {
        return &self.correct;
    }

    /// Returns a reference to a HashSet of all incorrectly guessed characters.
    pub fn get_incorrect_guesses(&self) -> &std::collections::HashSet<char> {
        return &self.incorrect;
    }

    /// Returns the result of the game.
    /// Returns Some(true) if the user guessed all the characters in the word without exceeding
    /// the allowed number of guesses.
    /// Returns Some(false) if the user made too many incorrect guesses.
    /// Otherwise, the game is in progress, so return None.
    pub fn get_game_result(&self) -> Option<bool> {
        let mut t = true;
        for i in self.s.chars() {
            if !self.correct.contains(&i) {
                t = false;
                break;
            }
        }
        if t {
            return Option::Some(true);
        }
        if self.chances >= NUM_GUESSES_TOTAL  {
            return Option::Some(false);
        }
        return Option::None;
    }
}
