#include<iostream>
#include<fstream>
#include<string>

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
	int getlen(Pos start, Pos finish)
	{
		BFS_horse1(start);
		return BFS_horse2(finish);
	}

private:
	void BFS_horse1(Pos start)
	{
		q.push(start);
		_disM[start.x][start.y][0] = 0;

		while (!q.empty())
		{
			Pos cur = q.front();
			q.pop();
			step1(cur, 0);//x+1 y+2
			step2(cur, 0);//x-1 y+2
			step3(cur, 0);//x+1 y-2
			step4(cur, 0);//x-1 y-2
			step5(cur, 0);//x+2 y+1
			step6(cur, 0);//x-2 y+1
			step7(cur, 0);//x+2 y-1
			step8(cur, 0);//x-2 y-1
		}
	}
	int BFS_horse2(Pos finish)
	{
		q.push(finish);
		_disM[finish.x][finish.y][1] = 0;

		while (!q.empty())
		{
			Pos cur = q.front();
			q.pop();
			if (_disM[cur.x][cur.y][0] == _disM[cur.x][cur.y][1])
			{
				return _disM[cur.x][cur.y][1];
			}
			step1(cur, 1);//x+1 y+2
			step2(cur, 1);//x-1 y+2
			step3(cur, 1);//x+1 y-2
			step4(cur, 1);//x-1 y-2
			step5(cur, 1);//x+2 y+1
			step6(cur, 1);//x-2 y+1
			step7(cur, 1);//x+2 y-1
			step8(cur, 1);//x-2 y-1
		}
		return -1;
	}
	void step1(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x + 1, cur.y + 2);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	void step2(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x - 1, cur.y + 2);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	void step3(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x + 1, cur.y - 2);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	void step4(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x - 1, cur.y - 2);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	void step5(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x + 2, cur.y + 1);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	void step6(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x - 2, cur.y + 1);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	void step7(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x + 2, cur.y - 1);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	void step8(Pos cur, const int n)
	{
		Pos tmp = Pos(cur.x - 2, cur.y - 1);
		if (step(tmp, n))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][n] = _disM[cur.x][cur.y][n] + 1;
		}
	}
	bool step(Pos newpos, const int n)
	{
		if (newpos.x < 10 && newpos.y < 10
			&& newpos.x > 0 && newpos.y > 0
			&& _matrix[newpos.x][newpos.y] == '.' && _disM[newpos.x][newpos.y][n] == -1)
		{
			return true;
		}
		return false;
	}
	queue<Pos> q;
};

int main(int argc, char* argv[])
{

	std::string h1 = "";
	std::string h2 = "";

	fin >> h1;
	fin >> h2;

	int x1 = h1[0] - 'a' + 1;
	int y1 = h1[1] - '1' + 1;
	int x_end = h2[0] - 'a' + 1;
	int y_end = h2[1] - '1' + 1;

	Pos start = Pos(x1, y1);
	Pos finish = Pos(x_end, y_end);

	MyBFS horses = MyBFS(8, 8, 2);
	horses.CreateGraph();
	fout << horses.getlen(start, finish);

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}


