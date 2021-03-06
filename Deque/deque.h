//
// Created by Надежда on 09.04.16.
//

#ifndef H_W_DEQUEUE_DEQUEUE_H
#define H_W_DEQUEUE_DEQUEUE_H

#include <cstddef>
#include <iostream>

class deque_base
{
public:
    size_t _buff_size;
    deque_base()
        :_buff_size(0)
    {}
};

template <class val_type>
struct node
{
    typedef deque_base _deque;

    val_type _value;
    node* _next;
    node* _prev;
    _deque* _base;
    node(val_type value = 0, node* next = nullptr, node* prev = nullptr, _deque* base = nullptr):
            _value(value), _prev(prev), _next(next), _base(base)
    {
        if(_base)
            _base->_buff_size++;
    }
    ~node() {
        if (_base)
            _base->_buff_size--;
    }
};

template <class val_type, class ref, class ptr>
struct deque_iterator
{
    typedef node<val_type> Node;
    typedef deque_iterator<val_type, val_type&, val_type*> iterator;
    typedef deque_iterator<val_type, const val_type&, const val_type*> const_iterator;
    typedef deque_base _deque;

    Node* _cur;
    Node* _first;
    Node* _last;
    _deque* _base;
    deque_iterator(Node* base): _cur(base), _first(nullptr), _last(nullptr), _base(nullptr)
    {}
    deque_iterator(Node* cur, Node* first, _deque* base): _cur(cur), _first(first), _base(base)
    {
        _cur->_base = base;
        _first->_base = base;
        _last->_base = base;
        Node *t = _first;
        while(t->_next)
        {
            t = t->_next;
            _base->_buff_size++;
        }
        _last = t;
        t = nullptr;
    }
    deque_iterator(Node* cur = nullptr, Node* first = nullptr, Node* last = nullptr, _deque* base = nullptr):
            _cur(cur), _first(first), _last(last), _base(base)
    {}
    deque_iterator(const iterator& T): _cur(T._cur), _first(T._first), _last(T._last), _base(T._base)
    {}
    val_type& operator* () const
    {
        return _cur->_value;
    }
    deque_iterator& operator++ ()
    {
        if (_cur == _last)
        {
            Node t(0, nullptr, _cur, _base);
            _cur = &t;
            _last->_next = &t;
            _last = &t;
            return *this;
        }
        _cur = _cur->_next;
        return *this;
    }
    deque_iterator operator+ (ptrdiff_t n) const
    {
        for (ptrdiff_t i = 0; i < n; i++)
            ++this;
        return *this;
    }
    deque_iterator operator++ (int)
    {
        deque_iterator t = *this;
        ++(*this);
        return t;
    }
    deque_iterator& operator+= (ptrdiff_t n)
    {
        deque_iterator t = *this;
        return t+n;
    }
    deque_iterator& operator-- ()
    {
        if (_cur == _first)
        {
            Node t(0, _first, nullptr, _base);
            _first->_prev = &t;
            _first = &t;
            _cur = &t;
            return *this;
        }
        _cur = _cur->_prev;
        return *this;
    }
    deque_iterator& operator-- (int)
    {
        deque_iterator t = *this;
        --(*this);
        return t;
    }
    deque_iterator& operator- (ptrdiff_t n) const
    {
        for (ptrdiff_t i = 0; i < n; i++)
            --this;
        return *this;
    }
    deque_iterator& operator-= (ptrdiff_t n)
    {
        deque_iterator t = *this;
        return t-n;
    }
    val_type* operator-> () const
    {
        return &(_cur->_value);
    }
    val_type& operator[] (ptrdiff_t n) const
    {
        if (n < _base->_buff_size)
        {
            return *(_first+n);
        }
    }
    deque_iterator& operator=(const iterator& copy)
    {
        if (this == &copy) return *this;
        _cur = copy._cur;
        _base = copy._base;
        _first = copy._first;
        _last = copy._last;
        return *this;
    }
};
//без поддержки работы с const_iterator/iterator

template <class val_type>
inline bool operator== (const deque_iterator<val_type, val_type&, val_type*>& it1,
                        const deque_iterator<val_type, val_type&, val_type*>& it2)
{
    return it1._cur == it2._cur;
}

