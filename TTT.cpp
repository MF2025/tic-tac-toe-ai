#include <iostream>
#include <string>
#include <ctime>
#include <FileEditor.cpp>
#include <StringParser.cpp>

using namespace std;

//created August 2020
//revised June 2021

//ai log for playing against itself
FileEditor fe("TTT Log 4.txt");
//log against real players
FileEditor fe2("TTT Log 3.txt");
StringParser sp(0);
string board[9];
string gameLog = "- |-";
string sols[24];
int scores[9] = { 0,0,0,0,0,0,0,0,0 };
char computerChar;

//1 means put numbers, 0 means put spaces
void initialize(int a)
{
	if (a == 1)
	{
		for (int i = 0; i < 9; i++)
			board[i] = to_string(i + 1);
	}
	else
	{
		for (int i = 0; i < 9; i++)
			board[i] = " ";
	}
}

/*
in computer, player sees 1 to 9
 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8
*/
void printBoard()
{
	for (int i = 0; i < 9; i++)
	{
		cout << " " + board[i] + " ";
		if (i % 3 < 2)
			cout << "|";
		else
		{
			if (i != 8)
				cout << endl << "---+---+---" << endl;
			else
				cout << endl;
		}
	}
	cout << endl;
}

/*
returns array of all the solutions from the board
	IDs (with direction):
		0:middle column v
		1:middle row >
		2:decay diag v
		3:growth diag v
		4:top row >
		5:right column v
		6:bottom row <
		7:left column >
*/
void updateSols()
{
	//8 solutions, each with 3 spaces
	//goes through each solution's 1st coordinates, then 2nd, then 3rd (3 sets of 8)

	sols[0] = "1";
	sols[8] = "4";
	sols[16] = "7";

	sols[1] = "3";
	sols[9] = "4";
	sols[17] = "5";

	sols[2] = "0";
	sols[10] = "4";
	sols[18] = "8";

	sols[3] = "2";
	sols[11] = "4";
	sols[19] = "6";

	sols[4] = "0";
	sols[12] = "1";
	sols[20] = "2";

	sols[5] = "2";
	sols[13] = "5";
	sols[21] = "8";

	sols[6] = "8";
	sols[14] = "7";
	sols[22] = "6";

	sols[7] = "6";
	sols[15] = "3";
	sols[23] = "0";

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			sols[x + y * 8] = string(sols[x + y * 8]) + string(board[(int)sols[x + y * 8].at(0) - 48]);
		}
	}
}

/*
returns score array of all the solutions from the board
	IDs:
		0:middle column
		1:middle row
		2:decay diag
		3:growth diag
		4:top row
		5:right column
		6:bottom row
		7:left column
	Scores:
		0 for neutral
		n for X
		-n for O
*/
void updateScores()
{
	//X scores
	int solutionsX[8] = { 0,0,0,0,0,0,0,0 };
	//O scores
	int solutionsO[8] = { 0,0,0,0,0,0,0,0 };

	//X's
	if (board[0].compare("X") == 0)
	{
		solutionsX[2]++;
		solutionsX[4]++;
		solutionsX[7]++;
	}
	if (board[1].compare("X") == 0)
	{
		solutionsX[0]++;
		solutionsX[4]++;
	}
	if (board[2].compare("X") == 0)
	{
		solutionsX[3]++;
		solutionsX[4]++;
		solutionsX[5]++;
	}
	if (board[3].compare("X") == 0)
	{
		solutionsX[1]++;
		solutionsX[7]++;
	}
	if (board[4].compare("X") == 0)
	{
		solutionsX[0]++;
		solutionsX[1]++;
		solutionsX[2]++;
		solutionsX[3]++;
	}
	if (board[5].compare("X") == 0)
	{
		solutionsX[1]++;
		solutionsX[5]++;
	}
	if (board[6].compare("X") == 0)
	{
		solutionsX[3]++;
		solutionsX[6]++;
		solutionsX[7]++;
	}
	if (board[7].compare("X") == 0)
	{
		solutionsX[0]++;
		solutionsX[6]++;
	}
	if (board[8].compare("X") == 0)
	{
		solutionsX[2]++;
		solutionsX[5]++;
		solutionsX[6]++;
	}

	//O's
	if (board[0].compare("O") == 0)
	{
		solutionsO[2]++;
		solutionsO[4]++;
		solutionsO[7]++;
	}
	if (board[1].compare("O") == 0)
	{
		solutionsO[0]++;
		solutionsO[4]++;
	}
	if (board[2].compare("O") == 0)
	{
		solutionsO[3]++;
		solutionsO[4]++;
		solutionsO[5]++;
	}
	if (board[3].compare("O") == 0)
	{
		solutionsO[1]++;
		solutionsO[7]++;
	}
	if (board[4].compare("O") == 0)
	{
		solutionsO[0]++;
		solutionsO[1]++;
		solutionsO[2]++;
		solutionsO[3]++;
	}
	if (board[5].compare("O") == 0)
	{
		solutionsO[1]++;
		solutionsO[5]++;
	}
	if (board[6].compare("O") == 0)
	{
		solutionsO[3]++;
		solutionsO[6]++;
		solutionsO[7]++;
	}
	if (board[7].compare("O") == 0)
	{
		solutionsO[0]++;
		solutionsO[6]++;
	}
	if (board[8].compare("O") == 0)
	{
		solutionsO[2]++;
		solutionsO[5]++;
		solutionsO[6]++;
	}
	for (int i = 0; i < 8; i++)
	{
		if (solutionsX[i] > 0 && solutionsO[i] > 0)
			scores[i] = 0;
		else
			scores[i] = solutionsX[i] - solutionsO[i];
	}
}

