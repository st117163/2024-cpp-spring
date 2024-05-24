#include<iostream>
#include<fstream>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Pos
{
	int dir;
	int x;
	int y;
	Pos(const int dir, const int x, const int y) : dir(dir), x(x), y(y) {}
};


void getCoords(int& xs, int& ys, char l, char(&matrix)[21][21])
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (matrix[i][j] == l)
			{
				xs = i;
				ys = j;
			}
		}
	}
}

int My_BFS(int x, int y, char(&matrix)[21][21])
{
	int xs = 0;
	int ys = 0;
	
	getCoords(xs, ys, 'S', matrix);

	int dis[4][21][21] = { 0 };
	for (int k = 0; k < 4; ++k)
	{
		for (int i = 0; i < 21; ++i)
		{
			for (int j = 0; j < 21; ++j)
			{
				if (i != xs || j != ys)
					dis[k][i][j] = -1;
				else
				{
					dis[k][i][j] = 0;
				}
			}
		}
	}
	std::queue<Pos> q;
	Pos start = Pos(0, xs, ys);
	q.push(start);

	while (!q.empty())
	{
		Pos pn = q.front();
		q.pop();

		if (matrix[pn.x][pn.y] == 'F')
		{
			return dis[pn.dir-1][pn.x][pn.y];
		}
		switch (pn.dir)
		{
		case 0:
			if (matrix[pn.x - 1][pn.y] != 'X')
			{
				dis[0][pn.x - 1][pn.y] = 1;
				q.push(Pos(1, pn.x - 1, pn.y));

			}
			if (matrix[pn.x + 1][pn.y] != 'X')
			{
				dis[1][pn.x + 1][pn.y] = 1;
				q.push(Pos(2, pn.x + 1, pn.y));
			}
			if (matrix[pn.x][pn.y - 1] != 'X')
			{
				dis[2][pn.x][pn.y - 1] = 1;
				q.push(Pos(3, pn.x, pn.y - 1));
			}
			if (matrix[pn.x][pn.y + 1] != 'X')
			{
				dis[3][pn.x][pn.y + 1] = 1;
				q.push(Pos(4, pn.x, pn.y + 1));
			}
			break;
		case 1:
			if (matrix[pn.x - 1][pn.y] != 'X' && dis[0][pn.x - 1][pn.y] < 0)
			{
				dis[0][pn.x - 1][pn.y] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(1, pn.x - 1, pn.y));
			}
			if (matrix[pn.x][pn.y + 1] != 'X' && dis[3][pn.x][pn.y + 1] < 0)
			{
				dis[3][pn.x][pn.y + 1] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(4, pn.x, pn.y + 1));
			}
			break;
		case 2:
			if (matrix[pn.x + 1][pn.y] != 'X' && dis[1][pn.x + 1][pn.y] < 0)
			{
				dis[1][pn.x + 1][pn.y] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(2, pn.x + 1, pn.y));
			}
			if (matrix[pn.x][pn.y - 1] != 'X' && dis[2][pn.x][pn.y - 1] < 0)
			{
				dis[2][pn.x][pn.y - 1] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(3, pn.x, pn.y - 1));
			}
			break;
		case 3:
			if (matrix[pn.x][pn.y - 1] != 'X' && dis[2][pn.x][pn.y - 1] < 0)
			{
				dis[2][pn.x][pn.y - 1] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(3, pn.x, pn.y - 1));
			}
			if (matrix[pn.x - 1][pn.y] != 'X' && dis[0][pn.x - 1][pn.y] < 0)
			{
				dis[0][pn.x - 1][pn.y] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(1, pn.x - 1, pn.y));
			}
			break;
		case 4:
			if (matrix[pn.x + 1][pn.y] != 'X' && dis[1][pn.x + 1][pn.y] < 0)
			{
				dis[1][pn.x + 1][pn.y] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(2, pn.x + 1, pn.y));
			}
			if (matrix[pn.x][pn.y + 1] != 'X' && dis[3][pn.x][pn.y + 1] < 0)
			{
				dis[3][pn.x][pn.y + 1] = dis[pn.dir - 1][pn.x][pn.y] + 1;
				q.push(Pos(4, pn.x, pn.y + 1));
			}
			break;
		default:
			break;
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

	char dump[21] = {};
	fin.getline(dump, 21);

	char matrix[21][21] = {};

	for (int i = 0; i < x; ++i)
	{
		fin.getline(matrix[i], 21);
	}

	fout << My_BFS(x, y, matrix);

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}