template <class val_type>
inline bool operator!= (const deque_iterator<val_type, val_type&, val_type*>& it1,
                        const deque_iterator<val_type, val_type&, val_type*>& it2)
{
    return !(it1._cur == it2._cur);
}

template <class val_type>
bool operator< (const deque_iterator<val_type, val_type&, val_type*>& it1,
                const deque_iterator<val_type, val_type&, val_type*>& it2)
{
    node<val_type>* t1 = it1._first;
    node<val_type>* t2 = it2._first;
    size_t i1 = 0;
    size_t i2 = 0;
    while (t1 != it1)
    {
        t1 = t1->_next;
        i1++;
    }
    while (t2 != it2)
    {
        t2 = t2->_next;
        i2++;
    }
    return i1<i2;
}

template <class val_type>
bool operator> (const deque_iterator<val_type, val_type&, val_type*>& it1,
                const deque_iterator<val_type, val_type&, val_type*>& it2)
{
    return !(it1<it2);
}

template <class val_type>
bool operator<= (const deque_iterator<val_type, val_type&, val_type*>& it1,
                 const deque_iterator<val_type, val_type&, val_type*>& it2)
{
    if (it1 == it2)
        return true;
    return it1<it2;
}

template <class val_type>
bool operator>= (const deque_iterator<val_type, val_type&, val_type*>& it1,
                 const deque_iterator<val_type, val_type&, val_type*>& it2)
{
    if (it1 == it2)
        return true;
    return !(it1<it2);
}

template <class val_type>
ptrdiff_t operator-(const deque_iterator<val_type, val_type&, val_type*> it1,
                    const deque_iterator<val_type, val_type&, val_type*> it2)
{
    node<val_type>* t1 = it1._first;
    node<val_type>* t2 = it2._first;
    size_t i1 = 0;
    size_t i2 = 0;
    while (t1 != it1)
    {
        t1 = t1->_next;
        i1++;
    }
    while (t2 != it2)
    {
        t2 = t2->_next;
        i2++;
    }
    return i1-i2;
}

//operator вида 5 + it
template <class val_type>
deque_iterator<val_type, val_type&, val_type*> operator+ (ptrdiff_t n, deque_iterator<val_type, val_type&, val_type*> it)
{
    for (ptrdiff_t i = 0; i < n; i++)
        ++it;
    return *it;
}

template <class val_type>
class deque: public deque_base
{
public:
    static size_t _maxsize;

    typedef node<val_type> Node;
    typedef deque_iterator<val_type, val_type&, val_type*> iterator;
    typedef deque_iterator<val_type, const val_type&, const val_type*> const_iterator;
 
    deque() //default
            :deque_base(), rAccessIterator(nullptr, nullptr, nullptr, this), _start(nullptr, nullptr, nullptr, this),
              _finish(nullptr, nullptr, nullptr, this)
    { }

