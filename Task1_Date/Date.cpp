// ============================================================================
//  第 3 章  类和对象 —— 任务一：日期类 Date
//  文件：Date.cpp
//  作用：Date 类所有成员函数的实现
// ============================================================================
#include "Date.h"

#include <iostream>
#include <iomanip>

// ----------------------------------------------------------------------------
//  私有辅助函数
// ----------------------------------------------------------------------------

// 闰年判定：能被 4 整除且不能被 100 整除，或者能被 400 整除
bool Date::isLeapYearOf(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// 返回某年某月的天数（调用前 m 必须在 1~12 之间）
int Date::daysOfMonth(int y, int m)
{
    // 平年各月天数，下标 0 对应 1 月
    static const int DAYS[12] = { 31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31 };
    if (m == 2)
    {
        return isLeapYearOf(y) ? 29 : 28;   // 闰年 2 月为 29 天
    }
    return DAYS[m - 1];
}

// 日期合法性校验：先查年、月范围，再查“日”是否超过该月天数
bool Date::isValidDate(int y, int m, int d)
{
    if (y < 1 || y > 9999)                    // 年份越界
    {
        return false;
    }
    if (m < 1 || m > 12)                      // 月份越界
    {
        return false;
    }
    if (d < 1 || d > daysOfMonth(y, m))       // 日越界（含闰年 2 月）
    {
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------------
//  构造函数：初始化列表 + 合法性校验
// ----------------------------------------------------------------------------
Date::Date(int y, int m, int d) : year(y), month(m), day(d)
{
    if (!isValidDate(year, month, day))
    {
        std::cout << "Error: invalid date (" << y << "-" << m << "-" << d
                  << "), reset to 1900-01-01" << std::endl;
        year  = 1900;      // 非法日期统一置为默认日期
        month = 1;
        day   = 1;
    }
}

// ----------------------------------------------------------------------------
//  手工初始化：与构造函数做同样的校验
// ----------------------------------------------------------------------------
void Date::Init(int y, int m, int d)
{
    if (isValidDate(y, m, d))
    {
        year  = y;
        month = m;
        day   = d;
    }
    else
    {
        std::cout << "Error: invalid date (" << y << "-" << m << "-" << d
                  << "), reset to 1900-01-01" << std::endl;
        year  = 1900;
        month = 1;
        day   = 1;
    }
}

// ----------------------------------------------------------------------------
//  读接口
// ----------------------------------------------------------------------------
int Date::getYear()  const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay()   const { return day; }

// ----------------------------------------------------------------------------
//  写接口：以“当前对象的另外两个分量”为上下文做整体校验，
//  因此不会出现 2 月 30 日、4 月 31 日这类非法状态。
// ----------------------------------------------------------------------------
void Date::setYear(int y)
{
    if (isValidDate(y, month, day))
    {
        year = y;
    }
    else
    {
        std::cout << "Error: invalid year " << y
                  << " (would make " << y << "-" << month << "-" << day
                  << " illegal), value not changed" << std::endl;
    }
}

void Date::setMonth(int m)
{
    if (isValidDate(year, m, day))
    {
        month = m;
    }
    else
    {
        std::cout << "Error: invalid month " << m
                  << " (would make " << year << "-" << m << "-" << day
                  << " illegal), value not changed" << std::endl;
    }
}

void Date::setDay(int d)
{
    if (isValidDate(year, month, d))
    {
        day = d;
    }
    else
    {
        std::cout << "Error: invalid day " << d
                  << " (would make " << year << "-" << month << "-" << d
                  << " illegal), value not changed" << std::endl;
    }
}

// ----------------------------------------------------------------------------
//  输出：YYYY-MM-DD，不足位数用 0 补齐
// ----------------------------------------------------------------------------
void Date::display() const
{
    std::cout << std::setfill('0')
              << std::setw(4) << year  << '-'
              << std::setw(2) << month << '-'
              << std::setw(2) << day
              << std::setfill(' ');      // 恢复默认填充字符，避免影响后续输出
}

// ----------------------------------------------------------------------------
//  星期计算：基姆拉尔森（Kim Larsen）公式
//      Weekday = (d + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400 + 1) % 7
//  计算前把 1 月、2 月分别看成上一年的 13 月、14 月；
//  公式中的除法为整数除法，结果对 7 取余，0~6 依次对应星期日~星期六。
// ----------------------------------------------------------------------------
int Date::calWeekday() const
{
    int y = year;
    int m = month;

    if (m == 1 || m == 2)
    {
        m += 12;    // 1 月 -> 13 月，2 月 -> 14 月
        --y;        // 归属到上一年
    }

    int weekday = (day + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
    return weekday;
}

// ----------------------------------------------------------------------------
//  提高要求：判断当前对象年份是否为闰年
// ----------------------------------------------------------------------------
bool Date::isLeapYear() const
{
    return isLeapYearOf(year);
}

// ----------------------------------------------------------------------------
//  提高要求：推算“明日日期”
//  进位规则：日未到月末则日加 1；否则日变为 1、月加 1；
//            若已是 12 月末则月变为 1、年加 1。
//  因为 daysOfMonth 已考虑闰年，故闰年 2 月 28 日会自动进位到 2 月 29 日。
// ----------------------------------------------------------------------------
void Date::nextDay()
{
    if (day < daysOfMonth(year, month))
    {
        ++day;                          // 普通情况：日加 1
    }
    else
    {
        day = 1;                        // 月末：进入下个月的第 1 天
        if (month < 12)
        {
            ++month;
        }
        else
        {
            month = 1;                  // 年末：进入下一年的 1 月
            ++year;
        }
    }
}
