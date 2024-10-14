#ifndef LISTNODE_H
#define LISTNODE_H

typedef int Rank;
#include <cstddef>

#define ListNodePosi(T) ListNode<T>*  //定义链表节点指针类型

template <typename T> struct ListNode{  //双向链表做列表
    T data;  //数据域
    ListNodePosi(T) pred;  //前驱指针
    ListNodePosi(T) succ;  //后继指针


    ListNode(){}  //默认构造函数,对于header,trailer
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL): data(e), pred(p), succ(s){} //构造器

    ListNodePosi(T) insertAsPred(T const& e);   //插入前驱
    ListNodePosi(T) insertAsSucc(T const& e);   //插入后继
};

#endif