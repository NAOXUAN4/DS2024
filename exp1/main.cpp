#include <bits/stdc++.h>
#include "utilities/vector/Vector.h"
#include <chrono>

#define MAX_SIZE 10

using namespace std;

class Complex {  //定义复数类
    public:
        double real;
        double imag;
        double module;
        

    Complex() : real(0), imag(0), module(0) {}  // 默认构造函数
    Complex(double real, double imag) {
        this->real = real;
        this->imag = imag;
        this->module = sqrt(real * real + imag * imag);
    }

  bool operator<(const Complex& other) const {
        if (std::abs(module - other.module) < 1e-9) {
            return real < other.real || (std::abs(real - other.real) < 1e-9 && imag < other.imag);
        }
        return module < other.module;
    }
    bool operator>(const Complex& other) const {
        if (this->module == other.module) {
            return this->real > other.real;
        }
        return this->module > other.module;
    }

    bool operator!=(const Complex& other) const {
        return this->real != other.real || this->imag != other.imag;
    }

    bool operator==(const Complex& other) const {
        return this->real == other.real && this->imag == other.imag;
    }
};




template<typename Func>
double clock_v(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
}



void print(Complex &a)   //输出函数
{
    cout<<a.real<<"+" << a.imag << "i   ";
}


template <typename T>
void COMPLEX_interval_Search(Complex complex_min,Complex complex_max,Vector<T> &parent,Vector<T>& child)
{
    int min = parent.search(complex_min); int max = parent.search(complex_max);
    for (int i = 0; i < max-min; i++)
    {
        Complex tmp(parent[i+min].real,parent[i+min].imag);
        child.push_Back(tmp);
    }
    
}





int main(){

    int size_v;
    cout<<"复数向量实验"<<endl;
    cout<<"输入复数向量数量：";
    cin>>size_v;




    srand(static_cast<unsigned int>(time(nullptr)));  // 使用当前时间作为种子

    Complex defaultComplex;  //生成一个实例以便构造向量
    
    int num  = size_v;  //默认复数向量成员数：10
    Vector<Complex> complex_vector(num,0,defaultComplex);
    for(int i  = 0;i < num;i++)
    {
        Complex new_complex = Complex(double(rand()%100)/10,double(rand()%100)/10);  //产生随机复数
        complex_vector.push_Back(new_complex);
    }

    for(int i = 0;i < num/3;i++)   //取大约三分之一的元素和别的重复
    {
        complex_vector[i] = complex_vector[rand()%num];    //制造重复
    }

    cout<<"\n生成复数向量: \n";
    complex_vector.traverse(print);
    cout<<endl;

    cout<<"\n置乱: \n";
    complex_vector.unsort();
    complex_vector.traverse(print);
    cout<<endl;


    
    cout<<"查找： \n";
    int chose_index = rand()%num;
    cout<<"choose :" <<complex_vector[chose_index].real<<"+"<<complex_vector[chose_index].imag<<"i"<<endl;
    Complex same_complex = Complex(complex_vector[chose_index].real,
                                                complex_vector[chose_index].imag);
    int place = complex_vector.find(same_complex);
                                                
    cout<<"place :"<<place<<endl;
    cout<<endl;

    cout<<"\n插入: \n";
    Complex new_complex = Complex(rand()%10,rand()%10);
    cout<<"new :"<<new_complex.real<<"+"<<new_complex.imag<<"i"<<endl;
    place = rand()%num;
    cout<<"insert_place :"<<place<<endl;
    complex_vector.insert(place,new_complex);
    complex_vector.traverse(print);
    cout<<endl;

    cout<<"\n删除: \n";
    place = rand()%num;
    cout<<"delete :"<<complex_vector[place].real<<"+"<<complex_vector[place].imag<<"i"<<endl;
    cout<<"delete_place :"<<place<<endl;
    complex_vector.remove(place);
    complex_vector.traverse(print);
    cout<<endl;

    //cout<<"\n唯一化： \n";

    Vector<Complex> tosort_vector(complex_vector);

    cout<<"\n排序: \n";
    double time_b = clock_v([&]() { 
        tosort_vector.sort(1);   //使用匿名函数传入
    });


    double time_m = clock_v([&]() {
        complex_vector.sort(3);
    });

    cout<<"乱序冒泡排序时间："<<time_b<<" us   "<< "乱序归并排序时间："<< time_m<<" us"<<endl;
    
    

    time_b = clock_v([&]() { 
        complex_vector.sort(1);   //使用匿名函数传入
    });

    time_m = clock_v([&]() {
        complex_vector.sort(3);
    });

    cout<<"有序冒泡排序时间："<<time_b<<" us   "<< "有序归并排序时间："<< time_m<<" us"<<endl;

    for (int i = 0; i < complex_vector.size(); i++) 
    {
        tosort_vector[tosort_vector.size() - i - 1] = complex_vector[i]; //将排序后的向量元素逆序
    }

    complex_vector = tosort_vector;
    
    time_b = clock_v([&]() { 
        tosort_vector.sort(1);   //使用匿名函数传入
    });

    time_m = clock_v([&]() {
        complex_vector.sort(3);
    });

    cout<<"逆序冒泡排序时间："<<time_b<<" us   "<< "逆序归并排序时间："<< time_m<<" us"<<endl;

    cout<<"\n排序后复数向量: \n";
    complex_vector.traverse(print);
    cout<<endl;


    cout<<"\n区间查找: \n";
    Complex min = complex_vector[rand()%(complex_vector.size()/2)];
    Complex max = complex_vector[complex_vector.size()/2 + rand()%(complex_vector.size()/2)];

    cout<<"min :"<<min.real<<"+"<<min.imag<<"i       "<<"max :"<<max.real<<"+"<<max.imag<<"i"<<endl;
    Vector<Complex> interval_vector(0,0,defaultComplex);
    COMPLEX_interval_Search(min,max,complex_vector, interval_vector);
    interval_vector.traverse(print);
    cout<<endl;




    return 0;
}