#ifndef ROCKET_NET_EVENTLOOP_H
#define ROCKET_NET_EVENTLOOP_H

#include "/home/hollow/Vs-Cpp/this-Rpc/rocket/rocket/common/mutex.h"
#include "fd_event.h"
#include "wakeup_fd_event.h"
#include <functional>
#include <pthread.h>
#include <queue>
#include <set>

namespace rocket {
class EventLoop {
public:
  EventLoop();

  ~EventLoop();

  void loop();

  void wakeup();

  void stop();

  void addEpollEvent(FdEvent *event);

  void deleteEpollEvent(FdEvent *event);

  bool isInLoopThread();

  void addTask(std::function<void()> cb, bool is_wake_up = false);

private:
  void dealWakeup();

  void initWakeUpFdEevent();

private:
  pid_t m_thread_id{0};

  int m_epoll_fd{0};

  int m_wakeup_fd{0};

  WakeUpFdEvent *m_wakeup_fd_event{NULL};

  bool m_stop_flag{false};

  std::set<int> m_listen_fds;

  std::queue<std::function<void()>> m_pending_tasks;

  Mutex m_mutex;
};

} // namespace rocket

#endif