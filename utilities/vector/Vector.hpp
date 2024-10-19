#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdexcept>

using namespace std;

typedef int Rank;          // 秩
#define DEFAULT_CAPACITY 3 // 默认初始容量

// #define Vector iyan_vector

template <typename T>
class Vector
{ // 模板类 “向量”
protected:
    Rank _size;
    int _capacity;
    T *_elem;                                    // 定义规模 ，容量 ，数据空间
    void copyFrom(T const *A, Rank lo, Rank hi); // 定义复制数组区间   首地址,起始索引,结束索引  (A[lo,hi])

    void expand(); // 扩容函数
    void shrink(); // 缩容函数

    bool bubble(Rank lo, Rank hi);     // 扫描交换
    void bubbleSort(Rank lo, Rank hi); // 冒泡排序函数 范围（lo --> hi）

    Rank max(Rank lo, Rank hi); // 获取最大元素

    void selectionSort(Rank lo, Rank hi); // 选择排序函数 范围（lo --> hi）

    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi); // 归并排序函数 low，middle，high

    Rank partition(Rank lo, Rank hi); // 轴点构造函数 （？）

    void quickSort(Rank lo, Rank hi); // 快排函数

    void heapSort(Rank lo, Rank hi); // 堆排序函数

public:
    // 构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T const &v = 0) // 容量：c，规模：s，元素：v
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    } // 定义存储空间，初始化存储空间

    // 拷贝构造函数
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }               // 数组区间复制
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }                           // 数组整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } // 向量区间复制
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }               // 向量整体复制

    // 析构函数
    //~Vector() { delete[] _elem; } // 释放储存空间

    // 只读访问接口
    void push_Back(T const &e);           // 添加元素
    Rank size() const { return _size; }   // 查询规模
    bool empty() const { return !_size; } // 查询是否为空
    int disordered() const;               // 向量是否排序过标志位

    Rank find(T const &e) const { return find(e, 0, _size); } // 无序向量整体查找
    Rank find(T const &e, Rank lo, Rank hi) const;            // 无序向量区间查找

    Rank search(T const &e) const
    { return (0 >= _size) ? -1 : search(e, 0, _size); } // 向量整体查找
    Rank search(T const &e, Rank lo, Rank hi) const; // 向量区间查找 lo -> hi

    // 可访问接口
    T &operator[](Rank r) const;          // 重载索引运算符，使得向量可以用类似数组的形式访问
    Vector &operator=(Vector<T> const &); // 重载赋值运算符，赋值直接调用克隆向量

    T remove(Rank r);             // remove函数,删除秩为r的元素
    int remove(Rank lo, Rank hi); // 重载remove函数,删除区间[lo,hi)的元素

    Rank insert(Rank r, T const &e);                     // 插入元素e，在秩为r的首地址插入    Rank insert(T const &e) { return insert(_size, e); } // 重载insert函数，当唯一参数时，默认在末尾插入

    void sort(Rank lo, Rank hi, int ID); // 区间排序  lo -> hi
    void sort(int ID) { sort(0, _size, ID); }      // 整体排序,默认归并

    
    void unsort(Rank lo, Rank hi);      // 区间打乱， lo -> hi
    void unsort() { unsort(0, _size); } // 整体打乱

    int deduplicate(); // 无序去重
    int uniquify();    // 有序去重

    // 遍历
    void traverse(void (*)(T &)); // 传入函数指针，遍历
    template <typename VST>
    void traverse(VST &); // 传入函数对象，遍历
};

/*-------------------------------------------------------
 * 函数名称：push_Back(T const& e)
 * 函数功能：向量尾部增加元素
 */
template <typename T>
void Vector<T>::push_Back(T const &value)
{ // 添加元素
    if (_size == _capacity)
        expand(); // 需要扩容
    _elem[_size++] = value;
}

