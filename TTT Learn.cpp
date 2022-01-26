#include <iostream>
#include <string>
#include <ctime>
#include <forward_list>
#include <FileEditor.cpp>

using namespace std;

//FileEditor f1("TTT Log.txt");
	//every move completely random
//FileEditor f2("TTT Log 2.txt");
	//with algorithm to finish and block rows
FileEditor f3("TTT Log 3.txt");
	//records against player
FileEditor f4("TTT Log 4.txt");
	//playing self
string board[9];
string sols[24];
int scores[9] = { 0,0,0,0,0,0,0,0,0 };

//1 means put numbers, 0 means put spaces
void initialize(int a)
{
	if (a == 1)
	{
		for (int i = 0; i < 9; i++)
			board[i] = "" + to_string(i + 1);
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
		7:left column ^
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
			sols[x + y*8] = string(sols[x + y*8]) + string(board[(int)sols[x + y*8].at(0) - 48]);
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
				base = base.substr(0,i) + "6" + base.substr(i + 1);
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

//manipulates board according to game path
void test(string path, bool print)
{
	initialize(0);
	for (int i = 2; path.at(i) != '|'; i++)
	{
		if (i % 2 == 0)
			board[(int)path.at(i) - 48] = "X";
		else
			board[(int)path.at(i) - 48] = "O";
		if (print)printBoard();
	}
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
					if (sols[x + (y*8)].at(1) != 'X')
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

//generates game log
//format is "winner path|transformation"
string play()
{
	string s = "- |-";
	int move = 0;
	
	//adding moves
	for (int n = 0; n < 9; n++)
	{
		test(s,false);
		
		bool x = false;
		if (s.length() % 2 == 0)
			x = true;
		int obv = obvious(x);
		if (obv > -1)
		{
			move = obv;
			//adds obvious move
			s = s.substr(0, s.length() - 2) + to_string(move) + "|-";
		}
		else
		{
			move = rand() % 9;

			//checking if move is a repeat
			while (s.find(to_string(move)) != -1)
				move = rand() % 9;
			//adds random move
			s = s.substr(0, s.length() - 2) + to_string(move) + "|-";
		}

		//testing game path on board
		initialize(0);
		for (int i = 2; s.at(i) != '|'; i++)
		{
			if (i % 2 == 0)
				board[(int)s.at(i) - 48] = "X";
			else
				board[(int)s.at(i) - 48] = "O";
		}

		//checking for winner and ending loop if there is one
		if (check() == 1)
		{
			s = "X" + s.substr(1);
			break;
		}
		else if (check() == -1)
		{
			s = "O" + s.substr(1);
			break;
		}
		else if (check() == 2)
		{
			s = "T" + s.substr(1);
			break;
		}
	}
	return s;
}

/*generates games in the file
void gen()
{
	srand((unsigned)time(0));
	for (int i = 0; i < 1000000; i++)
	{
		f2.add(format(play()), 0);
		if (i % 1000 == 0)
			cout << i << endl;
	}
}*/

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

//generates game log
//format is "winner path|transformation"
string play2()
{
	string s = "- |-";
	int move = 0;

	//adding moves
	for (int n = 0; n < 9; n++)
	{
		test(s, false);

		//whether the current move is 'X' or 'O'
		bool x = false;
		if (s.length() % 2 == 0)
			x = true;

		int obv = obvious(x);
		if (obv > -1)
		{
			move = obv;
			//adds obvious move
			s = s.substr(0, s.length() - 2) + to_string(move) + "|-";
		}
		else
		{
			//how "good" each position is
			//based on how often the move results in a win vs loss
			//-1 mil = already taken
			for (int i = 0; i < 9; i++)scores[i] = 0;

			//illegal moves
			for (int i = 0; i < 9; i++)
			{
				if (board[i] != " ")
				{
					scores[i] = -1000000;
				}
			}
			
			//going through computer battle database
			f4.resetIt();
			for (int i = 0; i < f4.lines(); i++)
			{
				//only games that have the same path thus far
				if (f4.getIt().substr(2, n).compare(s.substr(2, n)) == 0)
				{
					//adjusting appropriate score value
					if (x)
					{
						if (f4.getIt().at(0) == 'T')
							scores[(int)f4.getIt().at(2 + n) - 48] -= 0;
						else if(f4.getIt().at(0) == 'X')
							scores[(int)f4.getIt().at(2 + n) - 48] += 10;
						else
							scores[(int)f4.getIt().at(2 + n) - 48] -= 10;
					}
					else
					{
						if (f4.getIt().at(0) == 'T')
							scores[(int)f4.getIt().at(2 + n) - 48] += 1;
						else if (f4.getIt().at(0) == 'O')
							scores[(int)f4.getIt().at(2 + n) - 48] += 10;
						else
							scores[(int)f4.getIt().at(2 + n) - 48] -= 10;
					}
				}
				f4.iter();
			}

			//going through player battle database
			f3.resetIt();
			for (int i = 0; i < f3.lines(); i++)
			{
				//only games that have the same path thus far
				if (f3.getIt().substr(2, n).compare(s.substr(2, n)) == 0)
				{
					//adjusting appropriate score value
					if (x)
					{
						if (f3.getIt().at(0) == 'T')
							scores[(int)f3.getIt().at(2 + n) - 48] -= 0;
						else if (f3.getIt().at(0) == 'X')
							scores[(int)f3.getIt().at(2 + n) - 48] += 10;
						else
							scores[(int)f3.getIt().at(2 + n) - 48] -= 10;
					}
					else
					{
						if (f3.getIt().at(0) == 'T')
							scores[(int)f3.getIt().at(2 + n) - 48] += 1;
						else if (f3.getIt().at(0) == 'O')
							scores[(int)f3.getIt().at(2 + n) - 48] += 10;
						else
							scores[(int)f3.getIt().at(2 + n) - 48] -= 10;
					}
				}
				f3.iter();
			}

			//eliminating redundant moves
			if (n < 3)
			{
				for (int i = 0; i < 9; i++)
				{
					if (scores[i] > -900000)
					{
						if (redundant(s, i))
						{
							scores[i] = -500000;
						}
					}
				}
			}
			
			move = choose(scores);

			//adds educated move
			s = s.substr(0, s.length() - 2) + to_string(move) + "|-";
		}
		/*for (int i = 0; i < 9; i++)
		{
			cout << to_string(i) + ": " + to_string(scores[i]) << endl;
		}
		cout << "---" << endl;*/

		//testing game path on board
		initialize(0);
		for (int i = 2; s.at(i) != '|'; i++)
		{
			if (i % 2 == 0)
				board[(int)s.at(i) - 48] = "X";
			else
				board[(int)s.at(i) - 48] = "O";
		}

		//checking for winner and ending loop if there is one
		if (check() == 1)
		{
			s = "X" + s.substr(1);
			break;
		}
		else if (check() == -1)
		{
			s = "O" + s.substr(1);
			break;
		}
		else if (check() == 2)
		{
			s = "T" + s.substr(1);
			break;
		}
	}
	return s;
}

void gen2()
{
	srand((unsigned)time(0));
	for (int i = 0; i < 100; i++)
	{
		f4.add(format(play2()), 0);
		if (i % 50 == 0)
			cout << i << endl;
	}
}

int main()
{
	gen2();
	f4.save();
	return 0;
}
