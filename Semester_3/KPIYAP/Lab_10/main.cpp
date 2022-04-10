#include <iostream>

// дубликаты +
// поиск подстроки +
// удаление подмножества (последовательности) +

using namespace std;

class ExceptionClass : public exception
{
public:
    ExceptionClass(const char* message){}
    ~ExceptionClass() {}
    void wrongValue()
    {
        cin.clear();
        cin.ignore(100, '\n');
    }
};

template <class T>
class Ring
{
private:
    class Node
    {
    public:
        T value;
        Node* next;
        Node* prev;
        Node(T newVal) :value(newVal) { next =prev= this; }
        Node() { next = prev = this; value = 0; }
        ~Node() {}
        void print()
        {
            cout << value << " ";
        }
        int getValue()
        {
            return value;
        }
        Node& operator=(const Node&x)
        {
            value = x.value;
            next = x.next;
            prev = x.prev;
        }
    };
public:
    class iterator
    {
    private:
        friend class Ring<T>;
        Node* node;
    public:
        iterator(Node* n) :node(n) {}
        iterator() : node(0) {}
        iterator(const iterator& iterator) :node(iterator.node) {}
        iterator& operator=(const iterator& it)
        {
            node = it.node;
            return *this;
        }
        bool operator==(const iterator& it) const
        {
            return (node == it.node);
        }
        bool operator!=(const iterator& it) const
        {
            return !(it == *this);
        }
        iterator& operator++()
        {
            if (node == 0)  throw "Error! Incrementation of empty iterator!\n";
            if (node->next == 0)    throw "Error!!! 'Next' is NULL!\n";
            node = node->next;
            return *this;
        }
        iterator& operator--()
        {
            if (node == 0)  throw "Error! Decrementation of empty iterator!\n";
            if (node->prev == 0)    throw "Error!!! 'Prev' is NULL!\n";
            node = node->prev;
            return *this;
        }
        T& operator*() const
        {
            if (node == 0)  throw "Error! Dereference of empty iterator!";
            return node->value;
        }
    };
private:
    Node* head;
    Node* tail;
    //Ring& operator=(const Ring&);
    Ring(const Ring&);
    iterator headIterator;
    iterator tailIterator;
public:
    Ring()
    {
        head = tail = new Node;
        tail->next = 0;
        tail->prev = 0;
        headIterator = iterator(head);
        tailIterator = iterator(tail);
    }
    Ring(T newVal)
    {
        head = tail = new Node;
        tail->next = this;
        tail->prev = this;
        headIterator = iterator(head);
        tailIterator = iterator(tail);
        add(newVal);
    }
    ~Ring()
    {
        Node* delNode = head;
        for (Node* sn = head; sn != tail; sn = sn->next)
        {
            //delete delNode;
            delNode = sn;
        }
        delete delNode;
    }
    bool isEmpty() { return head == tail; }
    iterator front() { return headIterator; }
    iterator rear() { return tailIterator; }
    void add(T newVal)
    {
        Node* addNode = new Node(newVal);
        addNode->next = head;
        addNode->prev = tail;
        head->prev = addNode;
        tail->next = addNode;
        head = addNode;
        headIterator = iterator(head);
    }
    bool remove_it(iterator key)
    {
        for (Node* dn = head; dn != tail; dn = dn->next)
            if (dn == key.node)
            {
                dn->prev->next = dn->next;
                dn->next->prev = dn->prev;
                delete dn;
                key.node = 0;
                return true;
            }
        return false;
    }
    iterator find(T val) const
    {
        for (Node* dn = head; dn != tail; dn = dn->next)
            if (dn->value == val) return iterator(dn);
        return tailIterator;
    }

