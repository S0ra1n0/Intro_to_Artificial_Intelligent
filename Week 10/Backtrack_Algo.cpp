#include <bits/stdc++.h>
#define el "\n";
using namespace std;
using namespace std::chrono;

int check = 2;

bool isSafe(vector<vector<int>> &mat, int row, int col, int num) {

    // Check if num exist in the row
    for (int x = 0; x <= 8; x++)
        if (mat[row][x] == num && x != col)
            return false;

    // Check if num exist in the col
    for (int x = 0; x <= 8; x++)
        if (mat[x][col] == num && x != row)
            return false;

    // Check if num exist in the 3x3 sub-matrix
    int startRow = row - (row % 3), startCol = col - (col % 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i + startRow) == row && (j + startCol) == col)
                continue;
            if (mat[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

bool solveSudokuRec(vector<vector<int>> &mat, int row, int col) {
    int n = mat.size();

    // base case: Reached nth column of last row
    if (row == n - 1 && col == n)
        return true;

    // If last column of the row go to next row
    if (col == n) {
        row++;
        col = 0;
    }

    // If cell is already occupied then move forward
    if (mat[row][col] != 0)
        return solveSudokuRec(mat, row, col + 1);

    for (int num = 1; num <= n; num++) {

        // If it is safe to place num at current position
        if (isSafe(mat, row, col, num)) {
            mat[row][col] = num;
            if (solveSudokuRec(mat, row, col + 1))
                return true;
            mat[row][col] = 0;
        }
    }
  
  	return false;
}

void solveSudoku(vector<vector<int>> &mat) {
  	solveSudokuRec(mat, 0, 0);
}

int main() {
    int a, b;
    vector<vector<int>> mat = {
        {0, 0, 0, 0, 0, 0, 8, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 5, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 7, 0, 0, 0, 0},
        {0, 0, 8, 0, 0, 0, 6, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0, 0, 0, 0}};
    
    //starting timer
    auto start = high_resolution_clock::now();

    //solving
    solveSudoku(mat);
	
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
    
  	for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat.size(); j++) {
            cout << mat[i][j] << " ";
            if (mat[i][j] == 0) {check = 1;}
        }
        cout << el
    }
    
    if (check == 2) {
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat.size(); j++) {
                if (!isSafe(mat, i, j, mat[i][j])) {a = i; b = j; check = 0; i = 10; break;}
            }
        }
    }
    
    if (check == 2) {cout << "Solved successfully" << el}
    else if (check == 1) {cout << "Cannot be solved" << el}
    else {cout << "Puzzle error: i = " << a << ", j = " << b << el}
    
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds" << el
}
