#include "/home/hollow/Vs-Cpp/this-Rpc/rocket/rocket/common/config.h"
#include "/home/hollow/Vs-Cpp/this-Rpc/rocket/rocket/common/log.h"
#include <pthread.h>

void *fun(void *) {
  DEBUGLOG("debug this is thread in %s", "fun");
  INFOLOG("info this is thread in %s", "fun");
  return NULL;
}

int main() {

  rocket::Config::SetGlobalConfig("../conf/rocket.xml");
  rocket::Logger::InitGlobalConfig();
  pthread_t thread;
  pthread_create(&thread, NULL, &fun, NULL);

  DEBUGLOG("test debug log %s", "11");
  INFOLOG("test info log %s", "11");
  
  pthread_join(thread,NULL);
  return 0;
}