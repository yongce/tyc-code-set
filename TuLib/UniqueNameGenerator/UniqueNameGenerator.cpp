/*!
* @file    UniqueNameGenerator.cpp
* @brief   Implementation file for class UniqueNameGenerator
* @date    2010-04-16 21:33:49
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Date$
*/


#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>

#include "UniqueNameGenerator.h"

using namespace std;


/*
* ����һ���ܹ����ɲ����������ַ�����
* @param maxCount ��ͬһʱ�̣���ȷ���룩��ϵͳ�ܹ�ӵ�еĲ�ͬ���ֵ�������
*/
UniqueNameGenerator::UniqueNameGenerator(size_t maxCount): 
    m_counter(0), m_maxCount(maxCount)
{
    // ���������ʮ���Ʊ�ʾ�����λ������ȣ�
    m_maxWidth = 1;

    if (maxCount <= 10)
        return;

    bool zeroEnded = true;
    size_t count = maxCount;

    while (count >= 10)
    {
        ++m_maxWidth;
        if (zeroEnded && count % 10)
            zeroEnded = false;
        count /= 10;
    }

    if (zeroEnded && count == 1)
        --m_maxWidth;
}


/*
* ���ɲ�����������
* @param dataTime �Ƿ�������ǰ����ϵͳ������ʱ�䣨Ĭ����ӣ��������������
*/
template <typename CharT>
basic_string<CharT> UniqueNameGenerator::DoGenerateName(bool dataTime)
{
    basic_ostringstream<CharT> oss;
    oss.fill('0');
    CharT delimiter('_');

    if (dataTime)
    {
        time_t curTime = time(0);
        struct tm now;
        localtime_s(&now, &curTime);
        oss << setw(4) << (now.tm_year + 1900) << setw(2) << (now.tm_mon + 1)
            << setw(2) << now.tm_mday << delimiter << setw(2) << now.tm_hour 
            << setw(2) << now.tm_min << setw(2) << now.tm_sec << delimiter;
    }

    if (m_maxCount > 0)
    {
        oss << setw(m_maxWidth) << m_counter;
        // ���¼���
        m_counter = ++m_counter % m_maxCount;
    }

    return oss.str();
}


template <>
string UniqueNameGenerator::GenerateName<char>(bool dataTime /* = true */)
{
    return DoGenerateName<char>(dataTime);
}


template <>
wstring UniqueNameGenerator::GenerateName<wchar_t>(bool dataTime /* = true */)
{
    return DoGenerateName<wchar_t>(dataTime);
}

