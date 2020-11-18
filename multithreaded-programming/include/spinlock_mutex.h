#include <atomic>

#ifndef __SPINLOCK_MUTEX_H__
#define __SPINLOCK_MUTEX_H__

class spinlock_mutex {
private:
  std::atomic_flag flag;
public:
  spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}
  void lock() {
    while(flag.test_and_set(std::memory_order_acquire));
  }
  void unlock() {
    flag.clear(std::memory_order_release);
  }
};


#endif // __SPINLOCK_MUTEX_H__