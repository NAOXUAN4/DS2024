// HuffChar.hpp - Huffman字符节点类的完整实现
#ifndef _HUFFCHAR_H_
#define _HUFFCHAR_H_

#include <stdio.h>
#include <string>
#include <iostream>

class HuffChar {
public:
    char ch;      // 字符
    int weight;   // 频率/权重
    
    // 构造函数
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {}
    
    // 拷贝构造函数
    HuffChar(const HuffChar& hc) : ch(hc.ch), weight(hc.weight) {}
    
    // 比较器：小于
    bool operator< (const HuffChar& hc) const { 
        return weight > hc.weight;  // 注意：Huffman树中权重越小优先级越高
    }
    
    // 比较器：大于
    bool operator> (const HuffChar& hc) const { 
        return weight < hc.weight; 
    }
    
    // 比较器：等于
    bool operator== (const HuffChar& hc) const { 
        return weight == hc.weight; 
    }
    
    // 比较器：不等于
    bool operator!= (const HuffChar& hc) const {
        return weight != hc.weight;
    }
    
    // 比较器：小于等于
    bool operator<= (const HuffChar& hc) const {
        return weight >= hc.weight;
    }
    
    // 比较器：大于等于
    bool operator>= (const HuffChar& hc) const {
        return weight <= hc.weight;
    }
    
    // 赋值运算符
    HuffChar& operator= (const HuffChar& hc) {
        if (this != &hc) {
            ch = hc.ch;
            weight = hc.weight;
        }
        return *this;
    }
    
    // 用于输出的运算符重载
    friend std::ostream& operator<< (std::ostream& os, const HuffChar& hc) {
        os << "[" << ((hc.ch >= ' ') ? hc.ch : '@') << ":" << hc.weight << "]";
        return os;
    }
    
    // 获取字符
    char getChar() const { return ch; }
    
    // 获取权重
    int getWeight() const { return weight; }
    
    // 设置字符
    void setChar(char c) { ch = c; }
    
    // 设置权重
    void setWeight(int w) { weight = w; }
    
    // 增加权重
    void increaseWeight(int delta = 1) { weight += delta; }
    
    // 判断是否为非打印字符
    bool isNonPrintable() const { return ch < ' '; }
    
    // 转换为字符串（用于调试）
    std::string toString() const {
        char buf[64];
        sprintf(buf, "[%c:%d]", isNonPrintable() ? '@' : ch, weight);
        return std::string(buf);
    }
};

// 用于测试的示例函数
void huffCharExample() {
    // 创建HuffChar对象
    HuffChar hc1('a', 10);
    HuffChar hc2('b', 5);
    HuffChar hc3('c', 15);
    
    // 测试比较操作
    std::cout << "hc1 < hc2: " << (hc1 < hc2) << std::endl;
    std::cout << "hc1 > hc3: " << (hc1 > hc3) << std::endl;
    
    // 测试输出
    std::cout << "hc1: " << hc1 << std::endl;
    std::cout << "hc2: " << hc2 << std::endl;
    std::cout << "hc3: " << hc3 << std::endl;
    
    // 测试权重修改
    hc1.increaseWeight(5);
    std::cout << "After increasing weight of hc1: " << hc1 << std::endl;
    
    // 测试拷贝构造
    HuffChar hc4(hc1);
    std::cout << "Copy of hc1: " << hc4 << std::endl;
    
    // 测试赋值运算符
    HuffChar hc5;
    hc5 = hc2;
    std::cout << "Assignment of hc2: " << hc5 << std::endl;
    
    // 测试非打印字符处理
    HuffChar hc6('\n', 1);
    std::cout << "Non-printable character: " << hc6 << std::endl;
    
    // 测试toString方法
    std::cout << "hc1 as string: " << hc1.toString() << std::endl;
}

#endif