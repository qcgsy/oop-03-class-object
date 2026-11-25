// ============================================================================
//  第 3 章  类和对象 —— 任务三：动态整型数组类 MyArray
//  文件：main.cpp
//  作用：测试 MyArray 类的全部功能
//        ① 合并 ② 四则运算 ③ 长度不一致的处理 ④ 下标越界 ⑤ 除数为 0
//        ⑥ 深拷贝验证 ⑦ 空数组与默认构造
// ============================================================================
#include "MyArray.h"

#include <iostream>

// 用一个整型数组给 MyArray 对象赋值，避免重复书写循环
static void fill(MyArray& arr, const int* data, int n)
{
    for (int i = 0; i < n; ++i)
    {
        arr.set(i, data[i]);
    }
}

int main()
{
    std::cout << "===== 第 3 章  任务三：动态整型数组类 MyArray =====" << std::endl;

    // ------------------------------------------------------------------
    //  1. 合并与四则运算（两个数组长度相同）
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 1. 合并与四则运算 ----------" << std::endl;

    const int DATA_A[3] = { 6, 8, 9 };
    const int DATA_B[3] = { 3, 2, 4 };

    MyArray A(3);           // 带默认参数的构造函数：3 个元素，初值 0
    MyArray B(3);
    fill(A, DATA_A, 3);
    fill(B, DATA_B, 3);

    // 每个运算函数都返回新的 MyArray 对象（按值返回，会调用拷贝构造函数）
    MyArray merged   = A.merge(B);
    MyArray sumAB    = A.add(B);
    MyArray diffAB   = A.subtract(B);
    MyArray prodAB   = A.multiply(B);
    MyArray quotAB   = A.divide(B);

    std::cout << "A = ";         A.display();      std::cout << std::endl;
    std::cout << "B = ";         B.display();      std::cout << std::endl;
    std::cout << "A merge B = "; merged.display(); std::cout << std::endl;
    std::cout << "A + B = ";     sumAB.display();  std::cout << std::endl;
    std::cout << "A - B = ";     diffAB.display(); std::cout << std::endl;
    std::cout << "A * B = ";     prodAB.display(); std::cout << std::endl;
    std::cout << "A / B = ";     quotAB.display(); std::cout << std::endl;

    // ------------------------------------------------------------------
    //  2. 两个数组长度不一致：按较短长度计算，多出的元素忽略
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 2. 长度不一致的情况 ----------" << std::endl;

    const int DATA_C[3] = { 1, 2, 3 };
    const int DATA_D[2] = { 4, 5 };

    MyArray C(3);
    MyArray D(2);
    fill(C, DATA_C, 3);
    fill(D, DATA_D, 2);

    std::cout << "C = "; C.display(); std::cout << std::endl;
    std::cout << "D = "; D.display(); std::cout << std::endl;

    // 先做运算（这一步会输出长度不一致的提示），再输出结果
    MyArray sumCD = C.add(D);
    std::cout << "C + D = "; sumCD.display(); std::cout << std::endl;

    // ------------------------------------------------------------------
    //  3. 深拷贝验证：拷贝后修改副本，原对象不受影响
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 3. 深拷贝验证 ----------" << std::endl;

    MyArray CopyA = A;      // 拷贝构造函数（深拷贝）
    CopyA.set(0, 100);      // 修改副本

    std::cout << "执行 MyArray CopyA = A; 再 CopyA.set(0, 100);" << std::endl;
    std::cout << "A     = "; A.display();     std::cout << std::endl;
    std::cout << "CopyA = "; CopyA.display(); std::cout << std::endl;
    std::cout << "结论：修改 CopyA 后 A 保持不变，说明拷贝构造函数实现了深拷贝。"
              << std::endl;

    // 赋值运算符同样做了深拷贝
    MyArray AssignA(2, 7);
    AssignA = A;            // 调用 operator=
    AssignA.set(1, 55);
    std::cout << "执行 AssignA = A; 再 AssignA.set(1, 55);" << std::endl;
    std::cout << "A       = "; A.display();       std::cout << std::endl;
    std::cout << "AssignA = "; AssignA.display(); std::cout << std::endl;

    // ------------------------------------------------------------------
    //  4. 下标越界检查
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 4. 下标越界检查 ----------" << std::endl;

    std::cout << "A.size() = " << A.size() << std::endl;
    std::cout << "A.get(2) = " << A.get(2) << std::endl;

    std::cout << "读取越界下标 A.get(5)：" << std::endl;
    int bad = A.get(5);
    std::cout << "  函数返回 " << bad << "，本次操作被忽略。" << std::endl;

    std::cout << "写入越界下标 A.set(-1, 9)：" << std::endl;
    A.set(-1, 9);
    std::cout << "  A 仍为 "; A.display(); std::cout << std::endl;

    // ------------------------------------------------------------------
    //  5. 除法：某个除数元素为 0
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 5. 除数为 0 的处理 ----------" << std::endl;

    MyArray X(3);
    MyArray Y(3);
    const int DATA_X[3] = { 10, 20, 30 };
    const int DATA_Y[3] = { 2, 0, 5 };
    fill(X, DATA_X, 3);
    fill(Y, DATA_Y, 3);

    std::cout << "X = "; X.display(); std::cout << std::endl;
    std::cout << "Y = "; Y.display(); std::cout << std::endl;

    // 先做运算（这一步会输出除数为 0 的提示），再输出结果
    MyArray quotXY = X.divide(Y);
    std::cout << "X / Y = "; quotXY.display(); std::cout << std::endl;

    // ------------------------------------------------------------------
    //  6. 空数组与非法长度
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 6. 空数组与非法长度 ----------" << std::endl;

    MyArray Empty;                          // 默认构造：空数组
    std::cout << "MyArray Empty;          ->  Empty.display() = ";
    Empty.display();
    std::cout << "，size = " << Empty.size() << std::endl;

    std::cout << "MyArray Zero(0);        ->  Zero.display() = ";
    MyArray Zero(0);
    Zero.display();
    std::cout << "，size = " << Zero.size() << std::endl;

    std::cout << "MyArray Neg(-3);（非法长度，先给出提示再构造空数组）" << std::endl;
    MyArray Neg(-3);
    std::cout << "                            Neg.display() = ";
    Neg.display();
    std::cout << "，size = " << Neg.size() << std::endl;

    std::cout << std::endl
              << "说明：所有对象都在离开作用域时调用析构函数释放堆内存；"
              << std::endl
              << "      由于实现了深拷贝，本程序退出时不会出现 double free 崩溃。"
              << std::endl;
    std::cout << "\n程序正常结束。" << std::endl;
    return 0;
}
