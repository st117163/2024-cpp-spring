#include<iostream>
#include<iostream>
#include<fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Pos
{
	int x;
	int y;
	Pos() : x(0), y(0) {}
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
		: CGraph(), q() {}
	MyBFS(int N, int M, const int DisCount)
		: CGraph(N, M, DisCount), q() {}
	int getlen(Pos start)
	{
		int ans = BFS(start);
		cleanDisM();
		return ans;
	}

private:
	int BFS(Pos start)
	{
		q.push(start);
		_disM[start.x][start.y][0] = 0;

		while (!q.empty())
		{
			Pos cur = q.front();
			q.pop();
			if (_matrix[cur.x][cur.y] == '2')
			{
				while (!q.empty())
				{
					q.pop();
				}
				return _disM[cur.x][cur.y][0];
			}
			step1(cur);//x+
			step2(cur);//x-
			step3(cur);//y+
			step4(cur);//y-
		}
		return -1;
	}

	void step1(Pos cur)
	{
		int i = 1;
		while (_matrix[cur.x + i][cur.y] != '1')
		{
			if (_matrix[cur.x + i][cur.y] == '2' && _disM[cur.x + i][cur.y][0] == -1)
			{
				q.push(Pos(cur.x + i, cur.y));
				_disM[cur.x + i][cur.y][0] = _disM[cur.x][cur.y][0] + 1;
				return;
			}
			++i;
		}
		if (_disM[cur.x + i - 1][cur.y][0] == -1)
		{
			q.push(Pos(cur.x + i - 1, cur.y));
			_disM[cur.x + i - 1][cur.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step2(Pos cur)
	{
		int i = 1;
		while (_matrix[cur.x - i][cur.y] != '1')
		{
			if (_matrix[cur.x - i][cur.y] == '2' && _disM[cur.x - i][cur.y][0] == -1)
			{
				q.push(Pos(cur.x - i, cur.y));
				_disM[cur.x - i][cur.y][0] = _disM[cur.x][cur.y][0] + 1;

				return;
			}
			++i;
		}
		if (_disM[cur.x - i + 1][cur.y][0] == -1)
		{
			q.push(Pos(cur.x - i + 1, cur.y));
			_disM[cur.x - i + 1][cur.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step3(Pos cur)
	{
		int i = 1;
		while (_matrix[cur.x][cur.y + i] != '1')
		{
			if (_matrix[cur.x][cur.y + i] == '2' && _disM[cur.x][cur.y + i][0] == -1)
			{
				q.push(Pos(cur.x, cur.y + i));
				_disM[cur.x][cur.y + i][0] = _disM[cur.x][cur.y][0] + 1;
				return;
			}
			++i;
		}
		if (_disM[cur.x][cur.y + i - 1][0] == -1)
		{
			q.push(Pos(cur.x, cur.y + i - 1));
			_disM[cur.x][cur.y + i - 1][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step4(Pos cur)
	{
		int i = 1;
		while (_matrix[cur.x][cur.y - i] != '1')
		{
			if (_matrix[cur.x][cur.y - i] == '2' && _disM[cur.x][cur.y - i][0] == -1)
			{
				q.push(Pos(cur.x, cur.y - i));
				_disM[cur.x][cur.y - i][0] = _disM[cur.x][cur.y][0] + 1;
				return;
			}
			++i;
		}
		if (_disM[cur.x][cur.y - i + 1][0] == -1)
		{
			q.push(Pos(cur.x, cur.y - i + 1));
			_disM[cur.x][cur.y - i + 1][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	queue<Pos> q;
};

int main(int argc, char* argv[])
{
	int x = 0;
	int y = 0;
	fin >> x;
	fin >> y;

	MyBFS labyr = MyBFS(x, y, 1);
	labyr.fReadGraph('1');

	fout << labyr.getlen(Pos(1, 1)) << std::endl;
	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}