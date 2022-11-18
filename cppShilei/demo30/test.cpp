#include <iostream>
using namespace std;

/*
运算符的重载：成员方法、全局方法
内存池  进程池  线程池  连接池  对象池
*/
template <typename T>
class Queue {
   public:
    Queue() { _front = _rear = new QueueItem(); }
    ~Queue() {
        QueueItem* cur = _front;
        while (cur != nullptr) {
            _front = _front->_next;
            delete cur;
            cur = _front;
        }
    }
    void push(const T& val)  // 入队操作
    {
        QueueItem* item = new QueueItem(val);  // malloc
        _rear->_next = item;
        _rear = item;
    }
    void pop() {
        if (empty()) return;
        QueueItem* first = _front->_next;
        _front->_next = first->_next;
        if (_front->_next == nullptr) {
            _rear = _front;
        }
        delete first;  // free
    }
    T front() const { return _front->_next->_data; }
    bool empty() const { return _front == _rear; }

   private:
    // 产生一个QueueItem的对象池（10000个QueueItem节点）
    struct QueueItem {
        QueueItem(T data = T()) : _data(data), _next(nullptr) {}
        // 给QueueItem提供自定义内存管理
        // 请在vs注释掉void* operator new 和 void operator
        // delete对比单步调试情况
        void* operator new(size_t size) {
            if (_itemPool == nullptr) {
                _itemPool =
                    (QueueItem*)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
                QueueItem* p = _itemPool;
                for (; p < _itemPool + POOL_ITEM_SIZE - 1; ++p) {
                    p->_next = p + 1;
                }
                p->_next = nullptr;
            }

            QueueItem* p = _itemPool;
            _itemPool = _itemPool->_next;
            return p;
        }
        void operator delete(void* ptr) {
            QueueItem* p = (QueueItem*)ptr;
            p->_next = _itemPool;
            _itemPool = p;
        }
        T _data;
        QueueItem* _next;
        static QueueItem* _itemPool;
        static const int POOL_ITEM_SIZE = 100000;
    };

    QueueItem* _front;  // 指向头节点
    QueueItem* _rear;   // 指向队尾
};

template <typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_itemPool = nullptr;

int main() {
    Queue<int> que;
    for (int i = 0; i < 1000000; ++i) {
        que.push(i);  // QueueItem(i)
        que.pop();    // QueueItem
    }
    cout << que.empty() << endl;

    return 0;
}