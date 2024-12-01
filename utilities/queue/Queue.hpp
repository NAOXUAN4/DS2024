#ifndef QUEUE_HPP
#define QUEUE_HPP


#include "utilities/list/List.hpp" //以List为基类 
template <typename T> class Queue: public List<T> { //队列模板类（继承List原有接口） 
public: //size()、empty()以及其它开放接口均可直接沿用 
    void enqueue(T const& e) { insertAsLast(e); } //入队：尾部揑入 
    T dequeue() { return remove(this -> first()); } //出队：首部初除 
    T& front() { return this -> first()->data; } //队首 

    void push(const T& value) {
        this->enqueue(value);
    }

    // 移动语义版本
    void push(T&& value) {
        this->enqueue(std::move(value));
    }

    // 从队列前端移除元素
    T pop() {
        dequeue();
    }
}; 


#endif