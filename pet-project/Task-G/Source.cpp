#include<iostream>
#include<fstream>
#include<string>
#include<queue>
int** initDesk()
{
	int** desk = new int* [8];
	for (int i = 0; i < 8; ++i)
	{
		desk[i] = new int[8];
		for (int j = 0; j < 8; ++j)
		{
			desk[i][j] = 100000;
		}
	}
	return desk;
}
void pullDesk1(int x, int y, int** desk)
{
	desk[x][y] = 0;
	std::queue<int> qx;
	std::queue<int> qy;
	qx.push(x);
	qy.push(y);
	while (!qx.empty())
	{
		int xt = qx.front();
		int yt = qy.front();
		qx.pop();
		qy.pop();
		if ((xt + 2) < 8 && (yt + 1) < 8 && desk[xt + 2][yt + 1] == 100000)
		{
			desk[xt + 2][yt + 1] = desk[xt][yt] + 1;
			qx.push(xt + 2);
			qy.push(yt + 1);
		}
		if ((xt + 1) < 8 && (yt + 2) < 8 && desk[xt + 1][yt + 2] == 100000)
		{
			desk[xt + 1][yt + 2] = desk[xt][yt] + 1;
			qx.push(xt + 1);
			qy.push(yt + 2);
		}
		if ((xt + 2) < 8 && (yt - 1) >= 0 && desk[xt + 2][yt - 1] == 100000)
		{
			desk[xt + 2][yt - 1] = desk[xt][yt] + 1;
			qx.push(xt + 2);
			qy.push(yt - 1);
		}
		if ((xt + 1) < 8 && (yt - 2) >= 0 && desk[xt + 1][yt - 2] == 100000)
		{
			desk[xt + 1][yt - 2] = desk[xt][yt] + 1;
			qx.push(xt + 1);
			qy.push(yt - 2);
		}
		if ((xt - 2) >= 0 && (yt + 1) < 8 && desk[xt - 2][yt + 1] == 100000)
		{
			desk[xt - 2][yt + 1] = desk[xt][yt] + 1;
			qx.push(xt - 2);
			qy.push(yt + 1);
		}
		if ((xt - 2) >= 0 && (yt - 1) >= 0 && desk[xt - 2][yt - 1] == 100000)
		{
			desk[xt - 2][yt - 1] = desk[xt][yt] + 1;
			qx.push(xt - 2);
			qy.push(yt - 1);
		}
		if ((xt - 1) >= 0 && (yt + 2) < 8 && desk[xt - 1][yt + 2] == 100000)
		{
			desk[xt - 1][yt + 2] = desk[xt][yt] + 1;
			qx.push(xt - 1);
			qy.push(yt + 2);
		}
		if ((xt - 1) >= 0 && (yt - 2) >= 0 && desk[xt - 1][yt - 2] == 100000)
		{
			desk[xt - 1][yt - 2] = desk[xt][yt] + 1;
			qx.push(xt - 1);
			qy.push(yt - 2);
		}
	}

}
int pullDesk2(int x, int y, int** desk, int** desk1)
{
	desk[x][y] = 0;
	std::queue<int> qx;
	std::queue<int> qy;
	qx.push(x);
	qy.push(y);
	while (!qx.empty())
	{
		int xt = qx.front();
		int yt = qy.front();
		qx.pop();
		qy.pop();
		if (desk1[xt][yt] == desk[xt][yt])
		{
			return desk1[xt][yt];
		}
		if ((xt + 2) < 8 && (yt + 1) < 8 && desk[xt + 2][yt + 1] == 100000)
		{
			desk[xt + 2][yt + 1] = desk[xt][yt] + 1;
			qx.push(xt + 2);
			qy.push(yt + 1);
		}
		if ((xt + 1) < 8 && (yt + 2) < 8 && desk[xt + 1][yt + 2] == 100000)
		{
			desk[xt + 1][yt + 2] = desk[xt][yt] + 1;
			qx.push(xt + 1);
			qy.push(yt + 2);
		}
		if ((xt + 2) < 8 && (yt - 1) >= 0 && desk[xt + 2][yt - 1] == 100000)
		{
			desk[xt + 2][yt - 1] = desk[xt][yt] + 1;
			qx.push(xt + 2);
			qy.push(yt - 1);
		}
		if ((xt + 1) < 8 && (yt - 2) >= 0 && desk[xt + 1][yt - 2] == 100000)
		{
			desk[xt + 1][yt - 2] = desk[xt][yt] + 1;
			qx.push(xt + 1);
			qy.push(yt - 2);
		}
		if ((xt - 2) >= 0 && (yt + 1) < 8 && desk[xt - 2][yt + 1] == 100000)
		{
			desk[xt - 2][yt + 1] = desk[xt][yt] + 1;
			qx.push(xt - 2);
			qy.push(yt + 1);
		}
		if ((xt - 2) >= 0 && (yt - 1) >= 0 && desk[xt - 2][yt - 1] == 100000)
		{
			desk[xt - 2][yt - 1] = desk[xt][yt] + 1;
			qx.push(xt - 2);
			qy.push(yt - 1);
		}
		if ((xt - 1) >= 0 && (yt + 2) < 8 && desk[xt - 1][yt + 2] == 100000)
		{
			desk[xt - 1][yt + 2] = desk[xt][yt] + 1;
			qx.push(xt - 1);
			qy.push(yt + 2);
		}
		if ((xt - 1) >= 0 && (yt - 2) >= 0 && desk[xt - 1][yt - 2] == 100000)
		{
			desk[xt - 1][yt - 2] = desk[xt][yt] + 1;
			qx.push(xt - 1);
			qy.push(yt - 2);
		}
	}
	return -1;
}
int main(int argc, char* argv[])
{
	std::ifstream fin("input.txt");

	std::string h1 = "";
	std::string h2 = "";

	fin >> h1;
	fin >> h2;

	int x1 = h1[0] - 'a';
	int y1 = h1[1] - '1';
	int x_end = h2[0] - 'a';
	int y_end = h2[1] - '1';

	int** desk1 = initDesk();
	int** desk2 = initDesk();

	pullDesk1(x1, y1, desk1);

	std::ofstream fout("output.txt");
	fout << pullDesk2(x_end, y_end, desk2, desk1) << std::endl;

	fin.close();
	fout.close();
	delete[] desk1;
	delete[] desk2;

	return EXIT_SUCCESS;
}


