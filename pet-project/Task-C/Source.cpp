#include<iostream>
#include<fstream>
#include<string>

int abs_n(int a)
{
	if (a < 0)
	{
		return -a;
	}
	else
	{
		return a;
	}
}
int min(int a, int b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}
int** readMatrix(std::string filename)
{
	std::ifstream fin(filename);
	int x = 0;
	int y = 0;
	fin >> x;
	fin >> y;
	int** matrix = new int* [x];
	for (int i = 0; i < x; ++i)
	{
		matrix[i] = new int[y];
		for (int j = 0; j < y; ++j)
		{
			fin >> matrix[i][j];
		}
	}
	fin.close();
	return matrix;
}
int OneCount(int** matrix, int x, int y)
{
	int n = 0;
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (matrix[i][j] == 1)
			{
				++n;
			}
		}
	}
	return n;
}
int** edinici(int x, int y, int** matrix, int n)
{
	int** coords = new int* [n];
	int k = 0;
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (matrix[i][j] == 1)
			{
				coords[k] = new int[2]{ i, j };
				++k;
			}
		}
	}
	return coords;
}
int** ansfunc(int x, int y, int** matrix, int n)
{
	int** answer = new int* [x];
	int** coords = edinici(x, y, matrix, n);

	for (int i = 0; i < x; ++i)
	{
		answer[i] = new int[y] {0};
	}
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			int min_dis = 10000;
			int tmp = 0;
			for (int k = 0; k < n; ++k)
			{
				tmp = abs_n(i - coords[k][0]) + abs_n(j - coords[k][1]);
				min_dis = min(min_dis, tmp);
			}
			answer[i][j] = min_dis;
		}
	}
	delete[] coords;
	return answer;

}
void PrintAnswer(int** answer, int x, int y, std::string filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			fout << answer[i][j] << " ";
		}
		fout << std::endl;
	}
	fout.close();
}

int main(int argc, char* argv[])
{
	std::ifstream fin("input.txt");
	int x = 0;
	int y = 0;

	fin >> x;
	fin >> y;
	fin.close();
	int** matrix = readMatrix("input.txt");
	int n = OneCount(matrix, x, y);
	int** answer = ansfunc(x, y, matrix, n);
	PrintAnswer(answer, x, y, "output.txt");
	delete[] matrix;
	delete[] answer;

	return EXIT_SUCCESS;
}
