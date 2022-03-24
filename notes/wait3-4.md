# WAIT4(2)

## []NAME         

       wait3, wait4 - wait for process to change state, BSD style

## []SYNOPSIS       
 
       **#include <sys/wait.h>**

       **pid_t wait3(int ***_wstatus_**, int** _options_**, struct rusage ***_rusage_**);**
       **pid_t wait4(pid_t** _pid_**, int ***_wstatus_**, int** _options_**,**
                   **struct rusage ***_rusage_**);**

   Feature Test Macro Requirements for glibc (see
   [feature_test_macros(7)](https://man7.org/linux/man-pages/man7/feature_test_macros.7.html)):

       **wait3**():
           Since glibc 2.26:
               _DEFAULT_SOURCE
                   || (_XOPEN_SOURCE >= 500 &&
                       ! (_POSIX_C_SOURCE >= 200112L
                          || _XOPEN_SOURCE >= 600))
           From glibc 2.19 to 2.25:
               _DEFAULT_SOURCE || _XOPEN_SOURCE >= 500
           Glibc 2.19 and earlier:
               _BSD_SOURCE || _XOPEN_SOURCE >= 500

       **wait4**():
           Since glibc 2.19:
               _DEFAULT_SOURCE
           Glibc 2.19 and earlier:
               _BSD_SOURCE

## []DESCRIPTION         

       These functions are nonstandard; in new programs, the use of
       [waitpid(2)](https://man7.org/linux/man-pages/man2/waitpid.2.html) or [waitid(2)](https://man7.org/linux/man-pages/man2/waitid.2.html) is preferable.

       The **wait3**() and **wait4**() system calls are similar to [waitpid(2)](https://man7.org/linux/man-pages/man2/waitpid.2.html),
       but additionally return resource usage information about the
       child in the structure pointed to by _rusage_.

       Other than the use of the _rusage_ argument, the following **wait3**()
       call:

           wait3(wstatus, options, rusage);

       is equivalent to:

           waitpid(-1, wstatus, options);

       Similarly, the following **wait4**() call:

           wait4(pid, wstatus, options, rusage);

       is equivalent to:

           waitpid(pid, wstatus, options);

       In other words, **wait3**() waits of any child, while **wait4**() can be
       used to select a specific child, or children, on which to wait.
       See [wait(2)](https://man7.org/linux/man-pages/man2/wait.2.html) for further details.

       If _rusage_ is not NULL, the _struct rusage_ to which it points will
       be filled with accounting information about the child.  See
       [getrusage(2)](https://man7.org/linux/man-pages/man2/getrusage.2.html) for details.

## []RETURN VALUE       

       As for [waitpid(2)](https://man7.org/linux/man-pages/man2/waitpid.2.html).

## []ERRORS        

       As for [waitpid(2)](https://man7.org/linux/man-pages/man2/waitpid.2.html).

## []CONFORMING TO        

       4.3BSD.

       SUSv1 included a specification of **wait3**(); SUSv2 included
       **wait3**(), but marked it LEGACY; SUSv3 removed it.

## []NOTES      

       Including _<sys/time.h>_ is not required these days, but increases
       portability.  (Indeed, _<sys/resource.h>_ defines the _rusage_
       structure with fields of type _struct timeval_ defined in
       _<sys/time.h>_.)

   **C library/kernel differences**
       On Linux, **wait3**() is a library function implemented on top of the
       **wait4**() system call.

## []SEE ALSO       

       [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html), [getrusage(2)](https://man7.org/linux/man-pages/man2/getrusage.2.html), [sigaction(2)](https://man7.org/linux/man-pages/man2/sigaction.2.html), [signal(2)](https://man7.org/linux/man-pages/man2/signal.2.html), [wait(2)](https://man7.org/linux/man-pages/man2/wait.2.html),
       [signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)

## []COLOPHON      

       This page is part of release 5.13 of the Linux _man-pages_ project.
       A description of the project, information about reporting bugs,
       and the latest version of this page, can be found at
       [https://www.kernel.org/doc/man-pages/](https://www.kernel.org/doc/man-pages/).