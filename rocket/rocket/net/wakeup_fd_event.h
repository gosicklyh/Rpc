#ifndef ROCKET_NET_WAKEUP_FDEVENT_H
#define ROCKET_NET_WAKEUP_FDEVENT_H

#include "fd_event.h"

namespace rocket {

class WakeUpFdEvent : public FdEvent {
public:
  WakeUpFdEvent(int fd);

  ~WakeUpFdEvent();

  void wakeup();

private:
};

} // namespace rocket

#endif