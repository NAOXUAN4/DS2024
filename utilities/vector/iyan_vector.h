#ifndef _VECTOR_H
#define _VECTOR_H
#define Vector iyan_vector
using namespace std;



typedef int Rank;  //秩
#define DEFAULT_CAPACITY  3  //默认初始容量


template <typename T > class Vector {   //模板类 “向量”
protected:
    Rank _size; int _capacity; T* _elem;  //定义规模 ，容量 ，数据空间
    void copyFrom(T const* A, Rank lo, Rank hi); //定义复制数组区间   首地址,起始索引,结束索引  (A[lo,hi])
    
    void expand();  //扩容函数 
    void shrink(); //缩容函数 

    bool bubble(Rank lo, Rank hi);  //扫描交换
    bool bubbleSort(Rank lo, Rank hi);   //冒泡排序函数 范围（lo --> hi）
    
    Rank max(Rank lo, Rank hi);   //获取最大元素
    
    void selectionSort(Rank lo, Rank hi); //选择排序函数 范围（lo --> hi）

    void merge(Rank lo, Rank mi, Rank hi);  
    void mergeSort(Rank lo, Rank hi);  //归并排序函数 low，middle，high

    Rank partition(Rank lo, Rank hi); //轴点构造函数 （？）

    void quickSort(Rank lo, Rank hi); //快排函数

    void heapSort(Rank lo, Rank hi); //堆排序函数


public:
    
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T const& v = 0) //容量：c，规模：s，元素：v
    {_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);}  //定义存储空间，初始化存储空间

    //拷贝构造函数
    Vector(T const* A,Rank lo,Rank hi) {copyFrom(A,lo,hi);}  //数组区间复制
    Vector(T const* A,Rank n) {copyFrom(A,0,n);}  //数组整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) {copyFrom(V._elem,lo,hi);}  //向量区间复制
    Vector(Vector<T> const& V) {copyFrom(V._elem,0,V._size);} //向量整体复制

    //析构函数 
    ~Vector() {delete [] _elem;}  //释放储存空间

    //只读访问接口
    Rank size() const {return _size;} //查询规模
    bool empty() const {return !_size;} //查询是否为空
    int disordered() const;     //向量是否排序过标志位
    
    Rank find(T const& e) const {return find(e,0,_size);}  //无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const;   //无序向量区间查找
    
    Rank search(T const& e) const 
    {return search(0 >= _size) ? -1: search(e,0,_size);}   //向量整体查找
    Rank search(T const& e, Rank lo, Rank hi) const;   //向量区间查找 lo -> hi

    //可访问接口
    T& operator[](Rank r) const; //重载索引运算符，使得向量可以用类似数组的形式访问
    Vector& operator=(Vector<T> const&);  //重载赋值运算符，赋值直接调用克隆向量
    
    T remove(Rank r); //remove函数,删除秩为r的元素
    int remove(Rank lo, Rank hi); // 重载remove函数,删除区间[lo,hi)的元素

    Rank insert(Rank r, T const& e);  //插入元素e，在秩为r的首地址插入
    Rank insert(T const& e) {return insert(_size,e);}  //重载insert函数，当唯一参数时，默认在末尾插入

    void sort(Rank lo, Rank hi);  //区间排序  lo -> hi
    void sort() {sort(0,_size);}   //整体排序

    void unsort(Rank lo, Rank hi); //区间打乱， lo -> hi
    void unsort() {unsort(0,_size);}  //整体打乱

    int depduplicate();  //无序去重
    int uniquify(); //有序去重

    //遍历
    void traverse(void (*)(T&));  //传入函数指针，遍历
    template <typename VST> void traverse(VST&); //传入函数对象，遍历

};

