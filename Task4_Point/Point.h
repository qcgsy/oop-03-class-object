// ============================================================================
//  第 3 章  类和对象 —— 任务四：空间点类 Point（友元函数）
//  文件：Point.h
//  作用：Point 类的声明，并在类内用 friend 声明四个友元函数
//  说明：使用 #ifndef / #define / #endif 防止头文件被重复包含
// ============================================================================
#ifndef POINT_H
#define POINT_H

class Point
{
private:
    // ---------- 私有数据成员：三个坐标分量 ----------
    double x;
    double y;
    double z;

public:
    // ---------- 构造函数：带默认参数 ----------
    Point(double x = 0, double y = 0, double z = 0);

    // ---------- 手工初始化 ----------
    void Init(double x, double y, double z);

    // ---------- 读写接口 ----------
    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    // ---------- 输出函数：按 (x, y, z) 格式输出，各分量保留两位小数 ----------
    void display() const;

    // ---------- 成员函数版本的欧氏距离：借助 this 指针访问当前对象，
    //             另一个点只能作为参数传入 ----------
    double distanceTo(const Point& other) const;

    // ------------------------------------------------------------------
    //  友元函数声明（在类内声明，在类外定义）
    //  友元函数不是类的成员函数，但它可以访问 Point 对象的私有成员，
    //  因此可以把“两个点”放在完全对等的位置上进行计算。
    // ------------------------------------------------------------------
    friend double euclideanDistance(const Point& a, const Point& b);
    friend double manhattanDistance(const Point& a, const Point& b);
    friend double chebyshevDistance(const Point& a, const Point& b);
    friend Point  midpoint(const Point& a, const Point& b);

    // ---------- 提高要求（选做）：重载友元函数，计算点到原点的欧氏距离 ----------
    friend double euclideanDistance(const Point& p);
};

#endif // POINT_H
