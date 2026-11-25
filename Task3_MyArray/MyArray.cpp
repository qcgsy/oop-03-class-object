// ============================================================================
//  第 3 章  类和对象 —— 任务三：动态整型数组类 MyArray
//  文件：MyArray.cpp
//  作用：MyArray 类所有成员函数的实现
// ============================================================================
#include "MyArray.h"

#include <iostream>

// ----------------------------------------------------------------------------
//  默认构造函数：空数组，p 指向空，N 为 0
// ----------------------------------------------------------------------------
MyArray::MyArray() : p(nullptr), N(0)
{
}

// ----------------------------------------------------------------------------
//  带默认参数的构造函数：申请 n 个 int 的堆空间，全部初始化为 value
// ----------------------------------------------------------------------------
MyArray::MyArray(int n, int value) : p(nullptr), N(0)
{
    if (n <= 0)
    {
        if (n < 0)
        {
            std::cout << "Error: invalid size " << n
                      << ", an empty array is created" << std::endl;
        }
        return;                     // n == 0 时保持空数组状态
    }

    p = new int[n];                 // 动态申请 n 个元素的空间
    N = n;
    for (int i = 0; i < N; ++i)
    {
        p[i] = value;
    }
}

// ----------------------------------------------------------------------------
//  拷贝构造函数：深拷贝
//  不复制 other.p 指针的值，而是按 other.N 重新申请一块同样大小的内存，
//  再逐元素复制内容，这样两个对象各有一份独立的数据，互不影响。
//  若只写 p = other.p（浅拷贝），析构时同一块内存会被 delete[] 两次，
//  导致 double free 而崩溃。
// ----------------------------------------------------------------------------
MyArray::MyArray(const MyArray& other) : p(nullptr), N(0)
{
    if (other.N > 0)
    {
        p = new int[other.N];
        N = other.N;
        for (int i = 0; i < N; ++i)
        {
            p[i] = other.p[i];
        }
    }
}

// ----------------------------------------------------------------------------
//  析构函数：释放动态数组空间，并把指针与长度复位
// ----------------------------------------------------------------------------
MyArray::~MyArray()
{
    delete[] p;
    p = nullptr;
    N = 0;
}

// ----------------------------------------------------------------------------
//  赋值运算符重载：深拷贝
//  注意三点：① 自赋值检查；② 先申请新内存，成功后再释放旧内存；
//            ③ 返回 *this 以支持连续赋值 a = b = c。
// ----------------------------------------------------------------------------
MyArray& MyArray::operator=(const MyArray& other)
{
    if (this == &other)             // 自赋值：a = a 时直接返回
    {
        return *this;
    }

    int* newP = nullptr;
    if (other.N > 0)
    {
        newP = new int[other.N];
        for (int i = 0; i < other.N; ++i)
        {
            newP[i] = other.p[i];
        }
    }

    delete[] p;                     // 释放原有的内存
    p = newP;
    N = other.N;
    return *this;
}

// ----------------------------------------------------------------------------
//  元素个数
// ----------------------------------------------------------------------------
int MyArray::size() const
{
    return N;
}

// ----------------------------------------------------------------------------
//  读元素：下标越界时给出提示并忽略本次操作（返回 0）
// ----------------------------------------------------------------------------
int MyArray::get(int index) const
{
    if (index < 0 || index >= N)
    {
        std::cout << "Error: index " << index << " out of range [0, "
                  << N - 1 << "], get ignored" << std::endl;
        return 0;
    }
    return p[index];
}

// ----------------------------------------------------------------------------
//  写元素：下标越界时给出提示并忽略本次操作
// ----------------------------------------------------------------------------
void MyArray::set(int index, int value)
{
    if (index < 0 || index >= N)
    {
        std::cout << "Error: index " << index << " out of range [0, "
                  << N - 1 << "], set ignored" << std::endl;
        return;
    }
    p[index] = value;
}

// ----------------------------------------------------------------------------
//  输出：按 {a, b, c} 格式输出，空数组输出 {}
// ----------------------------------------------------------------------------
void MyArray::display() const
{
    std::cout << '{';
    for (int i = 0; i < N; ++i)
    {
        std::cout << p[i];
        if (i < N - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << '}';
}

// ----------------------------------------------------------------------------
//  求较短长度；两个数组长度不同时输出提示信息
// ----------------------------------------------------------------------------
int MyArray::shorterSize(const MyArray& other) const
{
    if (N != other.N)
    {
        std::cout << "Warning: different sizes (" << N << " vs " << other.N
                  << "), use the shorter one" << std::endl;
    }
    return (N < other.N) ? N : other.N;
}

// ----------------------------------------------------------------------------
//  合并：本对象元素在前，other 元素在后，结果放在新对象中返回
// ----------------------------------------------------------------------------
MyArray MyArray::merge(const MyArray& other) const
{
    MyArray result(N + other.N, 0);
    int k = 0;
    for (int i = 0; i < N; ++i)
    {
        result.p[k++] = p[i];
    }
    for (int i = 0; i < other.N; ++i)
    {
        result.p[k++] = other.p[i];
    }
    return result;
}

// ----------------------------------------------------------------------------
//  加法：按元素对应相加，长度不一致时按较短长度计算
// ----------------------------------------------------------------------------
MyArray MyArray::add(const MyArray& other) const
{
    int n = shorterSize(other);
    MyArray result(n, 0);
    for (int i = 0; i < n; ++i)
    {
        result.p[i] = p[i] + other.p[i];
    }
    return result;
}

// ----------------------------------------------------------------------------
//  减法
// ----------------------------------------------------------------------------
MyArray MyArray::subtract(const MyArray& other) const
{
    int n = shorterSize(other);
    MyArray result(n, 0);
    for (int i = 0; i < n; ++i)
    {
        result.p[i] = p[i] - other.p[i];
    }
    return result;
}

// ----------------------------------------------------------------------------
//  乘法
// ----------------------------------------------------------------------------
MyArray MyArray::multiply(const MyArray& other) const
{
    int n = shorterSize(other);
    MyArray result(n, 0);
    for (int i = 0; i < n; ++i)
    {
        result.p[i] = p[i] * other.p[i];
    }
    return result;
}

// ----------------------------------------------------------------------------
//  除法：整数除法；除数为 0 的位置结果记为 0，并给出提示
// ----------------------------------------------------------------------------
MyArray MyArray::divide(const MyArray& other) const
{
    int n = shorterSize(other);
    MyArray result(n, 0);
    for (int i = 0; i < n; ++i)
    {
        if (other.p[i] == 0)
        {
            std::cout << "Warning: division by zero at index " << i
                      << ", result set to 0" << std::endl;
            result.p[i] = 0;
        }
        else
        {
            result.p[i] = p[i] / other.p[i];
        }
    }
    return result;
}