/*------------------------------------------------------
函数名称：copyFrom(T const* A, Rank lo, Rank hi)
函数功能：拷贝向量
*/
template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{ // 数组区间复制 lo -> hi
    /*template <typename T>         void     Vector<T>::                copyFrom(T const* A, Rank lo, Rank hi）*/
    /*自定义数据类型（int，char）    返回空    类外部定义函数的作用域声明     函数名                  参数         */

    _elem = new T[_capacity = 2 * (hi - lo)]; // 申请预留两倍空间
    _size = 0;                                // 初始化数据规模
    while (lo < hi)                           // A[lo,hi]
        _elem[_size++] = A[lo++];             // 复制至_elem[0,hi-lo]
}

/*------------------------------------------------------
函数名称：operator=(Vector<T> const& V)
函数功能：重载赋值运算符
*/
template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &V)
{ // 用成员函数方法，重载运算符
    if (_elem)
        delete[] _elem;            // 释放对象原有的空间
    copyFrom(V._elem, 0, V._size); // 对已经清空的空间，整体赋值
    return *this;                  // 返回当前对象指针
}

/*------------------------------------------------------
函数名称：operator[](Rank r)
函数功能：重载[]运算符
*/
template <typename T>
T &Vector<T>::operator[](Rank r) const
{ // ！！！ T&指定索引的元素，使得可以通过改变如：v[i]来直接改变向量元素，而不只是一个拷贝
    if (r < 0 || r >= _size)
        throw std::out_of_range("Index out of range");
    return _elem[r]; // 返回对应索引的元素
}

/*------------------------------------------------------
函数名称：expand()
函数功能：扩容
*/
template <typename T>
void Vector<T>::expand()
{ // 扩容函数
    if (_size < _capacity)
        return; // 容量未满，无需扩容
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY; // 如果当前空间小于默认空间，扩容到默认大小
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1]; // 扩容到原来的两倍
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i]; // 赋值原来的内容到新的空间
    delete[] oldElem;          // 释放原有空间
}

/*------------------------------------------------------
函数名称：shrink()
函数功能：缩容
*/
template <typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1)
        return; // 不至于缩容到默认容量（<<2联系上文是默认预留冗余）
    if (_size << 2 > _capacity)
        return;                     // 内容已经达到容器设计极限的1/4，无需缩容
    T *oldElem = _elem;             // 把原本空间里的内容暂存中介
    _elem = new T[_capacity >>= 1]; // 扩容为原来的两倍
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i]; // 把原来的内容从中介搬到到新的空间
    delete[] oldElem;          // 释放中介空间
}


/*------------------------------------------------------
函数名称：unsort(Rank lo, Rank hi)
函数功能：区间置乱函数接口
*/
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T *V = _elem + lo;
    while (lo < --hi)
        swap(V[lo++], V[rand() % (hi - lo + 1) + lo]); 
    
}

/*------------------------------------------------------
函数名称：
函数功能：重载 ‘==’，‘<’,'>'  判等和比较器
*/
// 泛用性考虑 1，3为指针版本，接收指针，在函数里面解指针，再调用重载的引用版本
template <typename T>
static bool lt(T *a, T *b) { return lt(*a, *b); } // 比较（小于）
template <typename T>
static bool lt(T &a, T &b) { return a < b; }

template <typename T>
static bool eq(T *a, T *b) { return eq(*a, *b); } // 判等
template <typename T>
static bool eq(T &a, T &b) { return a == b; }

/*------------------------------------------------------
函数名称：find(T const& e, Rank lo, Rank hi) const
函数功能：无序向量的顺序查找
*/
template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{ // 要查找的元素引用（可以是结构体等较大的数据类型，用引用节省空间），查找区间
    while ((lo < hi--) && (e != _elem[hi]));      // 从hi末尾向前查找
    return hi; // 返回查找到的索引，若无，返回-1
}

/*---------------------------------------------------------
 * 函数名称：insert(Rank r, T const& e)    //rank，value
 * 函数功能：插入
 */
