// Connect4 AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>


class Player {			//should be private with get/set
public:
	char color;
	char name [8] = { 'P','l','a','y','e','r',' ',' ' };
	Player(char color, char number) {	// need to update the constructor if I use it more. 
		this->color = color;
		name[7] = number;
	}

	Player() {
		color = '?';
		name[7] = '?';
	}

	void printName() {
		for (int i = 0; i < 8; i++) {
			std::cout << this->name[i];
		}
	}
};

class Board {
public:
	char board[6][7] = { { ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',} };

	int heights[7] = { 6,6,6,6,6,6,6 };			//remaining room in each column

	void clear() {
		for (int k = 0; k < 7; k++) {
			heights[k] = 6;
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				board[i][j] = ' ';
			}
		}
	}

	// Check to see if the move is a playable move
	// 
	// Parameter column - the column to check for availability. Starts at 0
	// return			- true if move can be played, false if not.

	bool isValid(int column) {
		if (column > 6) {
			return false;
		}
		else if (heights[column] == 0) {
			return false;
		}
		return true;
	}

	// play a move ** should be checked by isValid first **
	// 

	void play(int column, Player player) {		// column starts at 0 
		board[(heights[column] - 1)][column] = player.color;
		heights[column]--;
	}


	bool isWin(int column, Player player) {			//should be called after the move has been made on the board.

		if (dDiagonalWin(column, player.color) > 3) {				// check for descending diagonal win.
			return true;
		}
		else if (aDiagonalWin(column, player.color) > 3) {				// check for ascending diagonal win.
			return true;
		}
		else if (horizontalWin(column, player.color) > 3) {			// check for horizontal win
			return true;
		}
		else if (heights[column] < 3) {					// check for a vertical win only when the height of the column allows it
			if (verticalWin(column, player.color) > 3) {
				return true;
			}
		}
		return false;
	}

	void print() {
		std::cout << "\n  0  1  2  3  4  5  6 ";
		for (int i = 0; i < 6; i++) {
			std::cout << "\n|";
			for (int j = 0; j < 7; j++) {
				std::cout << board[i][j] << " " << "|";
			}

		}
		std::cout << "\n\n\n\n\n\n";
	}
	int verticalWin(int column, char playerColor) {
		int connected = 1;
		int temp = heights[column] + 1;
		while (temp < 6) {
			if (board[temp][column] == playerColor) {
				connected++;
			}
			else {
				return connected;															//** is this how break works?
			}
			temp++;
		}
		return connected;
	}

	int horizontalWin(int column, char playerColor) {
		int connected = 1;
		int temp = heights[column];
		column--;

		while (column >= 0 && board[temp][column] == playerColor) {
			//			std::cout << "looking left at position " << temp << " " << column << "    " << board[temp][column] << " matches " << player.color << "\n";
			connected++;
			column--;
		}
		column = column + connected + 1;
		while (column <= 6 && board[temp][column] == playerColor) {
			//			std::cout << "looking right at position " << temp << " " << column << "   " << board[temp][column] << " matches " << player.color << "\n";
			connected++;
			column++;
		}
		//		std::cout << "found " << connected << "connected";
		return connected;
	}
	int dDiagonalWin(int column, char playerColor) {
		int connected = 1;								// the first item will always be "connected" so just skip searching it
		int tempRow = heights[column] - 1;
		int tempCol = column - 1;

		while (tempCol >= 0 && tempRow >= 0 && board[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking up/left at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol--;
			tempRow--;

		}
		tempCol = column + 1;
		tempRow = heights[column] + 1;
		while (tempCol <= 6 && tempRow <= 5 && board[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking down/right at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol++;
			tempRow++;

		}
		return connected;
	}
	int aDiagonalWin(int column, char playerColor) {
		int connected = 1;								// the first item will always be "connected" so just skip searching it
		int tempRow = heights[column] - 1;
		int tempCol = column + 1;

		while (tempCol <= 6 && tempRow >= 0 && board[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking up/right at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol++;
			tempRow--;

		}
		tempCol = column - 1;
		tempRow = heights[column] + 1;
		while (tempCol >= 0 && tempRow <= 5 && board[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking down/left at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol--;
			tempRow++;

		}
		return connected;
	}


};

class Computer : public Player {
private:
	//AI values:
	int centerValue = 3;
	int edgePenalty = 1;
	int connect2Value = 2;
	int connect3Value = 4;
	int connect4value = 100;


	Computer(char color, char number) {	// need to update the constructor if I use it more. 
		this->color = color;
		name[7] = number;
	}

	int aDiagonalVal(int column, Board board) {						// ascending diagonal value for connections. (All ___Val are clones of each other)
		if (board.aDiagonalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.aDiagonalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.aDiagonalWin(column, this->color) >= 4) {
			return connect4value;
		}
	}

	int dDiagonalVal(int column, Board board) {						// Descending diagonal value for connections. (All ___Val are clones of each other)
		if (board.dDiagonalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.dDiagonalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.dDiagonalWin(column, this->color) >= 4) {
			return connect4value;
		}
	}
	int horizontalVal(int column, Board board) {						//  Horizontal value for connections. (All ___Val are clones of each other)
		if (board.horizontalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.horizontalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.horizontalWin(column, this->color) >= 4) {
			return connect4value;
		}
	}
	int verticalVal(int column, Board board) {						//  Vertical value for connections. (All ___Val are clones of each other)
		if (board.verticalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.verticalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.verticalWin(column, this->color) >= 4) {
			return connect4value;
		}
	}

	int columnVal(int column) {			// for the raw column values, no connections included // should be private

		if (column == 3) {
			return centerValue;
		}
		else if (column == 0 || column == 6) {
			return edgePenalty;
		}
	}

public:
	int evaluateColumn(int column, Board board) {		// only pass on valid columns 

		int value = 0;
		value += (aDiagonalVal(column, board));
		std::cout << "ascending diagonal value is " << (aDiagonalVal(column, board));

		value += (dDiagonalVal(column, board));
		std::cout << "descending diagonal value is " << (dDiagonalVal(column, board));

		value += (horizontalVal(column, board));
		std::cout << "Horizontal value is " << (horizontalVal(column, board));

		value += (verticalVal(column, board));
		std::cout << "vertical value is " << (verticalVal(column, board));

		value += (columnVal(column));
		std::cout << "column value is " << (columnVal(column));

		std::cout << "total value of column " << column << " is " << value;
		return value;
	}
};


int main() {
	srand(time(NULL));
	int turn = (rand() % 2);
	Board board;
	int input;
	int counter = 0;
	Player player1 = Player('R', '1');
	Player player2 = Player('B', '2');
	board.print();


	while (true) {
//		Computer computer = computer('R', '1');

		Player currentPlayer = player2;
		if (turn == 0) {
			currentPlayer = player1;
		}

		std::cout << "WTF Enter your next move ";
		currentPlayer.printName();
		std::cout << "\n";
		std::cin >> input;


		while (!(board.isValid(input))) {										// ensure proper input from user
			std::cout << "Please enter a valid input for your next move\n";
			std::cin >> input;
		}

		std::cout << "should've ??? \n";

		board.play(input, currentPlayer);
//		computer.evaluateColumn(input, board);
		std::cout << "should've worked \n";
		counter++;
		turn++;
		turn = turn % 2;

		if (board.isWin(input, currentPlayer)) {										// if the move wins, then print and clear board
			board.print();
			std::cout << "Congratuations ";
			currentPlayer.printName();
			std::cout << " You win! \n";
			board.clear();
			counter = 0;
		}
		board.print();
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
