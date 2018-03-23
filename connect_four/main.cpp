//#include <stdafx.h>
#include <iostream>
#include <string>

using namespace std;

#define EMPTY_CELL_VALUE '_'
#define RED_CELL_VALUE 'X'
#define BLUE_CELL_VALUE 'O'

char DISK = RED_CELL_VALUE || BLUE_CELL_VALUE;

#define count_check (4)
#define max_rows (5)
#define max_col (5)
#if (count_check>max_col||count_check>max_rows)
#endif

char board[max_col][max_rows];

int charsPlaced = 0;

int col_num;

void setup()
{
	charsPlaced = 0; //resets board to zero
	for (int row = 0; row < max_rows; row++) {
		for (int col = 0; col < max_col; col++) {
			board[col][row] = EMPTY_CELL_VALUE; //resets board to all empty values
		}
	}
}
void draw_board() {
	system("cls");
	cout << "----------------------" << endl;
	for (int i = 1; i <= max_col; i++) {
		string dash = "---";
		cout << dash;
	}
	cout << endl;
	for (int row = 0; row < max_rows; row++) {
		for (int col = 0; col < max_col; col++) {
			cout << "|" << board[col][row] << "|";
		}
		cout << endl;
	}
	for (int i = 1; i <= max_col; i++) {
		int col_num = i; 
		cout << "[" << col_num << "]";
	}	
	cout << endl;
	for (int i = 1; i <= max_col; i++) {
		string dash = "---";
		cout << dash;
	}
	cout << endl;
	cout << "----------------------" << endl;
}
char getDisk(int p) {
	if (p == 0) {
		return RED_CELL_VALUE;
	}
	else if (p == 1) {
		return BLUE_CELL_VALUE;
	}
	else {
		return false;
	}
}
bool col_full(int c) {
	if (board[c - 1][0] != EMPTY_CELL_VALUE) {
		return true;
	}
	else {
		return false;
	}
}
void drop(int c, int p) {
	for (int r = max_rows - 1; r >= 0; r--) {
		if (board[c][r] == '_') {
			if (p == 0) {
				board[c][r] = RED_CELL_VALUE;
			}
			if (p == 1) {
				board[c][r] = BLUE_CELL_VALUE;
			}
			break;
		}
	}

}
/*char getBoardValue(int col, int row) {
	return board[col][row] == EMPTY_CELL_VALUE;
}
bool isEmpty(int col, int  row) {
	return board[col][row] == EMPTY_CELL_VALUE;
}
bool isFull(int col, int row) {
	return !isEmpty(col, row);
}*/
//the above is code which calls itself and will therefore cause issues.  Do not call.



bool checkHorizontal(int p){
	int count;
	for (int r = 0; r < max_rows; r++) {
		count = 0;
		for (int c = 0; c < max_col; c++) {
			if (board[c][r] == getDisk(p)) {
				count++;
			}
			else{
				count = 0;
			}
			if (count == count_check) {
				return true;
			}
		}
	}
	return false;
}

bool checkVertical(int p){
	int count;
	for (int c = 0; c < max_col; c++) {
		count = 0;
		for (int r = 0; r < max_rows; r++) {
			if (board[c][r] == getDisk(p)) {
				count++;
			}
			else {
				count = 0; 
			}
			if (count == count_check) {
				return true;
			}
		}
	}
	
	return false;
};
bool checkUpDiag(int p) {
	for (int c = 0; c < max_col - count_check + 1; c++) {
		for (int r = max_rows - 1; r >= max_rows - count_check; r--) {
			int count = 0;
			for (int x = 0; x < count_check; x++) {
				if (board[c + x][r - x] == getDisk(p)) {
					count++;
				}
				if (count == count_check) {
					return true;
				}
			}
		}
	}
	return false;
};
	/*int count;
	int ro;
	int co;
	for (int c = 0; c < max_col; c++) {
		count = 0;
		co = c;
		for (int r = 0; r < max_rows; r++) {
			count = 0;
			ro = r; // move to else
			if (board[co][ro] == getDisk(p)) {
					count++;
					if (count == 4) {
						return true;
					}
					else {
						co++;
						ro++;
					}
			}
			else {
				count = 0;
			}
		}
	}
	return false;*/
bool checkDownDiag(int p){
	for (int c = 0; c <= max_col - count_check; c++) {
		for (int r = 0; r <= max_rows - count_check; r++) {
			int count = 0;
			for (int x = 0; x < count_check; x++) {
				if (board[c + x][r + x] == getDisk(p)) {
					count++;
				}
				if (count == count_check) {
					return true;
				}
			}
		}
	}
	return false;
};
bool checkWin(int p) {
	if (checkHorizontal(p)) {
		return true;
	}
	if (checkVertical(p)) {
		return true;
	}
	if (checkUpDiag(p)) {
		return true;
	}
	if (checkDownDiag(p)) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	setup();
	int p = 0;
	int c;
	bool gameover = false;

	while (!gameover)
	{
		if (charsPlaced == max_col * max_rows) {
			gameover = true;
			draw_board();
			cout << "Tie game" << endl;
			system("pause");
		}
		draw_board();
		cout << endl;
		cout << "Player " << p + 1 << ", in which column do you want to place your piece?" << endl;
		cin >> c;
		if (c >= 0 && c <= max_col)//assumes first col is 0
		{
		
			if (col_full(c)){
				cout << "Pick an empty column......and may every sock you wear be slightly rotated, just enough to be uncomfortable."  << endl;
				cout << endl;
				system("pause");
				p = 1 - p;
			}
			else {
				drop(c - 1, p); /*not row b/c row is determined by an actual function
								p drops specific character either X or O,
								is (c - 1) because the player will  see a larger value displayed,
								(eg col[0] as col[1])*/
				charsPlaced++; //total pieces on board increase, used for tie game
				if (checkWin(p)) {
					draw_board();
					cout << "Player " << p + 1 << " Wins!" << endl;
					system("pause");
					gameover = true;
					setup();
					p = 0;
					draw_board();

					continue; /*actual code where you must interact to continue,
							  just like retro games*/
			}
			}
			p = 1 - p; // the great toggle of player switching
		}
		else {
			cout << "Pick a number between 1-" << max_col << ", you walnut." << endl << endl;
			system("pause");
		}
	}
	return 0;
}


