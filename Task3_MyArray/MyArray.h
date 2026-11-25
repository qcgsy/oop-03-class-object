// ============================================================================
//  第 3 章  类和对象 —— 任务三：动态整型数组类 MyArray
//  文件：MyArray.h
//  作用：MyArray 类的声明（类的接口与实现分离，便于多文件工程组织）
//  说明：使用 #ifndef / #define / #endif 防止头文件被重复包含
// ============================================================================
#ifndef MYARRAY_H
#define MYARRAY_H

class MyArray
{
private:
    int* p;     // 指向动态数组首地址（堆内存）
    int  N;     // 数组元素个数

    // 求两个数组的较短长度；长度不同时输出提示，符合“按较短长度计算”的要求
    int shorterSize(const MyArray& other) const;

public:
    // ---------- 构造函数族 ----------
    MyArray();                                        // 默认构造：空数组
    MyArray(int n, int value = 0);                    // n 个元素，全部初始化为 value
    MyArray(const MyArray& other);                    // 拷贝构造：必须深拷贝
    ~MyArray();                                       // 析构函数：释放堆内存

    // 赋值运算符重载（“三法则”的补充）：默认赋值只做浅拷贝，
    // 会让两个对象共用同一块内存，因此这里同样实现深拷贝。
    MyArray& operator=(const MyArray& other);

    // ---------- 基本操作 ----------
    int  size() const;                  // 元素个数
    int  get(int index) const;          // 读元素（带下标越界检查）
    void set(int index, int value);     // 写元素（带下标越界检查）
    void display() const;               // 输出 {a, b, c}，空数组输出 {}

    // ---------- 数组合并：本对象元素在前，other 元素在后 ----------
    MyArray merge(const MyArray& other) const;

    // ---------- 按元素四则运算，返回新对象 ----------
    MyArray add(const MyArray& other) const;
    MyArray subtract(const MyArray& other) const;
    MyArray multiply(const MyArray& other) const;
    MyArray divide(const MyArray& other) const;      // 除数为 0 的位置结果记 0
};

#endif // MYARRAY_H
