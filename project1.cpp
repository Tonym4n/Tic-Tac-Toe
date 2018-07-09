#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <ctime>
#include <cmath>
#include <fstream>
#include <list>
#include <stack>
#define ARGUMENT VALUE
using namespace std;

class ticTacToe
{
	public:
		int choice;												//choice is public is to determine
	private:													//whether player is X or O;
		char player[2];
		char board[9];
		int turn_count;
	public:
		ticTacToe();
		void setup();
		void user_turn();
		void comp_turn();
		void display_board();
		bool status();
};

int main()
{	
	ticTacToe game;
	game.setup();												//intro + decision to play as X or O;
	while(game.status() == true)
	{
		if(game.choice == 0)									//playing as X
		{
			game.display_board();
			game.user_turn();
			if(game.status() == false)
			{
				break;
			}
			game.display_board();
			game.comp_turn();
		}
		else if(game.choice == 1)								//playing as O
		{
			game.comp_turn();
			if(game.status() == false)
			{
				break;
			}
			game.display_board();
			game.user_turn();
			game.display_board();
		}
	}
}

ticTacToe::ticTacToe()
{
	srand(time(NULL));											//initialize psuedo random seed;
	player[0] = 'X';
	player[1] = 'O';
	for(int i = 0; i < 9; i++)
	{
		board[i] = ' ';
	}
	turn_count = 0;
}

void ticTacToe::setup()
{
	cout << "Welcome to TIC TAC TOE." << endl;
	cout << "Use the number pad (1 - 9) to designate your moves." << endl;
	cout << "X will go first. O will go second. " << endl;
	do
	{
		cout << "Would you like to be first or second (ENTER 1 or 2)? ";
		cin >> choice;
	} while(choice != 1 && choice != 2);
	choice--;													//subtract one for easy programming purposes;
	cout << endl;
}

void ticTacToe::user_turn()
{
	int n;
	cout << "Your turn: ";
	cin >> n;
	n -= 1;
	if(n < 0 || n > 8 || board[n] == 'X' || board[n] == 'O')	//if board is full or n is out of range, try again;
	{
		cout << "Invalid move. ";
		user_turn();
	}
	else
	{
		board[n] = player[choice];
		turn_count++;
		cout << endl;
	}
}

void ticTacToe::comp_turn()
{
	int n = rand() % 9;
	if(n < 0 || n > 8 || board[n] == 'X' || board[n] == 'O')	//if board is full or n is out of range, try again;
	{
		comp_turn();
	}
	else
	{
		cout << "Comp turn: " << n + 1 << endl << endl;
		board[n] = player[(choice + 1) % 2];					//the choice not chosen by player;
		turn_count++;
	}
}

void ticTacToe::display_board()
{
	for(int i = 0; i < 9; i += 3)
	{
		if(i % 3 == 0 && i != 0)								//display the following every other row;
		{
			cout << endl << "-+-+-" << endl;
		}
		cout << board[i] << "|" << board[i + 1] << "|" << board[i + 2];
	}
	cout << endl << endl;
}

bool ticTacToe::status()										//determines if game is over or still running;
{
	if((board[0]+board[1]+board[2] == 3*board[0] && board[0] != ' ') || (board[3]+board[4]+board[5] == 3*board[3] && board[3] != ' ')	//initiates if winning combo is detected;
	|| (board[6]+board[7]+board[8] == 3*board[6] && board[6] != ' ') || (board[0]+board[3]+board[6] == 3*board[0] && board[0] != ' ')
	|| (board[1]+board[4]+board[7] == 3*board[1] && board[1] != ' ') || (board[2]+board[5]+board[8] == 3*board[2] && board[2] != ' ')
	|| (board[0]+board[4]+board[8] == 3*board[0] && board[0] != ' ') || (board[2]+board[4]+board[6] == 3*board[2] && board[2] != ' '))
	{
		if((turn_count % 2 == 1 && choice == 0) || (turn_count % 2 == 0 && choice == 1))												//determine who initiated winning combo;
		{
			display_board();
			cout << "You WIN! " << endl;
			return false;
		}
		else if((turn_count % 2 == 0 && choice == 0) || (turn_count % 2 == 1 && choice == 1))
		{
			display_board();
			cout << "You LOSE! " << endl;
			return false;
		}
	}
	else if(turn_count == 9)
	{
		display_board();										//if a winning combo has not been initiated,
		cout << "DRAW! GAME OVER!";								//and this is the 9th turn, it's a draw;
		return false;
	}
	else
	{
		return true;
	}
}
