// HuffCode.hpp - Huffman编码串的类型定义
#ifndef _HUFFCODE_H_
#define _HUFFCODE_H_

#include "utilities/others/bitmap.hpp"// 使用位图类

typedef Bitmap HuffCode; // Huffman编码串的类型别名

#endif

// HuffChar.hpp - Huffman字符类型定义
#ifndef _HUFFCHAR_H_
#define _HUFFCHAR_H_

#include <stdio.h>

struct HuffChar { // Huffman字符类
    char ch;      // 字符
    int weight;   // 权重（频率）
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {} // 构造函数
    // 比较器
    bool operator< (const HuffChar& hc) { return weight > hc.weight; }
    bool operator> (const HuffChar& hc) { return weight < hc.weight; }
    bool operator== (const HuffChar& hc) { return weight == hc.weight; }
};

#endif

// HuffTree.hpp - Huffman树类的实现
#ifndef _HUFFTREE_H_
#define _HUFFTREE_H_

#include "utilities/bintree/BinTree.hpp"
#include "HuffChar.hpp"
#include "utilities/vector/Vector.hpp"

#define N_CHAR (0x80 - 0x20) // 字符集规模：仅以可打印字符为例

class HuffTree : public BinTree<HuffChar> {
public:
    HuffTree() {}
    // 构造Huffman树
    HuffTree(int* freq, int n) { // 根据频率数组freq[]构造Huffman树
        Vector<HuffTree*> forest; // 初始森林
        
        // 为每个字符创建一棵树
        for (int i = 0; i < n; i++) {
            if (freq[i]) { // 只处理频率不为0的字符
                HuffTree* tree = new HuffTree();
                tree->insertAsRoot(HuffChar(0x20 + i, freq[i]));
                forest.push_Back(tree);
            }
        }
        
        // 主体算法：反复合并频率最小的两棵树
        while (forest.size() > 1) {
            // 找到两个权重最小的树
            BinTree<HuffChar> *T1 = minTree(forest);
            BinTree<HuffChar> *T2 = minTree(forest);
            
            // 构造新树
            HuffTree* S = new HuffTree();
            S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
            S->attachAsLC(S->root(), T1);
            S->attachAsRC(S->root(), T2);
            
            // 将新树加入森林
            forest.push_Back(S);
        }
        
        // 将最后剩下的树作为当前树
        if (!forest.empty()) {
            _root = forest[0]->_root;
            _size = forest[0]->_size;
            forest[0]->_root = NULL;
            delete forest[0];
        }
    }

    // 生成Huffman编码
    void generateCodes(HuffCode* codes, int length) {
        HuffCode code;
        generateCodes(root(), codes, code, length);
    }

protected:
    // 在forest中找到权重最小的树
    static HuffTree* minTree(Vector<HuffTree*>& forest) {
        if (forest.empty()) return NULL;
        
        int minIndex = 0;
        for (int i = 1; i < forest.size(); i++) {
            if (forest[i]->root()->data.weight < forest[minIndex]->root()->data.weight) {
                minIndex = i;
            }
        }
        
        HuffTree* T = forest[minIndex];
        forest.remove(minIndex);
        return T;
    }
    
    // 递归生成Huffman编码
    static void generateCodes(BinNodePosi(HuffChar) v, HuffCode* codes, HuffCode& prefix, int length) {
        if (!v) return;
        
        if (!v->lChild && !v->rChild) { // 若是叶节点
            codes[v->data.ch - 0x20] = prefix; // 将当前前缀码作为对应字符的编码
            return;
        }
        
        // 左子树：续接0
        prefix.set(length, 0);
        generateCodes(v->lChild, codes, prefix, length + 1);
        
        // 右子树：续接1
        prefix.set(length, 1);
        generateCodes(v->rChild, codes, prefix, length + 1);
        
        // 回溯前复原
        prefix.clear(length);
    }
};

#endif

