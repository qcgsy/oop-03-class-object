// ============================================================================
//  第 3 章  类和对象 —— 任务四：空间点类 Point（友元函数）
//  文件：main.cpp
//  作用：测试 Point 类的全部功能
//        ① 三种距离（欧氏、曼哈顿、切比雪夫） ② 中点
//        ③ 成员函数 distanceTo 与友元函数的对比 ④ 重载友元函数
// ============================================================================
#include "Point.h"

#include <iostream>

int main()
{
    std::cout << "===== 第 3 章  任务四：空间点类 Point =====" << std::endl;

    // ------------------------------------------------------------------
    //  1. 读入两个点的坐标并输出结果（对应题目的输入输出示例）
    // ------------------------------------------------------------------
    double x1 = 0.0, y1 = 0.0, z1 = 0.0;
    double x2 = 0.0, y2 = 0.0, z2 = 0.0;

    std::cout << "请输入点 A 的坐标（x y z）：";
    if (!(std::cin >> x1 >> y1 >> z1))
    {
        std::cout << "输入格式错误，程序结束。" << std::endl;
        return 1;
    }
    std::cout << "请输入点 B 的坐标（x y z）：";
    if (!(std::cin >> x2 >> y2 >> z2))
    {
        std::cout << "输入格式错误，程序结束。" << std::endl;
        return 1;
    }

    Point A(x1, y1, z1);
    Point B(x2, y2, z2);

    std::cout << "A = "; A.display(); std::cout << std::endl;
    std::cout << "B = "; B.display(); std::cout << std::endl;

    std::cout << "Euclidean distance: " << euclideanDistance(A, B) << std::endl;
    std::cout << "Manhattan distance: " << manhattanDistance(A, B) << std::endl;
    std::cout << "Chebyshev distance: " << chebyshevDistance(A, B) << std::endl;

    std::cout << "Midpoint: ";
    midpoint(A, B).display();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    //  2. 附加测试
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 附加测试 ----------" << std::endl;

    // [1] 成员函数与友元函数实现同一件事的对比
    std::cout << "[1] 成员函数 distanceTo 与友元函数的对比：" << std::endl;
    std::cout << "    A.distanceTo(B)          = " << A.distanceTo(B) << std::endl;
    std::cout << "    euclideanDistance(A, B)  = " << euclideanDistance(A, B)
              << "   （两者结果相同）" << std::endl;

    // [2] 重载的友元函数：单参数版本求点到原点的欧氏距离
    std::cout << "[2] 重载友元函数 euclideanDistance(p) 求点到原点的欧氏距离：" << std::endl;
    std::cout << "    euclideanDistance(A)     = " << euclideanDistance(A) << std::endl;
    std::cout << "    euclideanDistance(B)     = " << euclideanDistance(B) << std::endl;

    // [3] 两点重合时的中点与距离
    Point C(2.5, -3.5, 4.0);
    Point D(2.5, -3.5, 4.0);
    std::cout << "[3] 两个重合的点：" << std::endl;
    std::cout << "    C = "; C.display(); std::cout << std::endl;
    std::cout << "    D = "; D.display(); std::cout << std::endl;
    std::cout << "    euclideanDistance(C, D) = " << euclideanDistance(C, D) << std::endl;
    std::cout << "    midpoint(C, D)          = ";
    midpoint(C, D).display();
    std::cout << std::endl;

    // [4] 含负坐标的点：验证绝对值处理
    Point E(-3.0, 4.0, -12.0);
    Point F(1.0, 1.0, 1.0);
    std::cout << "[4] 含负坐标的点：" << std::endl;
    std::cout << "    E = "; E.display(); std::cout << std::endl;
    std::cout << "    F = "; F.display(); std::cout << std::endl;
    std::cout << "    euclideanDistance(E, F) = " << euclideanDistance(E, F) << std::endl;
    std::cout << "    manhattanDistance(E, F) = " << manhattanDistance(E, F) << std::endl;
    std::cout << "    chebyshevDistance(E, F) = " << chebyshevDistance(E, F) << std::endl;

    // [5] 默认构造与 Init、set 接口
    Point G;                        // 默认构造：原点
    std::cout << "[5] 默认构造 G = "; G.display(); std::cout << std::endl;
    G.Init(1.0, 2.0, 3.0);
    std::cout << "    Init 之后 G   = "; G.display(); std::cout << std::endl;
    G.setX(10.0);
    G.setY(20.0);
    G.setZ(30.0);
    std::cout << "    set 之后  G   = "; G.display(); std::cout << std::endl;

    // 恢复 std::cout 的定点两位小数不影响的整数输出
    std::cout << "\n程序正常结束。" << std::endl;
    return 0;
}
