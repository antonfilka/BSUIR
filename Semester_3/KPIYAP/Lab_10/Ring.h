template <class T>
struct RingNode
{
    T word;
    RingNode* next = nullptr;
    RingNode* prev = nullptr;
};

template <class T>
class Ring
{
protected:
    RingNode<T>* first;
    RingNode<T>* last;
public:
    Ring()
    {
        first = nullptr;
        last = nullptr;
    }

    ~Ring()
    {
        clear();
    }

    void pushback(const T& value);

    void popfront();
    T popback();
    void popAny(const int index);

    void findByValue();
    void showList();
    void sortlist();
    void clear();
    bool isEmpty();
    int howmany_links();
    void editElement();
};