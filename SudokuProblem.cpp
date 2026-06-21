#include "SudokuProblem.h"

void SudokuProblem::Execute(int** sudoku)
{
	// 9x9, 0 -> means no value exist
	Sudoku(sudoku, 0, 0);
}

void SudokuProblem::Sudoku(int** sudoku, int row, int col)
{

	if (row == 9)
	{
		Print(sudoku);
		return;
	}


	if (sudoku[row][col] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{
			if (isValid(sudoku, row, col, i))
			{
				sudoku[row][col] = i;
				Sudoku(sudoku, col == 8 ? row + 1 : row, (col + 1) % 9);
				// go back
				sudoku[row][col] = 0;
			}
		}
	}
	else {
		Sudoku(sudoku, col == 8 ? row + 1 : row, (col + 1) % 9);
	}

}


bool SudokuProblem::isValid(int** sudoku, int row, int col, int key)
{
	// check col
	for (int j = 0; j < 9; j++)
	{
		if (sudoku[j][col] == key) return false;
	}
	// check row
	for (int i = 0; i < 9; i++)
	{
		if (sudoku[row][i] == key) return false;
	}
	// check block
	int blockRow = row - row % 3;
	int blockcol = col - col % 3;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (sudoku[blockRow + i][blockcol + j] == key)
				return false;
		}
	}
	return true;
}

void SudokuProblem::Print(int** sudoku)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << sudoku[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n=====================================================\n";

}


void SudokuProblem::TestBehavior()
{
	// إنشاء مصفوفة 9x9 ديناميكياً
	int** sudoku = new int* [9];
	for (int i = 0; i < 9; i++)
	{
		sudoku[i] = new int[9];
	}

	// لغز سودوكو حقيقي (0 يمثل الخلايا الفارغة)
	int grid[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9}
	};

	// نسخ اللغز إلى المصفوفة الديناميكية
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = grid[i][j];
		}
	}

	std::cout << "Solving Sudoku...\n\n";

	// تشغيل الخوارزمية
	SudokuProblem::Execute(sudoku);

	// تنظيف الذاكرة
	for (int i = 0; i < 9; i++)
	{
		delete[] sudoku[i];
	}
	delete[] sudoku;
}