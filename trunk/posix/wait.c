#include "/usr/include/sys/wait.h"

int Pure_wait(__WAIT_STATUS* arg0)
{
  return wait(*arg0);
}

int Pure_wait3(__WAIT_STATUS* arg0, int arg1, struct rusage* arg2)
{
  return wait3(*arg0, arg1, arg2);
}

int Pure_wait4(int arg0, __WAIT_STATUS* arg1, int arg2, struct rusage* arg3)
{
  return wait4(arg0, *arg1, arg2, arg3);
}
