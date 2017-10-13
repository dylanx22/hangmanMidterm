#pragma once


int	MAX_TRIES		= 5;

int	total_guesses	= 0;

int matchLetter(char, std::string, std::string &);

int hangMan(std::string word);

int calcScore(int, int);

int statsMenu();

int loadStats();

void instructions();

void saveGame(std::string, double);

void recentGames();

void statsMain();

void displayStats();

void sortStats();



std::string	word;
std::string	words[6][5]	=
{
    {
        "countries", "science terms", "food", "coding terms", "computer games"					// catagories
    },		
    {
        "mexico", "supernova", "burrito", "function", "snake"								
    },																		// Each column under a category are it's word choices.
    {
        "canada", "element", "spaghetti", "namespace", "wolfenstein"
    },
    {
        "spain", "photosynthesis", "rice", "include", "mindsweep"
    },
    {
        "japan", "protein", "cornbread", "operator", "castlevania"
    },
    {
        "pakistan", "gravity", "meatloaf", "header", "mario"
    }
};

std::string pickWord();

std::string	savedWords[50];
int			scores[50];
