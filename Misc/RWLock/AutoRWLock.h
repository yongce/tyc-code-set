/*!
* @file    AutoRWLock.h
* @brief   Header file
* @date    2010-04-18 23:38:06
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


#ifndef AUTORWLOCK_H_GUID_E82F22F4_77C6_42A7_BFFC_FCE3ADCF24C6
#define AUTORWLOCK_H_GUID_E82F22F4_77C6_42A7_BFFC_FCE3ADCF24C6


#include <stdexcept>
#include <string>

#include "RWLock.h"


/*!
* @brief Auto read-lock
*/
class AutoReadLock
{
private:
    RWLock &m_rwLock;
    bool m_locked;

public:
    AutoReadLock(RWLock &rwLock, bool locked = true) : m_rwLock(rwLock), m_locked(false)
    {
        if (locked)
        {
            Lock();
        }
    }

    ~AutoReadLock()
    {
        if (IsLocked())
        {
            Unlock();
        }
    }

    void Lock()
    {
        m_rwLock.ReadLock();
        m_locked = true;
    }

    void Unlock()
    {
        m_rwLock.ReadUnlock();
        m_locked = false;
    }

    bool IsLocked()
    {
        return m_locked;
    }

private:
    // Forbid copy constructor & copy assignment operator
    AutoReadLock(const AutoReadLock &);
    AutoReadLock& operator= (const AutoReadLock &);
};


/*!
* @brief Auto write-lock
*/
class AutoWriteLock
{
private:
    RWLock &m_rwLock;
    bool m_locked;

public:
    AutoWriteLock(RWLock &rwLock, bool locked = true) : m_rwLock(rwLock), m_locked(false)
    {
        if (locked)
        {
            Lock();
        }
    }

    ~AutoWriteLock()
    {
        if (IsLocked())
        {
            Unlock();
        }
    }

    void Lock()
    {
        m_rwLock.WriteLock();
        m_locked = true;
    }

    void Unlock()
    {
        m_rwLock.WriteUnlock();
        m_locked = false;
    }

    bool IsLocked()
    {
        return m_locked;
    }

private:
    // Forbid copy constructor & copy assignment operator
    AutoWriteLock(const AutoWriteLock &);
    AutoWriteLock& operator= (const AutoWriteLock &);
};


#endif //AUTORWLOCK_H_GUID_E82F22F4_77C6_42A7_BFFC_FCE3ADCF24C6

