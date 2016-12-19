#ifndef FASTLIST_HPP
#define FASTLIST_HPP

#include <stdexcept>
#include <cmath>
#include <iostream>

using namespace std;

template <typename T> class fast_list {
public:
    fast_list() : front(new T[4]), end(new T[4]), size(0), capacity(8), head(0), tail(0) {}
    ~fast_list() {
        delete [] front;
        delete [] end;
    }

    void push_back(const T &item) {
        if (size == capacity)
            reallocate(1);
        if (tail << 1 == capacity)
            balance();
        end[tail++] = item;
        ++size;
    }
    
    T pop_back() {
        if (size > 0) {
            if (capacity > 15 && size << 2 <= capacity) {
                reallocate(0);
            }
            if (tail == 0) {
                balance();
            }
            --size;
            return end[--tail];
        }
        throw range_error("\nList is empty, can not pop");
    }

    void push_front(const T &item) {
        if (size == capacity)
            reallocate(1);
        if (head << 1 == capacity)
            balance();
        front[head++] = item;
        ++size;
    }

    T pop_front() {
        if (size > 0) {
            if (capacity > 15 && size << 2 <= capacity) {
                reallocate(0);
            }
            if (head == 0) {
                balance();
            }
            --size;
            return front[--head];
        }
        throw range_error("\nList is empty, can not pop");
    }

    void print() {
        cout << endl;
        for (int i = head - 1; i >= 0; --i) {
            cout << front[i] << ' ';
        }
        for (int i = 0; i < tail; ++i) {
            cout << end[i] << ' ';
        }
        cout << endl;
    }

private:
    T *front, *end;
    int size, capacity, head, tail;

    void reallocate(bool need_more) {
        T *tmp_front = nullptr, *tmp_end = nullptr;
        capacity = need_more ? (capacity << 1) : (capacity >> 1);
        tmp_front = new T[capacity >> 1], tmp_end = new T[capacity >> 1];
        for (int i = 0; i < head; ++i) {
            tmp_front[i] = front[i];
        }
        for (int i = 0; i < tail; ++i) {
            tmp_end[i] = end[i];
        }
        delete [] front;
        delete [] end;
        front = tmp_front;
        end = tmp_end;
    }

    void balance() {
        int offset = ceil(abs(tail - head) / 2.0);
        int i, j = 0;
        if (tail > head) {
            head += offset;
            tail -= offset;
            for (i = head - 1; i > offset - 1; --i) {
                front[i] = front[i - offset];
            }
            for (; i >= 0; --i, ++j) {
                front[i] = end[j];
            }
            for(i = 0; i < tail; ++i) {
                end[i] = end[i + offset];
            }
        } else {
            tail += offset;
            head -= offset;
            for (i = tail - 1; i > offset - 1; --i) {
                end[i] = end[i - offset];
            }
            for (; i >= 0; --i, ++j) {
                end[i] = front[j];
            }
            for(i = 0; i < head; ++i) {
                front[i] = front[i + offset];
            }
        }
    }
};

#endif
