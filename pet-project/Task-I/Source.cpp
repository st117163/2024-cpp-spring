#include<iostream>
#include<fstream>
#include<string>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

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

struct Reaction
{
	int n;
	std::string from;
	std::string to;
	Reaction() : n(0), from(""), to("") {}
	Reaction(int N, std::string From, std::string To) : n(N), from(From), to(To) {}
};

class ReactionList
{
public:

	ReactionList() : _N(0), _reactions(nullptr), _dis(nullptr) {}
	ReactionList(int N) : _N(N), _reactions(nullptr), _dis(nullptr) {}
	~ReactionList()
	{
		dispose();
	}
	void fReadReactions()
	{
		if (_N != 0)
		{
			init();
			for (int i = 0; i < _N; ++i)
			{
				std::string strelka = "->";
				std::string from = "->";
				std::string to = "->";

				fin >> from;
				fin >> strelka;
				fin >> to;
				_reactions[i] = Reaction(i, from, to);
			}
		}
	}

	int _N;
	Reaction* _reactions;
	int* _dis;
private:
	void init()
	{
		dispose();
		initReactions();
		initDis();
	}
	void initReactions()
	{
		_reactions = new Reaction[_N];
	}
	void initDis()
	{
		_dis = new int[_N]{0};
	}
	void dispose()
	{
		if (_reactions != nullptr)
		{
			delete[] _reactions;
		}
		_reactions = nullptr;
		if (_dis != nullptr)
		{
			delete[] _dis;
		}
		_dis = nullptr;
	}
};

class MyBFS : public ReactionList {
public:
	MyBFS()
		: ReactionList(), q() {}
	MyBFS(int N)
		: ReactionList(N), q() {}
	int getlen(std::string start, std::string finish)
	{
		return BFS_reactions(start, finish);
	}

private:
	int BFS_reactions(std::string start, std::string finish)
	{
		if (start == finish)
		{
			return 0;
		}
		for (int i = 0; i < _N; ++i)
		{
			if (_reactions[i].from == start)
			{
				q.push(_reactions[i]);
				_dis[i] = 1;
			}
		}
		while (!q.empty())
		{
			Reaction cur = q.front();
			q.pop();
			if (cur.to == finish)
			{
				return _dis[cur.n];
			}
			for (int i = 0; i < _N; ++i)
			{
				if (_reactions[i].from == cur.to)
				{
					_reactions[i].from = "passed";
					{

						_dis[i] = _dis[cur.n] + 1;
						q.push(_reactions[i]);
					}
				}
			}
		}
		return -1;
	}

	queue<Reaction> q;
};


int main(int argc, char* argv[])
{
	int n = 0;
	fin >> n;

	MyBFS reactions = MyBFS(n);
	reactions.fReadReactions();

	std::string start = "";
	std::string finish = "";

	fin >> start;
	fin >> finish;

	fout << reactions.getlen(start, finish) << std::endl;

	fin.close();
	fout.close();

	return EXIT_SUCCESS;
}