/*------------------------------------------------------
函数名称：copyFrom(T const* A, Rank lo, Rank hi)
函数功能：拷贝向量
------------------------------------------------------*/
template <typename T>void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi){  //数组区间复制 lo -> hi   
/*template <typename T>         void     Vector<T>::                copyFrom(T const* A, Rank lo, Rank hi）*/      
/*自定义数据类型（int，char）    返回空    类外部定义函数的作用域声明     函数名                  参数         */

    _elem = new T[_capacity = 2*(hi - lo)];     //申请预留两倍空间
    _size = 0;                      //初始化数据规模
    while(lo < hi)                  //A[lo,hi]
         _elem[_size++] = A[lo++];  //复制至_elem[0,hi-lo]
}


/*------------------------------------------------------
函数名称：operator=(Vector<T> const& V)
函数功能：重载赋值运算符
------------------------------------------------------*/
template <typename T>Vector<T>& Vector<T>::operator=(Vector<T> const& V){  //用成员函数方法，重载运算符
    if (_elem) delete [] _elem;  //释放对象原有的空间
    copyFrom(V._elem,0,V._size); //对已经清空的空间，整体赋值
    return *this;                //返回当前对象指针
}

/*------------------------------------------------------
函数名称：operator[](Rank r)
函数功能：重载[]运算符
------------------------------------------------------*/
template <typename T> T& Vector<T>::operator[](Rank r) const{  // ！！！ T&指定索引的元素，使得可以通过改变如：v[i]来直接改变向量元素，而不只是一个拷贝
    return _elem[r];  //返回对应索引的元素
}




/*------------------------------------------------------
函数名称：expand()
函数功能：扩容
------------------------------------------------------*/
template <typename T> void Vector<T>::expand(){  //扩容函数
    if (_size < _capacity) return; //容量未满，无需扩容
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //如果当前空间小于默认空间，扩容到默认大小
    T* oldElem = _elem; _elem = new T[_capacity <<= 1];  //扩容到原来的两倍
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //赋值原来的内容到新的空间
    delete [] oldElem;  //释放原有空间
}

/*------------------------------------------------------
函数名称：shrink()
函数功能：缩容
------------------------------------------------------*/
template <typename T> void Vector<T>::shrink(){
    if (_capacity < DEFAULT_CAPACITY << 1) return;  //不至于缩容到默认容量（<<2联系上文是默认预留冗余）
    if (_size << 2 > _capacity) return;  //内容已经达到容器设计极限的1/4，无需缩容
    T* oldElem = _elem;                  //把原本空间里的内容暂存中介
    _elem = new T[_capacity >>= 1];      //扩容为原来的两倍
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];   //把原来的内容从中介搬到到新的空间
    delete [] oldElem;   //释放中介空间
}

/*------------------------------------------------------
函数名称：premute(Vector<T>& V)
函数功能：置乱函数核心
------------------------------------------------------*/
template <typename T> void premute(Vector<T>& V){   //参数：直接填入待排序向量名称，即为一个vector类型的应引用
    for (int i = V._size; i>0; i--)               //从后向前
        swap(V[i-1], V[rand() % i]);            //把当前索引的元素和随机索引的元素交换  随机原理：rand() % i 永不超过 i，即为 0 ~ i-1
}

/*------------------------------------------------------
函数名称：unsort(Rank lo, Rank hi)
函数功能：区间置乱函数接口
------------------------------------------------------*/
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi){
    premute(Vector<T>(_elem + lo, hi - lo));    //对核心传入待置乱的区间组成的子函数  参数：区间首地址，子区间Rank
}


/*------------------------------------------------------
函数名称：
函数功能：重载 ‘==’，‘<’,'>'  判等和比较器
------------------------------------------------------*/
//泛用性考虑 1，3为指针版本，接收指针，在函数里面解指针，再调用重载的引用版本
template <typename T>static bool lt(T* a, T* b){return lt(*a,*b);}  //比较（小于）
template <typename T>static bool lt(T& a,T& b){return a < b;} 

template <typename T>static bool eq(T* a, T* b){return eq(*a,*b);} //判等
template <typename T>static bool eq(T& a,T& b){return a == b;}












#endif