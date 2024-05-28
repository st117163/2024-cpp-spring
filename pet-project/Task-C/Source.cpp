#include<iostream>
#include<fstream>
std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

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

struct Pos
{
	int x;
	int y;
	Pos() : x(0), y(0) {}
	Pos(const int x, const int y) : x(x), y(y) {}
};

class CGraph {
public:
	CGraph()
		: _N(0), _M(0), _disCount(), _matrix(nullptr), _disM(nullptr) {}
	CGraph(int N, int M, const int disCount)
		: _N(N), _M(M), _disCount(disCount), _matrix(nullptr), _disM(nullptr)
	{
		init();
	}
	~CGraph()
	{
		dispose();
	}
	void fReadGraph(char borders = '#')
	{
		if (!fin.is_open())
		{
			return;
		}
		init();
		for (int i = 0; i < _N + 2; ++i)
		{
			for (int j = 0; j < _M + 2; ++j)
			{
				if (i != 0 && j != 0 && i != _N + 1 && j != _M + 1)
				{
					fin >> _matrix[i][j];
				}
				else
				{
					_matrix[i][j] = borders;
				}
			}
		}
	}


	char** _matrix;
	int*** _disM;
	int _N; //количество строк
	int _M; //количество столбцов
	const int _disCount;

private:
	void init()
	{
		dispose();
		initMatrix();
		initDisM();
	}
	void initMatrix() {
		if (_N == 0 && _M == 0)
		{
			return;
		}
		_matrix = new char* [_N + 2];
		for (int i = 0; i < _N + 2; ++i)
		{
			_matrix[i] = new char[_M + 2];
		}
	}
	void initDisM()
	{
		if (_matrix == nullptr)
		{
			return;
		}
		_disM = new int** [_N + 2];
		for (int i = 0; i < _N + 2; ++i)
		{
			_disM[i] = new int* [_M + 2];
			for (int j = 0; j < _M + 2; ++j)
			{
				_disM[i][j] = new int[_disCount];
				for (int k = 0; k < _disCount; ++k)
					_disM[i][j][k] = -1;
			}
		}
	}
	void dispose()
	{
		if (_matrix != nullptr)
		{
			for (int i = 0; i < _N + 2; ++i)
			{
				delete[] _matrix[i];
			}
			delete[] _matrix;
			_matrix = nullptr;
		}
		if (_disM != nullptr)
		{
			for (int i = 0; i < _N + 2; ++i)
			{
				for (int j = 0; j < _M + 2; ++j)
				{
					delete _disM[i][j];
				}
				delete[] _disM[i];
			}
			delete[] _disM;
			_disM = nullptr;
		}
	}
};
class MyBFS : public CGraph {
public:
	MyBFS()
		: CGraph() {}
	MyBFS(int N, int M, const int DisCount)
		: CGraph(N, M, DisCount) {}
	void PrintAnswer()
	{
		ansfunc();
		for (int i = 1; i <= _N; ++i)
		{
			for (int j = 1; j <= _M; ++j)
			{
				fout << _disM[i][j][0] << " ";
			}
			fout << std::endl;
		}
	}

private:
	int OneCount()
	{

		int n = 0;
		for (int i = 0; i < _N + 2; ++i)
		{
			for (int j = 0; j < _M + 2; ++j)
			{
				if (_matrix[i][j] == '1')
				{
					++n;
				}
			}
		}
		return n;
	}
	Pos* edinici()
	{
		int n = OneCount();
		Pos* coords = new Pos[n];
		int k = 0;
		for (int i = 0; i < _N + 2; ++i)
		{
			for (int j = 0; j < _M + 2; ++j)
			{
				if (_matrix[i][j] == '1')
				{
					if(k < n)
					{
						coords[k] = Pos(i, j);
						++k;
					}
				}
			}
		}
		return coords;
	}
	void ansfunc()
	{
		int n = OneCount();
		Pos* coords = edinici();

		for (int i = 0; i < _N + 2; ++i)
		{
			for (int j = 0; j < _M + 2; ++j)
			{
				int min_dis = 10000;
				int tmp = 0;
				for (int k = 0; k < n; ++k)
				{
					tmp = abs_n(i - coords[k].x) + abs_n(j - coords[k].y);
					min_dis = min(min_dis, tmp);
				}
				_disM[i][j][0] = min_dis;
			}
		}
		delete[] coords;
	}
};



int main(int argc, char* argv[])
{
	int x = 0;
	int y = 0;

	fin >> x;
	fin >> y;
	MyBFS bfs = MyBFS(x, y, 1);

	bfs.fReadGraph();
	bfs.PrintAnswer();

	return EXIT_SUCCESS;
}
