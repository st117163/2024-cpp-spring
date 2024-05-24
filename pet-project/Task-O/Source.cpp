#include<iostream>
#include<fstream>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

char** readMatrix(int n)
{
	char** matrix = new char* [n];

	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new char[n];
		for (int j = 0; j < n; ++j)
		{
			fin >> matrix[i][j];
		}
	}
	return matrix;
}
int** createDisM(int n)
{
	int** matrix = new int* [n];

	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new int[n];
		for (int j = 0; j < n; ++j)
		{
			matrix[i][j] = 65000;
		}
	}
	return matrix;
}

void SF_cord(int& xs, int& ys, int& xf, int& yf, int n, char** matrix)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] == '@')
			{
				xs = i;
				ys = j;
			}
			if (matrix[i][j] == 'X')
			{
				xf = i;
				yf = j;
			}
		}
	}
}

bool My_BFS(int n, int** disM, char** matrix)
{
	int xs = 0;
	int ys = 0;
	int xf = 0;
	int yf = 0;
	SF_cord(xs, ys, xf, yf, n, matrix);

	disM[xs][ys] = 0;

	std::queue<int> q;
	q.push(xs);
	q.push(ys);
	while (!q.empty())
	{
		int xn = q.front();
		q.pop();
		int yn = q.front();
		q.pop();

		if (xn - 1 == xf && yn == yf)
		{
			disM[xf][yf] = disM[xn][yn] + 1;
			return true;
		}
		if (xn + 1 == xf && yn == yf)
		{
			disM[xf][yf] = disM[xn][yn] + 1;
			return true;
		}
		if (xn == xf && yn - 1 == yf)
		{
			disM[xf][yf] = disM[xn][yn] + 1;
			return true;
		}
		if (xn == xf && yn + 1 == yf)
		{
			disM[xf][yf] = disM[xn][yn] + 1;
			return true;
		}

		if (xn - 1 >= 0 && matrix[xn - 1][yn] == '.' && disM[xn - 1][yn] == 65000)
		{
			q.push(xn - 1);
			q.push(yn);
			disM[xn - 1][yn] = disM[xn][yn] + 1;
		}
		if (xn + 1 < n && matrix[xn + 1][yn] == '.' && disM[xn + 1][yn] == 65000)
		{
			q.push(xn + 1);
			q.push(yn);
			disM[xn + 1][yn] = disM[xn][yn] + 1;
		}
		if (yn - 1 >= 0 && matrix[xn][yn - 1] == '.' && disM[xn][yn - 1] == 65000)
		{
			q.push(xn);
			q.push(yn - 1);
			disM[xn][yn - 1] = disM[xn][yn] + 1;
		}
		if (yn + 1 < n && matrix[xn][yn + 1] == '.' && disM[xn][yn + 1] == 65000)
		{
			q.push(xn);
			q.push(yn + 1);
			disM[xn][yn + 1] = disM[xn][yn] + 1;
		}
	}
	return false;
}


void nazad(int n, int** disM, char** matrix)
{
	int xs = 0;
	int ys = 0;
	int xf = 0;
	int yf = 0;
	SF_cord(xs, ys, xf, yf, n, matrix);

	int xn = xf;
	int yn = yf;
	int dis = disM[xf][yf];
	while (dis > 0)
	{
		matrix[xn][yn] = '+';

		if (xn - 1 >= 0 && disM[xn - 1][yn] == dis - 1)
		{
			--dis;
			--xn;
			continue;
		}
		if (xn + 1 < n && disM[xn + 1][yn] == dis - 1)
		{
			--dis;
			++xn;
			continue;
		}
		if (yn - 1 >= 0 && disM[xn][yn - 1] == dis - 1)
		{
			--dis;
			--yn;
			continue;
		}
		if (yn + 1 < n && disM[xn][yn + 1] == dis - 1)
		{
			--dis;
			++yn;
			continue;
		}
	}
}

void printMatrix(int n, char** matrix)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			fout << matrix[i][j];
		}
		fout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	int  n = 0;
	fin >> n;

	char** matrix = readMatrix(n);
	int** disM = createDisM(n);

	if (My_BFS(n, disM, matrix))
	{
		fout << 'Y' << std::endl;
		nazad(n, disM, matrix);
		printMatrix(n, matrix);
	}
	else
	{
		fout << 'N' << std::endl;
	}
	fin.close();
	fout.close();

	for (int i = 0; i < n; ++i)
	{
		delete[] matrix[i];
		delete[] disM[i];
	}
	delete[] matrix;
	delete[] disM;
	return EXIT_SUCCESS;
}