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
	bool haslen()
	{
		Pos start = getcoord('@');
		int ans = BFS(start);
		if (ans == -1)
		{
			return false;
		}
		return true;
	}
	void printMatrix()
	{
		nazad();
		for (int i = 1; i < _N + 1; ++i)
		{
			for (int j = 1; j < _M + 1; ++j)
			{
				fout << _matrix[i][j];
			}
			fout << std::endl;
		}
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
			if (_matrix[cur.x][cur.y] == 'X')
			{
				while (!q.empty())
				{
					q.pop();
				}
				return _disM[cur.x][cur.y][0];
			}
			step1(cur);//x+1
			step2(cur);//x-1
			step3(cur);//y+1
			step4(cur);//y-1
		}
		return -1;
	}
	Pos getcoord(const char c)
	{
		for (int i = 0; i < _N + 2; ++i)
		{
			for (int j = 0; j < _M + 2; ++j)
			{
				if (_matrix[i][j] == c)
				{
					return Pos(i, j);
				}
			}
		}
		return Pos();
	}
	void step1(Pos cur)
	{
		Pos tmp = Pos(cur.x + 1, cur.y);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step2(Pos cur)
	{
		Pos tmp = Pos(cur.x - 1, cur.y);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step3(Pos cur)
	{
		Pos tmp = Pos(cur.x, cur.y + 1);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step4(Pos cur)
	{
		Pos tmp = Pos(cur.x, cur.y - 1);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	bool step(Pos newpos)
	{
		if (_matrix[newpos.x][newpos.y] != 'O' && _disM[newpos.x][newpos.y][0] == -1)
		{
			return true;
		}
		return false;
	}
	void nazad()
	{
		Pos f = getcoord('X');
		int dis = _disM[f.x][f.y][0];
		while (dis > 0)
		{
			_matrix[f.x][f.y] = '+';

			if (_disM[f.x - 1][f.y][0] == dis - 1)
			{
				--dis;
				--f.x;
				continue;
			}
			if (_disM[f.x + 1][f.y][0] == dis - 1)
			{
				--dis;
				++f.x;
				continue;
			}
			if (_disM[f.x][f.y - 1][0] == dis - 1)
			{
				--dis;
				--f.y;
				continue;
			}
			if (_disM[f.x][f.y + 1][0] == dis - 1)
			{
				--dis;
				++f.y;
				continue;
			}
		}
	}
	queue<Pos> q;
};

int main(int argc, char* argv[])
{
	int  n = 0;
	fin >> n;

	MyBFS labyr = MyBFS(n, n, 1);
	labyr.fReadGraph('O');

	if (labyr.haslen())
	{
		fout << 'Y' << std::endl;
		labyr.printMatrix();
	}
	else
	{
		fout << 'N' << std::endl;
	}
	fin.close();
	fout.close();
	return EXIT_SUCCESS;
}