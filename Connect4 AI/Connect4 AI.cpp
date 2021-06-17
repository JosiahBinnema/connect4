#include <iostream>
#include <stdlib.h>
#include <time.h>

class Player {			//should be private with get/set
public:
	char color;
	bool isAI;
	char name[8] = { 'P','l','a','y','e','r',' ',' ' };
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

class Board {					// make a damn constructor for this class wtf
public:
	char boardArray[6][7] = { { ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
							{ ' ', ' ', ' ', ' ', ' ', ' ', ' ',} };
	int remainingRoom[7] = { 6,6,6,6,6,6,6 };			//remaining room in each column
	int leastRemaining = 6;
	void clear() {
		for (int k = 0; k < 7; k++) {
			remainingRoom[k] = 6;
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				boardArray[i][j] = ' ';
			}
		}
	}
	void buildBoard(int newHeights[7], char newBoard[6][7], int newLeastRemaining) {			// this should be a constructor
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				boardArray[i][j] = newBoard[i][j];
			}
		}
		for (int k = 0; k < 7; k++) {
			remainingRoom[k] = newHeights[k];
		}
		leastRemaining = newLeastRemaining;
	}
	bool isValid(int column) {
		if (column > 6) {
			return false;
		}
		else if (remainingRoom[column] == 0) {
			return false;
		}
		return true;
	}
	void play(int column, Player player) {		// column starts at 0 
		boardArray[(remainingRoom[column] - 1)][column] = player.color;
		remainingRoom[column]--;
		if (remainingRoom[column] < leastRemaining) {
			leastRemaining = remainingRoom[column];
		}
	}
	void unPlay(int column) {
		boardArray[remainingRoom[column]][column] = ' ';
	}
	bool isWin(int column, Player player) {			//should be called before the move has been made on the board.

		if (isDDiagonalWin(column, player.color)) {				// check for descending diagonal win.
			std::cout << "Descending diagonal win for " << player.color << "\n";
			return true;
		}
		else if (isADiagonalWin(column, player.color)) {				// check for ascending diagonal win.
			std::cout << "Ascending diagonal win for " << player.color << "\n";
			return true;
		}
		else if (isHorizontalWin(column, player.color)) {			// check for horizontal win
			std::cout << "Horizontal win for " << player.color << "\n";
			return true;
		}
		else if (remainingRoom[column] < 3) {					// check for a vertical win only when the height of the column allows it
			if (isVerticalWin(column, player.color)) {
				std::cout << "Vertical win for " << player.color << "\n";
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
				std::cout << boardArray[i][j] << " " << "|";
			}

		}
		std::cout << "\n\n\n\n\n\n";
	}
	bool isVerticalWin(int column, char playerColor) {
		int connected = 1;
		int temp = remainingRoom[column] + 1;
		while (temp < 6) {
			if (boardArray[temp][column] == playerColor) {
				connected++;
				if (connected == 4) {
					return true;

				}
			}
			else {
				return false;
			}
			temp++;
		}
		return false;
	}
	bool isHorizontalWin(int column, char playerColor) {
		int connected = 1;
		int temp = remainingRoom[column];
		column--;

		while (column >= 0 && boardArray[temp][column] == playerColor) {
			//			std::cout << "looking left at position " << temp << " " << column << "    " << board[temp][column] << " matches " << player.color << "\n";
			connected++;
			column--;
		}
		column = column + connected + 1;
		while (column <= 6 && boardArray[temp][column] == playerColor) {
			//			std::cout << "looking right at position " << temp << " " << column << "   " << board[temp][column] << " matches " << player.color << "\n";
			connected++;
			column++;
		}
		//		std::cout << "found " << connected << "connected";
		if (connected > 3) {
			return true;

		}
		else {
			return false;
		}
	}
	bool isDDiagonalWin(int column, char playerColor) {
		int connected = 1;								// the first item will always be "connected" so just skip searching it
		int tempRow = remainingRoom[column] - 1;
		int tempCol = column - 1;

		while (tempCol >= 0 && tempRow >= 0 && boardArray[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking up/left at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol--;
			tempRow--;

		}
		tempCol = column + 1;
		tempRow = remainingRoom[column] + 1;
		while (tempCol <= 6 && tempRow <= 5 && boardArray[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking down/right at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol++;
			tempRow++;

		}
		if (connected > 3) {
			return true;

		}
		else {
			return false;
		}
	}
	bool isADiagonalWin(int column, char playerColor) {
		int connected = 1;								// the first item will always be "connected" so just skip searching it
		int tempRow = remainingRoom[column] - 1;
		int tempCol = column + 1;

		while (tempCol <= 6 && tempRow >= 0 && boardArray[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking up/right at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol++;
			tempRow--;

		}
		tempCol = column - 1;
		tempRow = remainingRoom[column] + 1;
		while (tempCol >= 0 && tempRow <= 5 && boardArray[tempRow][tempCol] == playerColor) {
			connected++;
			//			std::cout << "looking down/left at postion " << tempRow << " " << tempCol << "   " << board[tempRow][tempCol] << " matches " << player.color << "\n";
			tempCol--;
			tempRow++;

		}
		if (connected > 3) {
			return true;

		}
		else {
			return false;
		}
	}

};

class Computer : public Player {
private:
	//AI values:
	int centerValue = 6;
	int middleValue = 3;
	int edgePenalty = -1;
	int connect1Value = 1;
	int connect2Value = 3;
	int connect3Value = 15;
	int connect4value = 1000;
	int columnVal(int column) {			// for the raw column values, no connections included
		if (column == 3) {
			return centerValue;
		}
		else if (column == 2 || column == 4) {
			return middleValue;
		}
		else if (column == 0 || column == 6) {
			return edgePenalty;
		}
		else {
			return connect1Value;
		}
	}
	int verticalVal(int column, Board board) {						//  Vertical value for connections. (All ___Val are clones of each other)
		if (board.isVerticalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.isVerticalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.isVerticalWin(column, this->color) >= 4) {
			return connect4value;
		}
		else {
			return connect1Value;
		}
	}
	int aDiagonalVal(int column, Board board) {						// ascending diagonal value for connections. (All ___Val are clones of each other)
		if (board.isADiagonalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.isADiagonalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.isADiagonalWin(column, this->color) >= 4) {
			return connect4value;
		}
		else {
			return connect1Value;
		}
	}
	int dDiagonalVal(int column, Board board) {						// Descending diagonal value for connections. (All ___Val are clones of each other)
		if (board.isDDiagonalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.isDDiagonalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.isDDiagonalWin(column, this->color) >= 4) {
			return connect4value;
		}
		else {
			return connect1Value;
		}
	}
	int horizontalVal(int column, Board board) {						//  Horizontal value for connections. (All ___Val are clones of each other)
		if (board.isHorizontalWin(column, this->color) == 2) {
			return connect2Value;
		}
		else if (board.isHorizontalWin(column, this->color) == 3) {
			return connect3Value;
		}
		else if (board.isHorizontalWin(column, this->color) >= 4) {
			return connect4value;
		}
		else {
			return connect1Value;
		}
	}
	int returnValue(int count) {
		if (count == 4) {
			return connect4value;
		}
		else if (count == 3) {
			return connect3Value;
		}
		else if (count == 2) {
			return connect2Value;
		}
		else if (count == 1) {
			return connect1Value;
		}
		else if (count == 0) {
			return 0;
		}
		else if (count == -4) {
			return -connect4value;
		}
		else if (count == -3) {
			return -(connect3Value + 30);
		}
		else if (count == -2) {
			return -connect2Value;
		}
		else if (count == -1) {
			return -connect1Value;
		}
	}
	int evaluate4Horizontal(Board board, int row, int column, Player player) {		// only pass with column < 4
//		std::cout << "the character at examined is |";
		int count = 0;
		bool player1 = false;
		bool player2 = false;
		for (int i = column; i < (column + 4); i++) {
//			std::cout << board.boardArray[row][i] << " |";
			if (board.boardArray[row][i] != ' ') {

				if (player.color == board.boardArray[row][i]) {
					count++;
					player1 = true;
				}
				else {
					player2 = true;
					count--;
				}
				if (player2 && player1) {
					//					std::cout <<"Both players are in this";
					return 0;
				}
			}
		}
		//		std::cout << " \n value is " << returnValue(count) << "\n";
		return returnValue(count);
	}
	int evaluateRow(Board board, int row, Player player) {
		int value = 0;
		for (int i = 0; i < 4; i++) {
			value += evaluate4Horizontal(board, row, i, player);
		}
//			std::cout << "Total value of row " << row << " is " << value << "\n";
		return value;
	}
	int evaluateColumn(Board board, int column, Player player) {				// only pass with row < 3
		int count = 0;
		bool player1 = false;
		bool player2 = false;

		for (int i = 5; i >= 0; i--) {
			if (count + i >= 3) {
//				std::cout << board.boardArray[i][column] << " |";
				if (board.boardArray[i][column] == ' ') {
					break;
				}
				if (player.color == board.boardArray[i][column]) {
					if (player1) {
						count++;
					}
					else {
						player1 = true;
						player2 = false;
						count = 1;
					}
				}
				else {
					if (player2) {
						count++;
					}
					else {
						player1 = false;
						player2 = true;
						count = 1;
					}
				}
			}
			else {
//				std::cout << "row " << i << " with " << count << " Means no more room in this column \n";
				return 0;
			}
		}
//		std::cout << " \n value is " << returnValue(count) << "\n";
		if (player2) {
			return returnValue(-count);
		}
		else {
			return returnValue(count);
		}

	}
	int evaluateADiagonal4(Board board, int row, int column, Player player) {
		int count = 0;
		int i = row;
		int j = column;
		bool player1 = false;
		bool player2 = false;
		for (int k = 0; k < 4; k++) {
//			std::cout << board.boardArray[i][j] << " |";
			if (board.boardArray[i][j] != ' ') {
				if (player.color == board.boardArray[i][j]) {
					count++;
					player1 = true;
				}
				else {
					player2 = true;
					count--;
				}
				if (player2 && player1) {
					return 0;
				}
			}
			i--;
			j++;
		}
//		std::cout << "\n";
		return returnValue(count);
	}
	int evaluateDDiagonal4(Board board, int row, int column, Player player) {
		int count = 0;
		int i = row;
		int j = column;
		bool player1 = false;
		bool player2 = false;
		for (int k = 0; k < 4; k++) {
//			std::cout << board.boardArray[i][j] << " |";
			if (board.boardArray[i][j] != ' ') {
				if (player.color == board.boardArray[i][j]) {
					count++;
					player1 = true;
				}
				else {
					player2 = true;
					count--;
				}
				if (player2 && player1) {
					return 0;
				}
			}
			i--;
j--;
		}
		//		std::cout << "\n";
		return returnValue(count);
	}
	int evaluateHorizontals(Board board, Player player) {
		int value = 0;
		for (int i = 5; i >= (board.leastRemaining); i--) {
			value += evaluateRow(board, i, player);
		}
		return value;
	}
	int evaluateColumns(Board board, Player player) {
		int value = 0;
		for (int i = 0; i < 7; i++) {
			value += evaluateColumn(board, i, player);
		}
		return value;
	}
	int evaluateADiagonals(Board board, Player player) {
		int value = 0;
		for (int i = 5; i > 3; i--) {
			for (int j = 3; j >= 0; j--) {
				value += evaluateADiagonal4(board, i, j, player);
			}
			return value;
		}
	}
	int evaluateDDiagonals(Board board, Player player) {
		int value = 0;
		for (int i = 5; i > 3; i--) {
			for (int j = 3; j < 7; j++) {
				value += evaluateDDiagonal4(board, i, j, player);
			}
			return value;
		}
	}
	int evaluateColumn(int column, Board board) {		// only pass on valid columns 
		board.print();
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
public:
	Computer(char color, char number, bool other) {	// need to update the constructor if I use it more. 
		this->color = color;
		name[7] = number;
		this->isAI = true;
	}
	int getBestTurnOUTDATED(Board board, Player player) { // ignores enemy player and plays "best move"
		int maxTurnVal = -999;
		int bestColumn;
		for (int i = 0; i < 7; i++) {
//			std::cout << "\n\n Evaluating column " << i << "\n";
			if (board.isValid(i)) {
				Board board2;
				board2.buildBoard(board.remainingRoom, board.boardArray, board.leastRemaining);
				board2.play(i, player);
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
	int evaluatePosition(Board board, Player player) {
		return (evaluateDDiagonals(board, player) + evaluateADiagonals(board, player) + evaluateColumns(board, player) + evaluateHorizontals(board, player));
	}
	int getBestMove(Board board, Player player, Player enemyPlayer) {
		int maxTurnVal = -999999;
		int bestColumn = 3;
		for (int i = 0; i < 7; i++) {
			if (board.isValid(i)) {
				board.play(i, player);
				int tempVal = evaluatePosition(board, player);

				if (tempVal > maxTurnVal) {
					maxTurnVal = tempVal;
					bestColumn = i;
				}
				board.unPlay(i);
			}
		}
		std::cout << "\n\n BEST COLUMN FOUND IS  " << bestColumn << " WITH VALUE " << maxTurnVal << "\n";
		return bestColumn;
	}

	int miniMax(Board board, Player currentPlayer, Player enemyPlayer, bool isMaximizing, int depth) { // check for win
		int bestColumn;
		if (depth == 0) {
			return evaluatePosition(board, currentPlayer);
		}

		if (isMaximizing) {
			int value = -999999;
			for (int i = 0; i < 7; i++) {
				if (board.isValid(i)) {
					if (board.isWin(i, currentPlayer)) {
						std::cout << " found winning move!! ";
						board.play(i, currentPlayer);
						board.print();
						board.unPlay(i);
						return connect4value;
					}
					Board board2;
					board2.buildBoard(board.remainingRoom, board.boardArray, board.leastRemaining);
					board2.play(i, currentPlayer);
									board2.print();
									std::cout << " depth is " << depth << "\n";


					int tempVal = miniMax(board2,  currentPlayer, enemyPlayer, !isMaximizing, (depth - 1));
								std::cout << "^this is an evaluated board given the value of " << tempVal << "(played in column) " << i << "\n";
					if (tempVal > value) {
						std::cout << "value chosen from list above is " << tempVal << " which is greater than the previous amount " << value << "\n";
						value = tempVal;
						bestColumn = i;
					}
				}
			}
			return value;
		} else {
			int value = 999999;
			for (int i = 0; i < 7; i++) {
				if (board.isValid(i)) {
					if (board.isWin(i, enemyPlayer)) {
						std::cout << " found winning move!! ";
						board.play(i, currentPlayer);
						board.print();
						board.unPlay(i);
						return -connect4value;
					}
					Board board2;
					board2.buildBoard(board.remainingRoom, board.boardArray, board.leastRemaining);
					board2.play(i, enemyPlayer);
									board2.print();
									std::cout << " depth is " << depth << "\n";


					int tempVal = miniMax(board2,  currentPlayer, enemyPlayer, !isMaximizing, (depth - 1));
									std::cout << "^this is an evaluated board given the value of " << tempVal << "(played in column) " << i << "\n";
					if (tempVal < value) {
						std::cout << "value chosen from list above is " << tempVal << " which is less than the previous amount " << value << "\n";
						value = tempVal;
						bestColumn = i;
					}
				}
			}
			return value;
		}
	}

	int miniMaxShell(Board board, Player currentPlayer, Player enemyPlayer, int depth) { // person calling this will always be maximizing. Depth must be >=1 (this is for the AILevels feature;
		int maxTurnVal = -999999;
		int bestColumn = 3;
		for (int i = 0; i < 7; i++) {
			if (board.isValid(i)) {
				board.play(i,currentPlayer);
				int tempVal = miniMax(board, enemyPlayer, currentPlayer, false , depth - 1);
				board.unPlay(i);
				if (tempVal >= maxTurnVal) {
					maxTurnVal = tempVal;
					bestColumn = i;
				}
			}
		}
			std::cout << "\n\n minimax algorithm with depth" << depth <<  "believes the BEST COLUMN FOUND IS  " << bestColumn << " WITH VALUE " << maxTurnVal << "\n";
			return bestColumn;
	}

};


int level1Move(Board board, Computer player2) {
	int output = player2.getBestTurnOUTDATED(board, player2);
	std::cout << "level 1 AI played in column " << output << "\n";
	return output;
}
int level2Move(Board board, Computer player2, Player player1) {
	int output = player2.getBestMove(board, player2, player1);
	std::cout << "level 2 AI played in column " << output << "\n";
	return output;
}
int getPlayerInput(Board board, Player player) {
	int input;
	std::cout << "Enter your next move ";
	player.printName();
	std::cout << "\n";
	std::cin >> input;
	while (!(board.isValid(input))) {										// ensure proper input from user
		std::cout << "Please enter a valid input for your next move\n";
		std::cin >> input;
	}
	return input;
}
int getAILevel() {
	int input;
	std::cout << "What level AI (1-10) would you like to face? levels higher than 6 may slow down your computer. Enter 0 to play versus another person locally \n";
	std::cin >> input;
	while (!(input < 11 && input >= 0)) {
		std::cout << "Please enter a level between 1-10, or 0 to play locally";
		std::cin >> input;
	}
	return input;
}
int getAIInput(Board board, Computer computer, Player player, int level) {
	int input;
	if (level > 2 && level <= 10) {
		input = computer.miniMaxShell(board, computer, player, level);
		std::cout << " level " << level << " AI played in column " << input;
	} else if (level == 2) {
		input = level2Move(board, computer, player);
	}
	else if (level == 1) {
		input = level1Move(board, computer);
	}
	else {
		input = getPlayerInput(board,computer);
	}
	return input;
}


int main() {
	srand(time(NULL));
	int turn = (rand() % 2);
	Board board;
	int input;
	int computerLevel = 2;
	int counter = 0;
	Player player1 = Player('O', '1', false);
	Computer player2 = Computer('X', '2', true);
	Player currentPlayer;
	Player enemyPlayer;

	computerLevel = getAILevel();
	board.print();

		while (true) {


			if (turn == 0) {
				currentPlayer = player1;
				enemyPlayer = player2;
			}
			else {
				currentPlayer = player2;
				enemyPlayer = player1;
			}

			if (currentPlayer.isAI) {
//				input = getAIInput(board, currentPlayer, enemyPlayer, computerLevel);			//TODO: Change computer level to a computer variable, then set it there and change this back to 
				input = getAIInput(board, player2, enemyPlayer, computerLevel);

			}
			else {
				input = getPlayerInput(board, currentPlayer);
			}
			


//			int minimaxValue = player2.miniMax(board, currentPlayer, enemyPlayer, true, 3);

//			std::cout << "\n\n\n\n";
//			board.print();
			board.play(input, currentPlayer);

//			std::cout << "minimax evaluation believes this ^^^^ value to be " << minimaxValue;
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
	};