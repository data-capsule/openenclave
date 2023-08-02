// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <locale.h>
#include <openenclave/enclave.h>
#include <stdio.h>
#include <stdlib.h>

long long int strtoll_l(const char* nptr, char** endptr, int base, locale_t loc)
{
    OE_UNUSED(loc);
    return strtoll(nptr, endptr, base);
}

unsigned long long strtoull_l(
    const char* nptr,
    char** endptr,
    int base,
    locale_t loc)
{
    OE_UNUSED(loc);
    return strtoull(nptr, endptr, base);
}

int fchmod(int fd, int perms)
{
    //   HANDLE h = reinterpret_cast<HANDLE>(_get_osfhandle(fd));
    return 0;
}

int execv(const char* path, char* const argv[])
{
    return 0;
}

int fork()
{
    return 0;
}

int wait()
{
    return 0;
}

int sigprocmask()
{
    return 0;
}

int sigfillset()
{
    return 0;
}

int fstatfs()
{
    return 0;
}

int chmod()
{
    return 0;
}

int isatty()
{
    return 0;
}

int symlink()
{
    return 0;
}

int futimens()
{
    return 0;
}

int posix_spawn_file_actions_init()
{
    return 0;
}

int posix_spawn_file_actions_destroy()
{
    return 0;
}

int sigemptyset()
{
    return 0;
}

int pthread_attr_init()
{
    return 0;
}

int pthread_getattr_np()
{
    return 0;
}

int pthread_attr_setstacksize()
{
    return 0;
}

int pthread_condattr_setclock()
{
    return 0;
}

int pthread_condattr_init()
{
    return 0;
}

int pthread_setname_np()
{
    return 0;
}
int pthread_attr_getstack()
{
    return 0;
}

int pthread_attr_destroy()
{
    return 0;
}

int pthread_attr_getguardsize()
{
    return 0;
}

int pthread_attr_setdetachstate()
{
    return 0;
}

int sigaddset()
{
    return 0;
}

int getpwuid_r()
{
    return 0;
}

int fchown()
{
    return 0;
}

int getrusage()
{
    return 0;
}

int sigaltstack()
{
    return 0;
}

int umask()
{
    return 0;
}

char* realpath(const char* __restrict x, char* __restrict y)
{
    return "path";
}

int __sched_cpucount()
{
    return 0;
}

int utimes()
{
    return 0;
}
int statvfs64()
{
    return 0;
}
int pathconf()
{
    return 0;
}

int sched_getaffinity()
{
    return 0;
}

int alarm()
{
    return 0;
}

int wait4()
{
    return 0;
}

int posix_spawn_file_actions_adddup2()
{
    return 0;
}

int readlink()
{
    return 0;
}

int execve()
{
    return 0;
}

int setrlimit()
{
    return 0;
}

int waitpid()
{
    return 0;
}

int posix_madvise()
{
    return 0;
}

int getpwnam_r()
{
    return 0;
}

int getgrnam_r()
{
    return 0;
}

int posix_spawn()
{
    return 0;
}

int statfs()
{
    return 0;
}

int dlopen()
{
    return 0;
}

int posix_spawn_file_actions_addopen()
{
    return 0;
}

int pthread_condattr_destroy()
{
    return 0;
}

int dlclose()
{
    return 0;
}

int mprotect()
{
    return 0;
}

int telldir()
{
    return 0;
}

int seekdir()
{
    return 0;
}

int clock_getres()
{
    return 0;
}

int dlsym()
{
    return 0;
}

int getClockResAsI128()
{
    return 0;
}

int raise()
{
    return 0;
}

int lstat()
{
    return 0;
}

int fdopendir()
{
    return 0;
}

int pthread_sigmask()
{
    return 0;
}

int siglongjmp()
{
    return 0;
}

int dlerror()
{
    return 0;
}

int sigsetjmp()
{
    return 0;
}

int pthread_mutex_consistent()
{
    return 0;
}

int pthread_mutexattr_setpshared()
{
    return 0;
}

int pthread_mutexattr_setrobust()
{
    return 0;
}

int sigwait()
{
    return 0;
}

int madvise()
{
    return 0;
}

int msync()
{
    return 0;
}

int unlinkat()
{
    return 0;
}

int utimensat()
{
    return 0;
}