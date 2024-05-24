#include<iostream>
#include<fstream>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Pos
{
	int x;
	int y;
	Pos(const int x, const int y) : x(x), y(y) {}
};

void readMatrix(int x, int y, char(&matrix)[1002][1002])
{
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (i == 0 || j == 0 || i == x - 1 || j == y - 1)
			{
				matrix[i][j] = 'E';
			}
			else
			{
				fin >> matrix[i][j];
			}
		}
	}
}

void getCoords(int& xs, int& ys, char l, char(&matrix)[1002][1002])
{
	for (int i = 0; i < 1002; ++i)
	{
		for (int j = 0; j < 1002; ++j)
		{
			if (matrix[i][j] == l)
			{
				xs = i;
				ys = j;
			}
		}
	}
}

bool is_free(char lS, char n)
{
	if (lS == 'T')
	{
		return (n == '.' || n == 'K' || n == 'E');
	}
	else
		return (n != '#');
}

int My_BFS(int x, int y, char lS, char lF, char(&matrix)[1002][1002])
{
	int xs = 0;
	int ys = 0;

	getCoords(xs, ys, lS, matrix);

	int** dis = new int* [x];
	for (int i = 0; i < x; ++i)
	{
		dis[i] = new int[y];
		for (int j = 0; j < y; ++j)
		{
			dis[i][j] = -1;
		}
	}
	dis[xs][ys] = 0;

	std::queue<Pos> q;
	Pos start = Pos(xs, ys);
	q.push(start);

	while (!q.empty())
	{
		Pos pn = q.front();
		q.pop();

		if (matrix[pn.x][pn.y] == lF)
		{
			return dis[pn.x][pn.y];
		}

		if (is_free(lS, matrix[pn.x - 1][pn.y]) && dis[pn.x - 1][pn.y] < 0)
		{
			dis[pn.x - 1][pn.y] = dis[pn.x][pn.y] + 1;
			q.push(Pos(pn.x - 1, pn.y));
		}
		if (is_free(lS, matrix[pn.x + 1][pn.y]) && dis[pn.x + 1][pn.y] < 0)
		{
			dis[pn.x + 1][pn.y] = dis[pn.x][pn.y] + 1;
			q.push(Pos(pn.x + 1, pn.y));
		}
		if (is_free(lS, matrix[pn.x][pn.y - 1]) && dis[pn.x][pn.y - 1] < 0)
		{
			dis[pn.x][pn.y - 1] = dis[pn.x][pn.y] + 1;
			q.push(Pos(pn.x, pn.y - 1));
		}
		if (is_free(lS, matrix[pn.x][pn.y + 1]) && dis[pn.x][pn.y + 1] < 0)
		{
			dis[pn.x][pn.y + 1] = dis[pn.x][pn.y] + 1;
			q.push(Pos(pn.x, pn.y + 1));
		}
	}
	for (int i = 0; i < x; ++i)
	{
		delete[] dis[i];
	}
	delete[] dis;
	return -1;
}


int main(int argc, char* argv[])
{
	int x = 0;
	int y = 0;
	fin >> x;
	fin >> y;
	x += 2;
	y += 2;

	char matrix[1002][1002] = {};
	readMatrix(x, y, matrix);
	if (My_BFS(x, y, 'T', 'E', matrix) != -1)
	{
		fout << My_BFS(x, y, 'T', 'E', matrix);
	}
	else
	{
		fout << "No way ";
		if (My_BFS(x, y, 'T', 'K', matrix) != -1)
		{
			fout << My_BFS(x, y, 'T', 'K', matrix) << " ";
			if (My_BFS(x, y, 'K', 'E', matrix) != -1)
			{
				fout << My_BFS(x, y, 'K', 'E', matrix);
			}
			else
			{
				fout << "No way ";
			}
		}
		else
		{
			fout << "No key ";
		}
	}

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}