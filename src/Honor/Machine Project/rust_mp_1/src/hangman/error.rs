/// Error message for an invalid character
const INVALID_CHARACTER : &str = "Invalid character guessed. \
    Only letters are allowed. Guess another character with !guess.";

/// Error message for an invalid word
const INVALID_WORD : &str = "Invalid word entered. Words can only consist of \
    letters. Choose a new word with !new.";

/// Error message for when the user guesses a character that was already guessed
const ALREADY_GUESSED : &str = "Character already guessed. \
    Guess another character with !guess.";

/// Error message for an unrecognized command
const COMMAND_NOT_RECOGNIZED : &str = "Command Not Recognized.";

/// Error message for when a game is not in progress.
const GAME_NOT_STARTED : &str = "No game in progress. Start a new game with !new.";

/// Error message for when a game is not in progress.
const ARG_ERROR : &str = "Error in the number of arguments provided.";

/// Error message for when a game is not in progress.
const GAME_ALREADY_OVER : &str = "Game already over. Start a new game with !new.";

/// Custom struct for error handling.
#[derive(Debug)]
pub struct HangmanError {
    pub error_type : HangmanErrorKind,
    pub error_msg : String,
    pub user_input: String
}

/// Enum to describe the different possible types of errors.
#[derive(Debug, PartialEq)]
pub enum HangmanErrorKind {
    InvalidWord,
    InvalidCharacter,
    AlreadyGuessedCharacter,
    CommandNotRecognized,
    ArgError,
    GameNotStarted,
    GameAlreadyOver
}

/// Display implementation for HangmanErrorKind for user output in the CLI.
impl std::fmt::Display for HangmanErrorKind {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "HangmanError::{:?}", self)
    } 
}

/// HangmanError impl block
impl HangmanError {
    /// Instantiates a new HangmanError object with the given error_type attached
    /// to the given user_input.
    pub fn new(error_type: HangmanErrorKind, user_input: String) -> HangmanError {
        let error_msg = match error_type {
            HangmanErrorKind::InvalidCharacter => INVALID_CHARACTER.to_string(),
            HangmanErrorKind::InvalidWord => INVALID_WORD.to_string(),
            HangmanErrorKind::AlreadyGuessedCharacter => ALREADY_GUESSED.to_string(),
            HangmanErrorKind::CommandNotRecognized => COMMAND_NOT_RECOGNIZED.to_string(),
            HangmanErrorKind::GameNotStarted => GAME_NOT_STARTED.to_string(),
            HangmanErrorKind::GameAlreadyOver => GAME_ALREADY_OVER.to_string(),
            HangmanErrorKind::ArgError => ARG_ERROR.to_string()
        };
        HangmanError {
            error_type,
            error_msg,
            user_input
        }
    }
}

/// Display implementation for HangmanError for user output in the CLI.
impl std::fmt::Display for HangmanError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        writeln!(f, "{} --- (user_input : {})\n{}",
            self.error_type, self.user_input, self.error_msg)
    } 
}

/// Error impl for HangmanError.
impl std::error::Error for HangmanError {}
