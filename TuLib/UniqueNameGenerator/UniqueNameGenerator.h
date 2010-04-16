/*!
* @file    UniqueNameGenerator.h
* @brief   Header file for class UniqueNameGenerator
* @date    2010-04-16 21:33:49
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


#ifndef UNIQUENAMEGENERATOR_H_GUID_78C7CAB6_77EF_448E_8ABF_3AC6F1DA1D02
#define UNIQUENAMEGENERATOR_H_GUID_78C7CAB6_77EF_448E_8ABF_3AC6F1DA1D02


#ifndef _MSC_VER
#error Only works with VC compiler. Because the function localtime_s() from VC is invoked.
#endif


#include <string>


/*!
* @brief   ��UniqueNameGenerator�ṩ���������������ɷ���
* @details ���ɵ����ֵ���������Ϊ��[ϵͳ���� + ϵͳʱ�� + ����]
*/
class UniqueNameGenerator
{
private:
    size_t m_counter;
    size_t m_maxCount;
    size_t m_maxWidth;

public:
    /*!
    * @brief ����һ���ܹ����ɲ����������ַ�����
    * @param maxCount ��ͬһʱ�̣���ȷ���룩��ϵͳ�ܹ�ӵ�еĲ�ͬ���ֵ�������
    */
    UniqueNameGenerator(size_t maxCount = 10000);

    /*!
    * @brief ���ɲ�����������
    * @tparam CharT �ַ����ͣ���ǰֻ֧��char��wchar_t��������
    * @param dataTime �Ƿ�������ǰ����ϵͳ������ʱ�䣨Ĭ����ӣ��������������
    * @return �������ɵ�����
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
