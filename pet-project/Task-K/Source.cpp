#include<iostream>
#include<fstream>
#include<queue>
#include<map>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

class Jammed
{
public:

	Jammed() : sharp_i(0), sharp_j(0), desk() {}
	Jammed(const Jammed& other);
	void fReadJammed();
	Jammed move_N() const;
	Jammed move_S() const;
	Jammed move_W() const;
	Jammed move_E() const;
	bool operator == (const Jammed& other) const;
	bool operator < (const Jammed& other) const;

private:

	int sharp_i;
	int sharp_j;
	char desk[2][4];
};

int jammedBFS(Jammed start, Jammed end)
{
	std::queue <Jammed> q;
	q.push(start);

	std::map<Jammed, int>  lens;
	lens[start] = 0;

	while (!q.empty())
	{
		Jammed jam = q.front();
		q.pop();

		if (jam == end)
		{
			return lens[jam];
		}
		Jammed jam_N = jam.move_N();
		if (lens.count(jam_N) == 0)
		{
			lens[jam_N] = lens[jam] + 1;
			q.push(jam_N);
		}

		Jammed jam_S = jam.move_S();
		if (lens.count(jam_S) == 0)
		{
			lens[jam_S] = lens[jam] + 1;
			q.push(jam_S);
		}

		Jammed jam_W = jam.move_W();
		if (lens.count(jam_W) == 0)
		{
			lens[jam_W] = lens[jam] + 1;
			q.push(jam_W);
		}

		Jammed jam_E = jam.move_E();
		if (lens.count(jam_E) == 0)
		{
			lens[jam_E] = lens[jam] + 1;
			q.push(jam_E);
		}

	}
	return -1;
}

int main(int argc, char* argv[])
{
	Jammed start;
	Jammed end;
	start.fReadJammed();
	end.fReadJammed();
	fout << jammedBFS(start, end);

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}


Jammed::Jammed(const Jammed& other)
{
	sharp_i = other.sharp_i;
	sharp_j = other.sharp_j;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			desk[i][j] = other.desk[i][j];
		}
	}
}

void Jammed::fReadJammed()
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			fin >> desk[i][j];
			if (desk[i][j] == '#')
			{
				sharp_i = i;
				sharp_j = j;
			}
		}
	}
}

Jammed Jammed::move_N() const
{
	Jammed jam = *this;
	if (sharp_i - 1 < 0)
	{
		return jam;
	}
	else
	{
		jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i - 1][sharp_j];
		jam.desk[sharp_i - 1][sharp_j] = '#';
		--jam.sharp_i;
	}
	return jam;
}

Jammed Jammed::move_S() const
{
	Jammed jam = *this;
	if (sharp_i + 1 > 1)
	{
		return jam;
	}
	else
	{
		jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i + 1][sharp_j];
		jam.desk[sharp_i + 1][sharp_j] = '#';
		++jam.sharp_i;
	}
	return jam;
}

Jammed Jammed::move_W() const
{
	Jammed jam = *this;
	if (sharp_j - 1 < 0)
	{
		return jam;
	}
	else
	{
		jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i][sharp_j - 1];
		jam.desk[sharp_i][sharp_j - 1] = '#';
		--jam.sharp_j;
	}
	return jam;
}

Jammed Jammed::move_E() const
{
	Jammed jam = *this;
	if (sharp_j + 1 > 3)
	{
		return jam;
	}
	else
	{
		jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i][sharp_j + 1];
		jam.desk[sharp_i][sharp_j + 1] = '#';
		++jam.sharp_j;
	}
	return jam;
}

bool Jammed::operator==(const Jammed& other) const
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (desk[i][j] != other.desk[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool Jammed::operator<(const Jammed& other) const
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (desk[i][j] != other.desk[i][j])
			{
				return desk[i][j] < other.desk[i][j];
			}
		}
	}
	return false;
}
