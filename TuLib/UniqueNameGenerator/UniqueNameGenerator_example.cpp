/*!
* @file    UniqueNameGenerator_example.cpp
* @brief   ��UniqueNameGenerator��ʾ��
* @date    2010-04-16 22:06:05
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Revision$ $Author$ $Date$
*/


/*!
* @example UNG_example.cpp
* ��������UniqueNameGenerator��һ��ʾ����
*/

#include <iostream>
#include <sstream>
#include <set>
#include <string>
#include <stdexcept>

#include "UniqueNameGenerator.h"

using namespace std;


template <typename CharT>
void ShowUsage(basic_ostream<CharT> &os);

template <typename CharT>
void Test();

template <typename CharT>
void TestCase(size_t count);


int main()
{
    Test<char>();
    Test<wchar_t>();

    ShowUsage<char>(cout);
    ShowUsage<wchar_t>(wcout);
    
    return 0;
}

template <typename CharT>
void ShowUsage(basic_ostream<CharT> &os)
{
    UniqueNameGenerator gen(17);
    for (size_t i = 0; i <= 17; ++i) 
        os << gen.GenerateName<CharT>() << '\n';
    os << endl;

    UniqueNameGenerator gen2(10);
    for (size_t i = 0; i <= 10; ++i) 
        os << gen2.GenerateName<CharT>(false) << ' ';
    os << endl;

    UniqueNameGenerator gen3(20);
    for (size_t i = 0; i <= 20; ++i) 
        os << gen3.GenerateName<CharT>(false) << ' ';
    os << '\n' << endl;

    UniqueNameGenerator gen4(200);
    for (size_t i = 0; i <= 200; ++i) 
        os << gen4.GenerateName<CharT>(false) << ' ';
    os << '\n' << endl;
}


template <typename CharT>
void Test()
{
    try
    {
        TestCase<CharT>(0);
        TestCase<CharT>(9);
        TestCase<CharT>(10);
        TestCase<CharT>(15);
        TestCase<CharT>(20);
        TestCase<CharT>(99);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }    
}


template <typename CharT>
void TestCase(size_t count)
{
    typedef basic_string<CharT> StringT;

    UniqueNameGenerator gen(count);

    if (count == 0)
    {
        if (!gen.GenerateName<CharT>(false).empty())
        {
            // ����
            ostringstream oss;
            oss << "File: " << __FILE__ << ", Line: " << __LINE__;
            throw runtime_error(oss.str());
        }
        return;
    }

    typedef typename set<StringT>::iterator Iterator;

    set<StringT> names;

    for (size_t i = 0; i < count; ++i)
    {
        StringT oneName = gen.GenerateName<CharT>(false);
        pair<Iterator, bool> ret = names.insert(oneName);
        if (!ret.second)
        {
            // ����
            ostringstream oss;
            oss << "File: " << __FILE__ << ", Line: " << __LINE__;
            throw runtime_error(oss.str());
        }
        
    }

    StringT oneName = gen.GenerateName<CharT>(false);
    pair<Iterator, bool> ret = names.insert(oneName);
    if (ret.second)
    {
        // Ӧ������ȴû������
        ostringstream oss;
        oss << "File: " << __FILE__ << ", Line: " << __LINE__;
        throw runtime_error(oss.str());
    }
}

