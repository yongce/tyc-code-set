/*!
* @file    RWLock_example.cpp
* @brief   Test and exmaple for class RWLock
* @date    2010-04-17 20:37:14
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


/*!
* @example RWLock_example.cpp
* This is a test program and also an example for class RWLock.
*/


#include <iostream>
#include <string>
#include <process.h>
#include <Windows.h>

#include "RWLock.h"
#include "AutoRWLock.h"

using namespace std;


const int LOOP_NUM = 2000;


// Anonymous
namespace
{
    struct TestData
    {
        volatile __int64 m_data;
        CRITICAL_SECTION m_cs;
        RWLock m_rwLock;
    };

    struct ThreadParam
    {
        int m_id;
        TestData *m_shared;

        ThreadParam(int id, TestData *shared) : m_id(id), m_shared(shared) { }
    };
}


void TestCase();
unsigned WINAPI ReaderThread(void *pParam);
unsigned WINAPI WriterThread1(void *pParam);
unsigned WINAPI WriterThread2(void *pParam);


int main()
{
    try
    {
        for (int i = 0; i < 100; ++i)
        {
            TestCase();
        }
    }
    catch (const string &err)
    {
        cout << "Error: " << err << endl;
        return -1;
    }

    cout << "Successful!" << endl;
}


void TestCase()
{
    TestData sharedData;

    ::InitializeCriticalSection(&sharedData.m_cs);
    sharedData.m_data = 0;

    // Create worker threads simulating readers and writers
    HANDLE readers[20];
    for (int i = 0; i < _countof(readers); ++i)
    {
        readers[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThread, new ThreadParam(i, &sharedData), 
            CREATE_SUSPENDED, NULL);
    }

    HANDLE writers1[5];
    for (int i = 0; i < _countof(writers1); ++i)
    {
        writers1[i] = (HANDLE)_beginthreadex(NULL, 0, WriterThread1, new ThreadParam(i, &sharedData), 
            CREATE_SUSPENDED, NULL);
    }

    HANDLE writers2[5];
    for (int i = 0; i < _countof(writers2); ++i)
    {
        writers2[i] = (HANDLE)_beginthreadex(NULL, 0, WriterThread2, new ThreadParam(i, &sharedData), 
            CREATE_SUSPENDED, NULL);
    }

    // Resume worker threads
    for (int i = 0; i < _countof(readers); ++i)
    {
        ::ResumeThread(readers[i]);
    }
    
    for (int i = 0; i < _countof(writers1); ++i)
    {
        ::ResumeThread(writers1[i]);
    }

    for (int i = 0; i < _countof(writers2); ++i)
    {
        ::ResumeThread(writers2[i]);
    }

    // Waiting for the worker threads to finish
    ::WaitForMultipleObjects(_countof(readers), readers, TRUE, INFINITE);
    ::WaitForMultipleObjects(_countof(writers1), writers1, TRUE, INFINITE);
    ::WaitForMultipleObjects(_countof(writers2), writers2, TRUE, INFINITE);

    // Release handles
    for (int i = 0; i < _countof(readers); ++i)
    {
        ::CloseHandle(readers[i]);
    }

    for (int i = 0; i < _countof(writers1); ++i)
    {
        ::CloseHandle(writers1[i]);
    }

    for (int i = 0; i < _countof(writers2); ++i)
    {
        ::CloseHandle(writers2[i]);
    }

    ::DeleteCriticalSection(&sharedData.m_cs);

    // Check the result
    cout << ">> Expected data value is " << 0 << ", and the real value is " << sharedData.m_data << endl;

    if (sharedData.m_data != 0)
        throw string("Failed to validate the result!");
}


unsigned WINAPI ReaderThread(void *pParam)
{
    ThreadParam *p = (ThreadParam*)pParam;
    int id = p->m_id;
    TestData *pSharedData = p->m_shared;

    ::EnterCriticalSection(&pSharedData->m_cs);
    cout << "Reader [" << id << "] is starting..." << endl;
    ::LeaveCriticalSection(&pSharedData->m_cs);

    __int64 max = 0;
    __int64 min = 0;

    for (int i = 0; i < LOOP_NUM / 2; ++i)
    {
        Sleep(rand() % 3);
        pSharedData->m_rwLock.ReadLock();

        __int64 data = pSharedData->m_data;
        if (data > max)
            max = data;
        if (data < min)
            min = data;

        pSharedData->m_rwLock.ReadUnlock();
    }

    for (int i = 0; i < LOOP_NUM / 2; ++i)
    {
        Sleep(rand() % 3);
        AutoReadLock(pSharedData->m_rwLock);

        __int64 data = pSharedData->m_data;
        if (data > max)
            max = data;
        if (data < min)
            min = data;
    }

    ::EnterCriticalSection(&pSharedData->m_cs);
    cout << "Reader [" << id << "] is quitting, max = " << max << ", min = " << min << endl;
    ::LeaveCriticalSection(&pSharedData->m_cs);

    delete pParam;

    return 0;
}

unsigned WINAPI WriterThread1(void *pParam)
{
    ThreadParam *p = (ThreadParam*)pParam;
    int id = p->m_id;
    TestData *pSharedData = p->m_shared;

    ::EnterCriticalSection(&pSharedData->m_cs);
    cout << "Writer1 [" << id << "] is starting..." << endl;
    ::LeaveCriticalSection(&pSharedData->m_cs);

    for (int i = 0; i < LOOP_NUM; ++i)
    {
        Sleep(rand() % 3);
        pSharedData->m_rwLock.WriteLock();
        pSharedData->m_data += i;
        pSharedData->m_rwLock.WriteUnlock();
    }

    ::EnterCriticalSection(&pSharedData->m_cs);
    cout << "Writer1 [" << id << "] is quitting." << endl;
    ::LeaveCriticalSection(&pSharedData->m_cs);

    delete pParam;

    return 0;
}

unsigned WINAPI WriterThread2(void *pParam)
{
    ThreadParam *p = (ThreadParam*)pParam;
    int id = p->m_id;
    TestData *pSharedData = p->m_shared;

    ::EnterCriticalSection(&pSharedData->m_cs);
    cout << "Writer2 [" << id << "] is starting..." << endl;
    ::LeaveCriticalSection(&pSharedData->m_cs);

    for (int i = 0; i < LOOP_NUM; ++i)
    {
        Sleep(rand() % 3);
        AutoWriteLock lock(pSharedData->m_rwLock);
        pSharedData->m_data -= i;
    }

    ::EnterCriticalSection(&pSharedData->m_cs);
    cout << "Writer2 [" << id << "] is quitting." << endl;
    ::LeaveCriticalSection(&pSharedData->m_cs);

    delete pParam;

    return 0;
}

