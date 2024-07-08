/*
Monae White
This file contains void functions that displays the user's status
*/

#include "playbyplay.hpp"

int playByPlay::getAttemptsLeft(){
	return attempts_left;
}

void playByPlay::setAttemptsLeft(){
	return attempts_left --;
}

bool playByPlay::checkValidity(char letter){
    return isalpha(letter);
}

void playByPlay::guessLetter(char letter){
	bool found = false;

	guessed_letters.insert(letter);

	for(int i = 0; i < word.length(); ++i){
		if(word[i] == letter){
			hidden_word[i] = letter; // replaces placeholder with the correct character
			found = true; // the letter made an appearance at least once
		}
	}
	if(!found){ // the letter made zero appearances
		setAttemptsLeft(); 
	}
}

void playByPlay::displayStatus(){
	picturedisplay(attempts_left); // stick figure icon

	std::cout << "Word: ";
	for(char c : hidden_word){
		std::cout << c << ' ';
	}

	std::cout << "\nAttempts left: " << getAttemptsLeft() << "\nGuessed letters: ";
	for(char c : guessed_letters) {
		std::cout << c << ' ';
	}
	std::cout << std::endl;

}

bool playByPlay::checkWin(){
	return std::find(hidden_word.begin(), hidden_word.end(), '*') == hidden_word.end();
}

bool playByPlay::checkLoss(){
	return attempts_left == 0;
}

void playByPlay::play(){
	while(!checkLoss() && !checkWin()){
		displayStatus();
		char guess;
		std::cout << "Guess a letter: ";
		std::cin >> guess;

		if(guessed_letters.find(guess) != guessed_letters.end()){ // user is repeating guesses
            std::cout << "You already guessed that letter!" << std::endl;
			continue; // so the user will not cause the guessLetter function to execute on an already guessed character
        } 
		else if(checkValidity(guess)){
        	guessLetter(guess);			
		}
		else{
			std::cout << "Invalid guess. Ensure your guess consists of only alphabetical characters.";
		}
	}
	if(checkWin()){
            std::cout << "Congratulations! You've guessed the word: " << word << std::endl;
            std::cout << "Definition: " << definition << std::endl;
			std::cout << "Did you learn something new?" << std::endl;
        } 
	if(checkLoss()){
        std::cout << "Sorry, you've been hanged! The word was: " << word << std::endl;
    }
}