//checks the state of the board
	//0 = no winner
	//-1 = computer wins
	//1 = player wins
	//2 = tie (filled but no winner)
int check()
{
	updateScores();

	for (int i = 0; i < 8; i++)
	{
		if (scores[i] == 3)
			return 1;
		if (scores[i] == -3)
			return -1;
	}

	//tie
	int filled = 0;
	for (int i = 0; i < 9; i++)
	{
		if (board[i].compare("O") == 0 || board[i].compare("X") == 0)
			filled++;
	}
	if (filled == 9)
		return 2;
	return 0;
}

//reflects or rotates board so there are less combinations
//type = type of transformation, base = game log
//does not update transformation on the log
string shift(string type, string base)
{
	//reflect over
	if (type.compare("x") == 0)
	{
		for (int i = 2; base.at(i) != '|'; i++)
		{
			switch (base.at(i))
			{
			case '0':
				base = base.substr(0, i) + "6" + base.substr(i + 1);
				break;
			case '1':
				base = base.substr(0, i) + "7" + base.substr(i + 1);
				break;
			case '2':
				base = base.substr(0, i) + "8" + base.substr(i + 1);
				break;
			case '6':
				base = base.substr(0, i) + "0" + base.substr(i + 1);
				break;
			case '7':
				base = base.substr(0, i) + "1" + base.substr(i + 1);
				break;
			case '8':
				base = base.substr(0, i) + "2" + base.substr(i + 1);
				break;
			default:
				break;
			}
		}
	}
	else if (type.compare("y") == 0)
	{
		for (int i = 2; base.at(i) != '|'; i++)
		{
			switch (base.at(i))
			{
			case '0':
				base = base.substr(0, i) + "2" + base.substr(i + 1);
				break;
			case '2':
				base = base.substr(0, i) + "0" + base.substr(i + 1);
				break;
			case '3':
				base = base.substr(0, i) + "5" + base.substr(i + 1);
				break;
			case '5':
				base = base.substr(0, i) + "3" + base.substr(i + 1);
				break;
			case '6':
				base = base.substr(0, i) + "8" + base.substr(i + 1);
				break;
			case '8':
				base = base.substr(0, i) + "6" + base.substr(i + 1);
				break;
			default:
				break;
			}
		}
	}
	else if (type.compare("/") == 0)
	{
		for (int i = 2; base.at(i) != '|'; i++)
		{
			switch (base.at(i))
			{
			case '0':
				base = base.substr(0, i) + "8" + base.substr(i + 1);
				break;
			case '1':
				base = base.substr(0, i) + "5" + base.substr(i + 1);
				break;
			case '3':
				base = base.substr(0, i) + "7" + base.substr(i + 1);
				break;
			case '5':
				base = base.substr(0, i) + "1" + base.substr(i + 1);
				break;
			case '7':
				base = base.substr(0, i) + "3" + base.substr(i + 1);
				break;
			case '8':
				base = base.substr(0, i) + "0" + base.substr(i + 1);
				break;
			default:
				break;
			}
		}
	}
	else if (type.compare("\\") == 0)
	{
		for (int i = 2; base.at(i) != '|'; i++)
		{
			switch (base.at(i))
			{
			case '1':
				base = base.substr(0, i) + "3" + base.substr(i + 1);
				break;
			case '2':
				base = base.substr(0, i) + "6" + base.substr(i + 1);
				break;
			case '3':
				base = base.substr(0, i) + "1" + base.substr(i + 1);
				break;
			case '5':
				base = base.substr(0, i) + "7" + base.substr(i + 1);
				break;
			case '6':
				base = base.substr(0, i) + "2" + base.substr(i + 1);
				break;
			case '7':
				base = base.substr(0, i) + "5" + base.substr(i + 1);
				break;
			default:
				break;
			}
		}
	}
	//rotate
	else if (type.compare("cw") == 0)
	{
		for (int i = 2; base.at(i) != '|'; i++)
		{
			switch (base.at(i))
			{
			case '0':
				base = base.substr(0, i) + "2" + base.substr(i + 1);
				break;
			case '1':
				base = base.substr(0, i) + "5" + base.substr(i + 1);
				break;
			case '2':
				base = base.substr(0, i) + "8" + base.substr(i + 1);
				break;
			case '3':
				base = base.substr(0, i) + "1" + base.substr(i + 1);
				break;
			case '5':
				base = base.substr(0, i) + "7" + base.substr(i + 1);
				break;
			case '6':
				base = base.substr(0, i) + "0" + base.substr(i + 1);
				break;
			case '7':
				base = base.substr(0, i) + "3" + base.substr(i + 1);
				break;
			case '8':
				base = base.substr(0, i) + "6" + base.substr(i + 1);
				break;
			default:
				break;
			}
		}
	}
	else if (type.compare("ccw") == 0)
	{
		for (int i = 2; base.at(i) != '|'; i++)
		{
			switch (base.at(i))
			{
			case '0':
				base = base.substr(0, i) + "6" + base.substr(i + 1);
				break;
			case '1':
				base = base.substr(0, i) + "3" + base.substr(i + 1);
				break;
			case '2':
				base = base.substr(0, i) + "0" + base.substr(i + 1);
				break;
			case '3':
				base = base.substr(0, i) + "7" + base.substr(i + 1);
				break;
			case '5':
				base = base.substr(0, i) + "1" + base.substr(i + 1);
				break;
			case '6':
				base = base.substr(0, i) + "8" + base.substr(i + 1);
				break;
			case '7':
				base = base.substr(0, i) + "5" + base.substr(i + 1);
				break;
			case '8':
				base = base.substr(0, i) + "2" + base.substr(i + 1);
				break;
			default:
				break;
			}
		}
	}
	else if (type.compare("180") == 0)
	{
		for (int i = 2; base.at(i) != '|'; i++)
		{
			switch (base.at(i))
			{
			case '0':
				base = base.substr(0, i) + "8" + base.substr(i + 1);
				break;
			case '1':
				base = base.substr(0, i) + "7" + base.substr(i + 1);
				break;
			case '2':
				base = base.substr(0, i) + "6" + base.substr(i + 1);
				break;
			case '3':
				base = base.substr(0, i) + "5" + base.substr(i + 1);
				break;
			case '5':
				base = base.substr(0, i) + "3" + base.substr(i + 1);
				break;
			case '6':
				base = base.substr(0, i) + "2" + base.substr(i + 1);
				break;
			case '7':
				base = base.substr(0, i) + "1" + base.substr(i + 1);
				break;
			case '8':
				base = base.substr(0, i) + "0" + base.substr(i + 1);
				break;
			default:
				break;
			}
		}
	}
	return base;
}