    void deleteSeq(){
        int* arr=NULL;
        int size = 0;
        while (1)
        {
            try
            {
                cout << "Enter element of plenty to delete: ";
                size++;
                arr = (int*)realloc(arr, size * sizeof(int));
                cin >> arr[size - 1];
                if (cin.fail() || arr[size - 1] < 0)   throw("Incorrect value!");
                cout << "To continue press y: ";
                rewind(stdin);
                if (getchar() != 'y') break;
            }
            catch (ExceptionClass& ex)
            {
                ex.what();
                ex.wrongValue();
            }
        }

        int i = 0;
        bool flag = false;
        Node* dn;
        Node* d1[10];
        for (dn = head; dn!=tail; dn=dn->next)
        {
            if (dn->value == arr[i])
            {
                d1[0] = dn;
                flag = true;
                for (Node* kn = dn; i<size; kn = kn->next, i++)
                {
                    d1[i] = kn;
                    if (kn->value != arr[i]) flag = false;
                }
            }
        }
        if (flag == true)
        {
            for (int i = 0; i < size; i++)
            {
                remove_it(iterator(d1[i]));
            }
            cout << "Your deleted sequence is ( ";
            for (int i = 0; i < size; i++)
            {
                cout << arr[i] << " ";
            }
            cout << ")!" << endl << "It was successfully deleted" << endl;
        }
        else
        {
            cout << "Not found..." << endl;
        }
        free(arr);
    }
    void search()
    {
        int* arr=NULL;
        int size = 0;
        while (1)
        {
            try
            {
                cout << "Enter element of plenty to search: ";
                size++;
                arr = (int*)realloc(arr, size * sizeof(int));
                cin >> arr[size - 1];
                if (cin.fail() || arr[size - 1] < 0)   throw("Incorrect value!");
                cout << "To continue press y: ";
                rewind(stdin);
                if (getchar() != 'y') break;
            }
            catch (ExceptionClass& ex)
            {
                ex.what();
                ex.wrongValue();
            }
        }

        int i = 0;
        bool flag = false;
        for (Node* dn = head; dn!=tail; dn=dn->next)
        {



            if (dn->value == arr[i])
            {
                flag = true;
                for (Node* kn = dn; i<size; kn = kn->next, i++)
                {
                    if (kn->value != arr[i]) flag = false;
                }
            }
        }
        if (flag == true)
        {
            cout << "Your sequence ( ";
            for (int i = 0; i < size; i++)
            {
                cout << arr[i] << " ";
            }
            cout << ") is found!"<<endl;
        }
        else
        {
            cout << "Not found..." << endl;
        }
        free(arr);
    }
    void dublicate()
    {
        int comp;
        for (int i = 0; i < size(); i++)
        {
            for (Node* dn = head; dn != tail; dn = dn->next)
            {
                bool flag = false;
                for (Node* n = dn->next; n != tail && flag == false; n = n->next)
                {
                    comp = dn->value;
                    if (comp == n->value)
                    {
                        remove_it(iterator(n));
                        flag = true;
                    }
                }
            }
        }
    }
    void sort()
    {
        for (int i = 0; i < size(); i++)
        {
            for (Node* dn = head; dn != tail; dn = dn->next)
            {

                Node* n = dn->next;
                if (dn->value > n->value)
                {
                    if (n->value == 0)     break;
                    Node* x = n->next;
                    Node* y = dn->prev;
                    n->prev = dn->prev;
                    dn->next = n->next;
                    dn->prev = n;
                    n->next = dn;
                    if (dn == head)    head = n;
                    if (n == tail)     tail = dn;
                    x->prev = dn;
                    y->next = n;
                }
            }
        }
        print();
    }
    int size() const
    {
        int count = 0;
        for (Node* dn = head; dn != tail; dn = dn->next) ++count;
        return count;
    }
    void print() const
    {
        for (Node* dn = head; dn != tail; dn = dn->next)
            dn->print();
        cout << endl;
    }
};


typedef int tip;

Ring<tip> ring;

int menu()
{
    int choise;
    while (true)
    {
        try
        {
            cout << "Choose:\n   (1)Add\n   (2)Show\n   (3)Search\n   (4)Sort\n   (5)Duplicates\n   (6)Delete subsequence\n  (0)Exit\n";

            cin >> choise;
            if (cin.fail() || choise < 0 || choise>6)
            {
                system("cls");
                throw ExceptionClass("Incorrect value!!!Try again...\n");
            }
            break;
        }
        catch (ExceptionClass& ex)
        {
            cout << ex.what();
            ex.wrongValue();
        }
    }
    return choise;
}

int add(Ring<tip> &ring)
{
    int num;
    while (1)
    {
        try
        {
            cout << "Your element:";
            cin >> num;
            if (cin.fail() || num < 0) throw("Incorrect value!\n");
            break;
        }
        catch (ExceptionClass& ex)
        {
            ex.what();
            ex.wrongValue();
        }
    }
    ring.add(num);
}

int main()
{

    while (1)
    {
        switch (menu())
        {
            case 1:
                add(ring);
                cout << "Your List: ";
                ring.print();
                break;
            case 2:
                ring.print();
                break;
            case 3:
                ring.search();
                break;
            case 4:
                ring.sort();
                break;
            case 5:
                ring.dublicate();
                break;
            case 6:
                ring.deleteSeq();
                break;
            case 0:
                return 0;
        }

    }
}

