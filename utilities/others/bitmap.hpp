// Bitmap.hpp - 位图类实现
#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdlib.h>
#include <string.h>
#include <iostream>

class Bitmap {
private:
    unsigned char* M; // 比特图所存放的空间M
    int N;           // 空间M的容量为N*sizeof(char)*8比特

protected:
    void init(int n) {
        M = new unsigned char[N = (n + 7) / 8]; // 申请内存空间
        memset(M, 0, N); // 初始化
    }

public:
    Bitmap(int n = 8) { init(n); } // 按指定容量创建位图

    Bitmap(const Bitmap& b) { // 拷贝构造函数
        init(b.N * 8);
        memcpy(M, b.M, N);
    }

    ~Bitmap() { delete[] M; M = NULL; } // 析构函数

    // 扩展或缩小位图
    void expand(int k) {
        if (k <= N * 8) return; // 如果容量足够，无需扩展
        
        unsigned char* oldM = M;
        int oldN = N;
        init(k);
        memcpy(M, oldM, oldN); // 复制原数据
        delete[] oldM; // 释放原空间
    }

    // 将第k位置设置为指定值v（v为0或1）
    void set(int k, bool v) {
        expand(k + 1); // 若必要，则扩容
        if (v) // 置1
            M[k >> 3] |= (0x80 >> (k & 0x07));
        else   // 置0
            M[k >> 3] &= ~(0x80 >> (k & 0x07));
    }

    // 获取第k位的值
    bool test(int k) {
        expand(k + 1); // 若必要，则扩容
        return M[k >> 3] & (0x80 >> (k & 0x07));
    }

    // 将第k位置取反
    void flip(int k) {
        expand(k + 1); // 若必要，则扩容
        M[k >> 3] ^= (0x80 >> (k & 0x07));
    }

    // 清除第k位（置0）
    void clear(int k) {
        expand(k + 1); // 若必要，则扩容
        M[k >> 3] &= ~(0x80 >> (k & 0x07));
    }

    // 获取位图大小（比特数）
    int size() const { return N * 8; }

    // 统计1的个数
    int count() const {
        int ones = 0;
        for (int i = 0; i < N; i++) {
            unsigned char byte = M[i];
            while (byte) {
                ones += (byte & 1);
                byte >>= 1;
            }
        }
        return ones;
    }

    // 打印位图内容（用于调试）
    void print(std::ostream& out) {
        for (int i = 0; i < N * 8; i++) {
            out << test(i);
            if ((i + 1) % 8 == 0) out << " ";
        }
        out << std::endl;
    }

    // 运算符重载
    bool operator[] (int k) { return test(k); }
    
    Bitmap& operator=(const Bitmap& b) {
        if (this != &b) {
            delete[] M;
            init(b.N * 8);
            memcpy(M, b.M, N);
        }
        return *this;
    }

    // 位图的与操作
    Bitmap& operator&=(const Bitmap& b) {
        for (int i = 0; i < N; i++)
            M[i] &= b.M[i];
        return *this;
    }

    // 位图的或操作
    Bitmap& operator|=(const Bitmap& b) {
        for (int i = 0; i < N; i++)
            M[i] |= b.M[i];
        return *this;
    }

    // 位图比较操作
    bool operator==(const Bitmap& b) const {
        return (N == b.N) && (memcmp(M, b.M, N) == 0);
    }

};

// // 使用示例
// void bitmapExample() {
//     Bitmap bm(16); // 创建一个16位的位图
    
//     // 设置一些位
//     bm.set(0, true);   // 设置第0位为1
//     bm.set(3, true);   // 设置第3位为1
//     bm.set(8, true);   // 设置第8位为1
    
//     // 测试位的值
//     std::cout << "Bit 0 is: " << bm.test(0) << std::endl;
//     std::cout << "Bit 1 is: " << bm.test(1) << std::endl;
    
//     // 打印整个位图
//     bm.print(std::cout);
    
//     // 计算1的个数
//     std::cout << "Number of ones: " << bm.count() << std::endl;
    
//     // 清除一个位
//     bm.clear(3);
    
//     // 再次打印
//     bm.print(std::cout);
// }

#endif