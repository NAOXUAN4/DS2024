#include "ListNode.cpp"

template<typename T> class List {
    
private:
    int _size; ListNodePosi(T) _header; ListNodePosi(T) _trailer; //规模,头哨兵,尾哨兵


protected:
    void init();//初始化
    int clear();
    void copyNodes(ListNodePosi(T), int); //复制节点
    void merge(ListNodePosi(T) &, int, List<T>&, ListNodePosi(T),int); //合并两个有序表
    void mergeSort(ListNodePosi(T), int); //归并排序
    void selectionSort(ListNodePosi(T), int);  //对从p开始的n个元素选择排序
    void insertionSort(ListNodePosi(T), int); //对从p开始的n个元素插入排序

public:
    List() { init(); } //默认构造函数
    List(List<T> &L); //复制构造函数
    List(List<T> const& L, Rank r, int n);  //复制列表从r开始的n个元素
    List(ListNodePosi(T) p,int n);  //复制从位置开始的n个元素

    ~List(); //析构函数

    // 只读访问接口
    Rank size() const { return _size; } // 返回表长
    bool empty() const { return !_size; } // 返回是否为空表
    
    T& operator[](Rank r) const;  // 重载下标运算符，只读,支持循序访问
    ListNodePosi(T) first() const { return _header->_succ; } // 返回首节点
    ListNodePosi(T) last() const { return _trailer->_pred; } // 返回尾节点
    bool vaild(ListNodePosi(T) p)  { return p && (_trailer != p) && (_header != p); } //判断位置是否合法
    int disordered() const  //判断是否有序

    ListNodePosi(T) find(const T& e) const
    { return find(e, _size, _trailer); }

    ListNodePosi(T) find(const T& e, int n, ListNodePosi(T) p) const; //从p开始找e,最多找n个元素
    ListNodePosi(T) search(const T& e) const
    { return search(e, _size, _trailer); }

    ListNodePosi(T) search(const T& e, int n, ListNodePosi(T) p) const; //从p开始找e,最多找n个元素

    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //从p开始找最大元素，最多找n个元素
    ListNodePosi(T) selectMax(){return selectMax(_header, _size);}  //整体找最大元素


    // 可写访问接口
    ListNodePosi(T) insertAsFirst(const T& e); //插入到表头
    ListNodePosi(T) insertAsLast(const T& e); //插入到表尾

    ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T& e); //把e插入到p之前
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T& e); //把e插入到p之后

    T remove(ListNodePosi(T) p); //删除p节点
    void merge(List<T>& L){merge(first(), _size, L, L.first(), L._size);} //整体合并
    
    void sort(ListNodePosi(T) p, int n);
    void sort(){sort(first(), _size);} //整体排序
    int deduplicate(); //删除重复元素
    int uniquify();
    void reverse();  //前后翻转

    void traverse(void (*)(T&)); //遍历
    template <typename VST> void traverse(VST&); //遍历,依次实施visit()


    //初始化
    template <typename T>void List <T>::init()
    {
        
        _header = new ListNode<T>;  // 头哨兵
        _trailer = new ListNode<T>;  // 尾哨兵
        _header->_succ = _trailer; _header->_pred = NULL;
        _trailer->_pred = _header; _trailer->_succ = NULL;
        _size = 0;
    }

    template <typename T> T& List<T> ::operator[](Rank r) const   //重载下标运算符，使用从头链表遍历查找的方法
    {   
        ListNodePosi(T) p = first(); 
        while(0 < r--) p = p->_succ;
        return p->data;
    }

    template <typename T> ListNodePosi(T) List<T>::find(const T& e, int n, ListNodePosi(T) p) const   //查找
    {
        while(0 < n--)
        {
            p = p->_succ;
            if(e == p->data) return p;
        } return NULL;
    }




    //插入
    template <typename T> ListNodePosi(T) List<T>::insertAsFirst(const T& e)
    {
        _size++;
        return _header->insertAsSucc(e);
    }

    template <typename T> ListNodePosi(T) List<T>::insertAsLast(const T& e)
    {
        _size++;
        return _trailer->insertAsPred(e);
    }
    
    template <typename T> ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, const T& e)
    {
        _size++;
        return p->insertAsPred(e);
    }

    template <typename T> ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, const T& e)
    {
        _size++;
        return p->insertAsSucc(e);
    }

    //前插入
     template <typename T> ListNodePosi(T) List<T>::insertAsPred( const T& e)
    {
        ListNodePosi(T) p = new ListNode(e,pred,this);
        pred->succ = p; pred = p;
        return p;
    }
    //后插入
    template <typename T> ListNodePosi(T) List<T>::insertAsSucc( const T& e)
    {
        ListNodePosi(T) p = new ListNode(e,this,succ);
        succ->pred = p; succ = p;
        return p;
    }




    //拷贝
    template <typename T> List<T>::copyNodes(ListNodePosi(T) p, int n)
    {
        init();
        while(n--)
        {
            insertAsLast(p->data);
            p = p->_succ;
        }
    }

    template <typename T> List<T>::List(ListNodePosi(T) p, int n)  //区间复制,从位置开始复制n个元素
    {
        copyNodes(p, n);
    }

    template <typename T> List<T>::List(List<T> &L)    //整体列表复制(传入列表重载)
    {
        copyNodes(L.first(), L._size);
    }

    template <typename T> List<T>::List(List<T> const& L, Rank r, int n)   //区间复制(传入区间+列表)
    {
        copyNodes(L[r], n);
    }


    // 删除
    template <typename T> T List<T>::remove(ListNodePosi(T) p)
    {
        T e = p->data;
        p->_pred->_succ = p->_succ;
        p->_succ->_pred = p->_pred;
        delete p;
        _size--;
        return e;
    }

    //析构

    template <typename T> List<T>::~List()
    {
        clear(); delete _header; delete _trailer;
    }

    template <typename T> void List<T>::clear()  //清空,返回旧表长
    {
        int oldSize = _size;
        while(_size) remove(header()->_succ);
        return oldSize;
    }


    //唯一化
    template <typename T> int List<T>::deduplicate()  //乱序的长耗时唯一化,通过find遍历函数知道唯一性
    {
        if(_size < 2) return 0;
        int oldSize = _size;
        ListNodePosi(T) p = header; Rank r = 0;
        while(_trailer != (q = p->_succ))
        {
            ListNodePosi(T) q = find(p->data,r,p);
            q? remove(q): r++;
        }
       return oldSize - _size;
    }

    template<typename T> int List<T>::uniquify()
    {
        if (_size < 2) return 0;
        int oldSize = _size;
        ListNodePosi(T) p; ListNodePosi(T) q;
        for(p  = header,q = p->_succ; q != trailer;p = q, q = q->_succ)  //从左到右遍历,删除重复元素
            if(p->data == q->data) { remove(q);q = p;}
        return oldSize - _size;
        
    }

    //遍历
    template <typename T> void List<T>::traverse(void (*)(T&))  //遍历
    {
        for(ListNodePosi(T) p = header->_succ; p != trailer; p = p->_succ)
            visit(p->data);
    }
    template <typename T> template <typename VST> void List<T>::traverse(VST& visit)  //遍历
    {
        for(ListNodePosi(T) p = header->_succ; p != trailer; p = p->_succ)
            visit(p->data);
    }

    //查找
    template <typename T> ListNodePosi(T) List<T> ::search(const T& e , int n,ListNodePosi(T) p)  //从位置p开始查找n个元素const
    {
        while(0<=n--) 
            if((p = p->_pred)->data <= e) break;
        return p;
    }


    //排序

    //插入排序
    template <typename T> void List<T>::insertionSort(ListNodePosi(T) p, int n)
    {
        
        for(int r = 0; r < n; r++)
        {
            insertAfter(search(p->data, r, p),p->data);  //插入位置
            p = p->_succ; remove(p->pred);  //删除原位置,转向下一个元素
        }
    }

    //选择排序
    template <typename T> void List<T>::selectionSort(ListNodePosi(T) p, int n)  //选最大的往尾部插入
    {
        ListNodePosi(T) head = p->_pred;  //头结点
        ListNodePosi(T) tail = p;  //尾结点
        while(1<n)
        {
            ListNodePosi(T) max = selectMax(head -> succ, n);  //选择最大元素
            insertBefore(tail, remove(max));
            tail = tail->_pred; n--; 
        }
    }

    template <typename T> ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)  //选择最大元素
    {
        ListNodePosi(T) max = p;  
        for(ListNodePosi(T) cur = p; 1 < n; n--)
        {
            cur = cur->_succ;
            if(max->data < cur->data) max = cur;    //遍历寻找最大元素
        }
        return max;
    }


    //归并排序
    template <typename T> void List<T>::merge(ListNodePosi(T) p, int n,List<T> &L, int m)  //归并排序
    {
        ListNodePosi(T) pp = p->pred;
        while(0<m)
        {
            if((0<n) && (p->data <= q->data))
            {
                if(q==(p = p->succ) break; n--;)
            }
            else
            { insertBefore(p, L.remove((q = q->succ)->pred)); m--; }
        }
        p = pp->_succ;
    }

    template <typename T> void List<T>::mergeSort(ListNodePosi(T)& p, int n)
    {
        if(n<2) return;
        int m = n>>1;  //将前半段和后半段分别排序
        ListNodePosi(T) q = p;
        for (int i = 1; i < m; i++) q = q->_succ;
        mergeSort(p, m); mergeSort(q,n-m);
        merge(p, m, *this, n-m);
    }


    

};