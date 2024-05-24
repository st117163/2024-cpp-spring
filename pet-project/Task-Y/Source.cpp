#include<iostream>
#include<fstream>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Pos
{
	int x;
	int y;
	int vis;
	Pos(const int x, const int y, const int v) : x(x), y(y), vis(v) {}
};

int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

void fReadStars(int n, int(&minX)[51], int(&maxX)[51], int& maxY)
{
	for (int i = 0; i < n; ++i)
	{
		int x = 0;
		int y = 0;
		fin >> x;
		fin >> y;
		maxY = max(maxY, y);
		minX[y] = min(minX[y], x);
		maxX[y] = max(maxX[y], x);
	}
}

int*** initDisT(int k)
{
	int size = 1 << (2 * k);
	int*** dis = new int** [52 - k];
	for (int i = 0; i < 52 - k; ++i)
	{
		dis[i] = new int* [52 - k];
		for (int j = 0; j < 52 - k; ++j)
		{
			dis[i][j] = new int[size];
			for (int m = 0; m < size; ++m)
			{
				dis[i][j][m] = -1;
			}
		}
	}
	return dis;
}

int calcVis(int x, int y, int k, int(&minX)[51], int(&maxX)[51])
{
	int vis = 0;
	for (int j = 0; j < k; ++j)
	{
		if (maxX[y + j] == 0)
		{
			vis |= 3 << (j * 2);
		}
		else
		{
			if (x <= minX[y + j] && minX[y + j] < x + k)
			{
				vis |= 1 << (j * 2);
			}
			if (x <= maxX[y + j] && maxX[y + j] < x + k)
			{
				vis |= 2 << (j * 2);
			}
		}
	}
	return vis;
}

int MyBFS(int k, int(&minX)[51], int(&maxX)[51], int maxY)
{
	int*** disT = initDisT(k);
	int v_start = calcVis(1, 1, k, minX, maxX);

	std::queue<Pos> q;
	disT[1][1][v_start] = 0;
	q.push(Pos(1, 1, v_start));

	while (!q.empty())
	{
		Pos pn = q.front();
		q.pop();

		if (pn.y >= maxY + 1 - k && pn.vis == ((1 << (2 * k)) - 1))
		{
			return disT[pn.x][pn.y][pn.vis];
		}

		if (pn.x > 1)
		{
			int new_vis = pn.vis | calcVis(pn.x - 1, pn.y, k, minX, maxX);
			Pos newp = Pos(pn.x - 1, pn.y, new_vis);
			if (disT[newp.x][newp.y][newp.vis] == -1)
			{
				disT[newp.x][newp.y][newp.vis] = disT[pn.x][pn.y][pn.vis] + 1;
				q.push(newp);
			}
		}
		if (pn.x < 51 - k)
		{
			int new_vis = pn.vis | calcVis(pn.x + 1, pn.y, k, minX, maxX);
			Pos newp = Pos(pn.x + 1, pn.y, new_vis);
			if (disT[newp.x][newp.y][newp.vis] == -1)
			{
				disT[newp.x][newp.y][newp.vis] = disT[pn.x][pn.y][pn.vis] + 1;
				q.push(newp);
			}
		}
		if (pn.y < 51 - k && (pn.vis & 3) == 3)
		{
			int new_vis = (pn.vis >> 2) | calcVis(pn.x, pn.y + 1, k, minX, maxX);
			Pos newp = Pos(pn.x, pn.y + 1, new_vis);
			if (disT[newp.x][newp.y][newp.vis] == -1)
			{
				disT[newp.x][newp.y][newp.vis] = disT[pn.x][pn.y][pn.vis] + 1;
				q.push(newp);
			}
		}
	}
	for (int i = 0; i < 52 - k; ++i)
	{
		for (int j = 0; j < 52 - k; ++j)
		{
			delete[] disT[i][j];
		}
		delete[] disT[i];
	}
	delete[] disT;
}

int main(int argc, char* argv[])
{
	int n = 0;
	int k = 0;
	fin >> n;
	fin >> k;
	int maxY = 0;
	int minX[51] = { 0 };
	int maxX[51] = { 0 };
	for (int i = 0; i < 51; ++i)
	{
		minX[i] = 51;
	}
	fReadStars(n, minX, maxX, maxY);

	fout << MyBFS(k, minX, maxX, maxY);

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}