#include<iostream>
#include<fstream>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

char** readMatrix(int x, int y)
{
	char** matrix = new char* [x];

	for (int i = 0; i < x; ++i)
	{
		matrix[i] = new char[y];
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
			matrix[i][j] = 100001;
		}
	}
	return matrix;
}


void getCoords(int& xs, int& ys, char l, char** matrix, int x, int y)
{
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (matrix[i][j] == l)
			{
				xs = i;
				ys = j;
			}
		}
	}
}

int My_BFS(int x, int y, int** disMx, int** disMy, char** matrix)
{
	int xs = 0;
	int ys = 0;
	getCoords(xs, ys, 'S', matrix, x, y);

	disMx[xs][ys] = 0;
	disMy[xs][ys] = 0;

	std::queue<int> q;
	q.push(xs);
	q.push(ys);
	while (!q.empty())
	{
		int xn = q.front();
		q.pop();
		int yn = q.front();
		q.pop();

		if (matrix[xn][yn] == 'E')
		{
			return disMx[xn][yn];
		}

		if (matrix[xn][yn] == 'B')
		{
			int c = q.front();
			q.pop();

			switch (c)
			{
			case 1:
				if (xn > 0)
				{
					if (matrix[xn - 1][yn] != '#')
					{
						if (matrix[xn - 1][yn] == 'B' && disMx[xn - 1][yn] == 100001)
						{
							disMx[xn - 1][yn] = disMx[xn][yn] + 1;
							q.push(xn - 1);
							q.push(yn);
							q.push(1);
						}
						else if (disMx[xn - 1][yn] == 100001)
						{
							disMx[xn - 1][yn] = disMx[xn][yn] + 1;
							disMy[xn - 1][yn] = disMx[xn][yn] + 1;
							q.push(xn - 1);
							q.push(yn);
						}
					}
				}
				break;
			case 2:
				if (yn > 0)
				{
					if (matrix[xn][yn - 1] != '#')
					{
						if (matrix[xn][yn - 1] == 'B' && disMy[xn][yn - 1] == 100001)
						{
							disMy[xn][yn - 1] = disMy[xn][yn] + 1;
							q.push(xn);
							q.push(yn - 1);
							q.push(2);
						}
						else if (disMy[xn][yn - 1] == 100001)
						{
							disMx[xn][yn - 1] = disMy[xn][yn] + 1;
							disMy[xn][yn - 1] = disMy[xn][yn] + 1;
							q.push(xn);
							q.push(yn - 1);
						}
					}
				}
				break;
			case 3:
				if (xn + 1< x)
				{
					if (matrix[xn + 1][yn] != '#')
					{
						if (matrix[xn + 1][yn] == 'B' && disMx[xn + 1][yn] == 100001)
						{
							disMx[xn + 1][yn] = disMx[xn][yn] + 1;
							q.push(xn + 1);
							q.push(yn);
							q.push(3);
						}
						else if (disMx[xn + 1][yn] == 100001)
						{
							disMx[xn + 1][yn] = disMx[xn][yn] + 1;
							disMy[xn + 1][yn] = disMx[xn][yn] + 1;
							q.push(xn + 1);
							q.push(yn);
						}
					}
				}
				break;
			case 4:
				if (yn +1< y)
				{
					if (matrix[xn][yn + 1] != '#')
					{
						if (matrix[xn][yn + 1] == 'B' && disMy[xn][yn + 1] == 100001)
						{
							disMy[xn][yn + 1] = disMy[xn][yn] + 1;
							q.push(xn);
							q.push(yn + 1);
							q.push(4);
						}
						else if (disMy[xn][yn + 1] == 100001)
						{
							disMx[xn][yn + 1] = disMy[xn][yn] + 1;
							disMy[xn][yn + 1] = disMy[xn][yn] + 1;
							q.push(xn);
							q.push(yn + 1);
						}
					}
				}
				break;
			default:
				break;
			}
		}
		else
		{
			if (xn > 0)
			{
				if (matrix[xn - 1][yn] != '#')
				{
					if (matrix[xn - 1][yn] == 'B' && disMx[xn - 1][yn] == 100001)
					{
						disMx[xn - 1][yn] = disMx[xn][yn] + 1;
						q.push(xn - 1);
						q.push(yn);
						q.push(1);
					}
					else if (disMx[xn - 1][yn] == 100001)
					{
						disMx[xn - 1][yn] = disMx[xn][yn] + 1;
						disMy[xn - 1][yn] = disMy[xn][yn] + 1;
						q.push(xn - 1);
						q.push(yn);
					}
				}
			}
			if (yn > 0)
			{
				if (matrix[xn][yn - 1] != '#')
				{
					if (matrix[xn][yn - 1] == 'B' && disMy[xn][yn - 1] == 100001)
					{
						disMy[xn][yn - 1] = disMy[xn][yn] + 1;
						q.push(xn);
						q.push(yn - 1);
						q.push(2);
					}
					else if (disMy[xn][yn - 1] == 100001)
					{
						disMx[xn][yn - 1] = disMx[xn][yn] + 1;
						disMy[xn][yn - 1] = disMy[xn][yn] + 1;
						q.push(xn);
						q.push(yn - 1);
					}
				}
			}
			if (xn + 1< x)
			{
				if (matrix[xn + 1][yn] != '#')
				{
					if (matrix[xn + 1][yn] == 'B' && disMx[xn + 1][yn] == 100001)
					{
						disMx[xn + 1][yn] = disMx[xn][yn] + 1;
						q.push(xn + 1);
						q.push(yn);
						q.push(3);
					}
					else if (disMx[xn + 1][yn] == 100001)
					{
						disMx[xn + 1][yn] = disMx[xn][yn] + 1;
						disMy[xn + 1][yn] = disMy[xn][yn] + 1;
						q.push(xn + 1);
						q.push(yn);
					}
				}
			}
			if (yn + 1 < y)
			{
				if (matrix[xn][yn + 1] != '#')
				{
					if (matrix[xn][yn + 1] == 'B' && disMy[xn][yn + 1] == 100001)
					{
						disMy[xn][yn + 1] = disMy[xn][yn] + 1;
						q.push(xn);
						q.push(yn + 1);
						q.push(4);
					}
					else if (disMy[xn][yn + 1] == 100001)
					{
						disMx[xn][yn + 1] = disMx[xn][yn] + 1;
						disMy[xn][yn + 1] = disMy[xn][yn] + 1;
						q.push(xn);
						q.push(yn + 1);
					}
				}
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

	char** matrix = readMatrix(x, y);
	int** disMx = createDisM(x, y);
	int** disMy = createDisM(x, y);

	fout << My_BFS(x, y, disMx, disMy, matrix) << std::endl;

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}