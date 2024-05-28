#include<iostream>
#include<fstream>
#include<string>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Pos
{
	int x;
	int y;
	int side;// 0 - from N, 1 - from W, 2 - from S, 3 - from E
	Pos() : x(0), y(0), side(0) {}
	Pos(const int x, const int y, const int s) : x(x), y(y), side(s) {}
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
	void fReadSpecial()
	{
		if (!fin.is_open())
		{
			return;
		}		
		init();
		char dump[21] = {};
		fin.getline(dump, 21);
		for (int i = 0; i < _N + 2; ++i)
		{
			fin.getline(_matrix[i], 21);
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
	int getlen()
	{
		Pos start = getcoord('S');
		int ans = BFS(start);
		return ans;
	}



private:
	int BFS(Pos start)
	{
		q.push(start);
		q.push(Pos(start.x, start.y, 1));
		q.push(Pos(start.x, start.y, 2));
		q.push(Pos(start.x, start.y, 3));
		_disM[start.x][start.y][0] = 0;
		_disM[start.x][start.y][1] = 0;
		_disM[start.x][start.y][2] = 0;
		_disM[start.x][start.y][3] = 0;

		while (!q.empty())
		{
			Pos cur = q.front();
			q.pop();
			if (_matrix[cur.x][cur.y] == 'F')
			{
				while (!q.empty())
				{
					q.pop();
				}
				return _disM[cur.x][cur.y][cur.side];
			}
			switch (cur.side)
			{
			case 0:
				step1(cur);//x+1
				step4(cur);//y-1
				break;
			case 1:
				step1(cur);
				step3(cur);//y+1
				break;
			case 2:
				step2(cur);//x-1
				step3(cur);
				break;
			case 3:
				step2(cur);
				step4(cur);
				break;
			default:
				break;
			}

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
					return Pos(i, j, 0);
				}
			}
		}
		return Pos();
	}
	void step1(Pos cur)
	{
		Pos tmp = Pos(cur.x + 1, cur.y, 0);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][tmp.side] = _disM[cur.x][cur.y][cur.side] + 1;

		}
	}
	void step2(Pos cur)
	{
		Pos tmp = Pos(cur.x - 1, cur.y, 2);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][tmp.side] = _disM[cur.x][cur.y][cur.side] + 1;

		}
	}
	void step3(Pos cur)
	{
		Pos tmp = Pos(cur.x, cur.y + 1, 1);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][tmp.side] = _disM[cur.x][cur.y][cur.side] + 1;

		}
	}
	void step4(Pos cur)
	{
		Pos tmp = Pos(cur.x, cur.y - 1, 3);
		if (step(tmp))
		{
			q.push(tmp);
			_disM[tmp.x][tmp.y][tmp.side] = _disM[cur.x][cur.y][cur.side] + 1;

		}
	}
	bool step(Pos newpos)
	{
		if (_matrix[newpos.x][newpos.y] != 'X' && _disM[newpos.x][newpos.y][newpos.side] == -1)
		{
			return true;
		}
		return false;
	}

queue<Pos> q;
};


int main(int argc, char* argv[])
{
	int x = 0;
	int y = 0;
	fin >> x;
	fin >> y;

	MyBFS onlyrigt = MyBFS(x, y, 4);
	onlyrigt.fReadSpecial();

	fout << onlyrigt.getlen();

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}