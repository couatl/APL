#pragma once
#ifndef LIST_H
#define LIST_H
#include <iostream>

template <typename Type>
struct Node
{
    Type _data;
    Node* _next;
    Node(Type data): _data(data), _next(nullptr)
    {}
    Node(Type data, Node* next): _data(data), _next(next)
    {}
};

template <typename Type>
class List
{
    typedef Node<Type> _Node;

    _Node* _head;
    size_t size;
public:
    List() : _head(nullptr)
    {
        size = 0;
    }
    List(const Type& data)
    {
        _head = new _Node(data);
        size = 1;
    }
    List(_Node* node): _head(node)
    {
        size = 1;
    }
    List(const List& other): _head(other._head), size(other.size)
    {}
    ~List()
    {
        if (size == 0) return;
        while(_head)
        {
            _Node * t = _head;
            _head = _head->_next;
            delete t;
        }
    }
    void AddBegin(const Type& data)
    {
        if (!_head)
        {
            _head = new _Node(data);
            size++;
        }
        else
        {
            _head = new _Node(data, _head);
            size++;
        }
    }
    _Node* AddEnd(const Type& data)
    {
        if (!_head)
        {
            _head = new _Node(data);
            size++;
            return _head;
        }
        _Node *t = _head;
        while (t->_next)
        {
            t = t->_next;
        }
        t->_next = new _Node(data);
        size++;
        return t->_next;
    }
    _Node* AddNth(const Type& data, size_t n)
    {
        if (n <= (size-1))
        {
            size_t i = 0;
            _Node *t = _head;
            while (!(i == (n-1)))
            {
                t = t->_next;
                i++;
            }
            t->_next = new _Node(data, t->_next);
            size++;
            return t->_next;
        }
        else
        {
            return nullptr;
        }
    }
    _Node* GetNth(size_t n) const
    {
        if(n <= (size-1))
        {
            size_t i = 0;
            _Node *t = _head;
            while (!(i == n))
            {
                t = t->_next;
                i++;
            }
            return t;
        }
        else
        {
            return nullptr;
        }
    }
    _Node* GetLast() const
    {
        if (size == 0) return nullptr;
        _Node *t = _head;
        while(t->_next)
        {
            t = t->_next;
        }
        return t;
    }
    void DeleteNth(size_t n)
    {
        if (!_head) return;
        if(n <= (size-1))
        {
            if (n == 0)
            {
                _Node *t = _head;
                _head = t->_next;
                delete t;
                return;
            }
            size_t i = 0;
            _Node* t = _head;
            while (!(i == (n-1)))
            {
                t = t->_next;
                i++;
            }
            _Node *t1 = t->_next;
            t->_next = t1->_next;
            delete t1;
            size--;
        }
        else
        {
            return;
        }
    }
     void DeleteNode(_Node &t)
     {
         if (!_head) return;
         if (&t == _head)
         {
             _head = t._next;
             delete &t;
             return;
         }
         _Node *t1 = _head;
         while(!(t1->_next == &t))
         {
             t1 = t1->_next;
         }
         t1->_next = t._next;
         delete &t;
     }
    void Clear()
    {
        if (size == 0) return;
        while(_head)
        {
            _Node* t = _head;
            _head = _head->_next;
            delete t;
        }
        size = 0;
    }
    void Print() const
    {
        std::cout << "Your list: " << std::endl;
        _Node *t = _head;
        while(t)
        {
            std::cout << " " << t->_data << std::endl;
            t = t->_next;
        }
    }
    List& operator= (const List &t)
    {
        if (this == &t)
            return *this;
        this->Clear();
        this->size = t.size;
        this->_head = t._head;
        return *this;
    }
    bool Empty() const
    {
        if(_head == 0)
            return true;
        else
        { return false; }
    }
    size_t Size() const
    { return size; }
};


#endif // LIST_H
