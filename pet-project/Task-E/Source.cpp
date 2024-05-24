#include<iostream>
#include<fstream>
#include<string>
#include<queue>

char** readMatrix(std::string filename)
{
	std::ifstream fin(filename);
	int x = 0;
	int y = 0;
	fin >> x;
	fin >> y;
	char** matrix = new char* [x];
	for (int i = 0; i < x; ++i)
	{
		matrix[i] = new char[y];
		for (int j = 0; j < y; ++j)
		{
			fin >> matrix[i][j];
		}
	}
	fin.close();
	return matrix;
}
void startrek(char** matrix, int i, int j, int x, int y)
{
	std::queue<int>  qx;
	std::queue<int>  qy;
	qx.push(i);
	qy.push(j);
	int sx = 0;
	int sy = 0;
	while (!qx.empty())
	{
		sx = qx.front();
		sy = qy.front();
		qx.pop();
		qy.pop();
		if (sx - 1 >= 0)
		{
			if (matrix[sx - 1][sy] == '*')
			{

				qx.push(sx - 1);
				qy.push(sy);
			}
		}
		if (sy - 1 >= 0)
		{
			if (matrix[sx][sy-1] == '*')
			{

				qx.push(sx);
				qy.push(sy-1);
			}
		}
		if (sx + 1 < x)
		{
			if (matrix[sx + 1][sy] == '*')
			{

				qx.push(sx + 1);
				qy.push(sy);
			}
		}
		if (sy + 1 < y)
		{
			if (matrix[sx][sy+1] == '*')
			{

				qx.push(sx);
				qy.push(sy+1);
			}
		}
		matrix[sx][sy] = '.';
	}
}
int ansfunc(char** matrix, int x, int y)
{
	int n = 0;
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (matrix[i][j] == '*')
			{
				startrek(matrix, i, j, x, y);
				++n;
			}
		}
	}
	return n;
}
int main(int argc, char* argv[])
{
	std::ifstream fin("input.txt");
	int x = 0;
	int y = 0;

	fin >> x;
	fin >> y;

	char** matrix = readMatrix("input.txt");

	std::ofstream fout("output.txt");
	fout << ansfunc(matrix, x, y) << std::endl;

	fin.close();
	fout.close();

	delete[] matrix;

	return EXIT_SUCCESS;
}