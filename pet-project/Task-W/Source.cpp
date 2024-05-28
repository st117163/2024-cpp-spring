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

class MyBFS : public CGraph {
public:
	MyBFS()
		: CGraph(), q() {}
	MyBFS(int N, int M, const int DisCount)
		: CGraph(N, M, DisCount), q() {}
	int getlen(char st, char end)
	{
		int ans = BFS(st, end);
		cleanDisM();
		return ans;
	}

private:
	int BFS(char st, char end)
	{
		Pos start = getcoord(st);
		q.push(start);
		_disM[start.x][start.y][0] = 0;

		while (!q.empty())
		{
			Pos cur = q.front();
			q.pop();
			if (_matrix[cur.x][cur.y] == end)
			{
				while (!q.empty())
				{
					q.pop();
				}
				return _disM[cur.x][cur.y][0];
			}
			step1(cur, st);//x+1
			step2(cur, st);//x-1
			step3(cur, st);//y+1
			step4(cur, st);//y-1
		}
		return -1;
	}

	void step1(Pos cur, char st)
	{
		Pos tmp = Pos(cur.x + 1, cur.y);
		if (step(tmp, st))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step2(Pos cur, char st)
	{
		Pos tmp = Pos(cur.x - 1, cur.y);
		if (step(tmp, st))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step3(Pos cur, char st)
	{
		Pos tmp = Pos(cur.x, cur.y + 1);
		if (step(tmp, st))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	void step4(Pos cur, char st)
	{
		Pos tmp = Pos(cur.x, cur.y - 1);
		if (step(tmp, st))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][0] = _disM[cur.x][cur.y][0] + 1;
		}
	}
	bool step(Pos newpos, char st)
	{
		char cell = _matrix[newpos.x][newpos.y];
		if (st == 'K')
		{
			if (cell != '#' && _disM[newpos.x][newpos.y][0] == -1)
			{
				return true;
			}
			return false;
		}
		else
		{
			if ((cell == '.' || cell == 'K' || cell == 'E') && _disM[newpos.x][newpos.y][0] == -1)
			{
				return true;
			}
			return false;
		}
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

	queue<Pos> q;
};


int main(int argc, char* argv[])
{
	int x = 0;
	int y = 0;
	fin >> x;
	fin >> y;

	MyBFS minotaur = MyBFS(x, y, 1);
	minotaur.fReadGraph('E');

	int way = minotaur.getlen('T', 'E');
	if (way != -1)
	{
		fout << way;
	}
	else
	{
		fout << "No way ";
		way = minotaur.getlen('T', 'K');
		if (way != -1)
		{
			fout << way << " ";
			way = minotaur.getlen('K', 'E');
			if (way != -1)
			{
				fout << way;
			}
			else
			{
				fout << "No way ";
			}
		}
		else
		{
			fout << "No key ";
		}
	}

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}