    deque(size_t n) //fill
        :deque_base()
    {
        if (n < _maxsize)
        {
            Node *t =  new Node(0, nullptr, nullptr, this);
            rAccessIterator(t, t, nullptr, this);
            for (size_t i = 0; i<n; i++)
            {
                rAccessIterator++;
            }
            _start(t, t, rAccessIterator._last, this);
            _finish(rAccessIterator._last, t, rAccessIterator._last, this);
        }
    }
    deque(size_t n, const val_type& var) //fill 2.0
        :deque_base()
    {

        if (n < _maxsize)
        {
            Node *t =  new Node(var, nullptr, nullptr, this);
            rAccessIterator(t, t, nullptr, this);
            for (size_t i = 0; i<n; i++)
            {
                rAccessIterator++;
                rAccessIterator._cur->_value = var;
            }
            _start(t, t, rAccessIterator._last, this);
            _finish(rAccessIterator._last, t, rAccessIterator._last, this);
        }
    }
    deque(deque && move) //move
        :deque_base(), rAccessIterator(nullptr, nullptr, nullptr, this), _start(nullptr, nullptr, nullptr, this),
          _finish(nullptr, nullptr, nullptr, this)
    {
        this->swap(move);
    }
    deque(const deque& Obj) //copy
    :deque_base()
    {
        this->clear();
        this->insert(begin(), Obj.begin(), Obj.end());
    }
    ~deque()
    {
        if(rAccessIterator._first == nullptr) return;
        while(rAccessIterator._first)
        {
            Node *t = rAccessIterator._first;
            rAccessIterator._first = rAccessIterator._first->_next;
            delete t;
        }
    }
    iterator begin()
    {
        return _start;
    }
    const_iterator begin() const
    {
        return _start;
    }
    iterator end()
    {
        return _finish;
    }
    const_iterator end() const
    {
        return _finish;
    }
    const_iterator cend() const
    {
        return _finish;
    }
    const_iterator cbegin() const
    {
        return _start;
    }
    deque& operator= (const deque& Obj)
    {
        if (this==Obj) return;
        this->clear();
        this->insert(begin(), Obj.begin(), Obj.end());
    }
    deque& operator= (deque&& x)
    {
        if (this==x) return;
        this->clear();
        this->swap(x);
        return  *this;
    }
    size_t size() const
    {
        return deque_base::_buff_size;
    }
    static size_t max_size()
    {
        return _maxsize;
    }
    void resize(size_t n)
    {
        if(n < _buff_size)
        {
            size_t i = 0;
            rAccessIterator._cur = rAccessIterator._first;
            while(i!=n)
            {
                rAccessIterator++;
                i++;
            }
            _finish._last = rAccessIterator._last;
            _finish._cur = rAccessIterator._last;
            this->erase(rAccessIterator, this->end());

        }
        else if (n < _maxsize)
        {
            size_t i = 0;
            rAccessIterator._cur = rAccessIterator._first;
            while(i!=n)
            {
                rAccessIterator++;
                i++;
            }
            _finish._last = rAccessIterator._last;
            _finish._cur = rAccessIterator._last;
        }
    }
    bool empty()
    {
        return !(rAccessIterator._first);
    }
    val_type& at (size_t n)
    {
        if (n < deque_base::_buff_size)
        {
            size_t i = 0;
            rAccessIterator._cur = rAccessIterator._first;
            while(i!=n)
            {
                rAccessIterator++;
                i++;
            }
            return rAccessIterator._cur->_value;
        }
    }
    const val_type& at (size_t n) const
    {
        if (n < deque_base::_buff_size)
        {
            size_t i = 0;
            rAccessIterator._cur = rAccessIterator._first;
            while(i!=n)
            {
                rAccessIterator++;
                i++;
            }
            return rAccessIterator._cur->_value;
        }
    }
    val_type&  front()
    {
        return rAccessIterator._first->_value;
    }
    const val_type&  front() const
    {
        return rAccessIterator._first->_value;
    }
    val_type& back()
    {
        return rAccessIterator._last->_value;
    }
    const val_type& back() const
    {
        return rAccessIterator._last->_value;
    }
    void push_front (const val_type& val)
    {
        if (deque_base::_buff_size == 0)
        {
            rAccessIterator._first = new Node(val, nullptr, nullptr, this);
            rAccessIterator._cur = rAccessIterator._first;
            rAccessIterator._last = rAccessIterator._first;
            _start = rAccessIterator;
            _finish = rAccessIterator;
        }
        else
        {
            Node *t = new Node(val, rAccessIterator._first, nullptr, this);
            rAccessIterator._first->_prev = t;
            rAccessIterator._first = t;
            rAccessIterator._cur = t;
            _start = rAccessIterator;
            _finish._first = rAccessIterator._first;
        }
    }
    void push_back (const val_type& val)
    {
        if (deque_base::_buff_size == 0)
        {
            rAccessIterator._first = new Node(val, nullptr, nullptr, this);
            rAccessIterator._cur = rAccessIterator._first;
            rAccessIterator._last = rAccessIterator._first;
            _start = rAccessIterator;
            _finish = rAccessIterator;
        }
        else
        {
            Node *t = new Node(val, nullptr, rAccessIterator._last, this);
            rAccessIterator._last->_next = t;
            rAccessIterator._last = t;
            rAccessIterator._cur = t;
            _finish = rAccessIterator;
            _start._last = rAccessIterator._last;
        }
    }
    void pop_back()
    {
        if(deque_base::_buff_size == 0) return;
        Node *t = rAccessIterator._last;
        rAccessIterator._last = rAccessIterator._last->_prev;
        _finish._last = _finish._last->_prev;
        _finish._last->_next = nullptr;
        rAccessIterator._last->_next = nullptr;
        _start._last = _finish._last;
        delete t;
    }
    void pop_front()
    {
        if(!rAccessIterator._first) return;
        Node *t = rAccessIterator._first;
        rAccessIterator._first = rAccessIterator._first->_next;
        rAccessIterator._first->_prev = nullptr;
        _start._first = _start._first->_next;
        _start._first->_prev = nullptr;
        _finish._first = _start._first;
        delete t;
    }
    void clear()
    {
        if (rAccessIterator._first == nullptr) return;
        while(rAccessIterator._first)
        {
            Node *t = rAccessIterator._first;
            rAccessIterator._first = rAccessIterator._first->_next;
            delete t;
        }
    }
    void assign (size_t n, const val_type& val)
    {
        if (n < _maxsize)
        {
            this->clear();
            rAccessIterator._first = new Node(val, nullptr, nullptr, this);
            rAccessIterator._cur = rAccessIterator._first;
            rAccessIterator._last = rAccessIterator._first;
            _start = rAccessIterator;
            for (size_t i = 0; i<n; i++)
            {
                rAccessIterator++;
                rAccessIterator._cur->_value = val;
            }
            _finish = rAccessIterator;
            _start._last = rAccessIterator._last;
        }
    }
    iterator insert (const_iterator position, const val_type& val)
    {
        iterator it(rAccessIterator._first, rAccessIterator._first, rAccessIterator._last, this);
        while (it!=position)
            it++;
        Node *t = new Node(val, it._cur, it._cur->_prev, this);
        it._cur->_prev->_next = t;
        it._cur->_prev = t;
        return it;
    }
    template <class InputIterator>
    iterator insert (const_iterator position, InputIterator first, InputIterator last)
    {
        iterator it(rAccessIterator._first, rAccessIterator._first, rAccessIterator._last, this);
        while (it!=position)
            it++;
        Node **t_array;
        size_t n = 0;
        for (auto i = first; i != last; ++i)
        {
            n++;
        }
        t_array = new Node*[n];

        size_t k = 0;
        for (auto i = first; i != last; ++i, k++)
        {
            t_array[k] = new Node(*first, nullptr, nullptr, this);
        }
        t_array[0]->_prev = it._cur;
        it._cur->_next = t_array[0];
        it._cur->_next->_prev = t_array[n];
        for (k = 1; k<(n-1); k++)
        {
            t_array[k]->_prev = t_array[k-1];
            t_array[k]->_next = t_array[k+1];
        }
        return it;
    }

    val_type& operator[](size_t n)
    {
        return rAccessIterator[n];
    }
    const val_type& operator[](size_t n) const
    {
        return rAccessIterator[n];
    }
    void swap(deque& b)
    {
        deque temp(*this);
        *this = b;
        b = temp;
    }
    iterator erase (const_iterator position)
    {
        static iterator it(rAccessIterator._first, rAccessIterator._first, rAccessIterator._last, this);
        while (it!=position)
            it++;
        Node *t = it._cur;
        it._cur = it._cur->_next;
        it._cur->_prev = t->_prev;
        delete t;
        return it;
    }
    iterator erase (const_iterator first, const_iterator last )
    {
        static iterator it(rAccessIterator._first, rAccessIterator._first, rAccessIterator._last, this);
        while (it!=first)
            it++;
        while (it!=last)
        {
            Node *t = it._cur;
            it._cur = it._cur->_next;
            it._cur->_prev = t->_prev;
            delete t;
            ++it;
        }
        return it;
    }
private:
    iterator rAccessIterator;
    iterator _start;
    iterator _finish;
};

template <class val_type>
size_t deque<val_type>::_maxsize = 100;

#endif //H_W_DEQUEUE_DEQUEUE_H
