Send signal to processes
## NAME         

       kill - send signal to a process

## []SYNOPSIS         

       **#include <signal.h>**

       **int kill(pid_t** _pid_**, int** _sig_**);**

   Feature Test Macro Requirements for glibc (see
   [feature_test_macros(7)](https://man7.org/linux/man-pages/man7/feature_test_macros.7.html)):

       **kill**():
           _POSIX_C_SOURCE

## []DESCRIPTION         

       The **kill**() system call can be used to send any signal to any
       process group or process.

       If _pid_ is positive, then signal _sig_ is sent to the process with
       the ID specified by _pid_.

       If _pid_ equals 0, then _sig_ is sent to every process in the process
       group of the calling process.

       If _pid_ equals -1, then _sig_ is sent to every process for which the
       calling process has permission to send signals, except for
       process 1 (_init_), but see below.

       If _pid_ is less than -1, then _sig_ is sent to every process in the
       process group whose ID is _-pid_.

       If _sig_ is 0, then no signal is sent, but existence and permission
       checks are still performed; this can be used to check for the
       existence of a process ID or process group ID that the caller is
       permitted to signal.

       For a process to have permission to send a signal, it must either
       be privileged (under Linux: have the **CAP_KILL** capability in the
       user namespace of the target process), or the real or effective
       user ID of the sending process must equal the real or saved set-
       user-ID of the target process.  In the case of **SIGCONT**, it
       suffices when the sending and receiving processes belong to the
       same session.  (Historically, the rules were different; see
       NOTES.)

## []RETURN VALUE         

       On success (at least one signal was sent), zero is returned.  On
       error, -1 is returned, and _[errno](https://man7.org/linux/man-pages/man3/errno.3.html)_ is set to indicate the error.

## []ERRORS         

       **EINVAL** An invalid signal was specified.

       **EPERM** The calling process does not have permission to send the
              signal to any of the target processes.

       **ESRCH** The target process or process group does not exist.  Note
              that an existing process might be a zombie, a process that
              has terminated execution, but has not yet been [wait(2)](https://man7.org/linux/man-pages/man2/wait.2.html)ed
              for.

## []CONFORMING TO         

       POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.

## []NOTES         

       The only signals that can be sent to process ID 1, the _init_
       process, are those for which _init_ has explicitly installed signal
       handlers.  This is done to assure the system is not brought down
       accidentally.

       POSIX.1 requires that _kill(-1,sig)_ send _sig_ to all processes that
       the calling process may send signals to, except possibly for some
       implementation-defined system processes.  Linux allows a process
       to signal itself, but on Linux the call _kill(-1,sig)_ does not
       signal the calling process.

       POSIX.1 requires that if a process sends a signal to itself, and
       the sending thread does not have the signal blocked, and no other
       thread has it unblocked or is waiting for it in [sigwait(3)](https://man7.org/linux/man-pages/man3/sigwait.3.html), at
       least one unblocked signal must be delivered to the sending
       thread before the **kill**() returns.

   **Linux notes**
       Across different kernel versions, Linux has enforced different
       rules for the permissions required for an unprivileged process to
       send a signal to another process.  In kernels 1.0 to 1.2.2, a
       signal could be sent if the effective user ID of the sender
       matched effective user ID of the target, or the real user ID of
       the sender matched the real user ID of the target.  From kernel
       1.2.3 until 1.3.77, a signal could be sent if the effective user
       ID of the sender matched either the real or effective user ID of
       the target.  The current rules, which conform to POSIX.1, were
       adopted in kernel 1.3.78.

## []BUGS         

       In 2.6 kernels up to and including 2.6.7, there was a bug that
       meant that when sending signals to a process group, **kill**() failed
       with the error **EPERM** if the caller did not have permission to
       send the signal to _any_ (rather than _all_) of the members of the
       process group.  Notwithstanding this error return, the signal was
       still delivered to all of the processes for which the caller had
       permission to signal.

## []SEE ALSO         

       [kill(1)](https://man7.org/linux/man-pages/man1/kill.1.html), [_exit(2)](https://man7.org/linux/man-pages/man2/_exit.2.html), [pidfd_send_signal(2)](https://man7.org/linux/man-pages/man2/pidfd_send_signal.2.html), [signal(2)](https://man7.org/linux/man-pages/man2/signal.2.html), [tkill(2)](https://man7.org/linux/man-pages/man2/tkill.2.html),
       [exit(3)](https://man7.org/linux/man-pages/man3/exit.3.html), [killpg(3)](https://man7.org/linux/man-pages/man3/killpg.3.html), [sigqueue(3)](https://man7.org/linux/man-pages/man3/sigqueue.3.html), [capabilities(7)](https://man7.org/linux/man-pages/man7/capabilities.7.html), [credentials(7)](https://man7.org/linux/man-pages/man7/credentials.7.html),
       [signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)