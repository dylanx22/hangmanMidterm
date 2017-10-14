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

void sortStats(std::string sortedWords[], int sortedStats[], int count);

bool wordPicked;

bool statsLoaded;


enum GAMESTATE : int { HELP, INTRODUCTION, SELECT_WORD, CUSTOM_WORD, PLAY_GAME, STATS, EXIT };

namespace Safe
{
    enum SORTING : int { EXIT = 0, SORT_BY_SCORE = 1, SORT_BY_AGE = 2  };
}

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

std::string	savedWords[10];
int			scores[10];
