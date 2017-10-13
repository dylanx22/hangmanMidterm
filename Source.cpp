
#include < string >
#include < iostream >
#include < cstdio >
#include < cctype >
#include < fstream >
#include < vector >
#include "Source.h"


int displayMenu()
{
    int	choice	= 0;

    std::cout << "|_____________________________________________________________________|" << std::endl;
    std::cout << "| 1. Instructions |\n" << std::endl;
    std::cout << "| 2. Choose Word |\n" << std::endl;
    std::cout << "| 3. Enter Custom Word |\n" << std::endl;
    std::cout << "| 4. Play Hangman! |\n" << std::endl;
    std::cout << "| 5. View Past Scores | \n" << std::endl;
    std::cout << "|_____________________________________________________________________|" << std::endl;
    std::cout << "\nEnter your choice here: \n" << std::endl;
    std::cin >> choice;

    return choice;
}

int main()
{
    int	option	= 0;

    do
    {
        int	option	= displayMenu();

        switch(option)
        {
            case 1 :
            {
                // Shows instructions
                instructions();

                break;
            }

            case 2 :
            {
                // Displays the word choice menu
                word	= pickWord();

                break;
            }

            case 3 :
            {
                // Uses user input to get the word
                std::cout << "Enter the secret word, no peeking player 2!";
                std::cin >> word;

                break;
            }

            case 4 :
            {
                // Play Hangman!
                hangMan(word);

                break;
            }

            case 5 :
            {
                // Show recent game statistics
                statsMain();

                break;
            }

            default :
            {
                break;
            }
        }
    }
    while( ( option == 0 ) || ( option == 1 ) || ( option == 2  )|| ( option == 3 ) || ( option == 4 ) || ( option == 5 ));
}

void instructions()
{
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\n\nWelcome to HANGMAN...";
    std::cout << "\n\nPick a word from the menu, then let a friend try to guess it!";
    std::cout << "\n\nOr you can enter your own custom word if you prefer.";
    std::cout << "\n\nEach letter is represented by a star.";
    std::cout << "\n\nType in one letter each turn";
    std::cout << "\n\nThe word is CASE SENSITIVE!";
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    system("pause");
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
        std::cout << MAX_TRIES - wrongAmts << " guesses remaining." << std::endl;

        // Check if the user has guessed correctly
        // if so, calculate and display final score.
        // and the end game message.
        // save the game info.
        if(word == unknown)
        {
            std::cout << word << std::endl;
            std::cout << "Congratulations! You win.";
            std::cout << "You score was: " << calcScore(remainder, score) << std::endl;

            saveGame(word, calcScore(remainder, score));

            break;
        }
    }

    if(wrongAmts == MAX_TRIES)
    {
        std::cout << "\nGAME OVER" << std::endl;
        std::cout << "The word was : " << word << std::endl;
    }

    std::cin.ignore();
    std::cin.get();

    return 0;
}

int matchLetter(char guess, std::string secret, std::string & guessword)
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

void saveGame(std::string pastWord, double score)	// saves the word and the score to a text file.
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

std::string pickWord()
{
    int	category, wordNumber;
    int	r, c;

    for ( c = 0; c < 5; c++ )
    {
        std::cout << c + 1 << ". " << words[0][c] << std::endl;
    }

    std::cout << "Enter a category:";
    std::cin >> category;

    for ( r = 1; r < 6; r++ )
    {
        std::cout << r + 1 << ". " << words[r][category - 1] << std::endl;
    }

    std::cout << "Now choose a word:";
    std::cin >> wordNumber;

    return words[wordNumber - 1][category - 1];
}

int statsMenu()
{
    int	choice	= 0;

    std::cout << "|_____________________________________________________________________|" << std::endl;
    std::cout << "\n| 0. Return to main menu |\n" << std::endl;
    std::cout << "| 1. View Past Games |\n" << std::endl;
    std::cout << "| 2. Sort Past Scores |\n" << std::endl;
    std::cout << "|_____________________________________________________________________|" << std::endl;
    std::cout << "\nEnter your choice here: \n" << std::endl;
    std::cin >> choice;

    return choice;
}

void statsMain()
{
    int	option	= 0;

    loadStats();

    do
    {
        int	option	= statsMenu();

        switch(option)
        {
            case 0 :
            {
                // return to main menu

                break;
            }

            case 1 :
            {
                // Show All Games
                displayStats();

                break;
            }

            case 2 :
            {
                // Sort by length of the word
                sortStats();

                break;
            }

            default :
            {
                break;
            }
        }
    }
    while( (option == 0 ) || ( option == 1 ) || ( option == 2 ) );
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
	
	return count;

}

void displayStats()
{
	int count = loadStats();

    for ( int i = 0; i < count; i++ )
    {
        std::cout << savedWords[i] << "\t" << scores[i] << std::endl;
    }
}

void sortStats()
{
    int	choice = 0;

    std::cout << "1. Sort by word length" << std::endl;
    std::cout << "2. Sort by score" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    int	minIdx	= 0;
    int	count	= 0;

    for ( int i = 0; i < count; i++ )
    {
        minIdx	= i;

        for ( int j = i + 1; j < count; j++ )
        {
            if(( choice == 1 ) && ( savedWords[j].length() < savedWords[minIdx].length() ))	// If sorting by word length
            {
                minIdx	= j;
            }
            else if(( choice == 2 ) && ( scores[j] < scores[minIdx] ))				// If sorting by score
            {
                minIdx	= j;
            }
        }

        if(i != minIdx)										// Swap if needed
        {
            std::string	tempWord	= savedWords[i];

            savedWords[i]	= savedWords[minIdx];
            savedWords[minIdx]	= tempWord;

            int	tempScore	= scores[i];

            scores[i]		= scores[minIdx];
            scores[minIdx]	= tempScore;
        }
    }

    std::cout << "Sorted scores:" << std::endl;

    for ( int i = 0; i < count; i++ )
    {
        std::cout << words[i] << "\t" << scores[i] << std::endl;
    }
}
