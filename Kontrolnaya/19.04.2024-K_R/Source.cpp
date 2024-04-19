#include <iostream>

struct Node
{
	int data;
	Node* next;

	Node() : data(0), next(nullptr) {}
	Node(int data) : data(data), next(nullptr) {}
	~Node() { data = 0; next = nullptr; }
	friend std::ostream& operator<<(std::ostream& stream, Node& node)
	{
		stream << node.data;
		return stream;
	}
};

class LinkedList
{
public:
	LinkedList() : head(nullptr) {}
	~LinkedList() { dispose(); }
	int Length()
	{
		int len = 0;
		Node* tmp = head;

		while (tmp != nullptr)
		{
			tmp = tmp->next;
			++len;
		}

		return len;
	}
	bool IsEmpty() { return head == nullptr; }
	void PushHead(int data)
	{
		Node* node = new Node(data);
		InsertNode(0, node);
	}
	void Insert(int index, int data)
	{
		Node* node = new Node(data);
		InsertNode(index, node);
	}
	void PushTail(int data)
	{
		Node* node = new Node(data);
		InsertNode(Length(), node);
	}
	int PopHead()
	{
		return PopData(ExtractNode(0));
	}
	int Extract(int index)
	{
		return PopData(ExtractNode(index));
	}
	int PopTail()
	{
		return PopData(ExtractNode(Length() - 1));
	}
	int Data(int index) const
	{
		Node* tmp = head;

		for (int i = 0; i < index && tmp != nullptr; ++i)
		{
			tmp = tmp->next;
		}
		if (tmp == nullptr)
		{
			return 0;
		}
		else
		{
			return tmp->data;
		}
	}

	void swap(int ia, int ib)
	{
		if (ia == ib || !IndexValid(ia) || !IndexValid(ib))
		{
			return;
		}
		if (ia > ib)
		{
			std::swap(ia, ib);
		}

		Node* nodeA = ExtractNode(ia);
		Node* nodeB = ExtractNode(ib - 1);

		if (nodeA == nullptr || nodeB == nullptr)
		{
			return;
		}

		InsertNode(ia, nodeB);
		InsertNode(ib, nodeA);
	}
	void insertionSort()
	{
		for (int i = 0; i < Length(); ++i)
		{
			int tmp = i;

			while (tmp > 0 && Data(tmp) < Data(tmp - 1))
			{
				swap(tmp, tmp - 1);
				--tmp;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& stream, const LinkedList& list)
	{
		Node* tmp = list.head;

		while (tmp != nullptr)
		{
			stream << *tmp << " ";
			tmp = tmp->next;
		}

		return stream;
	}
private:
	void dispose()
	{
		while (!IsEmpty())
		{
			PopHead();
		}
	}
	int PopData(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		int res = node->data;
		delete node;
		return res;
	}
	void InsertNode(int index, Node* node)
	{
		if (IndexValid(index) || index == Length())
		{
			if (index == 0)
			{
				node->next = head;
				head = node;
			}
			else
			{
				Node* tmp = head;

				for (int i = 0; i < index - 1 && tmp->next != nullptr; ++i)
				{
					tmp = tmp->next;
				}

				node->next = tmp->next;
				tmp->next = node;
			}
		}
	}
	Node* ExtractNode(int index)
	{
		if (!IndexValid(index))
		{
			return nullptr;
		}

		if (index == 0)
		{
			Node* tmp = head;
			head = head->next;
			return tmp;
		}

		Node* current = head;

		for (int i = 0; i < index - 1; ++i)
		{
			current = current->next;
		}

		Node* tmp = current->next;
		current->next = tmp->next;
		return tmp;
	}
	bool IndexValid(int index)
	{
		return (0 <= index && index < Length());
	}
	Node* head;
};

int main(int argc, char* argv[])
{
	LinkedList list;
	std::cout << list << std::endl;
	list.PushHead(1);
	std::cout << list << std::endl;
	list.PushTail(3);
	std::cout << list << std::endl;
	list.Insert(1, 2);
	std::cout << list << std::endl;
	list.Insert(3, 4);
	std::cout << list << std::endl << std::endl;
	std::cout << list << std::endl;
	std::cout << list.PopHead() << " ";
	std::cout << list.Extract(1) << " ";
	std::cout << list.PopTail() << " ";
	std::cout << list.Extract(0) << std::endl;
	std::cout << list << std::endl << std::endl;

	list.PushHead(3); list.PushHead(4); list.PushHead(1); list.PushHead(2);
	list.PushHead(7); list.PushHead(5); list.PushHead(8); list.PushHead(6);
	std::cout << list << std::endl;
	list.insertionSort();
	std::cout << list << std::endl;
	return EXIT_SUCCESS;
}