//formats a game log to reduce number of combinations
string format(string base)
{
	bool corner = true; //if the first non-middle move was a corner or edge
	char t = '-'; //transformation
	int active = 2;

	if (base.at(active) == '4')
		active++;

	//shifts corner to top left or edge to left
	switch (base.at(active))
	{
	case '1': t = '\\'; corner = false;
		break;
	case '2': t = 'y';
		break;
	case '3': corner = false;
		break;
	case '5': t = 'y'; corner = false;
		break;
	case '6': t = 'x';
		break;
	case '7': t = '/'; corner = false;
		break;
	case '8': t = '/';
		break;
	default:
		break;
	}

	string tStr(1, t);//t conversion to string
	base = shift(tStr, base);
	base = base.substr(0, base.find('|') + 1) + tStr;

	active++;
	if (base.at(active) == '4')
		active++;

	char t2 = '-'; //transformation 2

	//keeps second non-middle move either at top, right, or opposite of first move
	if (corner)
	{
		switch (base.at(active))
		{
		case '3': t2 = '\\';
			break;
		case '6': t2 = '\\';
			break;
		case '7': t2 = '\\';
			break;
		default:
			break;
		}
	}
	else
	{
		switch (base.at(active))
		{
		case '6': t2 = 'x';
			break;
		case '7': t2 = 'x';
			break;
		case '8': t2 = 'x';
			break;
		default:
			break;
		}
	}

	string tStr2(1, t2);//t2 conversion to string
	base = shift(tStr2, base);

	if (t == '-' && t2 != '-')
	{
		base = base.substr(0, base.find('|') + 1) + tStr2;
	}
	else if (t == '\\' && t2 == 'x')
	{
		base = base.substr(0, base.find('|') + 1) + "ccw";
	}
	else if (t == '\\' && t2 == '\\')
	{
		base = base.substr(0, base.find('|') + 1) + "-";
	}
	else if (t == '/' && t2 == 'x')
	{
		base = base.substr(0, base.find('|') + 1) + "cw";
	}
	else if (t == '/' && t2 == '\\')
	{
		base = base.substr(0, base.find('|') + 1) + "180";
	}
	else if (t == 'x' && t2 == 'x')
	{
		base = base.substr(0, base.find('|') + 1) + "-";
	}
	else if (t == 'x' && t2 == '\\')
	{
		base = base.substr(0, base.find('|') + 1) + "cw";
	}
	else if (t == 'y' && t2 == 'x')
	{
		base = base.substr(0, base.find('|') + 1) + "180";
	}
	else if (t == 'y' && t2 == '\\')
	{
		base = base.substr(0, base.find('|') + 1) + "ccw";
	}

	return base;
}

