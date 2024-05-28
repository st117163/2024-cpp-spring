#include<iostream>
#include<fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Pos
{
	int x;
	int y;
	Pos(const int x, const int y) : x(x), y(y) {}
};

template <class T>

struct Node
{
	T data;
	Node* next;

	Node() : data(T()), next(nullptr) {}
	Node(T data) : data(data), next(nullptr) {}
	~Node() { data = T(); next = nullptr; }
};

template <class T>

class queue
{
public:
	queue() : head(nullptr), tail(nullptr) {}
	~queue() { dispose(); }

	bool empty() { return head == nullptr; }
	void push(T data)
	{
		Node<T>* node = new Node<T>(data);
		if (empty())
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}
	}
	void pop()
	{
		if (empty())
		{
			return;
		}
		Node<T>* dump = head;
		head = head->next;
		delete dump;
		return;
	}
	T front()
	{
		if (empty())
		{
			T null = T();
			return null;
		}
		else
		{
			return head->data;
		}
	}

private:
	void dispose()
	{
		while (!empty())
		{
			pop();
		}
	}
	Node<T>* head;
	Node<T>* tail;

};

class CGraph {
public:
	CGraph()
		: _N(0), _M(0), _disCount(), _matrix(nullptr), _disM(nullptr) {}
	CGraph(int N, int M,int disCount)
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
	int _disCount;

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

class MyBFS: CGraph
{
public:
	int Basic_BFS()
	{
		Pos start = getstart();
		if (start.x == -1)
		{
			return -1;
		}
		_q.push(start);
		while (!_q.empty())
		{
			Pos cur = _q.front();
			_q.pop();
			stepN();
			stepW();
			stepE();
			stepS();

		}
		return getfinishdis(char finish);
	}
private:
	Pos getstart()
	{
		if (_matrix != nullptr)
		{
			for (int i = 0; i < _N + 2; ++i)
			{
				for (int j = 0; j < _M + 2; ++j)
				{
					if (_matrix[i][j] == _start)
					{
						for (int n = 0; n < _disCount; ++n)
						{
							_disM[i][j][n] = 0;
						}
						return Pos(i, j);
					}
				}
			}
		}
		return Pos(-1, -1);
	}
	void stepN(Pos cur)
	{
		if()
	}
	void stepW();
	void stepE();
	void stepS();

	char _start;
	char _finish;
	queue<Pos> _q;

};