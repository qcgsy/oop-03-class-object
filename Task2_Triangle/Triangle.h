// ============================================================================
//  第 3 章  类和对象 —— 任务二：三角形类 Triangle
//  文件：Triangle.h
//  作用：Triangle 类的声明
//  说明：使用 #ifndef / #define / #endif 防止头文件被重复包含
// ============================================================================
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
private:
    // ---------- 私有数据成员：三条边长 ----------
    double a;
    double b;
    double c;

    // 浮点数不能直接用 == 比较，这里用相对误差判断“两个边长是否相等”
    static bool nearlyEqual(double x, double y);

public:
    // ---------- 构造函数：带默认参数 ----------
    Triangle(double a = 1, double b = 1, double c = 1);

    // ---------- 手工初始化 ----------
    void Init(double a, double b, double c);

    // ---------- 是否构成三角形：三边均为正数，且任意两边之和大于第三边 ----------
    bool isTriangle() const;

    // ---------- 读写接口 ----------
    double getSideA() const;
    double getSideB() const;
    double getSideC() const;

    // 写入时校验边长必须为正数，非法值不予写入并给出提示
    void setSideA(double a);
    void setSideB(double b);
    void setSideC(double c);

    // ---------- 周长与面积 ----------
    double perimeter() const;      // 周长
    double area() const;           // 面积（海伦公式），不构成三角形时提示并返回 0

    // ---------- 类型判断 ----------
    //  返回 0：不构成三角形      1：直角三角形（非等腰）
    //       2：锐角三角形（非等腰） 3：钝角三角形（非等腰）
    //       4：等腰直角三角形      5：等边三角形      6：等腰三角形（锐角或钝角）
    //  优先级：等边 > 等腰直角 > 等腰 > 直角/锐角/钝角
    int typeTriangle() const;

    // 返回当前三角形类型的名称，供输出使用
    const char* typeName() const;

    // ---------- 输出函数：三边长、周长、面积与类型 ----------
    void display() const;
};

#endif // TRIANGLE_H
