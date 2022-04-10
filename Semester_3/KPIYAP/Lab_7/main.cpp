#include <cassert>
#include <iostream>
#include <cstdio>
using namespace std;
// Класс «Очередь».
//hello_world_lets_code

template<typename T> class Queue{
private:
    T *queuePtr;     // указатель на очередь
    const int size;
    int begin, end;
    int elemCT;      // счетчик элементов
public:
    Queue(int = 10);
    Queue(const Queue<T> &);
    ~Queue();

    void enqueue(const T &);
    T dequeue();
    void printQueue();
};

// конструктор по умолчанию
template<typename T> Queue<T>::Queue(int sizeQueue) :size(sizeQueue),  begin(0), end(0), elemCT(0)
{

    queuePtr = new T[size + 1];
}

// конструктор копии
template<typename T> Queue<T>::Queue(const Queue &otherQueue) : size(otherQueue.size) , begin(otherQueue.begin), end(otherQueue.end), elemCT(otherQueue.elemCT), queuePtr(new T[size + 1])
{
    for (int ix = 0; ix < size; ix++)
        queuePtr[ix] = otherQueue.queuePtr[ix];
}

// деструктор
template<typename T> Queue<T>::~Queue()
{
    delete [] queuePtr;
}

// добавлениe элемента
template<typename T> void Queue<T>::enqueue(const T &newElem)
{  // проверяем, ести ли свободное место в очереди

    assert( elemCT < size );
    queuePtr[end++] = newElem;
    elemCT++;

    // проверка кругового заполнения очереди
    if (end > size)
        end -= size + 1; // возвращаем end на начало очереди
}

// удаление элемента
template<typename T> T Queue<T>::dequeue()
{
    // есть ли в очереди элементы
    assert( elemCT > 0 );

    T returnValue = queuePtr[begin++];
    elemCT--;

    // проверка кругового заполнения очереди
    if (begin > size)
        begin -= size + 1; // возвращаем begin на начало очереди

    return returnValue;
}

template<typename T> void Queue<T>::printQueue()
{
    cout << "Queue: ";

    if (end == 0 && begin == 0)
        cout << " -/-\n";
    else
    {
        for (int i = end; i >= begin; i--)
            cout << queuePtr[i] << "";
        cout << endl;
    }
}



int main() {

    Queue<char> myQueue(22);
    //myQueue.printQueue();
    int ct = 1;
    char ch;

    cout << "Enter chars: ";
    while (ct++ < 22)
    {
        cin >> ch;
        myQueue.enqueue(ch);
    }
    myQueue.printQueue();

    for(int i =0; i < 7; i++){
        myQueue.dequeue();
    }

    myQueue.printQueue();

    cout << "\nCopy constructor:\n";
    Queue<char> newQueue(myQueue);

    newQueue.printQueue();

    return 0;
}




//массив строк
//1. добавить
//2. просмотреть
//3. удаление (строку или посимвольно)
//4. поиск подстроки
//5. удаление дубликатов
