#include<iostream>
#include<fstream>
#include<map>

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

class Jammed
{
public:

    Jammed() : sharp_i(0), sharp_j(0), desk() {}
    Jammed(const Jammed& other)
    {
        sharp_i = other.sharp_i;
        sharp_j = other.sharp_j;
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                desk[i][j] = other.desk[i][j];
            }
        }
    }
    void fReadJammed()
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                fin >> desk[i][j];
                if (desk[i][j] == '#')
                {
                    sharp_i = i;
                    sharp_j = j;
                }
            }
        }
    }
    Jammed move_N() const
    {
        Jammed jam = *this;
        if (sharp_i - 1 < 0)
        {
            return jam;
        }
        else
        {
            jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i - 1][sharp_j];
            jam.desk[sharp_i - 1][sharp_j] = '#';
            --jam.sharp_i;
        }
        return jam;
    }
    Jammed move_S() const
    {
        Jammed jam = *this;
        if (sharp_i + 1 > 1)
        {
            return jam;
        }
        else
        {
            jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i + 1][sharp_j];
            jam.desk[sharp_i + 1][sharp_j] = '#';
            ++jam.sharp_i;
        }
        return jam;
    }
    Jammed move_W() const
    {
        Jammed jam = *this;
        if (sharp_j - 1 < 0)
        {
            return jam;
        }
        else
        {
            jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i][sharp_j - 1];
            jam.desk[sharp_i][sharp_j - 1] = '#';
            --jam.sharp_j;
        }
        return jam;
    }
    Jammed move_E() const
    {
        Jammed jam = *this;
        if (sharp_j + 1 > 3)
        {
            return jam;
        }
        else
        {
            jam.desk[sharp_i][sharp_j] = jam.desk[sharp_i][sharp_j + 1];
            jam.desk[sharp_i][sharp_j + 1] = '#';
            ++jam.sharp_j;
        }
        return jam;
    }
    bool operator==(const Jammed& other) const
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (desk[i][j] != other.desk[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator<(const Jammed& other) const
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (desk[i][j] != other.desk[i][j])
                {
                    return desk[i][j] < other.desk[i][j];
                }
            }
        }
        return false;
    }

private:

    int sharp_i;
    int sharp_j;
    char desk[2][4];
};

int jammedBFS(Jammed start, Jammed end)
{
    queue <Jammed> q;
    q.push(start);

    std::map<Jammed, int>  lens;
    lens[start] = 0;

    while (!q.empty())
    {
        Jammed jam = q.front();
        q.pop();

        if (jam == end)
        {
            return lens[jam];
        }
        Jammed jam_N = jam.move_N();
        if (lens.count(jam_N) == 0)
        {
            lens[jam_N] = lens[jam] + 1;
            q.push(jam_N);
        }

        Jammed jam_S = jam.move_S();
        if (lens.count(jam_S) == 0)
        {
            lens[jam_S] = lens[jam] + 1;
            q.push(jam_S);
        }

        Jammed jam_W = jam.move_W();
        if (lens.count(jam_W) == 0)
        {
            lens[jam_W] = lens[jam] + 1;
            q.push(jam_W);
        }

        Jammed jam_E = jam.move_E();
        if (lens.count(jam_E) == 0)
        {
            lens[jam_E] = lens[jam] + 1;
            q.push(jam_E);
        }

    }
    return -1;
}

int main(int argc, char* argv[])
{
    Jammed start;
    Jammed end;
    start.fReadJammed();
    end.fReadJammed();
    fout << jammedBFS(start, end);

    fin.close();
    fout.close();

    return EXIT_SUCCESS;
}