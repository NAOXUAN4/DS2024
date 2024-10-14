#include "../utilities/vector/Vector.hpp"
#include <cstdint>

template <typename T> class Stack : public Vector<T> {
public: 
    void push(T const &e) { Vector<T>::push_Back(e); }  //末尾入栈
    T pop() { return remove(size() - 1); }
    T& top() { return (*this)[size() - 1]; }
};

// void convert(Stack<char>& S, __int64 n, int base){
//     static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
//     if(0 < n){  // 递归结束条件
//         convert(S, n / base, base);  // 递归
//         S.push(digit[n % base]);  // 余数入栈
//     }
// }

// void trim(const char exp[], int& lo, int& hi){         // 去掉表达式中的空格
//     while((lo <= hi) && (exp[lo] == '(') && (exp[lo] != ')' )) lo++;   //查找第一个和
//     while((lo <= hi) && (exp[hi] == ')') && (exp[hi] != '(' )) hi--;   //最后一个括号
// }

// int divide(const char exp[], int lo, int hi){
//     int mi = lo; int crc = 1;  // crc为当前括号匹配的次数
//     while ((0 < crc) && (++ mi <= hi))
//     {
//         if(exp[mi] == ')') crc--; if(exp[mi] == '(') crc++;
//     }
// }


// bool paren(const char exp[], int lo, int hi)
// {
//     trim(exp, lo, hi); 
//     if (lo > hi) { return true; }
//     if(exp[lo] != '(') return false;
//     if(exp[hi] != ')') return false;

//     int mi = divide(exp, lo, hi);
//     if (mi > hi) { return false; }
//     return paren(exp, lo, mi - 1) && paren(exp, mi + 1, hi - 1);  //检查左右子表达式
    
    
// }



