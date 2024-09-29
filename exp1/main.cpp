#include <bits/stdc++.h>
#include "utilities/vector/Vector.h"






class Complex {  //定义复数类
    public:
        double real;
        double imag;
        double modulus() const {
            return sqrt(real*real+imag*imag);
        }

    Complex() : real(0), imag(0) {}  // 默认构造函数
    Complex(double real, double imag) {
        this->real = real;
        this->imag = imag;
    }
};


class complex_v : public Vector<Complex> {
    public:
    using Vector<Complex>::Vector;  //继承Vector类所有成员
    bool operator<(Vector<Complex> const &V);  //重载运算符
};

bool complex_v::operator<(Vector<Complex> const &V)  //重载运算符
{
    
}






void print(Complex &a)   //输出函数
{
    cout<<a.real<<"+" << a.imag << "i   ";
}



int main(){

    srand(static_cast<unsigned int>(time(nullptr)));  // 使用当前时间作为种子

    Complex defaultComplex;  //生成一个实例以便构造向量
    Vector<Complex> complex_vector(10,0,defaultComplex);
    int num  = 10;  //默认复数向量成员数：10
    for(int i  = 0;i < num;i++)
    {
        Complex new_complex = Complex(rand()%10,rand()%10);  //产生随机复数
        complex_vector.push_Back(new_complex);
    }

    for(int i = 0;i < num/3;i++)   //取大约三分之一的元素和别的重复
    {
        complex_vector[i] = complex_vector[rand()%num];    //制造重复
    }

    cout<<"\n生成复数向量： \n";
    complex_vector.traverse(print);
    cout<<endl;

    cout<<"\n置乱： \n";
    complex_vector.unsort();
    complex_vector.traverse(print);
    cout<<endl;


    //比较器，判等器重载问题？？
    // cout<<"查找： \n";
    // int chose_index = rand()%num;
    // cout<<"choose :" <<complex_vector[chose_index].real<<"+"<<complex_vector[chose_index].imag<<"i"<<endl;
    // Complex same_complex = Complex(complex_vector[chose_index].real,
    //                                             complex_vector[chose_index].imag);
    // int place = complex_vector.find(same_complex);
                                                
    // cout<<"place :"<<place<<endl;
    // cout<<endl;

    cout<<"\n插入： \n";
    Complex new_complex = Complex(rand()%10,rand()%10);
    cout<<"new :"<<new_complex.real<<"+"<<new_complex.imag<<"i"<<endl;
    int place = rand()%num;
    cout<<"insert_place :"<<place<<endl;
    complex_vector.insert(place,new_complex);
    complex_vector.traverse(print);
    cout<<endl;

    cout<<"\n删除： \n";
    place = rand()%num;
    cout<<"delete :"<<complex_vector[place].real<<"+"<<complex_vector[place].imag<<"i"<<endl;
    cout<<"delete_place :"<<place<<endl;
    complex_vector.remove(place);
    complex_vector.traverse(print);
    cout<<endl;

    //cout<<"\n唯一化： \n";

    cout<<"\n排序： \n";
    complex_vector.sort(1);
    complex_vector.traverse(print);
    cout<<endl;

    






    return 0;
}