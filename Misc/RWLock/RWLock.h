/*!
* @file    RWLock.h
* @brief   Header file for class RWLock
* @date    2010-04-17 20:36:54
* @author  Tu Yongce <tuyongce@gmail.com>
* @version $Id$
*/


#ifndef RWLOCK_H_GUID_FF77630C_9BB0_465F_B60A_2DB16DE81404
#define RWLOCK_H_GUID_FF77630C_9BB0_465F_B60A_2DB16DE81404


#ifndef _WIN32
#error Only works on Windows.
#endif


#include <Windows.h>


/*!
* @brief Read-write lock implementation
* @details This read-write lock is implemented as writer with higher priority. Currently, it doesn't support timeout waiting. @n
*          This read-write lock is using Win32 API. So, it can only be used on Windows platform. 
* @todo To support timeout waiting.
*/
class RWLock
{
private:
    CRITICAL_SECTION m_cs;
    HANDLE           m_readersEvent;     // manual reset event
    HANDLE           m_writersEvent;     // auto reset event

    volatile int     m_waitingReaders;   // number of readers waiting
    volatile int     m_waitingWriters;   // number of writers waiting
    volatile int     m_refCount;         // number of threads owning the lock:
                                         // -1 if one writer thread owns the lock, or
                                         // 0  if no thread owns the lock, or
                                         // n if n reader theads own the lock

public:
    /*!
    * @brief Constructor
    */
    RWLock();

    /*!
    * @brief Destructor
    */
    ~RWLock();

    /*!
    * @brief Request the reader lock
    */
    void ReadLock();

    /*!
    * @brief Release the reader lock
    */
    void ReadUnlock();

    /*!
    * @brief Request the writer lock
    */
    void WriteLock();

    /*!
    * @brief Release the writer lock
    */
    void WriteUnlock();

private:
    // Forbid copy constructor & copy assignment operator
    RWLock(const RWLock&);
    RWLock& operator= (const RWLock&);
};


#endif //RWLOCK_H_GUID_FF77630C_9BB0_465F_B60A_2DB16DE81404

