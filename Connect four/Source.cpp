#include <iostream>
#include <fstream>
#define WIN32_WINNT 0*050;
#include<Windows.h>
#include<string>
using namespace std;
struct player
{
	string name;
	char symbol;
	int nowins;
	int score;
}p[2];
char board[8][8];
int turn = 0;
int choose;
fstream score_file;
bool c = true;
void display();
void empty();
int checky(int x);
bool checkwin(int x, int y, int nplayer);
void emptyPlaces();
void filewrite(int w);
void scores();
void gotoxy(int newx, int newy);
void drawframe(int f);
void drawlogo();
void menu();
void game(bool, bool);
void console_size(int x, int y);
void AI(int &x, int y);
int main()
{
	console_size(600, 800);
	drawlogo();
	while (c)
	{
		system("cls");
		menu();
		system("cls");
		switch (choose)
		{
		case 1:
		{
			game(false, false);
			break;
		}
		case 2:
		{
			int num;
			system("cls");
			system("color 1A");
			drawframe(68);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
			gotoxy(28, 17);
			cout << "                     ";
			gotoxy(28, 18);
			cout << " 1:      EASY        " << endl;
			gotoxy(28, 19);
			cout << "                     ";
			////////////////////////////////////////////////////////////////////
			gotoxy(28, 25);
			cout << "                     ";
			gotoxy(28, 26);
			cout << " 2:      HARD        " << endl;
			gotoxy(28, 27);
			cout << "                     ";
			/////////////////////////////////////////////////////////////////////
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);

			while (true)
			{
				gotoxy(39, 34);
				cout << "              ";
				gotoxy(39, 34);
				cin >> num;
				switch (num)
				{
				case 1:
				{
					game(true, false);
					break;
				}
				case 2:
				{
					game(true, true);
					break;
				}
				default:
				{
					gotoxy(30, 40);
					cout << "Choose between 1 and 2" << endl;
				}
				}
				break;
			}
			break;
		}
		case 3:
		{
			system("color 06");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "Scores of players! :" << endl;
			scores();
			gotoxy(25, 23);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
			system(" pause");
			break;
		}
		case 4:
		{
			system("color 97");
			drawframe(170);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 960);
			gotoxy(30, 2);
			cout << " Connect Four Game ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 144);
			gotoxy(28, 3);
			cout << "=======================";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 960);
			gotoxy(34, 6);
			cout << "How to win?";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159);
			gotoxy(4, 12);
			cout << "To win this game you have to connect four sympoles togeather horizontally";
			gotoxy(4, 13);
			cout << ",vertivally or diagonally.";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 144);
			gotoxy(6, 15);
			cout << "=====================================================================";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 960);
			gotoxy(36, 16);
			cout << "Score !";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159);
			gotoxy(4, 21);
			cout << "If you connected them vertically or horizontally you get 500 points.";
			gotoxy(4, 22);
			cout << "If you connected them diagonally you get 1000 points.";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 144);
			gotoxy(6, 24);
			cout << "=====================================================================";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 960);
			gotoxy(32, 25);
			cout << "Available modes";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159);
			gotoxy(4, 30);
			cout << "(PVP) mode : Player Versus Player";
			gotoxy(4, 32);
			cout << "(PVC) mode : Player Versus Computer";
			gotoxy(27, 34);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 153);
			system("pause");
			break;
		}
		case 5:
		{
			system("color 45");
			drawframe(170);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 75);
			gotoxy(34, 2);
			cout << "Credits";
			gotoxy(32, 3);
			cout << "============";
			gotoxy(25, 11);
			cout << " Abdelrahman Mohammed Ahmed.";
			gotoxy(25, 17);
			cout << " Aladdin Abdelrahman Elkashawy. ";
			gotoxy(25, 23);
			cout << " Abdelrahman Yousri Elsalahy.";
			gotoxy(25, 29);
			cout << " Mohammed Tarek Alatroush.";
			gotoxy(25, 35);
			cout << " Yahia Ahmed Borhan.";
			gotoxy(25, 41);
			cout << " Mahmoud Sayed Ibrahim.";
			gotoxy(27, 45);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 68);
			system("pause");
			break;
		}
		case 6:
		{
			system("color 0A");
			char ans;
			gotoxy(20, 20);
			cout << " ARE YOU SURE YOU WANT TO EXIT ?(Y/N) :  ";
			cin >> ans;
			if (ans == 'y' || ans == 'Y')
			{
				system("cls");
				c = false;
			}
			break;
		}
		default:
		{
			cout << "Choose between 1 and 6" << endl;
			break;
		}
		}
	}
	system("color 0A");
	gotoxy(30, 20);

	cout << " Thanks for playing " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	gotoxy(0, 20);
}
void empty()
{

	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
			board[a][b] = ' ';

	}
}
void display()
{

	int count = 8;
	cout << " ==============================================================================" << endl;
	cout << "\n\n                1      2      3      4      5      6      7      8" << endl;
	for (int i = 7; i >= 0; i--)
	{

		cout << "               ";
		for (int b = 0; b < 8; b++) cout << char(218) << char(196) << char(191) << "    ";
		cout << '\n';
		cout << "             " << count << " ";
		for (int b = 0; b < 8; b++) cout << char(179) << board[b][i] << char(179) << "    ";
		cout << endl << "               ";
		for (int b = 0; b < 8; b++) cout << char(192) << char(196) << char(217) << "    ";
		cout << '\n';
		count--;
	}
	cout << endl << endl;
	cout << " ==============================================================================" << endl;
	cout << " Empty places :" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
	emptyPlaces();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	cout << " ==============================================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 170);
	gotoxy(10, 1);
	cout << "                                                             ";
	for (int i = 2; i < 30; i++)
	{
		gotoxy(10, i);
		cout << "  ";
		gotoxy(69, i);
		cout << "  ";
	}
	gotoxy(11, 29);
	cout << "                                                           ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	gotoxy(0, 41);
}
int checky(int x)
{
	int y;
	if (board[x - 1][7] != ' ')
	{
		y = -1;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (board[x - 1][i] == ' ')
			{
				y = i;
				break;
			}

		}
	}
	return y;

}
bool checkwin(int x, int y, int npalyer)
{
	bool win = true;
	for (int v = 0; v < 5; v++)
	{
		if (board[x - 1][v] == p[npalyer].symbol&&
			board[x - 1][v + 1] == p[npalyer].symbol&&
			board[x - 1][v + 2] == p[npalyer].symbol&&
			board[x - 1][v + 3] == p[npalyer].symbol)
		{
			win = false;
			p[turn].score += 500;
			break;
		}
		if (board[v][y] == p[npalyer].symbol&&
			board[v + 1][y] == p[npalyer].symbol&&
			board[v + 2][y] == p[npalyer].symbol&&
			board[v + 3][y] == p[npalyer].symbol)
		{
			win = false;
			p[turn].score += 500;
			break;
		}


		if (((x - 1) - 3 + v) >= 0 && (y - 3 + v) >= 0 &&
			((x - 1) + v) <= 7 && (y + v) <= 7 &&
			board[(x - 1) - 3 + v][y - 3 + v] == p[npalyer].symbol&&
			board[(x - 1) - 2 + v][y - 2 + v] == p[npalyer].symbol&&
			board[(x - 1) - 1 + v][y - 1 + v] == p[npalyer].symbol&&
			board[(x - 1) + v][y + v] == p[npalyer].symbol)
		{
			win = false;
			p[turn].score += 1000;
			break;
		}
		if (((x - 1) - 3 + v) >= 0 && (y + 3 - v) <= 7 &&
			((x - 1) + v) <= 7 && (y - v) >= 0 &&
			board[(x - 1) - 3 + v][y + 3 - v] == p[npalyer].symbol&&
			board[(x - 1) - 2 + v][y + 2 - v] == p[npalyer].symbol&&
			board[(x - 1) - 1 + v][y + 1 - v] == p[npalyer].symbol&&
			board[(x - 1) + v][y - v] == p[npalyer].symbol)
		{
			win = false;
			p[turn].score += 1000;
			break;
		}

	}
	return win;
}
void emptyPlaces()
{
	for (int i = 0; i < 8; i++)
	{
		cout << "                ";
		for (int k = 0; k < 8; k++)
		{
			if (board[i][k] == ' ')
			{
				cout << "(" << i + 1 << "," << k + 1 << ") ";

			}

		}
		cout << endl;
	}
}
void filewrite(int w)
{
	ofstream out("score_file.txt", ios::app);
	out << p[w].name << "         " << p[w].score << endl;
	out.close();
}
void scores()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "Name         score" << endl;
	char cur;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	ifstream in("score_file.txt");
	while (!in.eof())
	{
		in.get(cur);
		cout << cur;
	}
}
void gotoxy(int newx, int newy)
{
	COORD xy;
	xy.X = newx;
	xy.Y = newy;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
void drawframe(int f)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), f);
	cout << "                                                                                  " << endl;
	for (int i = 0; i <= 45;i++)
	{
		cout << "  " << endl;
	}
	cout << "                                                                                " << endl;

	for (int i = 1; i <= 47;i++)
	{
		gotoxy(78, i);
		cout << "  ";
	}

}
void drawlogo()
{
	system("color 70");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 68);
	for (int i = 14; i < 23; i++)
	{
		gotoxy(5, i);
		cout << "                                                                     ";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
	gotoxy(8, 15);
	cout << "       " << endl;
	for (int i = 15; i <= 20; i++)
	{
		gotoxy(8, i);
		cout << " " << endl;
	}
	gotoxy(8, 20);
	cout << "       " << endl;
	///////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
	gotoxy(17, 15);
	cout << "      " << endl;
	for (int i = 15; i <= 20; i++)
	{
		gotoxy(17, i);
		cout << " " << endl;
	}
	gotoxy(17, 20);
	cout << "      ";
	for (int i = 15; i <= 20; i++)
	{
		gotoxy(23, i);
		cout << " ";
	}
	//////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
	for (int i = 15; i <= 20; i++)
	{
		gotoxy(26, i);
		cout << " " << endl;
	}
	gotoxy(26, 15);
	cout << "      " << endl;
	for (int i = 15; i <= 25; i++)
	{
		gotoxy(32, i);
		cout << " " << endl;
	}
	////////////////////////////////////////////////

	for (int i = 15; i <= 25; i++)
	{
		gotoxy(35, i);
		cout << " " << endl;
	}
	gotoxy(35, 15);
	cout << "       " << endl;
	for (int i = 15; i <= 20; i++)
	{
		gotoxy(41, i);
		cout << " " << endl;
	}
	//////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
	gotoxy(44, 15);
	cout << "       " << endl;
	for (int i = 15; i <= 20; i++)
	{
		gotoxy(44, i);
		cout << " " << endl;
	}
	for (int i = 15; i <= 17; i++)
	{
		gotoxy(51, i);
		cout << " " << endl;
	}

	gotoxy(44, 17);
	cout << "       " << endl;
	gotoxy(44, 20);
	cout << "        " << endl;
	////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
	gotoxy(54, 15);
	cout << "       " << endl;
	for (int i = 15; i <= 20; i++)
	{
		gotoxy(54, i);
		cout << " " << endl;
	}
	gotoxy(54, 20);
	cout << "       " << endl;
	///////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
	gotoxy(63, 15);
	cout << "        " << endl;
	for (int i = 13; i <= 20; i++)
	{
		gotoxy(65, i);
		cout << "  ";
	}
	gotoxy(65, 20);
	cout << "     ";
	//////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 68);
	for (int i = 23; i <= 27; i++)
	{
		gotoxy(33, i);
		cout << "  ";
	}
	gotoxy(33, 27);
	cout << "       ";
	for (int i = 25; i <= 30; i++)
	{
		gotoxy(40, i);
		cout << "  ";
	}
	/////////////////////////////////////////
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 113);
	gotoxy(55, 34);
	cout << " By ~DECODE TALKERS~";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 119);
	gotoxy(25, 46);
	system("pause");
}
void menu()
{
	system("color 70");
	gotoxy(25, 3);
	cout << "Enter your choice's number";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	gotoxy(28, 8);
	cout << "                     ";
	gotoxy(28, 9);
	cout << " 1: START GAME (PVP) " << endl;
	gotoxy(28, 10);
	cout << "                     ";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
	gotoxy(28, 14);
	cout << "                     ";
	gotoxy(28, 15);
	cout << " 2: START GAME (PVC) " << endl;
	gotoxy(28, 16);
	cout << "                     ";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(28, 20);
	cout << "                     ";
	gotoxy(28, 21);
	cout << " 3:  HALL OF FAME    " << endl;
	gotoxy(28, 22);
	cout << "                     ";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 155);
	gotoxy(28, 26);
	cout << "                     ";
	gotoxy(28, 27);
	cout << " 4:  HOW TO PLAY     " << endl;
	gotoxy(28, 28);
	cout << "                     ";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
	gotoxy(28, 32);
	cout << "                     ";
	gotoxy(28, 33);
	cout << " 5:    CREDITS       " << endl;
	gotoxy(28, 34);
	cout << "                     ";
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(28, 38);
	cout << "                     ";
	gotoxy(28, 39);
	cout << " 6:     EXIT         " << endl;
	gotoxy(28, 40);
	cout << "                     ";
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gotoxy(0, 0);
	drawframe(68);
	while (true)
	{
		gotoxy(38, 42);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 118);
		cin >> choose;
		if (choose > 6 || choose < 1)
		{
			gotoxy(32, 44);
			cout << "Enter a valid number";
			gotoxy(32, 42);
			cout << "             ";
			gotoxy(32, 42);
		}
		else
			break;
	}
}
void game(bool vs, bool level)
{
	int w = 0;
	system("color 1A");
	score_file.open("scores.txt", ios::app);
	empty();
	p[0].nowins = 0;
	p[1].nowins = 0;
	p[0].score = 0;
	p[1].score = 0;
	p[0].symbol = 'X';
	p[1].symbol = 'O';
	system("cls");
	drawframe(68);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	if (vs == false)
	{
		gotoxy(10, 10);
		cout << "Enter the name of player 1 :";
		cin >> p[0].name;
		gotoxy(10, 15);
		cout << "Enter the name of player 2 :";
		cin >> p[1].name;
		cout << endl;
	}
	else
	{
		gotoxy(10, 15);
		cout << "Enter your name :";
		cin >> p[0].name;
		p[1].name = "Computer";
	}
	system("cls");
	system("color 1F");

	int tcheck = 0, x, y;
	bool a = true;
	do {
		tcheck++;
		if (tcheck == 65)
		{
			a = false;
		}
		display();
		if (tcheck % 2 == 1)
		{
			turn = 0;
		}
		else
		{
			turn = 1;
		}

		while (true)
		{
			if (a == false)
			{
				break;
			}

			if (vs == false)
			{
				cout << p[turn].name << " please enter a column number:";
				cin >> x;

			}
			else
			{
				if (turn == 0)
				{
					cout <<
						p[turn].name << " please enter a column number:";
					cin >> x;


				}
				else
				{
					if (level == true)
						AI(x, y);
					else
					{
						x = (rand() % 8) + 1;

					}
				}
			}
			y = checky(x);
			if (x > 8 || x < 1)
			{
				cout << "Invalid place" << endl;
			}
			else if (y == -1)
			{
				cout << " This column is full , please try again " << endl;
			}
			else
				break;
		}

		board[x - 1][y] = p[turn].symbol;

		if (a != false)
			a = checkwin(x, y, turn);

		if (a == false)
		{
			if (tcheck == 65)
			{
				cout << "\nDraw !!!\n";
			}
			else
			{
				system("cls");
				display();
				if (vs == false)
					cout << p[turn].name << " wins this turn.";
				else
					if (turn == 0)
					{
						cout << "You win this turn.";
					}
					else
					{
						cout << " Computer wins this turn.";
					}

				p[turn].nowins++;
				cout << "\n===========================================\n";
			}
			if (p[0].score >= p[1].score)
			{
				cout << p[0].name << endl << "Number of wins:" << p[0].nowins << "           " << "score:" << p[0].score << endl;
				cout << p[1].name << endl << "Number of wins:" << p[1].nowins << "           " << "score:" << p[1].score;
				w = 0;
			}

			else if (p[0].score <= p[1].score)
			{
				cout << p[1].name << endl << "Number of wins:" << p[1].nowins << "           " << "score:" << p[1].score << endl;
				cout << p[0].name << endl << "Number of wins:" << p[0].nowins << "           " << "score:" << p[0].score;
				if (vs == false)
					w = 1;
				else
					w = 0;

			}

			cout << "\n===========================================\n";
			char ans;
			cout << "Do you want to continue?(y/n) :  ";
			cin >> ans;
			if (ans == 'y' || ans == 'Y')
			{
				a = true;
				empty();
				tcheck = 0;
			}
			system("cls");

		}

		system("cls");
	} while (a);
	char ans2;
	cout << " Do you want to save your score?(Y/N) : ";
	cin >> ans2;
	if (ans2 == 'y' || ans2 == 'Y')
	{
		filewrite(w);
	}
	cout << p[0].name << " won " << p[0].nowins << " times and scored " << p[0].score << " points" << endl;
	cout << p[1].name << " won " << p[1].nowins << " times and scored " << p[1].score << " points" << endl;
	cout << " =========================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 17);
	system("pause");
}
void console_size(int x, int y)
{
	HWND console = GetConsoleWindow();
	RECT dim;
	GetWindowRect(console, &dim);
	MoveWindow(console, dim.left, dim.top, x, y, true);
}
void AI(int&x, int y)
{
	bool win = false;
	for (int v = 0, npalyer = 0;v < 5; npalyer = 0, v++)
	{
		if (board[x - 1][v] == p[npalyer].symbol&&
			board[x - 1][v + 1] == p[npalyer].symbol&&
			board[x - 1][v + 2] == p[npalyer].symbol&&
			board[x - 1][v + 3] == ' ')
		{
			win = true;
			break;
		}
		if (board[v][y] == p[npalyer].symbol&&
			board[v + 1][y] == p[npalyer].symbol&&
			board[v + 2][y] == p[npalyer].symbol&&
			board[v + 3][y] == ' '&&
			y - 1 == -1)
		{
			win = true;
			x = (v + 3 + 1);
			break;
		}
		if (board[v][y] == p[npalyer].symbol&&
			board[v + 1][y] == p[npalyer].symbol&&
			board[v + 2][y] == p[npalyer].symbol&&
			board[v + 3][y] == ' ' &&
			board[v + 3][y] == 'O'
			)
		{
			win = true;
			x = (v + 3 + 1);
			break;
		}
		if (board[v][y] == p[npalyer].symbol&&
			board[v + 1][y] == p[npalyer].symbol&&
			board[v + 2][y] == p[npalyer].symbol&&
			board[v + 3][y] == ' ' &&
			board[v + 3][y] == p[npalyer].symbol)
		{
			win = true;
			x = (v + 3 + 1);
			break;
		}
		if (board[7 - v][y] == p[npalyer].symbol&&
			board[6 - v][y] == p[npalyer].symbol&&
			board[5 - v][y] == p[npalyer].symbol&&
			board[4 - v][y] == ' '&&
			y - 1 == 0
			)
		{
			win = true;
			x = (4 - v + 1);
			break;
		}
		if (board[7 - v][y] == p[npalyer].symbol&&
			board[6 - v][y] == p[npalyer].symbol&&
			board[5 - v][y] == p[npalyer].symbol&&
			board[4 - v][y] == ' '&&
			board[4 - v][y - 1] == p[npalyer].symbol
			)
		{
			win = true;
			x = (4 - v + 1);
			break;
		}
		if (board[7 - v][y] == p[npalyer].symbol&&
			board[6 - v][y] == p[npalyer].symbol&&
			board[5 - v][y] == p[npalyer].symbol&&
			board[4 - v][y] == ' '&&
			board[4 - v][y - 1] == 'O'
			)
		{
			win = true;
			x = (4 - v + 1);
			break;
		}
	}
	if (win == false)
		x = (rand() % 8) + 1;
}