#include<iostream>
#include<fstream>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

int** readMatrix(int x, int y)
{
	int** matrix = new int* [x];

	for (int i = 0; i < x; ++i)
	{
		matrix[i] = new int[y];
		for (int j = 0; j < y; ++j)
		{
			fin >> matrix[i][j];
		}
	}
	return matrix;
}
int** createDisM(int x, int y)
{
	int** matrix = new int* [x];

	for (int i = 0; i < x; ++i)
	{
		matrix[i] = new int[y];
		for (int j = 0; j < y; ++j)
		{
			matrix[i][j] = 10001;
		}
	}
	return matrix;
}



int My_BFS(int x, int y, int** disM, int** matrix)
{
	int xs = 0;
	int ys = 0;

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

		int tmp = xn;
		while (tmp > 0)
		{
			--tmp;
			if (matrix[tmp][yn] == 2)
			{
				return disM[xn][yn] + 1;
			}
			if (matrix[tmp][yn] == 1)
			{
				++tmp;
				break;
			}
		}
		if (xn != tmp)
		{
			if (disM[tmp][yn] == 10001)
			{
				disM[tmp][yn] = disM[xn][yn] + 1;
				q.push(tmp);
				q.push(yn);
			}
		}

		tmp = yn;
		while (tmp > 0)
		{
			--tmp;
			if (matrix[xn][tmp] == 2)
			{
				return disM[xn][yn] + 1;
			}
			if (matrix[xn][tmp] == 1)
			{
				++tmp;
				break;
			}
		}
		if (yn != tmp)
		{
			if (disM[xn][tmp] == 10001)
			{
				disM[xn][tmp] = disM[xn][yn] + 1;
				q.push(xn);
				q.push(tmp);
			}
		}

		tmp = xn;
		while (tmp < x - 1)
		{
			++tmp;
			if (matrix[tmp][yn] == 2)
			{
				return disM[xn][yn] + 1;
			}
			if (matrix[tmp][yn] == 1)
			{
				--tmp;
				break;
			}
		}
		if (xn != tmp)
		{
			if (disM[tmp][yn] == 10001)
			{
				disM[tmp][yn] = disM[xn][yn] + 1;
				q.push(tmp);
				q.push(yn);
			}
		}

		tmp = yn;
		while (tmp < y - 1)
		{
			++tmp;
			if (matrix[xn][tmp] == 2)
			{
				return disM[xn][yn] + 1;
			}
			if (matrix[xn][tmp] == 1)
			{
				--tmp;
				break;
			}
		}
		if (yn != tmp)
		{
			if (disM[xn][tmp] == 10001)
			{
				disM[xn][tmp] = disM[xn][yn] + 1;
				q.push(xn);
				q.push(tmp);
			}
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
	int x = 0;
	int y = 0;
	fin >> x;
	fin >> y;

	int** matrix = readMatrix(x, y);
	int** disM = createDisM(x, y);


	fout << My_BFS(x, y, disM, matrix) << std::endl;

	fin.close();
	fout.close();
	for (int i = 0; i < x; ++i)
	{
		delete[] matrix[i];
		delete[] disM[i];
	}
	delete[] matrix;
	delete[] disM;

	return EXIT_SUCCESS;
}