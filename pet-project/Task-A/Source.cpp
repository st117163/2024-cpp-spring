#include<iostream>
#include<fstream>
#include<string>

class CGraph {
public:
	CGraph();
	CGraph(int vertexes);
	~CGraph();
	void fRead(std::string filename);
	int RootLen();


private:
	void init();
	void initMatrix();
	void initMinRootMatrix();
	void calcMinRootMatrix();
	void finalMinRootMatrix();
	void dispose();

	int _vertexes;
	int _start;
	int _end;
	int** _matrix;
	int** _minrootmatr;
};


int main(int argc, char* argv[])
{
	CGraph graph;
	std::ofstream fout("output.txt");
	graph.fRead("input.txt");
	fout << graph.RootLen() << std::endl;
	fout.close();
	return EXIT_SUCCESS;
}

CGraph::CGraph()
	: _vertexes(0), _start(0), _end(0), _matrix(nullptr), _minrootmatr(nullptr) {}

CGraph::CGraph(int vertexes)
	: _vertexes(vertexes), _start(0), _end(0), _matrix(nullptr), _minrootmatr(nullptr)
{
	init();
}

CGraph::~CGraph()
{
	dispose();
}

void CGraph::fRead(std::string filename)
{
	std::ifstream fin(filename);
	fin >> _vertexes;
	initMatrix();
	for (int i = 0; i < _vertexes; ++i)
	{
		for (int j = 0; j < _vertexes; ++j)
		{
			fin >> _matrix[i][j];
		}
	}
	fin >> _start;
	--_start;
	fin >> _end;
	--_end;
	fin.close();
}

int CGraph::RootLen()
{
	finalMinRootMatrix();
	return _minrootmatr[_start][_end];
}

void CGraph::init()
{
	dispose();
	initMatrix();
	initMinRootMatrix();
}

void CGraph::initMatrix()
{
	if (_vertexes == 0)
	{
		return;
	}
	_matrix = new int* [_vertexes];
	for (int i = 0; i < _vertexes; ++i)
	{
		_matrix[i] = new int[_vertexes] { 0 };
	}
}

void CGraph::initMinRootMatrix()
{
	if (_matrix == nullptr)
	{
		return;
	}
	_minrootmatr = new int* [_vertexes];
	for (int i = 0; i < _vertexes; ++i)
	{
		_minrootmatr[i] = new int[_vertexes] { 0 };
	}
}

void CGraph::calcMinRootMatrix()
{
	initMinRootMatrix();
	for (int i = 0; i < _vertexes; ++i)
	{
		for (int j = 0; j < _vertexes; ++j)
		{
			if (_matrix[i][j] != 0)
			{
				_minrootmatr[i][j] = _matrix[i][j];
			}
			else
			{
				_minrootmatr[i][j] = 9999;
			}
		}
	}


	for (int k = 0; k < _vertexes; k++)
	{
		for (int i = 0; i < _vertexes; i++)
		{
			for (int j = 0; j < _vertexes; j++)
			{
				if (_minrootmatr[i][j] > (_minrootmatr[i][k] + _minrootmatr[k][j]))
					_minrootmatr[i][j] = _minrootmatr[i][k] + _minrootmatr[k][j];
			}
		}
	}
}

void CGraph::finalMinRootMatrix()
{
	calcMinRootMatrix();
	for (int i = 0; i < _vertexes; i++)
	{
		for (int j = 0; j < _vertexes; j++)
		{
			if (i == j)
			{
				_minrootmatr[i][j] = 0;
			}
			else if (_minrootmatr[i][j] == 9999)
			{
				_minrootmatr[i][j] = -1;
			}
		}
	}
}

void CGraph::dispose()
{
	if (_matrix != nullptr)
	{
		for (int i = 0; i < _vertexes; ++i)
		{
			delete[] _matrix[i];
		}
		delete[] _matrix;
		_matrix = nullptr;
	}
	if (_minrootmatr != nullptr)
	{
		for (int i = 0; i < _vertexes; ++i)
		{
			delete[] _minrootmatr[i];
		}
		delete[] _minrootmatr;
		_minrootmatr = nullptr;
	}
}