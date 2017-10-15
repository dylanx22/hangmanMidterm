
#include < string >
#include < iostream >
#include < cstdio >
#include < cctype >
#include < fstream >
#include < iomanip >
#include "Source.h"


int displayMenu()
{
	int	choice	= 0;

	std::cout << "|_____________________________________________________________________|" << std::endl;
	std::cout << "| 1. Instructions |\n" << std::endl;
	std::cout << "| 2. Choose Random Word From Category (Single Player Mode) |\n" << std::endl;
	std::cout << "| 3. Enter Custom Word (Multiplayer Mode) |\n" << std::endl;
	std::cout << "| 4. Play Hangman! |\n" << std::endl;
	std::cout << "| 5. View Past Scores | \n" << std::endl;
	std::cout << "|_____________________________________________________________________|" << std::endl;
	std::cout << "\nEnter your choice here: \n" << std::endl;
	std::cin >> choice;

	return choice;
}

int main()
{
	int option = 0;

	do
	{
		int	option = displayMenu();

		switch(option)
		{
		case GAMESTATE::INTRODUCTION:
			{
				// Shows instructions
				instructions();

				break;
			}

		case GAMESTATE::SELECT_WORD:
			{
				// Displays the word choice menu
				word = pickWord();

				break;
			}

		case GAMESTATE::CUSTOM_WORD:
			{
				// Uses user input to get the word
				std::cout << "Enter the secret word, no peeking player 2: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, word);
				wordPicked = true;

				break;
			}

		case GAMESTATE::PLAY_GAME:
			{
				// Play Hangman!
				if (wordPicked == true) // checks if a word has been picked before allowing user to enter game
				{
					hangMan(word);

					break;
				}
				else 
					std::cout << "Please enter a word before playing." << std::endl;

				break;
			}

		case GAMESTATE::STATS:
			{
				// Show recent game statistics
				if (statsLoaded = false) // load stats if they haven't been loaded yet.
				{
					loadStats();
					statsMain();
					break;
				}
					else
					statsMain();
					break;
			}

		default :
			{

				break;
			}
		}
	} while ( option != GAMESTATE::PLAY_GAME && option != GAMESTATE::EXIT );

	std::cout << "Game ended :(" << std::endl;
	return EXIT_SUCCESS;
}

void instructions()
{
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "\n\nWelcome to HANGMAN...";
	std::cout << "\n\nPick a word from the menu, then let a friend try to guess it!";
	std::cout << "\n\nOr you can enter your own custom word if you prefer.";
	std::cout << "\n\nEach letter is represented by a star.";
	std::cout << "\n\nSpaces will be represented by a star as well, but will be auto-guessed.";
	std::cout << "\n\nType in one letter each turn";
	std::cout << "\n\nThe word is CASE SENSITIVE!";
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
#ifdef _WIN32
	system("pause"); //pause console for 32bit
#endif
}

int hangMan(std::string word)
{
	std::string name;

	char	letter;

	int		wrongAmts		= 0;
	int		score			= 0;
	int		remainder		= ( MAX_TRIES - wrongAmts );
	int		wordLength		= word.length();

	// replace secret word with *****
	std::string unknown(word.length(), '*');
	// detect spaces in the word
	for (char& c : word) { 
    if ( std::isspace(c) ) {
        c = '*';
    }
}

	// game continues until out of tries
	while(wrongAmts < MAX_TRIES)
	{
		std::cout << "Your current score is: " << score;
		std::cout << "\n\n" << unknown;
		std::cout << "\n\nEnter a letter: ";
		std::cin >> letter;

		// replace * with letter if correct
		// increase score by 1
		// if incorrect add a wrong guess
		// and decrease score by 1
		if(matchLetter(letter, word, unknown) == 0)
		{
			std::cout << std::endl << "Nope! Try again." << std::endl;

			wrongAmts++;
			score--;
		}
		else
		{
			std::cout << "\nGood job! You found a letter." << std::endl;

			score++;
		}

		// display remaining guesses
		std::cout << MAX_TRIES - wrongAmts << " wrong guesses remaining." << std::endl;

		// Check if the user has guessed correctly
		// if so, calculate and display final score.
		// and the end game message.
		// save the game info.
		if(word == unknown)
		{
			std::cout << word << std::endl;
			std::cout << "Congratulations! You win." << std::endl;
			std::cout << "Your score was: " << calcScore(remainder, score) << std::endl;

			saveGame(word, calcScore(remainder, score)); // saves the game (word and score) using the saveGame function
													    // score is calculated by adding the remaining guesses to the score at the end of the game.

			break;

		}
	}

	if(wrongAmts == MAX_TRIES) // ends the game when out of guesses
	{
		std::cout << "\nGAME OVER" << std::endl;
		std::cout << "The word was : " << word << std::endl;
	}

	std::cin.ignore();
	std::cin.get();

	return 0;
}

