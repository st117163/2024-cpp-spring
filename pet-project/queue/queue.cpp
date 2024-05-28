#include <iostream>

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

int main(int argc, char* argv[])
{
	queue <int> q;
	int n = 0;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int data = 0;
		std::cin >> data;
		q.push(data);
	}
	for (int i = 0; i <= n; ++i)
	{
		std::cout << q.front() << std::endl;
		q.pop();
	}
	return EXIT_SUCCESS;
}