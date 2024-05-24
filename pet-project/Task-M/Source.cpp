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
void readMatrix(int x, int y, char(&matrix)[102][102])
{
	for (int i = 0; i < x+2; ++i)
	{
		for (int j = 0; j < y+2; ++j)
		{
			if (i == 0 || j == 0 || i == x + 1 || j == y + 1)
			{
				matrix[i][j] = '1';
			}
			else
			{
				fin >> matrix[i][j];
			}
		}
	}
}
void readEnters(int n, int(&enters)[100][2])
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			fin >> enters[i][j];
		}
	}
}

int MyBfs(int x, int y, char(&matrix)[102][102], int xs, int ys)
{
	Pos start = Pos(xs, ys);
	std::queue<Pos> q;
	q.push(start);

	int disM[102][102] = { 0 };
	for (int i = 0; i < 102; ++i)
	{
		for (int j = 0; j < 102; ++j)
		{
			disM[i][j] = -1;
		}
	}
	disM[xs][ys] = 0;

	while (!q.empty())
	{
		Pos pn = q.front();
		q.pop();
		if (matrix[pn.x][pn.y] == '*')
		{
			return disM[pn.x][pn.y];
		}
		if (matrix[pn.x - 1][pn.y] != '1' && disM[pn.x - 1][pn.y] == -1)
		{
			q.push(Pos(pn.x - 1, pn.y));
			disM[pn.x - 1][pn.y] = disM[pn.x][pn.y] + 1;
		}
		if (matrix[pn.x + 1][pn.y] != '1' && disM[pn.x + 1][pn.y] == -1)
		{
			q.push(Pos(pn.x + 1, pn.y));
			disM[pn.x + 1][pn.y] = disM[pn.x][pn.y] + 1;
		}
		if (matrix[pn.x ][pn.y - 1] != '1' && disM[pn.x ][pn.y - 1] == -1)
		{
			q.push(Pos(pn.x , pn.y - 1));
			disM[pn.x ][pn.y - 1] = disM[pn.x][pn.y] + 1;
		}
		if (matrix[pn.x ][pn.y + 1] != '1' && disM[pn.x ][pn.y + 1] == -1)
		{
			q.push(Pos(pn.x , pn.y + 1));
			disM[pn.x ][pn.y + 1] = disM[pn.x][pn.y] + 1;
		}
	}
	return 10001;
}

int min_ind(int* lens, int n)
{
	int min = 10000;
	int min_i = -1;
	for (int i = 0; i < n; ++i)
	{
		if (min > lens[i])
		{
			min = lens[i];
			min_i = i + 1;
		}
	}
	return min_i;
}

int main(int argc, char* argv[])
{
	int  x = 0;
	int  y = 0;

	fin >> x;
	fin >> y;

	char matrix[102][102] = { '0' };
	readMatrix(x, y, matrix);
	int n = 0;

	fin >> n;

	int enters[100][2] = { 0 };
	readEnters(n, enters);

	int lens[100] = { 0 };
	for (int i = 0; i < n; ++i)
	{
		int xs = enters[i][0];
		int ys = enters[i][1];
		lens[i] = MyBfs(x, y, matrix, xs, ys);
	}

	fout << min_ind(lens, n) << std::endl;

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}