int matchLetter(char guess, std::string secret, std::string & guessword) // Check if guessed letter is in the word.
{
	int	i;
	int	matches	= 0;
	int	length	= secret.length();

	for ( i = 0; i < length; i++ )
	{
		// Check to see if letter was previously guessed
		if(guess == guessword[i])
		{
			return 0;
		}

		// Check if the guess part of the correct word
		if(guess == secret[i])
		{
			guessword[i]	= guess;

			matches++;		// add a correct letter
		}
	}

	return matches;
}

void saveGame(std::string &pastWord, double score)	// saves the word and the score to a text file. (Up to 10 past games will be saved)
{
	std::ofstream stats;
	stats.open("stats.txt", std::ofstream::out | std::ofstream::app);

	stats << pastWord << std::endl;
	stats << score << std::endl;
	stats.close();
}

int calcScore(int r, int s)	// gets the remaining guesses and the score at end of the game and adds them to get final score
{
	return r + s;
}

std::string pickWord() // Pick a category, then the game chooses a random word from that category.
{
	int	category, wordNumber;
	int	r, c;

	for ( c = 0; c < 5; c++ )
	{
		std::cout << c + 1 << ". " << words[0][c] << std::endl;
	}

	std::cout << "Enter a category:";
	std::cin >> category;

	/*
	for ( r = 1; r < 6; r++ )
	{
		std::cout << r + 1 << ". " << words[r][category - 1] << std::endl; // code to choose words manually. decided to make pickWord a single player option, so the user doesn't know the word ahead of time.
	}
	*/
	std::cout << "Picking a random " << category << " for your hangman game!" << std::endl;
	wordPicked = true;
	return words[rand() % 6][category - 1];
}

int statsMenu()
{
	int	choice	= 0;

	std::cout << "|_____________________________________________________________________|" << std::endl;
	std::cout << "\n| 0. Exit this menu |\n" << std::endl;
	std::cout << "| 1. Sort by highest scores |\n" << std::endl;
	std::cout << "| 2. Sort by age of game (oldest first) |\n" << std::endl;
	std::cout << "|_____________________________________________________________________|" << std::endl;
	std::cout << "\nEnter your choice here: \n" << std::endl;
	std::cin >> choice;

	return choice;
}

void statsMain() 
{
	int	option	= 0;

	do
	{
		int	option	= statsMenu();

		switch(option)
		{
		case Safe::SORTING::SORT_BY_SCORE:
			{
				// Sort games by highest score (descending)
				sortStats(savedWords, scores, loadStats());
				break;
			}

		case Safe::SORTING::SORT_BY_AGE:
			{
				// Sort by the oldest saved game first
				displayStats();
				break;
			}

		case Safe::SORTING::EXIT:
			{
				break;
			}

		default :
			{
				break;
			}
		}
	} while ( option != Safe::SORTING::EXIT );
}

int loadStats()
{

	int count = 0;
	std::ifstream infile("stats.txt");

	if(!infile.is_open())
	{
		std::cout << "Error: could not open stats.txt" << std::endl;
	}

	while(infile >> savedWords[count])
	{
		infile >> scores[count];

		count++;
	}

	infile.close();

	bool statsLoaded = true;
	return count;
	

}

void displayStats()
{
	int count = loadStats();

	for ( int i = 0; i < count; i++ )
	{
		std::cout << "Word: " << std::setw(20) << std::left << savedWords[i] << "\t" << " Score: " << std::setw(5) << scores[i] << std::endl;
	}
}

void sortStats(std::string sortedWords[], int sortedScores[], int count)
{


	int	minIdx	= 0;
	std::string tempWord = "";
	int tempScore = 0;

	for ( int i = 0; i < count; i++ )
	{
		minIdx = i;

		for ( int j = i + 1; j < count; j++ )
		{
			if ( (sortedScores[j] > sortedScores[minIdx]) ) // Sort by the score
			{
				minIdx = j;
			}
		}

		if(i != minIdx)										// Swap if needed
		{
			std::string	tempWord = sortedWords[i];

			sortedWords[i] = sortedWords[minIdx];
			sortedWords[minIdx] = tempWord;

			int	tempScore = scores[i];

			sortedScores[i]	 = sortedScores[minIdx];
			sortedScores[minIdx] = tempScore;
		}
	}

	std::cout << "Sorted scores:" << std::endl;

	for ( int i = 0; i < count; i++ )
	{
		std::cout <<"Word: " << std::setw(20) << std::left << sortedWords[i] << "\t" << "Score: " << std::setw(5) << sortedScores[i] << std::endl;
	}
}
