/*!
* @file    UniqueNameGenerator.h
* @brief   Header file for class UniqueNameGenerator
* @date    2010-04-16 21:33:49
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


#ifndef UNIQUENAMEGENERATOR_H_GUID_78C7CAB6_77EF_448E_8ABF_3AC6F1DA1D02
#define UNIQUENAMEGENERATOR_H_GUID_78C7CAB6_77EF_448E_8ABF_3AC6F1DA1D02


#if !defined(_MSC_VER) && !(defined(__GNUC__) && !defined(__MINGW32__))
#error Currently only works with VC++ and GCC (not including MinGW-GCC).
#endif


#include <string>


/*!
* @brief   类UniqueNameGenerator提供不重名的名字生成服务
* @details 生成的名字的命名规则为：[系统日期 + 系统时间 + 计数]
*/
class UniqueNameGenerator
{
private:
    size_t m_counter;
    size_t m_maxCount;
    size_t m_maxWidth;

public:
    /*!
    * @brief 构造一个能够生成不重名的名字发生器
    * @param maxCount 在同一时刻（精确到秒），系统能够拥有的不同名字的最大个数
    */
    UniqueNameGenerator(size_t maxCount = 10000);

    /*!
    * @brief 生成不重名的名字
    * @tparam CharT 字符类型，当前只支持char和wchar_t两种类型
    * @param dataTime 是否在名字前加上系统日期与时间（默认添加，否则可能重名）
    * @return 返回生成的名字
    */
    template <typename CharT>
    std::basic_string<CharT> GenerateName(bool dataTime = true);  // not implemented!!!

private:
    template <typename CharT>
    std::basic_string<CharT> DoGenerateName(bool dataTime);    
};


template <>
std::string UniqueNameGenerator::GenerateName<char>(bool dataTime /* = true */);

template <>
std::wstring UniqueNameGenerator::GenerateName<wchar_t>(bool dataTime /* = true */);



#endif //UNIQUENAMEGENERATOR_H_GUID_78C7CAB6_77EF_448E_8ABF_3AC6F1DA1D02