//unformats game log so it can match the actual game
string unformat(string base)
{
	string t = "-";
	if (base.substr(base.find('|') + 1).compare("cw") == 0)
		t = "ccw";
	else if (base.substr(base.find('|') + 1).compare("ccw") == 0)
		t = "cw";
	else
		t = base.substr(base.find('|') + 1);
	return shift( t, base ).substr( 0, base.find('|') + 1 ) + "-";
}

//choosing a move based on the best score
//if multiple options have the same score, it chooses randomly from those options
int choose(int scores[])
{
	int greatestScore = scores[0];
	int numOfGreatests = 0;

	for (int i = 0; i < 9; i++)
	{
		if (scores[i] > greatestScore)
		{
			greatestScore = scores[i];
			numOfGreatests = 1;
		}
		else if (scores[i] == greatestScore)
		{
			numOfGreatests++;
		}
	}

	//random out of options with best score
	int r = rand() % numOfGreatests;
	//which option is active
	int n = 0;

	for (int i = 0; i < 9; i++)
	{
		if (scores[i] == greatestScore)
		{
			if (n == r)
				return i;
			n++;
		}
	}
	return 9;
}

//returns an obvious move (auto win or block) given a path
//-1 if no obvious move
//parameter is whether it is x or o's turn
int obvious(bool x)
{
	updateSols();
	updateScores();
	if (x)
	{
		for (int x = 0; x < 8; x++)
		{
			if (scores[x] == 2)
			{
				for (int y = 0; y < 3; y++)
				{
					if (sols[x + (y * 8)].at(1) != 'X')
					{
						return (int)sols[x + (y * 8)].at(0) - 48;
					}
				}
			}
		}

		for (int x = 0; x < 8; x++)
		{
			if (scores[x] == -2)
			{
				for (int y = 0; y < 3; y++)
				{
					if (sols[x + (y * 8)].at(1) != 'O')
					{
						return (int)sols[x + (y * 8)].at(0) - 48;
					}
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 8; x++)
		{
			if (scores[x] == -2)
			{
				for (int y = 0; y < 3; y++)
				{
					if (sols[x + (y * 8)].at(1) != 'O')
					{
						return (int)sols[x + (y * 8)].at(0) - 48;
					}
				}
			}
		}

		for (int x = 0; x < 8; x++)
		{
			if (scores[x] == 2)
			{
				for (int y = 0; y < 3; y++)
				{
					if (sols[x + (y * 8)].at(1) != 'X')
					{
						return (int)sols[x + (y * 8)].at(0) - 48;
					}
				}
			}
		}
	}
	return -1;
}

//finds whether the move is redundant given a path
//has already passed length test (moves done < 4)
bool redundant(string base, int move)
{
	base = base.substr(0, base.find('|')) + to_string(move) + "|-";
	if (format(base).compare(base) == 0)
		return false;
	return true;
}

bool playerMove()
{
	cout << "Where would you like to go?" << endl;
	string input = "";
	cin >> input;
	
	if (input.at(0) == '\\')
		return true;

	while (input.length() > 1 || input.length() < 1 || input.at(0) <= '0' || input.at(0) > '9'
		|| board[(int)(input.at(0) - 48) - 1].compare(" ") != 0)
	{
		if (input.length() > 1 || input.length() < 1 || input.at(0) <= '0' || input.at(0) > '9')
		{
			cout << "Please enter a number between 1 and 9." << endl;
			cin >> input;
		}
		else
		{
			cout << "Please enter a number that is not already taken." << endl;
			cin >> input;
		}
	}

	board[(int)(input.at(0) - 49)] = "X";
	gameLog = gameLog.substr(0, gameLog.find('|')) + to_string((int)(input.at(0) - 49)) + gameLog.substr(gameLog.find('|'));
	printBoard();

	return false;
}

void computerMove()
{
	string form = format(gameLog);
	int move = -1;
	int bestScore = -1000000;
	//list of scores
	//-1mil = not possible
	//0 = no occurrences
	//1 = only ties
	int scores[9] = { 0,0,0,0,0,0,0,0,0 };
	int movesDone = 0;

	for (int i = 2; form.at(i) != '|'; i++)
	{
		if (form.at(i) >= '0' && form.at(i) <= '9')
		{
			//recording spots as "not possible" if they have been taken
			scores[(int)form.at(i) - 48] = -1000000;

			//recording number of moves played
			movesDone++;
		}
	}

	if (obvious(false) > -1)
	{
		move = obvious(false);

		gameLog = gameLog.substr(0, gameLog.find('|')) + to_string(move) + gameLog.substr(gameLog.find('|'));
		board[(int)gameLog.at(gameLog.find('|') - 1) - 48] = 'O';

		cout << endl;
		printBoard();
		cout << "The computer went in spot " + to_string(move + 1) << endl;
	}
	else
	{
		fe.resetIt();
		cout << "Thinking..." << endl;
		for (int i = 0; i < fe.lines(); i++)
		{
			//only logs that contain the same moves as the current game
			if (fe.getIt().substr(2, movesDone).compare(form.substr(2, movesDone)) == 0)
			{
				//filters out logs that are shorter than the active game
				//only logs where the next move has not been taken
				if (fe.getIt().at(2 + movesDone) != '|' && scores[(int)fe.getIt().at(2 + movesDone) - 48] > -900000)
				{
					//making tie-resulting moves priority above impossible moves
					if (fe.getIt().at(0) == 'T')
					{
						if (scores[(int)fe.getIt().at(2 + movesDone) - 48] == 0)
						{
							scores[(int)fe.getIt().at(2 + movesDone) - 48] = 1;
						}
						else if (computerChar == 'O')
						{
							scores[(int)fe.getIt().at(2 + movesDone) - 48] += 1;
						}
					}
					//increasing score with a winning outcome
					else if (fe.getIt().at(0) == computerChar)
					{
						scores[(int)fe.getIt().at(2 + movesDone) - 48] += 10;
					}
					//decreasing score with a losing outcome
					else
					{
						scores[(int)fe.getIt().at(2 + movesDone) - 48] -= 10;
					}
				}
			}
			fe.iter();
		}

		//using the player file also
		fe2.resetIt();
		for (int i = 0; i < fe2.lines(); i++)
		{
			//only logs that contain the same moves as the current game
			if (fe2.getIt().substr(2, movesDone).compare(form.substr(2, movesDone)) == 0)
			{
				//filters out logs that are shorter than the active game
				//only logs where the next move has not been taken
				if (fe2.getIt().at(2 + movesDone) != '|' && scores[(int)fe2.getIt().at(2 + movesDone) - 48] > -900000)
				{
					//making tie-resulting moves priority above impossible moves
					if (fe2.getIt().at(0) == 'T')
					{
						if (scores[(int)fe2.getIt().at(2 + movesDone) - 48] == 0)
						{
							scores[(int)fe2.getIt().at(2 + movesDone) - 48] = 1;
						}
						else if (computerChar == 'O')
						{
							scores[(int)fe2.getIt().at(2 + movesDone) - 48] += 1;
						}
					}
					//increasing score with a winning outcome
					else if (fe2.getIt().at(0) == computerChar)
					{
						scores[(int)fe2.getIt().at(2 + movesDone) - 48] += 10;
					}
					//decreasing score with a losing outcome
					else
					{
						scores[(int)fe2.getIt().at(2 + movesDone) - 48] -= 10;
					}
				}
			}
			fe2.iter();
		}

		//eliminating redundant moves
		if (movesDone < 3)
		{
			for (int i = 0; i < 9; i++)
			{
				if (scores[i] > -900000)
				{
					if (redundant(form, i))
					{
						scores[i] = -500000;
					}
				}
			}
		}

		/*for (int i = 0; i < 9; i++)
		{
			cout << to_string(i) + ": " + to_string(scores[i]) << endl;
		}
		cout << "---" << endl;*/

		move = choose(scores);

		gameLog = unformat(form.substr(0, form.find('|')) + to_string(move) + form.substr(form.find('|')));
		board[(int)gameLog.at(gameLog.find('|') - 1) - 48] = 'O';

		int realMove = (int)gameLog.at(gameLog.find('|') - 1) - 48;

		printBoard();
		cout << "The computer went in spot " + to_string(realMove + 1) << endl;
	}
}

int main()
{
	srand((unsigned)time(0));

	initialize(1);
	printBoard();
	gameLog = "- |-";
	initialize(0);

	bool playAgain = true;
	bool first = true;
	string s;
	bool refresh = false;

	while (playAgain)
	{
		if (!first)
		{
			cout << "Would you like to play again?" << endl;
			cin >> s;
			if (sp.numberOf(s, "y") < 1 && sp.numberOf(s, "Y") < 1)
				break;

			cout << endl;
			initialize(1);
			printBoard();
			cout << "Would you like to go first?" << endl;
		}
		else
		{
			cout << "Would you like to go first?" << endl;
			first = false;
		}

		gameLog = "- |-";
		initialize(0);
		cin >> s;

		if (sp.numberOf(s, "y") > 0 || sp.numberOf(s, "Y") > 0)
		{
			refresh = playerMove();
			computerChar = 'O';
		}
		else
		{
			computerChar = 'X';
		}
		while (check() == 0 && !refresh)
		{
			computerMove();
			if (check() == 0)
				refresh = playerMove();
		}
		if (!refresh)
		{
			if (check() == -1)
			{
				cout << "Computer wins.";
				gameLog = computerChar + gameLog.substr(1);
			}
			else if (check() == 1)
			{
				cout << "You win!";
				if (computerChar == 'X')
					gameLog = "O" + gameLog.substr(1);
				else
					gameLog = "X" + gameLog.substr(1);
			}
			else
			{
				cout << "Tie!";
				gameLog = "T" + gameLog.substr(1);
			}

			//records data against actual players
			fe2.add(format(gameLog), 0);
			fe2.save();
		}

		refresh = false;
		cout << endl;
	}
	return 0;
}
