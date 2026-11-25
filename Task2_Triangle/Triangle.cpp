// ============================================================================
//  第 3 章  类和对象 —— 任务二：三角形类 Triangle
//  文件：Triangle.cpp
//  作用：Triangle 类所有成员函数的实现
// ============================================================================
#include "Triangle.h"

#include <iostream>
#include <iomanip>
#include <cmath>

namespace
{
    // 相对误差精度：用于浮点数比较，避免直接用 == 判断
    const double EPS = 1e-9;
}

// ----------------------------------------------------------------------------
//  浮点数比较：|x - y| 相对于两者中较大的量级足够小，即认为相等
// ----------------------------------------------------------------------------
bool Triangle::nearlyEqual(double x, double y)
{
    double scale = std::fabs(x) > std::fabs(y) ? std::fabs(x) : std::fabs(y);
    if (scale < 1.0)
    {
        scale = 1.0;
    }
    return std::fabs(x - y) <= EPS * scale;
}

// ----------------------------------------------------------------------------
//  构造函数：直接使用初始化列表
// ----------------------------------------------------------------------------
Triangle::Triangle(double a, double b, double c) : a(a), b(b), c(c)
{
}

// ----------------------------------------------------------------------------
//  手工初始化
// ----------------------------------------------------------------------------
void Triangle::Init(double a, double b, double c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

// ----------------------------------------------------------------------------
//  构成判断：三边都为正数，且任意两边之和大于第三边
// ----------------------------------------------------------------------------
bool Triangle::isTriangle() const
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }
    return (a + b > c) && (a + c > b) && (b + c > a);
}

// ----------------------------------------------------------------------------
//  读写接口
// ----------------------------------------------------------------------------
double Triangle::getSideA() const { return a; }
double Triangle::getSideB() const { return b; }
double Triangle::getSideC() const { return c; }

void Triangle::setSideA(double a)
{
    if (a > 0)
    {
        this->a = a;      // 用 this 指针区分“成员 a”与“参数 a”
    }
    else
    {
        std::cout << "Error: side length must be positive, value not changed"
                  << std::endl;
    }
}

void Triangle::setSideB(double b)
{
    if (b > 0)
    {
        this->b = b;
    }
    else
    {
        std::cout << "Error: side length must be positive, value not changed"
                  << std::endl;
    }
}

void Triangle::setSideC(double c)
{
    if (c > 0)
    {
        this->c = c;
    }
    else
    {
        std::cout << "Error: side length must be positive, value not changed"
                  << std::endl;
    }
}

// ----------------------------------------------------------------------------
//  周长
// ----------------------------------------------------------------------------
double Triangle::perimeter() const
{
    return a + b + c;
}

// ----------------------------------------------------------------------------
//  面积：海伦公式  S = sqrt(p * (p-a) * (p-b) * (p-c))，p 为半周长
// ----------------------------------------------------------------------------
double Triangle::area() const
{
    if (!isTriangle())
    {
        std::cout << "Error: cannot form a triangle, area is 0" << std::endl;
        return 0.0;
    }
    double p = perimeter() / 2.0;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

// ----------------------------------------------------------------------------
//  类型判断
//  思路：先找出最长边，再比较“另外两边的平方和”与“最长边的平方”：
//        a^2 + b^2 = c^2  -> 直角三角形
//        a^2 + b^2 > c^2  -> 锐角三角形
//        a^2 + b^2 < c^2  -> 钝角三角形
//  提高要求：在此基础上先判断等边、等腰直角、等腰三类重叠情况，
//            并按“等边 > 等腰直角 > 等腰 > 直角/锐角/钝角”的优先级返回。
// ----------------------------------------------------------------------------
int Triangle::typeTriangle() const
{
    if (!isTriangle())
    {
        return 0;                                   // 不构成三角形
    }

    // ---- 找出最长边放到 z 中，x、y 为另外两边（不修改成员变量）----
    double x = a;
    double y = b;
    double z = c;
    if (x > z) { double t = x; x = z; z = t; }
    if (y > z) { double t = y; y = z; z = t; }

    bool isEquilateral = nearlyEqual(a, b) && nearlyEqual(b, c);
    bool isIsosceles   = nearlyEqual(a, b) || nearlyEqual(b, c) || nearlyEqual(a, c);

    // 勾股比较的容差与边长量级相关
    double scale = z * z > 1.0 ? z * z : 1.0;
    double diff  = x * x + y * y - z * z;

    if (isEquilateral)
    {
        return 5;                                   // 等边三角形（优先级最高）
    }
    if (isIsosceles && std::fabs(diff) <= 1e-6 * scale)
    {
        return 4;                                   // 等腰直角三角形
    }
    if (isIsosceles)
    {
        return 6;                                   // 等腰三角形（锐角或钝角）
    }
    if (std::fabs(diff) <= 1e-6 * scale)
    {
        return 1;                                   // 直角三角形
    }
    if (diff > 0)
    {
        return 2;                                   // 锐角三角形
    }
    return 3;                                       // 钝角三角形
}

// ----------------------------------------------------------------------------
//  类型名称
// ----------------------------------------------------------------------------
const char* Triangle::typeName() const
{
    switch (typeTriangle())
    {
    case 1:  return "直角三角形";
    case 2:  return "锐角三角形";
    case 3:  return "钝角三角形";
    case 4:  return "等腰直角三角形";
    case 5:  return "等边三角形";
    case 6:  return "等腰三角形";
    default: return "不构成三角形";
    }
}

// ----------------------------------------------------------------------------
//  输出：三边长、周长、面积与类型
//  若不构成三角形，只输出边长与错误提示，避免输出无意义的周长和面积
// ----------------------------------------------------------------------------
void Triangle::display() const
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Sides: " << a << ' ' << b << ' ' << c << std::endl;

    if (!isTriangle())
    {
        std::cout << "Error: cannot form a triangle" << std::endl;
        return;
    }

    std::cout << "Perimeter: " << perimeter() << std::endl;
    std::cout << "Area: " << area() << std::endl;
    std::cout << "Type: " << typeName() << std::endl;
}
