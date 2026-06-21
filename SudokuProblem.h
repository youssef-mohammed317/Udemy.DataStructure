#pragma once
#include<iostream>

class SudokuProblem
{
	static void Sudoku(int** sudoku, int row, int col);
	static void Print(int** sudoku);
	static bool isValid(int** sudoku, int row, int col, int key);

public:
	static void Execute(int** sudoku);


	static void TestBehavior();

};

