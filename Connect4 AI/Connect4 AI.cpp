// Connect4 AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>


class Player {			//should be private with get/set
public:
	char color;
	bool isAI;
	char name [8] = { 'P','l','a','y','e','r',' ',' ' };
	Player(char color, char number, bool isAI) {	// need to update the constructor if I use it more. 
		this->color = color;
		name[7] = number;
		this->isAI = isAI;
	}

	Player() {
		this->color = '?';
		this->name[7] = '?';
		this->isAI = true;
	}

	void printName() {
		for (int i = 0; i < 8; i++) {
			std::cout << this->name[i];
		}
	}
};

class Board {
public:
	char board[6][7] =    { { ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
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

	void setHeights(int newHeights[7]) {
		for (int k = 0; k < 7; k++) {
			heights[k] = newHeights[k];
		}
	}

	void setBoard(char newBoard[6][7]) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				board[i][j] = newBoard[i][j];
			}
		}
	}

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
	int edgePenalty = -1;
	int connect1Value = 0;
	int connect2Value = 2;
	int connect3Value = 4;
	int connect4value = 100;

public:
	Computer(char color, char number,bool other) {	// need to update the constructor if I use it more. 
		this->color = color;
		name[7] = number;
		this->isAI = true;
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
		else {
			return connect1Value;
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
		else {
			return connect1Value;
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
		else {
			return connect1Value; 
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
		else {
			return connect1Value;
		}
	}
	int columnVal(int column) {			// for the raw column values, no connections included // should be private

		if (column == 3) {
			return centerValue;
		}
		else if (column == 0 || column == 6) {
			return edgePenalty;
		}
		else {
			return connect1Value;
		}
	}
	int evaluateColumn(int column, Board board) {		// only pass on valid columns 

		int value = 0;
		value += (aDiagonalVal(column, board));
		std::cout << "ascending diagonal value is " << (aDiagonalVal(column, board)) << "\n";

		value += (dDiagonalVal(column, board));
		std::cout << "descending diagonal value is " << (dDiagonalVal(column, board)) << "\n";

		value += (horizontalVal(column, board));
		std::cout << "Horizontal value is " << (horizontalVal(column, board)) << "\n";

		value += (verticalVal(column, board));
		std::cout << "vertical value is " << (verticalVal(column, board)) << "\n";

		value += (columnVal(column));
		std::cout << "column value is " << (columnVal(column)) << "\n";

		std::cout << "total value of column " << column << " is " << value << "\n";
		return value;
	}

	int getBestTurn(Board board, Player player, Player enemyPlayer) { // returns the column with the best score (eventually)
		int maxTurnVal = -999;
		int bestColumn;
		for (int i = 0; i < 7; i++) {
			std::cout << "\n\n Evaluating column " << i << "\n";
			if (board.isValid(i)) {
				Board board2;
				board2.setHeights(board.heights);
				board2.setBoard(board.board);
				board2.play(i, player);
				board2.print();
				int val = evaluateColumn(i, board2);
				if (val > maxTurnVal) {
					maxTurnVal = val;
					bestColumn = i;
				}
			}
		}
		std::cout << "\n\n BEST COLUMN FOUND IS  " << bestColumn << " WITH VALUE " << maxTurnVal << "\n";
		return bestColumn;
	}
};


int main() {
	srand(time(NULL));
	int turn = (rand() % 2);
	Board board;
	int input;
	int counter = 0;
	Player player1 = Player('O', '1', false);
	Computer player2 = Computer('X', '2', true);
	board.print();


	while (true) {

		Player currentPlayer = player2;
		if (turn == 0) {
			currentPlayer = player1;
		}

		if (currentPlayer.isAI) {
			input = player2.getBestTurn(board, player2,player1);
		}
		else {
			std::cout << "Enter your next move ";
			currentPlayer.printName();
			std::cout << "\n";
			std::cin >> input;
			while (!(board.isValid(input))) {										// ensure proper input from user
				std::cout << "Please enter a valid input for your next move\n";
				std::cin >> input;
			}
		}

		board.play(input, currentPlayer);

		
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
