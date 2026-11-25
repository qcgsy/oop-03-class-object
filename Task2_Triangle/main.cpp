// ============================================================================
//  第 3 章  类和对象 —— 任务二：三角形类 Triangle
//  文件：main.cpp
//  作用：测试 Triangle 类的全部功能（构造、Init、写接口校验、周长、
//        海伦公式求面积、类型判断以及选做的等腰/等边判断）
// ============================================================================
#include "Triangle.h"

#include <iostream>

// 输出一个三角形对象的信息，并显示类型编码
static void showTriangle(const char* tag, const Triangle& t)
{
    std::cout << tag << std::endl;
    t.display();
    std::cout << "TypeCode: " << t.typeTriangle() << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

int main()
{
    std::cout << "===== 第 3 章  任务二：三角形类 Triangle =====" << std::endl;

    // ------------------------------------------------------------------
    //  1. 读入三条边长并输出结果（对应题目的输入输出示例）
    // ------------------------------------------------------------------
    double a = 0.0, b = 0.0, c = 0.0;
    std::cout << "请输入三条边长：";
    if (!(std::cin >> a >> b >> c))
    {
        std::cout << "输入格式错误，程序结束。" << std::endl;
        return 1;
    }

    Triangle tri(a, b, c);
    tri.display();

    // ------------------------------------------------------------------
    //  2. 附加测试
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 附加测试 ----------" << std::endl;

    // [1] 写接口校验：负数边长不予写入
    Triangle t1(3, 4, 5);
    std::cout << "[1] setSideA(-2) 校验：" << std::endl;
    t1.setSideA(-2);
    std::cout << "    边长仍为: " << t1.getSideA() << ' ' << t1.getSideB()
              << ' ' << t1.getSideC() << std::endl;

    // [2] 用 setSide 构造一个 5-12-13 的直角三角形
    Triangle t2;
    t2.setSideA(5);
    t2.setSideB(12);
    t2.setSideC(13);
    showTriangle("[2] 5-12-13（三种 setSide 赋值）：", t2);

    // [3] 直角三角形（3-4-5）
    showTriangle("[3] 3-4-5：", Triangle(3, 4, 5));

    // [4] 5-5-6：等腰三角形（三个角均为锐角），按优先级“等腰优先于锐角”返回 6
    showTriangle("[4] 5-5-6：", Triangle(5, 5, 6));

    // [5] 钝角三角形（2-3-4）
    showTriangle("[5] 2-3-4：", Triangle(2, 3, 4));

    // [6] 等边三角形（6-6-6）
    showTriangle("[6] 6-6-6：", Triangle(6, 6, 6));

    // [7] 等腰直角三角形（1-1-sqrt(2)）
    showTriangle("[7] 1-1-1.41421356（等腰直角）：", Triangle(1, 1, 1.41421356));

    // [8] 不构成三角形：1-2-5（两边之和小于第三边）
    showTriangle("[8] 1-2-5：", Triangle(1, 2, 5));

    // [9] 不构成三角形：1-1-2（退化，两边之和等于第三边）
    showTriangle("[9] 1-1-2：", Triangle(1, 1, 2));

    // [10] 不构成三角形时的面积函数：提示错误并返回 0
    // 注意：area() 内部会先输出错误提示，因此先打印标题行再调用
    std::cout << "[10] 调用 1-2-5 的 area()：" << std::endl;
    Triangle t10(1, 2, 5);
    double area10 = t10.area();
    std::cout << "     area() 返回 " << area10 << std::endl;

    // [11] Init 手工初始化：把默认对象改成 2.5-3.5-4.5
    Triangle t11;
    t11.Init(2.5, 3.5, 4.5);
    showTriangle("[11] Init(2.5, 3.5, 4.5)：", t11);

    std::cout << "\n程序正常结束。" << std::endl;
    return 0;
}
