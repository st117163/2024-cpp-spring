#include<iostream>
#include<fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

class CGraph {
public:
	CGraph()
		: _N(0), _M(0), _disCount(0), _matrix(nullptr), _disM(nullptr) {}
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
	void CreateGraph(char free_cells = '.', char borders = '#')
	{
		init();
		for (int i = 0; i < _N + 2; ++i)
		{
			for (int j = 0; j < _M + 2; ++j)
			{
				if (i != 0 && j != 0 && i != _N + 1 && j != _M + 1)
				{
					_matrix[i][j] = free_cells;
				}
				else
				{
					_matrix[i][j] = borders;
				}
			}
		}
	}
	void cleanDisM()
	{
		deleteDisM();
		initDisM();
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
	void deleteDisM()
	{
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
		deleteDisM();
	}
};

int main()
{
	int x, y;
	x = 2;
	y = 3;
	CGraph graph = CGraph(x, y, 1);
}