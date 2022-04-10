#include <iostream>
#include <queue>
#include <cassert>
#include <cstring>

using namespace std;

template<typename T>
class Queue {
private:
    T *queuePtr;
    const int size;
    int begin,
            end;
    int elemCT;
public:
    Queue(int = 10);

    Queue(const Queue<T> &);

    ~Queue();

    void enqueue(const T &);

    T dequeue();

    void printQueue();
};

template<typename T>
Queue<T>::Queue(int sizeQueue) :
        size(sizeQueue),
        begin(0), end(0), elemCT(0) {
    queuePtr = new T[size + 1];
}

template<typename T>
Queue<T>::Queue(const Queue &otherQueue) :
        size(otherQueue.size), begin(otherQueue.begin),
        end(otherQueue.end), elemCT(otherQueue.elemCT),
        queuePtr(new T[size + 1]) {
    for (int ix = 0; ix < size; ix++)
        queuePtr[ix] = otherQueue.queuePtr[ix];
}

template<typename T>
Queue<T>::~Queue() {
    delete[] queuePtr;
}

template<typename T>
void Queue<T>::enqueue(const T &newElem) {
    assert(elemCT < size);

    queuePtr[end++] = newElem;

    elemCT++;

    if (end > size)
        end -= size + 1;
}

template<typename T>
T Queue<T>::dequeue() {
    assert(elemCT > 0);

    T returnValue = queuePtr[begin++];
    elemCT--;

    if (begin > size)
        begin -= size + 1;

    return returnValue;
}

template<typename T>
void Queue<T>::printQueue() {
    cout << "Queue: ";

    if (end == 0 && begin == 0)
        cout << " empty!\n";
    else {
        for (int ix = end; ix >= begin; ix--)
            cout << queuePtr[ix] << " ";
        cout << endl;
    }
}

template<>
class Queue<char *> {
private:
    char *queuePtr;
    const int size;
    int begin, end;
    int elemCT;
public:
    Queue(int sizeQueue) :
            size(sizeQueue),
            begin(0), end(0), elemCT(0) {
        queuePtr = new char[size + 1];
    }

    Queue(const Queue<char *> &otherQueue) : size(otherQueue.size), begin(otherQueue.begin),
                                             end(otherQueue.end), elemCT(otherQueue.elemCT),
                                             queuePtr(new char[size + 1]) {
        for (int ix = 0; ix < size; ix++)
            queuePtr[ix] = otherQueue.queuePtr[ix];
    }

    ~Queue() {
        delete[] queuePtr;
    }

    void enqueue(const char &newElem) {
        assert(elemCT < size);

        queuePtr[end++] = newElem;

        elemCT++;

        if (end > size)
            end -= size + 1;
    }

    char dequeue() {
        assert(elemCT > 0);

        char returnValue = queuePtr[begin++];
        elemCT--;

        if (begin > size)
            begin -= size + 1;

        return returnValue;
    }

    void printQueue() {
        cout << "Queue: ";

        if (end == 0 && begin == 0)
            cout << " empty!\n";
        else {
            for (int i = end - 1; i >= begin; -i)
            cout << queuePtr[i] << " ";
            cout << endl;
        }
    }

    friend void searching(Queue<char *> str, int n);
};


void searching(Queue<char *> str, int n) {
    char *search = (char *) calloc(n, sizeof(char));
    cin >> search;
    char *res = strstr(str.queuePtr, search);
    if (res != nullptr) {
        cout << "The start of your string is the element number " << res - str.queuePtr + 1 << "." << endl;
        cout << "The searching part is: " << search << endl;
    } else
        return;
}

int main() {

    int n;
    cout << "enter the number of elements: " << endl;
    cin >> n;
    Queue<char *> String(n);

    cout << "Enter your string: " << endl;
    int counter = 1;
    char ch;
    while (counter < n) {
        cin >> ch;
        String.enqueue(ch);
        counter++;
    }
    String.printQueue();

    searching(String, n);
}

// доп
// с клавы char строка, поиск подстроки