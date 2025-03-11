#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList
{
    Node *head, *tail;
    int nodeCnt;

public:
    LinkedList() : head(nullptr), tail(nullptr), nodeCnt(0) {}

    void push_back(int data)
    {
        Node *newNode = new Node(data);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        nodeCnt++;
    }

    void insert(int idx, int data)
    {
        Node *newNode = new Node(data);
        if (idx == 0)
        {
            newNode->next = head;
            head = newNode;
            if (!tail)
                tail = newNode;
        }
        else
        {
            Node *cur = head;
            for (int i = 0; i < idx - 1; i++)
                cur = cur->next;
            newNode->next = cur->next;
            cur->next = newNode;
            if (newNode->next == nullptr)
                tail = newNode; // tail 업데이트
        }
        nodeCnt++;
    }

    void erase(int idx)
    {
        if (idx == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            if (!head)
                tail = nullptr; // 리스트가 비면 tail도 nullptr로 설정
        }
        else
        {
            Node *cur = head;
            for (int i = 0; i < idx - 1; i++)
                cur = cur->next;
            Node *temp = cur->next;
            cur->next = temp->next;
            if (cur->next == nullptr)
                tail = cur; // tail 업데이트
            delete temp;
        }
        nodeCnt--;
    }

    void change(int idx, int data)
    {
        Node *cur = head;
        for (int i = 0; i < idx; i++)
            cur = cur->next;
        cur->data = data;
    }

    int get(int idx)
    {
        Node *cur = head;
        for (int i = 0; i < idx; i++)
            cur = cur->next;
        return cur->data;
    }

    int size()
    {
        return nodeCnt;
    }
};

int main()
{
    // freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        int n, m, l;
        cin >> n >> m >> l;

        LinkedList list;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            list.push_back(tmp);
        }

        for (int i = 0; i < m; i++)
        {
            char cmd;
            int idx, val;
            cin >> cmd;
            if (cmd == 'I')
            {
                cin >> idx >> val;
                list.insert(idx, val);
            }
            else if (cmd == 'D')
            {
                cin >> idx;
                list.erase(idx);
            }
            else if (cmd == 'C')
            {
                cin >> idx >> val;
                list.change(idx, val);
            }
        }

        if (l >= list.size())
        {
            cout << "#" << tc << " -1\n";
        }
        else
        {
            cout << "#" << tc << " " << list.get(l) << "\n";
        }
    }
    return 0;
}