template <typename T>
Rank Vector<T>::insert(Rank r, T const &e)
{
    expand(); // 如有必要，扩容
    for (int i = _size; i > r; i--)
    {
        
        _elem[i] = _elem[i - 1]; // 从 最后一个 到 第r个 把每个元素后移一位
    }
    _elem[r] = e;
    _size++; // 总体数据规模 +1
    return r;
}

/*-------------------------------------------------------
 * 函数名称：remove(Rank lo, Rank hi)
 * 函数功能：区间删除函数接口
 */
template <typename T>
Rank Vector<T>::remove(Rank lo, Rank hi)
{ // 返回删除区间的元素个数
    if (lo == hi)
        return 0; // 删除区间为空，无元素被删除,直接退出
    while (hi < _size)
        _elem[lo++] = _elem[hi++]; // 把区间后面的元素挨个复制到前面位置
    _size -= hi - lo;              // 规模减小
    shrink();                      // 如有必要缩容量
    return hi - lo;
}
/*-------------------------------------------------------
 * 函数名称：remove(Rank r)
 * 函数功能：从区间remove() 重载的单元素删除接口
 */
template <typename T>
T Vector<T>::remove(Rank r)
{ // 默认插入到末尾
    T e = _elem[r];
    remove(r, r + 1); // 单元素删除
    return e;         // 返回被删除的元素
}

/*-------------------------------------------------------
 * 函数名称：deplicate()
 * 函数功能：向量去重
 */
template <typename T>
int Vector<T>::deduplicate()
{

    // 对于无序的O(n^2)版本
    int oldSize = _size;                               // 记录原规模
    Rank i = 1;     
    while (i < _size) {
        if (find(_elem[i], 0, i) < 0) // 从第2个元素开始
            i++;     // 从后向前，逐个检查
        else
            remove(i);                                     
    }        
    return oldSize - _size; // 返回被删去的数量
}

template <typename T>
int Vector<T>::uniquify()
{
    // 对于有序向量的 O(n)版本
    int p1 = 0, p2 = p1;
    int oldSize = _size;
    while (p2 < _size - 1 && p1 <= p2)
    {
        p2++;
        if (_elem[p2] != _elem[p1])
            _elem[++p1] = _elem[p2];
    }
    remove(++p1, _size); // 区间删除
    shrink();
    return oldSize - _size; // 返回被删去的数量
}

/*-------------------------------------------------------
 * 函数名称：traverse(void (*visit)(T&))
 * 函数功能：使用函数指针，遍历所有元素
 */
template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{ // 利用函数指针，遍历所有元素
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

/*-------------------------------------------------------
 * 函数名称：traverse(VST& visit)
 * 函数功能：使用向量模板类，遍历所有元素
 */
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{ // 利用函数对象，遍历所有元素
    for (int i = 0; i < _size; i++)
        visit(_elem[i]); // visit函数对象，在遍历中运算
}

/*-------------------------------------------------------
 * 函数名称：increase(Vector<T>&)
 * 函数功能 递增一个T类对象中的元素
 */
template <typename T>
struct Increase
{
    virtual void operator()(T &e) const { ++e; }
}; // 重载Increase的（），为++；

template <typename T>
void increase(Vector<T> &V)
{
    Increase<T> increaser;
    V.traverse(increaser); // 调用traverse，遍历所有元素，调用重载的（）
}
// // 有问题的 increase 函数
// template <typename T> void increase(Vector<T>& V)
// { V.traverse(Increase<T>()); };  // 错误：传递了临时对象

/*-------------------------------------------------------
 * 函数名称：disordered()
 * 函数功能：整体有序性甄别
 */
template <typename T>
int Vector<T>::disordered() const
{
    int n = 0;
    for (int i = 1; i < _size; i++)
        if (_elem[i - 1] > _elem[i])
            n++;
    return n; // 返回逆序数,若有序泽则   n = 0
}

// 查找

/*-------------------------------------------------------
 * 函数名称：binSearch(T*A, T const& e, Rank lo, Rank hi)
 * 函数功能：二分查找
 */
template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) // 向量 A，查找元素e， 区间 [lo,hi）
{
    
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi])
        {
            hi = mi;
        }
        else if (A[mi] < e)
        {
            lo = mi + 1;
        }
        else
            return mi;
    }

    return -1;
}

