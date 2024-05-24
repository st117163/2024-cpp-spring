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
	if (i < 0)  return;
	if (i >= x) return;
	if (j < 0)  return;
	if (j >= y) return;
	if (matrix[i][j] != '*') return;

	matrix[i][j] = '.';
	startrek(matrix, i, j + 1, x, y);
	startrek(matrix, i, j - 1, x, y);
	startrek(matrix, i + 1, j, x, y);
	startrek(matrix, i - 1, j, x, y);
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