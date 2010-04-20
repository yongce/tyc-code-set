/*!
* @file    RWLock.cpp
* @brief   Implementation file for class RWLock
* @date    2010-04-17 20:36:54
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


#include <cassert>

#include "RWLock.h"



RWLock::RWLock() : m_waitingReaders(0), m_waitingWriters(0), m_refCount(0)
{
    ::InitializeCriticalSection(&m_cs);
    m_readersEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);    // manual reset event
    m_writersEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);   // auto reset event
}


RWLock::~RWLock()
{
    assert(m_waitingReaders == 0);
    assert(m_waitingWriters == 0);
    assert(m_refCount == 0);

    ::CloseHandle(m_readersEvent);
    ::CloseHandle(m_writersEvent);
    ::DeleteCriticalSection(&m_cs);
}


void RWLock::ReadLock()
{
    ::EnterCriticalSection(&m_cs);

    // Writers have higher priority than readers
    while (m_refCount < 0 || m_waitingWriters > 0)
    {
        ++m_waitingReaders;
        ::LeaveCriticalSection(&m_cs);

        ::WaitForSingleObject(m_readersEvent, INFINITE);

        ::EnterCriticalSection(&m_cs);
        --m_waitingReaders;
    }

    ++m_refCount;
    ::LeaveCriticalSection(&m_cs);
}


void RWLock::ReadUnlock()
{
    ::EnterCriticalSection(&m_cs);

    assert(m_refCount > 0);
    --m_refCount;

    if (m_refCount == 0)
    {
        // Now, no readers are using the lock
        // Check if there are writers waiting on the lock
        if (m_waitingWriters > 0)
        {
            // Signal one of the waiting writers
            ::SetEvent(m_writersEvent);
        }
    }

    ::LeaveCriticalSection(&m_cs);
}


void RWLock::WriteLock()
{
    ::EnterCriticalSection(&m_cs);

    // Stop all incoming readers
    ::ResetEvent(m_readersEvent);

    while (m_refCount != 0)
    {
        ++m_waitingWriters;
        ::LeaveCriticalSection(&m_cs);

        ::WaitForSingleObject(m_writersEvent, INFINITE);

        ::EnterCriticalSection(&m_cs);
        --m_waitingWriters;
    }

    m_refCount = -1;
    ::LeaveCriticalSection(&m_cs);
}


void RWLock::WriteUnlock()
{
    ::EnterCriticalSection(&m_cs);

    assert(m_refCount == -1);
    m_refCount = 0;

    // Writers have higher priority than readers
    if (m_waitingWriters > 0)
    {
        // Signal one of the waiting writers
        ::SetEvent(m_writersEvent);
    }
    else if (m_waitingReaders > 0)
    {
        // Signal all waiting readers
        ::SetEvent(m_readersEvent);
    }

    ::LeaveCriticalSection(&m_cs);
}


