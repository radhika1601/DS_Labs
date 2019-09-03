#include <bits/stdc++.h>
using namespace std;

int number = 0;

bool isValid(vector<vector<int>> &board, int row, int col,int n) {

	for(int i = 0; i < row; ++i)
		if(board[i][col] == 1)
			return false;
	
	for(int i = row, j = col; i >= 0 && j >= 0; i--, j-- )
		if(board[i][j] == 1)
			return false;

	for(int i = row, j = col; i >= 0 && j < n; i--, j++)
		if(board[i][j] == 1)
			return false;
	return true;
}

void print_all_possible_matrices(vector<vector<int>> &board, int row, int n) {

	if(row == n) {
		for(int i = 0; i < n; ++i){
			for(int j = 0;j < n;++j)
				cout << board[i][j] << " ";
			cout << endl;
		}
		number++;
		cout << endl;
		return;
	}

	for (int i = 0; i < n; ++i) {
		if(isValid(board, row, i,n)) {
			board[row][i] = 1;
			print_all_possible_matrices(board, row+1, n);
			board[row][i] = 0;
		}
		board[row][i]=0;
	}
}

int main(){
	
	int n;
	cout << "Enter n" << endl;
	cin >> n;
	vector<vector<int>> board(n,vector<int>(n));

	print_all_possible_matrices(board, 0, n);
	cout << number << endl;
	return 0;
}