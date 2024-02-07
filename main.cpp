#include <fstream>
#include <iostream>
using namespace std;

void display();
void instructions();
void readMaze(char **dptr, int &row, int &col, ifstream &fin);
void printMaze(char **dptr, int row, int col);
bool move(char **dptr, int &x, int &y, int &score, int &check, int &lives, int &click, char &moves);
char** regrow(char **o_dptr, int&row, int&col);
void copy_data(char **o_dptr, char **n_dptr, int &row, int &col);
void del_dptr(char **o_dptr, int&row);
void easy(ifstream &fin, ofstream &fout, char name[], int&score,int&check, int&lives, int&click, char&moves, int&row, int&col, int&x, int&y, char**dptr);
void medium(ifstream &fin, ofstream &fout, char name[], int&score, int&check, int&lives, int&click, char&moves, int&row, int&col, int&x, int&y, char**dptr);
void hard(ifstream &fin, ofstream &fout, char name[], int&score, int&check, int&lives, int&click, char&moves, int&row, int&col, int&x, int&y, char**dptr);

int main()
{
	ifstream fin;
	ofstream fout;

	fout.open("score.txt",ios::app);

	int option = 0, score = 0, check = 0, lives = 0, click = 0;
	char name[10] = { '\0' };
	char moves = '\0';

	int row = 6, col = 6;
	int x, y;

	char **dptr = new char *[row];
	for (int i = 0; i < row; i++)
	{
		dptr[i] = new char[col];
	}

	cout << "Enter your name: ";
	cin.getline(name, 10);

	display();
	cin >> option;

	if (option == 1)
	{
		easy(fin, fout, name, score, check, lives, click, moves, row, col, x, y, dptr);
	}

	else if (option == 2)
	{
		medium(fin, fout, name, score, check, lives, click, moves, row, col, x, y, dptr);
	}

	else if (option == 3)
	{
		hard(fin, fout, name, score, check, lives, click, moves, row, col, x, y, dptr);
	}
	else
	{
		cout << "Wrong Command" << endl;
	}

	fin.close();
	fout.close();

	system("pause");
	return 0;
}


