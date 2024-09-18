typedef int Rank;  //秩
#define DEFAULT_CAPACITY  3  //默认初始容量


template <typename T > class Vector {   //模板类 “向量”
protected:
    Rank _size; int_capacity; T* _elem;  //定义规模 ，容量 ，数据空间
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
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T const& v = 0); //容量：c，规模：s，元素：v
    {_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v)}  //定义存储空间，初始化存储空间

    //拷贝构造函数
    Vector(T const* A,Rank lo,Rank hi) {copyFrom(A,lo,hi)}  //数组区间复制
    Vector(T const* A,Rasnk n) {copyFrom(A,0,n)}  //数组整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) {copyFrom(V._elem,lo,hi)};  //向量区间复制
    Vector(Vector<T> const& V) {copyFrom(V._elem,0,V._size)}; //向量整体复制

    //析构函数 
    ~Vector() {delete [] _elem;}  //释放储存空间

    //只读访问接口
    Rank size() const {return _size;} //查询规模
    bool empty() const {return !_size;} //查询是否为空
    int disordered() const;     //向量是否排序过标志位
    
    Rank find(T const& e) const {return find(e,0,_size)};  //无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const;   //无序向量区间查找
    




};

