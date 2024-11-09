#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include "utilities/others/bitmap.hpp" 

using namespace std;

// HuffCode类 - 使用Bitmap存储编码
class HuffCode : public Bitmap {
public:
    HuffCode() : Bitmap(8) {} // 默认8位
    HuffCode(int n) : Bitmap(n) {} // 指定位数
};

// HuffChar类 - 存储字符及其频率
struct HuffChar {
    char ch;        // 字符
    int weight;     // 频率/权重
    HuffCode code;  // 编码
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {}
};

// HuffNode类 - Huffman树节点
template <typename T>
struct BinNode {
    T data;
    BinNode<T>* left;
    BinNode<T>* right;
    BinNode<T>* parent;
    
    BinNode() : left(nullptr), right(nullptr), parent(nullptr) {}
    BinNode(T e, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr, BinNode<T>* p = nullptr)
        : data(e), left(l), right(r), parent(p) {}
};

// HuffTree类 - Huffman树
class HuffTree {
private:
    BinNode<HuffChar>* root;    // 树根
    vector<BinNode<HuffChar>*> forest;  // 存储所有节点
    
    // 构建Huffman树
    void buildHuffTree(int* freq, int n) {
        // 初始化优先队列
        struct CompareNode {
            bool operator()(BinNode<HuffChar>* a, BinNode<HuffChar>* b) {
                return a->data.weight > b->data.weight;
            }
        };
        priority_queue<BinNode<HuffChar>*, vector<BinNode<HuffChar>*>, CompareNode> pq;
        
        // 创建叶子节点
        for (int i = 0; i < n; i++) {
            if (freq[i] > 0) {
                BinNode<HuffChar>* node = new BinNode<HuffChar>(HuffChar(i + 0x20, freq[i]));
                forest.push_back(node);
                pq.push(node);
            }
        }
        
        // 构建树
        while (pq.size() > 1) {
            BinNode<HuffChar>* left = pq.top(); pq.pop();
            BinNode<HuffChar>* right = pq.top(); pq.pop();
            
            // 创建父节点
            BinNode<HuffChar>* parent = new BinNode<HuffChar>(
                HuffChar('^', left->data.weight + right->data.weight),
                left, right
            );
            left->parent = parent;
            right->parent = parent;
            
            forest.push_back(parent);
            pq.push(parent);
        }
        
        root = pq.empty() ? nullptr : pq.top();
    }
    
    // 生成编码
    void generateCodes(BinNode<HuffChar>* node, HuffCode& prefix, int length, HuffCode codeTable[], int n) {
        if (!node) return;
        
        // 叶子节点
        if (!node->left && !node->right) {
            codeTable[node->data.ch - 0x20] = prefix;
            codeTable[node->data.ch - 0x20].expand(length);
            return;
        }
        
        // 左子树：添加0
        if (node->left) {
            prefix.set(length, 0);
            generateCodes(node->left, prefix, length + 1, codeTable, n);
        }
        
        // 右子树：添加1
        if (node->right) {
            prefix.set(length, 1);
            generateCodes(node->right, prefix, length + 1, codeTable, n);
        }
    }

public:
    HuffTree(int* freq, int n) {
        buildHuffTree(freq, n);
    }
    
    ~HuffTree() {
        for (auto node : forest) {
            delete node;
        }
        forest.clear();
    }
    
    void generateCodes(HuffCode codeTable[], int n) {
        if (!root) return;
        HuffCode prefix(n * 8); // 足够长的临时编码
        generateCodes(root, prefix, 0, codeTable, n);
    }
    
    // 打印编码表
    void printCodes(HuffCode codeTable[], int n) {
        std::cout << "Huffman编码表：\n";
        for (int i = 0; i < n; i++) {
            if (forest.size() > 0) {
                bool found = false;
                for (auto node : forest) {
                    if (node->data.ch == char(i + 0x20)) {
                        found = true;
                        std::cout << char(i + 0x20) << ": ";
                        // 只打印到实际编码长度
                        for (int j = 0; j < n * 8; j++) {
                            if (j > 0 && !codeTable[i].test(j)) {
                                bool allZeros = true;
                                for (int k = j + 1; k < n * 8; k++) {
                                    if (codeTable[i].test(k)) {
                                        allZeros = false;
                                        break;
                                    }
                                }
                                if (allZeros) break;
                            }
                            std::cout << (codeTable[i].test(j) ? "1" : "0");
                        }
                        std::cout << "\n";
                        break;
                    }
                }
            }
        }
    }
};

// 使用示例
void huffmanExample() {
    const int N_CHAR = 95; // 打印字符的数量
    
    // 统计字符频率
    string text = "aabaaab";

    std::ifstream file("word.txt");
    if (!file.is_open()) {
        std::cerr << "无法打开文件 input.txt" << std::endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        text += line + "\n"; // 逐行读取并合并到text中
    }
    file.close();

    cout << "输入文本：" << text << endl;

    int freq[N_CHAR] = {0};
    for (char c : text) {
        if (c >= 0x20) {
            freq[c - 0x20]++;
        }
    }
    
    // 构建Huffman树并生成编码
    HuffTree* tree = new HuffTree(freq, N_CHAR);
    HuffCode codeTable[N_CHAR];
    tree->generateCodes(codeTable, N_CHAR);
    
    // 打印编码表
    tree->printCodes(codeTable, N_CHAR);
    
    // 编码示例文本
    std::cout << "\n编码结果: ";
    HuffCode encodedText(text.length() * 8);
    int encodedLen = 0;
    
    for (char c : text) {
        if (c >= 0x20) {
            HuffCode& code = codeTable[c - 0x20];
            for (int j = 0; j < N_CHAR * 8; j++) {
                if (j > 0 && !code.test(j)) {
                    bool allZeros = true;
                    for (int k = j + 1; k < N_CHAR * 8; k++) {
                        if (code.test(k)) {
                            allZeros = false;
                            break;
                        }
                    }
                    if (allZeros) break;
                }
                encodedText.set(encodedLen++, code.test(j));
            }
        }
    }
    
    // 按字节打印编码结果
    for (int i = 0; i < encodedLen; i += 8) {
        for (int j = 0; j < 8 && i + j < encodedLen; j++) {
            std::cout << (encodedText.test(i + j) ? "1" : "0");
        }
        std::cout << " ";
    }
    std::cout << std::endl;
    
    delete tree;
}

int main() {
    huffmanExample();

    system("pause");
    return 0;
}