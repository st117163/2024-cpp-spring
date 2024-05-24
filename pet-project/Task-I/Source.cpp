#include<iostream>
#include<fstream>
#include<string>
#include<queue>
std::string** ReadFile(std::string filename)
{
	std::ifstream fin(filename);

	int n = 0;
	fin >> n;

	std::string** reactions = new std::string * [n + 1];
	int tmp = n;
	for (int i = 0; i < n; ++i)
	{
		reactions[i] = new std::string[2];
		std::string strelka = "";

		fin >> reactions[i][0];
		fin >> strelka;
		fin >> reactions[i][1];
	}
	reactions[n] = new std::string[2];
	fin >> reactions[n][0];
	fin >> reactions[n][1];
	fin.close();
	return reactions;
}

int ansfunc(std::string** reactions, int n)
{
	std::string start = reactions[n][0];
	std::string end = reactions[n][1];
	std::queue <std::string> q;
	q.push(start);

	int len[1001] = { 0 };

	len[0] = 0;

	int k = 1;
	int l = 0;
	while (!q.empty())
	{
		std::string sub = q.front();
		q.pop();
		if (sub == end)
		{
			return len[l];
		}
		for (int i = 0; i < n; ++i)
		{
			if (reactions[i][0] == sub)
			{
				len[k] = len[l] + 1;
				++k;

				q.push(reactions[i][1]);
				reactions[i][0] = "passed";
			}
		}
		++l;
	}
	return -1;

}

int main(int argc, char* argv[])
{
	std::ifstream fin("input.txt");
	int n = 0;
	fin >> n;

	std::string** reactions = ReadFile("input.txt");

	std::ofstream fout("output.txt");
	fout << ansfunc(reactions, n) << std::endl;

	fin.close();
	fout.close();
	delete[] reactions;

	return EXIT_SUCCESS;
}