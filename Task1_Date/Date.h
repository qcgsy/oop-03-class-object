// ============================================================================
//  第 3 章  类和对象 —— 任务一：日期类 Date
//  文件：Date.h
//  作用：Date 类的声明（数据成员私有，对外只暴露接口，体现封装）
//  说明：使用 #ifndef / #define / #endif 防止头文件被重复包含
// ============================================================================
#ifndef DATE_H
#define DATE_H

class Date
{
private:
    // ---------- 私有数据成员：外界不能直接读写，只能通过接口访问 ----------
    int year;      // 年份（1 ~ 9999）
    int month;     // 月份（1 ~ 12）
    int day;       // 日  （1 ~ 31，随月份与闰年变化）

    // ---------- 私有辅助函数：只在类内部使用 ----------
    static bool isLeapYearOf(int y);            // 判断给定年份 y 是否为闰年
    static int  daysOfMonth(int y, int m);      // 返回 y 年 m 月的天数
    static bool isValidDate(int y, int m, int d); // 判断 y-m-d 是否为合法日期

public:
    // ---------- 构造函数：带默认参数，同时充当默认构造函数 ----------
    //  采用初始化列表初始化数据成员，并在函数体内校验日期合法性；
    //  非法日期给出提示，并将对象置为默认日期 1900-01-01。
    Date(int y = 1900, int m = 1, int d = 1);

    // ---------- 手工初始化成员函数 ----------
    //  与构造函数的区别：构造函数在对象“创建时”自动调用，而 Init 必须显式调用，
    //  且对已存在的对象再次使用时容易遗漏初始化。
    void Init(int y, int m, int d);

    // ---------- 读接口（const 成员函数：只读，不修改对象状态） ----------
    int getYear()  const;
    int getMonth() const;
    int getDay()   const;

    // ---------- 写接口（写入前校验，非法值不予写入并给出提示） ----------
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);

    // ---------- 输出函数：按 YYYY-MM-DD 格式输出日期 ----------
    void display() const;

    // ---------- 星期计算：返回 0~6，依次对应星期日、星期一 …… 星期六 ----------
    int calWeekday() const;

    // ---------- 提高要求（选做） ----------
    bool isLeapYear() const;   // 判断当前对象所在年份是否为闰年
    void nextDay();            // 推算“明日”：处理月末、年末、闰年 2 月进位
};

#endif // DATE_H
