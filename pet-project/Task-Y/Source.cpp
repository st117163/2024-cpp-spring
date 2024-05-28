#include<iostream>
#include<fstream>
#include<queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

struct Pos
{
	int x;
	int y;
	int vis;
	Pos() : x(0), y(0), vis(0) {}
	Pos(const int x, const int y, const int v) : x(x), y(y), vis(v) {}
};

int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}


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
		: CGraph(), q(), k(0), maxY(0), minX(), maxX() 
	{
		for (int i = 0; i < 51; ++i)
		{
			minX[i] = 51;
		}
	}
	MyBFS(int N, int M, const int DisCount, int K)
		: CGraph(N, M, DisCount), q(), k(K), maxY(0), minX(), maxX()
	{
		for (int i = 0; i < 51; ++i)
		{
			minX[i] = 51;
		}
	}
	void fReadStars(int n)
	{
		for (int i = 0; i < n; ++i)
		{
			int x = 0;
			int y = 0;
			fin >> x;
			fin >> y;
			maxY = max(maxY, y);
			minX[y] = min(minX[y], x);
			maxX[y] = max(maxX[y], x);
		}
	}
	int getlen()
	{
		int ans = BFS();
		cleanDisM();
		return ans;
	}

private:
	int BFS()
	{
		int v_start = calcVis(1, 1);

		std::queue<Pos> q;
		_disM[1][1][v_start] = 0;
		q.push(Pos(1, 1, v_start));

		while (!q.empty())
		{
			Pos pn = q.front();
			q.pop();

			if (pn.y >= maxY + 1 - k && pn.vis == ((1 << (2 * k)) - 1))
			{
				return _disM[pn.x][pn.y][pn.vis];
			}

			if (pn.x > 1)
			{
				int new_vis = pn.vis | calcVis(pn.x - 1, pn.y);
				Pos newp = Pos(pn.x - 1, pn.y, new_vis);
				if (_disM[newp.x][newp.y][newp.vis] == -1)
				{
					_disM[newp.x][newp.y][newp.vis] = _disM[pn.x][pn.y][pn.vis] + 1;
					q.push(newp);
				}
			}
			if (pn.x < 51 - k)
			{
				int new_vis = pn.vis | calcVis(pn.x + 1, pn.y);
				Pos newp = Pos(pn.x + 1, pn.y, new_vis);
				if (_disM[newp.x][newp.y][newp.vis] == -1)
				{
					_disM[newp.x][newp.y][newp.vis] = _disM[pn.x][pn.y][pn.vis] + 1;
					q.push(newp);
				}
			}
			if (pn.y < 51 - k && (pn.vis & 3) == 3)
			{
				int new_vis = (pn.vis >> 2) | calcVis(pn.x, pn.y + 1);
				Pos newp = Pos(pn.x, pn.y + 1, new_vis);
				if (_disM[newp.x][newp.y][newp.vis] == -1)
				{
					_disM[newp.x][newp.y][newp.vis] = _disM[pn.x][pn.y][pn.vis] + 1;
					q.push(newp);
				}
			}
		}
		return -1;
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
	int calcVis(int x, int y)
	{
		int vis = 0;
		for (int j = 0; j < k; ++j)
		{
			if (maxX[y + j] == 0)
			{
				vis |= 3 << (j * 2);
			}
			else
			{
				if (x <= minX[y + j] && minX[y + j] < x + k)
				{
					vis |= 1 << (j * 2);
				}
				if (x <= maxX[y + j] && maxX[y + j] < x + k)
				{
					vis |= 2 << (j * 2);
				}
			}
		}
		return vis;
	}

	queue<Pos> q;
	int k;//ширина кадра
	int maxY;
	int minX[51];
	int maxX[51];
};






int main(int argc, char* argv[])
{
	int n = 0;
	int k = 0;
	fin >> n;
	fin >> k;
	MyBFS field = MyBFS(50-k, 50-k, 1 << 2 * k, k);
	field.CreateGraph();
	field.fReadStars(n);

	fout << field.getlen();

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}