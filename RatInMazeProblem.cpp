#include "RatInMazeProblem.h"


void RatInMazeProblem::Execute(int** maze, int n)
{
	// 0->open to go, 1->blocked
	int** sol = new int* [2];
	sol[0] = new int[n * n] {0};
	sol[1] = new int[n * n] {0};

	RIM(maze, sol, 0, 0, 0, n);

	delete[] sol[0];
	delete[] sol[1];
	delete[] sol;
}

void RatInMazeProblem::RIM(int** maze, int** sol, int k, int i, int j, int n)
{

	// mark it as selected
	maze[i][j] = 1;
	sol[0][k] = i;
	sol[1][k] = j;
	k++;


	if (i == n - 1 && j == n - 1)
	{
		Print(sol, k);
		maze[i][j] = 0;
		return;
	}

	// go right
	if (j + 1 < n && maze[i][j + 1] == 0)
	{
		RIM(maze, sol, k, i, j + 1, n);
	}
	// go down
	if (i + 1 < n && maze[i + 1][j] == 0)
	{
		RIM(maze, sol, k, i + 1, j, n);
	}
	// go left
	if (j - 1 >= 0 && maze[i][j - 1] == 0)
	{
		RIM(maze, sol, k, i, j - 1, n);
	}
	// go up
	if (i - 1 >= 0 && maze[i - 1][j] == 0)
	{
		RIM(maze, sol, k, i - 1, j, n);
	}

	// go back
	maze[i][j] = 0;
	k--;
}

void RatInMazeProblem::Print(int** sol, int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << "(" << sol[0][i] << ", " << sol[1][i] << ")";
		if (i < n - 1)
			std::cout << ", ";
	}
	std::cout << "\n===========================================\n";
}

void RatInMazeProblem::TestBehavior()
{
	int n = 4;

	// 1. حجز الذاكرة للمتاهة (Dynamic 2D Array)
	int** maze = new int* [n];
	for (int i = 0; i < n; i++)
	{
		maze[i] = new int[n];
	}

	// 2. تصميم المتاهة
	// 0 -> مسار مفتوح
	// 1 -> جدار (مغلق)
	int tempMaze[4][4] = {
		{0, 0, 0, 0},
		{1, 1, 0, 1},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	};

	// نسخ القيم من المتاهة المؤقتة إلى المتاهة الديناميكية
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			maze[i][j] = tempMaze[i][j];
		}
	}

	// 3. استدعاء خوارزمية الحل
	std::cout << "Finding paths for Rat in a Maze:\n";
	RatInMazeProblem::Execute(maze, n);

	// 4. تحرير الذاكرة (Memory Cleanup)
	for (int i = 0; i < n; i++)
	{
		delete[] maze[i];
	}
	delete[] maze;
}