void easy(ifstream &fin, ofstream &fout, char name[], int&score,int&check, int&lives, int&click, char&moves, int&row, int&col, int&x, int&y, char**dptr)
{
	fin.open("easy.txt");

	if (!fin.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		x = 0;
		y = 0;

		readMaze(dptr, row, col, fin);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (dptr[i][j] == 'S')
				{
					x = i;
					y = j;
				}
			}
		}

		system("cls");
		printMaze(dptr, row, col);
		instructions();

		check = 0;
		lives = 3;
		click = 15;
		bool flag = move(dptr, x, y, score, check, lives, click, moves);

		while (true)
		{
			if (flag == false)
			{
				if (moves == 'R' || moves == 'r')
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Game Resumed" << endl;
					bool flag = move(dptr, x, y, score, check, lives, click, moves);
				}
				else if (moves == 'P' || moves == 'p')
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "GAME PAUSED" << endl;
					cout << "Press 'R' to 'Resume' your game" << endl;
					cout << "Press 'N' to resume from start" << endl;
					bool flag = move(dptr, x, y, score, check, lives, click, moves);
				}
				else if (moves == 'N' || moves == 'n')
				{
					fin.close();
					fin.open("easy.txt");

					if (!fin.is_open())
					{
						cout << "File Not Found" << endl;
					}
					else
					{
						x = 0;
						y = 0;

						readMaze(dptr, row, col, fin);

						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (dptr[i][j] == 'S')
								{
									x = i;
									y = j;
								}
							}
						}

						system("cls");
						printMaze(dptr, row, col);
						cout << "\nNew Game" << endl;

						check = 0;
						lives = 3;
						click = 15;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);

						while (true)
						{
							if (flag == false)
							{
								if (moves == 'R' || moves == 'r')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game Resumed" << endl;
									bool flag = move(dptr, x, y, score, check, lives, click, moves);
								}
								else if (moves == 'P' || moves == 'p')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "GAME PAUSED" << endl;
									cout << "Press 'R' to 'Resume' your game" << endl;
									cout << "Press 'N' to resume from start" << endl;
									bool flag = move(dptr, x, y, score, check, lives, click, moves);
								}
								else if (moves == 'N' || moves == 'n')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (check != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else
								{
									if (click == 0 && lives == 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Moves left: " << click << endl;
										cout << "Lives left: " << lives << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (lives == 0 && click != 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "You lost you 3 lives" << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (click == 0 && lives != 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Moves left: " << click << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (click >= 0 && click<15)
									{
										if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
										{
											system("cls");
											printMaze(dptr, row, col);
											cout << "Invalid move." << endl;
											bool flag = move(dptr, x, y, score, check, lives, click, moves);
										}
										else
										{
											system("cls");
											printMaze(dptr, row, col);
											cout << "You enter 1 move" << endl;
											cout << "Moves left: " << click << endl;
											cout << "Lives left: " << lives << endl;
											bool flag = move(dptr, x, y, score, check, lives, click, moves);
										}
									}
								}
							}
							if (flag == true)
							{
								if (click == 0 && lives == 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Moves left: " << click << endl;
									cout << "Lives left: " << lives << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (lives == 0 && click != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "You lost you 3 lives" << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (click == 0 && lives != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Moves left: " << click << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (click >= 0 && click < 15)
								{
									if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Invalid move." << endl;
										bool flag = move(dptr, x, y, score, check, lives, click, moves);
									}
									else
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "You enter 1 move" << endl;
										cout << "Moves left: " << click << endl;
										cout << "Lives left: " << lives << endl;
										bool flag = move(dptr, x, y, score, check, lives, click, moves);
									}
								}
							}
						}
					}
				}
				else if (check != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else
				{
					if (click == 0 && lives == 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Moves left: " << click << endl;
						cout << "Lives left: " << lives << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (lives == 0 && click != 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "You lost you 3 lives" << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (click == 0 && lives != 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Moves left: " << click << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (click >= 0 && click<15)
					{
						if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
						{
							system("cls");
							printMaze(dptr, row, col);
							cout << "Invalid move." << endl;
							cout << "\n\nPress 'E' to end your game" << endl;
							bool flag = move(dptr, x, y, score, check, lives, click, moves);
						}
						else
						{
							system("cls");
							printMaze(dptr, row, col);
							cout << "You enter 1 move" << endl;
							cout << "Moves left: " << click << endl;
							cout << "Lives left: " << lives << endl;;
							bool flag = move(dptr, x, y, score, check, lives, click, moves);
						}
					}
				}
			}
			if (flag == true)
			{
				if (click == 0 && lives == 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Moves left: " << click << endl;
					cout << "Lives left: " << lives << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (lives == 0 && click != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "You lost you 3 lives" << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (click == 0 && lives != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Moves left: " << click << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (click >= 0 && click < 15)
				{
					if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Invalid move." << endl;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);
					}
					else
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "You enter 1 move" << endl;
						cout << "Moves left: " << click << endl;
						cout << "Lives left: " << lives << endl;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);
					}
				}
			}
		}
	}
}
void medium(ifstream &fin, ofstream &fout, char name[], int&score,int&check, int&lives, int&click, char&moves, int&row, int&col, int&x, int&y, char**dptr)
{
	fin.open("medium.txt");

	if (!fin.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		x = 0;
		y = 0;

		for (int i = 0; i < 6; i++)
		{
			dptr = regrow(dptr, row, col);
			row++;
			col++;
		}

		readMaze(dptr, row, col, fin);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (dptr[i][j] == 'S')
				{
					x = i;
					y = j;
				}
			}
		}

		system("cls");
		printMaze(dptr, row, col);
		instructions();

		check = 0;
		lives = 3;
		click = 20;
		bool flag = move(dptr, x, y, score, check, lives, click,moves);
		while (true)
		{
			if (flag == false)
			{
				if (moves == 'R' || moves == 'r')
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Game Resumed" << endl;
					bool flag = move(dptr, x, y, score, check, lives, click, moves);
				}
				else if (moves == 'P' || moves == 'p')
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "GAME PAUSED" << endl;
					cout << "Press 'R' to 'Resume' your game" << endl;
					cout << "Press 'N' to resume from start" << endl;
					bool flag = move(dptr, x, y, score, check, lives, click, moves);
				}
				else if (moves == 'N' || moves == 'n')
				{
					fin.close();
					fin.open("easy.txt");

					if (!fin.is_open())
					{
						cout << "File Not Found" << endl;
					}
					else
					{
						x = 0;
						y = 0;

						readMaze(dptr, row, col, fin);

						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (dptr[i][j] == 'S')
								{
									x = i;
									y = j;
								}
							}
						}

						system("cls");
						printMaze(dptr, row, col);
						cout << "\nNew Game" << endl;

						check = 0;
						lives = 3;
						click = 20;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);

						while (true)
						{
							if (flag == false)
							{
								if (moves == 'R' || moves == 'r')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game Resumed" << endl;
									bool flag = move(dptr, x, y, score, check, lives, click, moves);
								}
								else if (moves == 'P' || moves == 'p')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "GAME PAUSED" << endl;
									cout << "Press 'R' to 'Resume' your game" << endl;
									cout << "Press 'N' to resume from start" << endl;
									bool flag = move(dptr, x, y, score, check, lives, click, moves);
								}
								else if (moves == 'N' || moves == 'n')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (check != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else
								{
									if (click == 0 && lives == 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Moves left: " << click << endl;
										cout << "Lives left: " << lives << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (lives == 0 && click != 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "You lost you 3 lives" << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (click == 0 && lives != 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Moves left: " << click << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (click >= 0 && click<20)
									{
										if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
										{
											system("cls");
											printMaze(dptr, row, col);
											cout << "Invalid move." << endl;
											bool flag = move(dptr, x, y, score, check, lives, click, moves);
										}
										else
										{
											system("cls");
											printMaze(dptr, row, col);
											cout << "You enter 1 move" << endl;
											cout << "Moves left: " << click << endl;
											cout << "Lives left: " << lives << endl;
											bool flag = move(dptr, x, y, score, check, lives, click, moves);
										}
									}
								}
							}
							if (flag == true)
							{
								if (click == 0 && lives == 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Moves left: " << click << endl;
									cout << "Lives left: " << lives << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (lives == 0 && click != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "You lost you 3 lives" << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (click == 0 && lives != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Moves left: " << click << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (click >= 0 && click < 20)
								{
									if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Invalid move." << endl;
										bool flag = move(dptr, x, y, score, check, lives, click, moves);
									}
									else
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "You enter 1 move" << endl;
										cout << "Moves left: " << click << endl;
										cout << "Lives left: " << lives << endl;
										bool flag = move(dptr, x, y, score, check, lives, click, moves);
									}
								}
							}
						}
					}
				}
				else if (check != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else
				{
					if (click == 0 && lives == 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Moves left: " << click << endl;
						cout << "Lives left: " << lives << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (lives == 0 && click != 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "You lost you 3 lives" << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (click == 0 && lives != 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Moves left: " << click << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (click >= 0 && click<20)
					{
						if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
						{
							system("cls");
							printMaze(dptr, row, col);
							cout << "Invalid move." << endl;
							bool flag = move(dptr, x, y, score, check, lives, click, moves);
						}
						else
						{
							system("cls");
							printMaze(dptr, row, col);
							cout << "You enter 1 move" << endl;
							cout << "Moves left: " << click << endl;
							cout << "Lives left: " << lives << endl;
							bool flag = move(dptr, x, y, score, check, lives, click, moves);
						}
					}
				}
			}
			if (flag == true)
			{
				if (click == 0 && lives == 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Moves left: " << click << endl;
					cout << "Lives left: " << lives << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (lives == 0 && click != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "You lost you 3 lives" << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (click == 0 && lives != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Moves left: " << click << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (click >= 0 && click < 20)
				{
					if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Invalid move." << endl;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);
					}
					else
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "You enter 1 move" << endl;
						cout << "Moves left: " << click << endl;
						cout << "Lives left: " << lives << endl;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);
					}
				}
			}
		}
	}
}
void hard(ifstream &fin, ofstream &fout, char name[], int&score,int&check, int&lives, int&click, char&moves, int&row, int&col, int&x, int&y, char**dptr)
{
	fin.open("hard.txt");

	if (!fin.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		x = 0;
		y = 0;

		for (int i = 0; i < 10; i++)
		{
			dptr = regrow(dptr, row, col);
			row++;
			col++;
		}

		readMaze(dptr, row, col, fin);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (dptr[i][j] == 'S')
				{
					x = i;
					y = j;
				}
			}
		}

		system("cls");
		printMaze(dptr, row, col);
		instructions();

		check = 0;
		lives = 3;
		click = 30;
		bool flag = move(dptr, x, y, score, check, lives, click,moves);

		while (true)
		{
			if (flag == false)
			{
				if (moves == 'R' || moves == 'r')
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Game Resumed" << endl;
					bool flag = move(dptr, x, y, score, check, lives, click, moves);
				}
				else if (moves == 'P' || moves == 'p')
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "GAME PAUSED" << endl;
					cout << "Press 'R' to 'Resume' your game" << endl;
					cout << "Press 'N' to resume from start" << endl;
					bool flag = move(dptr, x, y, score, check, lives, click, moves);
				}
				else if (moves == 'N' || moves == 'n')
				{
					fin.close();
					fin.open("easy.txt");

					if (!fin.is_open())
					{
						cout << "File Not Found" << endl;
					}
					else
					{
						x = 0;
						y = 0;

						readMaze(dptr, row, col, fin);

						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (dptr[i][j] == 'S')
								{
									x = i;
									y = j;
								}
							}
						}

						system("cls");
						printMaze(dptr, row, col);
						cout << "\nNew Game" << endl;

						check = 0;
						lives = 3;
						click = 30;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);

						while (true)
						{
							if (flag == false)
							{
								if (moves == 'R' || moves == 'r')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game Resumed" << endl;
									bool flag = move(dptr, x, y, score, check, lives, click, moves);
								}
								else if (moves == 'P' || moves == 'p')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "GAME PAUSED" << endl;
									cout << "Press 'R' to 'Resume' your game" << endl;
									cout << "Press 'N' to resume from start" << endl;
									bool flag = move(dptr, x, y, score, check, lives, click, moves);
								}
								else if (moves == 'N' || moves == 'n')
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (check != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else
								{
									if (click == 0 && lives == 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Moves left: " << click << endl;
										cout << "Lives left: " << lives << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (lives == 0 && click != 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "You lost you 3 lives" << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (click == 0 && lives != 0)
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Moves left: " << click << endl;
										cout << "Game End!" << endl;
										cout << "Name:" << name << "  Score: " << score << endl;
										fout << "Name:" << name << "  Score: " << score << endl;
										break;
									}
									else if (click >= 0 && click<30)
									{
										if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
										{
											system("cls");
											printMaze(dptr, row, col);
											cout << "Invalid move." << endl;
											bool flag = move(dptr, x, y, score, check, lives, click, moves);
										}
										else
										{
											system("cls");
											printMaze(dptr, row, col);
											cout << "You enter 1 move" << endl;
											cout << "Moves left: " << click << endl;
											cout << "Lives left: " << lives << endl;
											bool flag = move(dptr, x, y, score, check, lives, click, moves);
										}
									}
								}
							}
							if (flag == true)
							{
								if (click == 0 && lives == 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Moves left: " << click << endl;
									cout << "Lives left: " << lives << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (lives == 0 && click != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "You lost you 3 lives" << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (click == 0 && lives != 0)
								{
									system("cls");
									printMaze(dptr, row, col);
									cout << "Moves left: " << click << endl;
									cout << "Game End!" << endl;
									cout << "Name:" << name << "  Score: " << score << endl;
									fout << "Name:" << name << "  Score: " << score << endl;
									break;
								}
								else if (click >= 0 && click < 30)
								{
									if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "Invalid move." << endl;
										bool flag = move(dptr, x, y, score, check, lives, click, moves);
									}
									else
									{
										system("cls");
										printMaze(dptr, row, col);
										cout << "You enter 1 move" << endl;
										cout << "Moves left: " << click << endl;
										cout << "Lives left: " << lives << endl;
										bool flag = move(dptr, x, y, score, check, lives, click, moves);
									}
								}
							}
						}
					}
				}
				else if (check != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else
				{
					if (click == 0 && lives == 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Moves left: " << click << endl;
						cout << "Lives left: " << lives << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (lives == 0 && click != 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "You lost you 3 lives" << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (click == 0 && lives != 0)
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Moves left: " << click << endl;
						cout << "Game End!" << endl;
						cout << "Name:" << name << "  Score: " << score << endl;
						fout << "Name:" << name << "  Score: " << score << endl;
						break;
					}
					else if (click >= 0 && click<30)
					{
						if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
						{
							system("cls");
							printMaze(dptr, row, col);
							cout << "Invalid move." << endl;
							bool flag = move(dptr, x, y, score, check, lives, click, moves);
						}
						else
						{
							system("cls");
							printMaze(dptr, row, col);
							cout << "You enter 1 move" << endl;
							cout << "Moves left: " << click << endl;
							cout << "Lives left: " << lives << endl;
							bool flag = move(dptr, x, y, score, check, lives, click, moves);
						}
					}
				}
			}
			if (flag == true)
			{
				if (click == 0 && lives == 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Moves left: " << click << endl;
					cout << "Lives left: " << lives << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (lives == 0 && click != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "You lost you 3 lives" << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (click == 0 && lives != 0)
				{
					system("cls");
					printMaze(dptr, row, col);
					cout << "Moves left: " << click << endl;
					cout << "Game End!" << endl;
					cout << "Name:" << name << "  Score: " << score << endl;
					fout << "Name:" << name << "  Score: " << score << endl;
					break;
				}
				else if (click >= 0 && click < 30)
				{
					if (moves != 'W' && moves != 'w' && moves != 'S' && moves != 's' && moves != 'D' && moves != 'd' && moves != 'A'&& moves != 'a')
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "Invalid move." << endl;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);
					}
					else
					{
						system("cls");
						printMaze(dptr, row, col);
						cout << "You enter 1 move" << endl;
						cout << "Moves left: " << click << endl;
						cout << "Lives left: " << lives << endl;
						bool flag = move(dptr, x, y, score, check, lives, click, moves);
					}
				}
			}
		}
	}
}
void display()
{
	cout << "\nSelect the Game mode" << endl;
	cout << "\nPress 1 for Easy mode" << endl;
	cout << "Press 2 for Medium mode" << endl;
	cout << "Press 3 for Hard mode" << endl;
	cout << "\nCommand: ";
}
void instructions()
{
	cout << "\nRead the instructions carefully" << endl;
	cout << "\nThe Character '*' is path free to go" << endl;
	cout << "The Character '|' is blockage in path" << endl;
	cout << "The Character '+' is Monster creature in path" << endl;
	cout << "\npress 'W' for moving Up" << endl;
	cout << "press 'A' for moving Left" << endl;
	cout << "press 'D' for moving Right" << endl;
	cout << "press 'S' for moving Down" << endl;
	cout << "\n\nPress 'E' to end your game" << endl;
	cout << "Press 'P' to 'Pause' your game" << endl;
	cout << "Press 'R' to 'Resume' your game"<< endl;
	cout << "Press 'N' to start your new game" << endl;
}
void readMaze(char **dptr, int &row, int &col, ifstream &fin)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fin >> dptr[i][j];
		}
	}
}
void printMaze(char **dptr, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << dptr[i][j];
		}
		cout << endl;
	}
}
bool move(char **dptr,int &x, int &y, int &score,int &check,int &lives,int &click,char &moves)
{
	cout << "\nEnter your Command (WASD): ";
	cin >> moves;

	if (moves == 'W' || moves == 'w')
	{
		if (dptr[x][y] == 'S' && dptr[x - 1][y] != '|' && dptr[x - 1][y] != '+')
		{
			dptr[x][y] = 'S';
			x--;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
		if (dptr[x - 1][y] == '|')
		{
			click--;
			return false;
		}
		if (dptr[x - 1][y] == '+')
		{
			lives--;
			click--;
			return false;
		}
		if (dptr[x][y] != 'S' && dptr[x - 1][y] == '*')
		{
			dptr[x][y] = '1';
			x--;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
	}
	else if (moves == 'A' || moves == 'a')
	{
		if (dptr[x][y] == 'S' && dptr[x][y - 1] != '|' && dptr[x][y - 1] != '+')
		{
			dptr[x][y] = 'S';
			y--;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
		if (dptr[x][y-1] == '|')
		{
			click--;
			return false;
		}
		if (dptr[x][y-1] == '+')
		{
			lives--;
			click--;
			return false;
		}
		if (dptr[x][y] != 'S' && dptr[x][y - 1] == '*')
		{
			dptr[x][y] = '1';
			y--;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
	}
	else if (moves == 'S' || moves == 's')
	{
		if (dptr[x][y] == 'S' && dptr[x + 1][y] != '|' && dptr[x + 1][y] != '+')
		{
			dptr[x][y] = 'S';
			x++;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
		if (dptr[x + 1][y] == '|')
		{
			click--;
			return false;
		}
		if (dptr[x +1][y] == '+')
		{
			lives--;
			click--;
			return false;
		}
		if (dptr[x][y] != 'S' && dptr[x + 1][y] == '*')
		{
			dptr[x][y] = '1';
			x++;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
	}
	else if (moves == 'D' || moves == 'd')
	{
		if (dptr[x][y] == 'S' && dptr[x][y + 1] != '|' && dptr[x][y + 1] != '+')
		{
			dptr[x][y] = 'S';
			y++;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
		if (dptr[x][y+1] == '|')
		{
			click--;
			return false;
		}
		if (dptr[x][y+1] == '+')
		{
			lives--;
			click--;
			return false;
		}
		if (dptr[x][y] != 'S' && dptr[x][y + 1] == '*')
		{
			dptr[x][y] = '1';
			y++;
			dptr[x][y] = '1';
			click--;
			score++;
			return true;
		}
	}
	else if (moves == 'E' || moves == 'e')
	{
		check++;
		return false;
	}
	else if (moves == 'R' || moves == 'r')
	{
		return false;
	}
	else if (moves == 'P' || moves == 'p')
	{
		return false;
	}
	else if (moves == 'N' || moves == 'n')
	{
		return false;
	}
	else
	{
		return false;
	}
}
char** regrow(char **o_dptr, int&row, int&col)
{
	char **n_dptr = new char *[row + 1];
	for (int i = 0; i < row + 1; i++)
	{
		n_dptr[i] = new char[col + 1];
	}

	copy_data(o_dptr, n_dptr, row, col);
	del_dptr(o_dptr, row);

	return n_dptr;
}
void copy_data(char **o_dptr, char **n_dptr, int &row, int &col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			n_dptr[i][j] = o_dptr[i][j];
		}
	}
}
void del_dptr(char **o_dptr, int&row)
{
	for (int i = 0; i < row; i++)
	{
		delete[] o_dptr[i];
	}
	delete[] o_dptr;
}