/**
 * ----------------------------------------------------------
 * @name search(T const& e, Rank lo, Rank hi)
 * @brief  查找函数接口 
 * @param T const& e 待查找元素
 * @param Rank lo 起始位置
 * @param Rank hi 结束位置
 * @return 返回二分查找
 * @note 
**/
template<typename T> Rank Vector<T>::search(T const& e,Rank lo,Rank hi) const {
    return binSearch(_elem,e,lo,hi);
} 




/**
 * ----------------------------------------------------------
 * @name sort(Rank lo, Rank hi, int ID)
 * @brief 排序整合接口
 * @param Rank lo
 * @param Rank hi
 * @param int ID 选取排序算法：1：冒泡排序；2：选择排序；3：归并排序；4：堆排序；5（默认）：快速排序
 * @note
 **/
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi, int ID)
{

    switch (ID)
    {
    case 1:
        bubbleSort(lo, hi);
        break;
    // case 2: selectionSort(lo, hi);break;
    case 3:
    
        mergeSort(lo, hi);
        break;
    // case 4: heapSort(lo, hi);break;
    default:
        break; // quickSort(lo,hi);
    }
}

/**
 * ----------------------------------------------------------
 * @name bubbleSort(Rank lo, Rank hi)
 * @brief 冒泡排序
 * @param Rank lo
 * @param Rank hi
 * @note 内核bubble()使用了快停（一次遍历未冒泡，说明整体有序）
 **/
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--));
} // 从前往后进行起泡交换

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
    bool sorted = true;
    while (++lo < hi)
    {
        if (_elem[lo - 1] > _elem[lo])
        {
            sorted = 0;
            swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted; // 若有序，触发快停
}

/**
 * ----------------------------------------------------------
 * @name mergeSort(Rank lo, Rank hi)
 * @brief 归并排序
 * @param Rank lo
 * @param Rank hi
 * @note
 **/

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) //[lo,hi)
{
    if (hi - lo < 2)
    {
        return;
    } // 递归到了最小单元
    int mi = (hi + lo) >> 1; // 对分

    mergeSort(lo, mi); //[lo,mi) 递归
    mergeSort(mi, hi);
    merge(lo, mi, hi); // 合并
}

// template <typename T>
// void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
// {
//     T *A = _elem + lo;                  // 合并之后存储结果的首地址
//     int lb_1 = mi - lo, lb_2 = hi - mi; // 子向量长度
//     T *B_1 = new T[lb_1];
//     T *B_2 = _elem + mi;            // 临时地址存储子向量（当然也可以把最终合并结果存一个临时向量，核心就是不要让合并的结果覆盖到子向量就行）
//     for (Rank i = 0; i < lb_1; i++) // 复制前子向量
//     {
//         B_1[i] = A[i];
//     }

//     for (Rank i = 0, j = 0, k = 0; (j < lb_1) || (k < lb_2);)
//     {
//         if ((j < lb_1) && (!(k <= lb_2) || (B_1[j] < B_2[k])))
//             A[i++] = B_1[j++]; // 两种情况：1.两指针都未走完，则比大小，2：有一个走完，就直接走另一个
//         if ((k < lb_2) && (!(j <= lb_1) || (B_2[k] < B_1[j])))
//             A[i++] = B_2[k++];
//     }
// }

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for (Rank i = 0; i < lb; i++) B[i] = A[i]; // 复制前子向量
    
    int lc = hi - mi;
    T* C = _elem + mi; // 后子向量C[0, lc)就地
    
    for (Rank i = 0, j = 0, k = 0; j < lb; ) { // 归并：反复从B和C中取出更小者
        if (k >= lc || B[j] < C[k]) A[i++] = B[j++];
        else A[i++] = C[k++];
    }
    
    delete [] B; // 释放临时空间B
}





#endif