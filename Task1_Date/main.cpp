// ============================================================================
//  第 3 章  类和对象 —— 任务一：日期类 Date
//  文件：main.cpp
//  作用：测试 Date 类的全部功能（构造、Init、读写接口、星期计算、
//        合法性校验、闰年判断、nextDay 进位）
// ============================================================================
#include "Date.h"

#include <iostream>

// 星期名称：下标 0~6 依次对应星期日、星期一 …… 星期六
static const char* const WEEK_NAME[7] =
{
    "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"
};

// 输出一个日期及其星期，便于观察测试结果
static void showDate(const char* tag, const Date& d)
{
    std::cout << tag;
    d.display();
    std::cout << "  " << WEEK_NAME[d.calWeekday()] << std::endl;
}

int main()
{
    std::cout << "===== 第 3 章  任务一：日期类 Date =====" << std::endl;

    // ------------------------------------------------------------------
    //  1. 读入日期并输出结果（对应题目的输入输出示例）
    // ------------------------------------------------------------------
    int y = 0, m = 0, d = 0;
    std::cout << "请输入日期（年 月 日）：";
    if (!(std::cin >> y >> m >> d))
    {
        std::cout << "输入格式错误，程序结束。" << std::endl;
        return 1;
    }

    Date date(y, m, d);
    std::cout << "Date: ";
    date.display();
    std::cout << std::endl;
    std::cout << "Weekday: " << WEEK_NAME[date.calWeekday()] << std::endl;

    // ------------------------------------------------------------------
    //  2. 附加测试：覆盖题目要求的各个接口与选做功能
    // ------------------------------------------------------------------
    std::cout << std::endl
              << "---------- 附加测试 ----------" << std::endl;

    // [1] 默认构造函数（三个参数全用默认值）
    Date d1;
    showDate("[1] 默认构造 Date()            -> ", d1);

    // [2] 非法日期：2026 年不是闰年，2 月没有 29 日
    std::cout << "[2] 构造非法日期 2026-02-29  -> ";
    Date d2(2026, 2, 29);
    std::cout << "    对象实际日期              -> ";
    d2.display();
    std::cout << std::endl;

    // [3] Init 手工初始化：2024 年是闰年，2 月 29 日合法
    Date d3;
    d3.Init(2024, 2, 29);
    showDate("[3] Init(2024, 2, 29)         -> ", d3);

    // [4] 写接口校验：非法值不写入，合法值正常写入
    Date d4(2026, 11, 24);
    showDate("[4] 修改前                    -> ", d4);
    d4.setMonth(13);        // 非法：月份只能是 1~12
    d4.setDay(31);          // 非法：11 月只有 30 天
    d4.setYear(0);          // 非法：年份必须 >= 1
    d4.setYear(2025);       // 合法
    d4.setDay(15);          // 合法
    showDate("    修改后                    -> ", d4);

    // [5] 闰年判断：1900 不是闰年（整百年需能被 400 整除），2000 是闰年
    std::cout << "[5] isLeapYear()              -> ";
    const int YEARS[4] = { 1900, 2000, 2024, 2026 };
    for (int i = 0; i < 4; ++i)
    {
        Date t(YEARS[i], 1, 1);
        std::cout << YEARS[i] << (t.isLeapYear() ? " 闰年  " : " 平年  ");
    }
    std::cout << std::endl;

    // [6] nextDay()：普通日期、月末、年末、闰年 2 月末、平年 2 月末
    struct Case { int y, m, d; };
    const Case CASES[5] =
    {
        { 2026, 11, 24 },   // 普通日期
        { 2026, 11, 30 },   // 月末
        { 2026, 12, 31 },   // 年末
        { 2028,  2, 28 },   // 闰年 2 月末
        { 2026,  2, 28 }    // 平年 2 月末
    };
    std::cout << "[6] nextDay() 明日推算：" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        Date t(CASES[i].y, CASES[i].m, CASES[i].d);
        std::cout << "      ";
        t.display();
        t.nextDay();
        std::cout << "  ->  ";
        t.display();
        std::cout << std::endl;
    }

    std::cout << "\n程序正常结束。" << std::endl;
    return 0;
}
