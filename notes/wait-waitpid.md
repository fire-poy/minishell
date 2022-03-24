# wait(3) - Linux man page

## Prolog

This manual page is part of the POSIX Programmer's Manual. The Linux implementation of this interface may differ (consult the corresponding Linux manual page for details of Linux behavior), or the interface may not be implemented on Linux.

## Name

wait, waitpid - wait for a child process to stop or terminate

## Synopsis

**#include <[sys/wait.h](https://linux.die.net/include/sys/wait.h)>  
**

pid_t wait(int *_stat_loc_**);  
**pid_t waitpid(pid_t _pid_**, int ***_stat_loc_**, int** _options_**);  
**

## Description

The _wait_() and _waitpid_() functions shall obtain status information pertaining to one of the caller's child processes. Various options permit status information to be obtained for child processes that have terminated or stopped. If status information is available for two or more child processes, the order in which their status is reported is unspecified.

The _wait_() function shall suspend execution of the calling thread until status information for one of the terminated child processes of the calling process is available, or until delivery of a signal whose action is either to execute a signal-catching function or to terminate the process. If more than one thread is suspended in _wait_() or _waitpid_() awaiting termination of the same process, exactly one thread shall return the process status at the time of the target process termination. If status information is available prior to the call to _wait_(), return shall be immediate.

The _waitpid_() function shall be equivalent to _wait_() if the _pid_ argument is (**pid_t**)-1 and the _options_ argument is 0. Otherwise, its behavior shall be modified by the values of the _pid_ and _options_ arguments.

The _pid_ argument specifies a set of child processes for which _status_ is requested. The _waitpid_() function shall only return the status of a child process from this set:

*

If _pid_ is equal to (**pid_t**)-1, _status_ is requested for any child process. In this respect, _waitpid_() is then equivalent to _wait_().

*

If _pid_ is greater than 0, it specifies the process ID of a single child process for which _status_ is requested.

*

If _pid_ is 0, _status_ is requested for any child process whose process group ID is equal to that of the calling process.

*

If _pid_ is less than (**pid_t**)-1, _status_ is requested for any child process whose process group ID is equal to the absolute value of _pid_.

The _options_ argument is constructed from the bitwise-inclusive OR of zero or more of the following flags, defined in the _<[sys/wait.h](https://linux.die.net/include/sys/wait.h)>_ header:

WCONTINUED

The _waitpid_() function shall report the status of any continued child process specified by _pid_ whose status has not been reported since it continued from a job control stop.

WNOHANG

The _waitpid_() function shall not suspend execution of the calling thread if _status_ is not immediately available for one of the child processes specified by _pid_.

WUNTRACED

The status of any child processes specified by _pid_ that are stopped, and whose status has not yet been reported since they stopped, shall also be reported to the requesting process.

If the calling process has SA_NOCLDWAIT set or has SIGCHLD set to SIG_IGN, and the process has no unwaited-for children that were transformed into zombie processes, the calling thread shall block until all of the children of the process containing the calling thread terminate, and _wait_() and _waitpid_() shall fail and set _errno_ to [ECHILD].

If _wait_() or _waitpid_() return because the status of a child process is available, these functions shall return a value equal to the process ID of the child process. In this case, if the value of the argument _stat_loc_ is not a null pointer, information shall be stored in the location pointed to by _stat_loc_. The value stored at the location pointed to by _stat_loc_ shall be 0 if and only if the status returned is from a terminated child process that terminated by one of the following means:

1.

The process returned 0 from _main_().

2.

The process called __exit_() or _exit_() with a _status_ argument of 0.

3.

The process was terminated because the last thread in the process terminated.

Regardless of its value, this information may be interpreted using the following macros, which are defined in _<[sys/wait.h](https://linux.die.net/include/sys/wait.h)>_ and evaluate to integral expressions; the _stat_val_ argument is the integer value pointed to by _stat_loc_.

WIFEXITED(_stat_val_)

Evaluates to a non-zero value if _status_ was returned for a child process that terminated normally.

WEXITSTATUS(_stat_val_)

If the value of WIFEXITED(_stat_val_) is non-zero, this macro evaluates to the low-order 8 bits of the _status_ argument that the child process passed to __exit_() or _exit_(), or the value the child process returned from _main_().

WIFSIGNALED(_stat_val_)

Evaluates to a non-zero value if _status_ was returned for a child process that terminated due to the receipt of a signal that was not caught (see _<[signal.h](https://linux.die.net/include/signal.h)>_).

WTERMSIG(_stat_val_)

If the value of WIFSIGNALED(_stat_val_) is non-zero, this macro evaluates to the number of the signal that caused the termination of the child process.

WIFSTOPPED(_stat_val_)

Evaluates to a non-zero value if _status_ was returned for a child process that is currently stopped.

WSTOPSIG(_stat_val_)

If the value of WIFSTOPPED(_stat_val_) is non-zero, this macro evaluates to the number of the signal that caused the child process to stop.

WIFCONTINUED(_stat_val_)

Evaluates to a non-zero value if _status_ was returned for a child process that has continued from a job control stop.

It is unspecified whether the _status_ value returned by calls to _wait_() or _waitpid_() for processes created by _posix_spawn_() or _posix_spawnp_() can indicate a WIFSTOPPED(_stat_val_) before subsequent calls to _wait_() or _waitpid_() indicate WIFEXITED(_stat_val_) as the result of an error detected before the new process image starts executing.

It is unspecified whether the _status_ value returned by calls to _wait_() or _waitpid_() for processes created by _posix_spawn_() or _posix_spawnp_() can indicate a WIFSIGNALED(_stat_val_) if a signal is sent to the parent's process group after _posix_spawn_() or _posix_spawnp_() is called.

If the information pointed to by _stat_loc_ was stored by a call to _waitpid_() that specified the WUNTRACED flag and did not specify the WCONTINUED flag, exactly one of the macros WIFEXITED(*_stat_loc_), WIFSIGNALED(*_stat_loc_), and WIFSTOPPED(*_stat_loc_) shall evaluate to a non-zero value.

If the information pointed to by _stat_loc_ was stored by a call to _waitpid_() that specified the WUNTRACED and WCONTINUED flags, exactly one of the macros WIFEXITED(*_stat_loc_), WIFSIGNALED(*_stat_loc_), WIFSTOPPED(*_stat_loc_), and WIFCONTINUED(*_stat_loc_) shall evaluate to a non-zero value.

If the information pointed to by _stat_loc_ was stored by a call to _waitpid_() that did not specify the WUNTRACED or WCONTINUED flags, or by a call to the _wait_() function, exactly one of the macros WIFEXITED(*_stat_loc_) and WIFSIGNALED(*_stat_loc_) shall evaluate to a non-zero value.

If the information pointed to by _stat_loc_ was stored by a call to _waitpid_() that did not specify the WUNTRACED flag and specified the WCONTINUED flag, or by a call to the _wait_() function, exactly one of the macros WIFEXITED(*_stat_loc_), WIFSIGNALED(*_stat_loc_), and WIFCONTINUED(*_stat_loc_) shall evaluate to a non-zero value.

If _POSIX_REALTIME_SIGNALS is defined, and the implementation queues the SIGCHLD signal, then if _wait_() or _waitpid_() returns because the status of a child process is available, any pending SIGCHLD signal associated with the process ID of the child process shall be discarded. Any other pending SIGCHLD signals shall remain pending.

Otherwise, if SIGCHLD is blocked, if _wait_() or _waitpid_() return because the status of a child process is available, any pending SIGCHLD signal shall be cleared unless the status of another child process is available.

For all other conditions, it is unspecified whether child _status_ will be available when a SIGCHLD signal is delivered.

There may be additional implementation-defined circumstances under which _wait_() or _waitpid_() report _status_. This shall not occur unless the calling process or one of its child processes explicitly makes use of a non-standard extension. In these cases the interpretation of the reported _status_ is implementation-defined.

If a parent process terminates without waiting for all of its child processes to terminate, the remaining child processes shall be assigned a new parent process ID corresponding to an implementation-defined system process.

## Return Value

If _wait_() or _waitpid_() returns because the status of a child process is available, these functions shall return a value equal to the process ID of the child process for which _status_ is reported. If _wait_() or _waitpid_() returns due to the delivery of a signal to the calling process, -1 shall be returned and _errno_ set to [EINTR]. If _waitpid_() was invoked with WNOHANG set in _options_, it has at least one child process specified by _pid_ for which _status_ is not available, and _status_ is not available for any process specified by _pid_, 0 is returned. Otherwise, (**pid_t**)-1 shall be returned, and _errno_ set to indicate the error.

## Errors

The _wait_() function shall fail if:

**ECHILD**

The calling process has no existing unwaited-for child processes.

**EINTR**

The function was interrupted by a signal. The value of the location pointed to by _stat_loc_ is undefined.

The _waitpid_() function shall fail if:

**ECHILD**

The process specified by _pid_ does not exist or is not a child of the calling process, or the process group specified by _pid_ does not exist or does not have any member process that is a child of the calling process.

**EINTR**

The function was interrupted by a signal. The value of the location pointed to by _stat_loc_ is undefined.

**EINVAL**

The _options_ argument is not valid.

_The following sections are informative._

## Examples

None.

## Application Usage

None.

## Rationale

A call to the _wait_() or _waitpid_() function only returns _status_ on an immediate child process of the calling process; that is, a child that was produced by a single _fork_() call (perhaps followed by an _exec_ or other function calls) from the parent. If a child produces grandchildren by further use of _fork_(), none of those grandchildren nor any of their descendants affect the behavior of a _wait_() from the original parent process. Nothing in this volume of IEEE Std 1003.1-2001 prevents an implementation from providing extensions that permit a process to get _status_ from a grandchild or any other process, but a process that does not use such extensions must be guaranteed to see _status_ from only its direct children.

The _waitpid_() function is provided for three reasons:

1.

To support job control

2.

To permit a non-blocking version of the _wait_() function

3.

To permit a library routine, such as _system_() or _pclose_(), to wait for its children without interfering with other terminated children for which the process has not waited

The first two of these facilities are based on the _wait3_() function provided by 4.3 BSD. The function uses the _options_ argument, which is equivalent to an argument to _wait3_(). The WUNTRACED flag is used only in conjunction with job control on systems supporting job control. Its name comes from 4.3 BSD and refers to the fact that there are two types of stopped processes in that implementation: processes being traced via the _ptrace_() debugging facility and (untraced) processes stopped by job control signals. Since _ptrace_() is not part of this volume of IEEE Std 1003.1-2001, only the second type is relevant. The name WUNTRACED was retained because its usage is the same, even though the name is not intuitively meaningful in this context.

The third reason for the _waitpid_() function is to permit independent sections of a process to spawn and wait for children without interfering with each other. For example, the following problem occurs in developing a portable shell, or command interpreter:

> stream = popen("/bin/true");
> (void) system("sleep 100");
> (void) pclose(stream);

On all historical implementations, the final _pclose_() fails to reap the _wait_() _status_ of the _popen_().

The status values are retrieved by macros, rather than given as specific bit encodings as they are in most historical implementations (and thus expected by existing programs). This was necessary to eliminate a limitation on the number of signals an implementation can support that was inherent in the traditional encodings. This volume of IEEE Std 1003.1-2001 does require that a _status_ value of zero corresponds to a process calling **_exit**(0), as this is the most common encoding expected by existing programs. Some of the macro names were adopted from 4.3 BSD.

These macros syntactically operate on an arbitrary integer value. The behavior is undefined unless that value is one stored by a successful call to _wait_() or _waitpid_() in the location pointed to by the _stat_loc_ argument. An early proposal attempted to make this clearer by specifying each argument as *_stat_loc_ rather than _stat_val_. However, that did not follow the conventions of other specifications in this volume of IEEE Std 1003.1-2001 or traditional usage. It also could have implied that the argument to the macro must literally be *_stat_loc_; in fact, that value can be stored or passed as an argument to other functions before being interpreted by these macros.

The extension that affects _wait_() and _waitpid_() and is common in historical implementations is the _ptrace_() function. It is called by a child process and causes that child to stop and return a _status_ that appears identical to the _status_ indicated by WIFSTOPPED. The _status_ of _ptrace_() children is traditionally returned regardless of the WUNTRACED flag (or by the _wait_() function). Most applications do not need to concern themselves with such extensions because they have control over what extensions they or their children use. However, applications, such as command interpreters, that invoke arbitrary processes may see this behavior when those arbitrary processes misuse such extensions.

Implementations that support **core** file creation or other implementation-defined actions on termination of some processes traditionally provide a bit in the _status_ returned by _wait_() to indicate that such actions have occurred.

Allowing the _wait_() family of functions to discard a pending SIGCHLD signal that is associated with a successfully waited-for child process puts them into the _sigwait_() and _sigwaitinfo_() category with respect to SIGCHLD.

This definition allows implementations to treat a pending SIGCHLD signal as accepted by the process in _wait_(), with the same meaning of "accepted" as when that word is applied to the _sigwait_() family of functions.

Allowing the _wait_() family of functions to behave this way permits an implementation to be able to deal precisely with SIGCHLD signals.

In particular, an implementation that does accept (discard) the SIGCHLD signal can make the following guarantees regardless of the queuing depth of signals in general (the list of waitable children can hold the SIGCHLD queue):

1.

If a SIGCHLD signal handler is established via _sigaction_() without the SA_RESETHAND flag, SIGCHLD signals can be accurately counted; that is, exactly one SIGCHLD signal will be delivered to or accepted by the process for every child process that terminates.

2.

A single _wait_() issued from a SIGCHLD signal handler can be guaranteed to return immediately with status information for a child process.

3.

When SA_SIGINFO is requested, the SIGCHLD signal handler can be guaranteed to receive a non-NULL pointer to a **siginfo_t** structure that describes a child process for which a wait via _waitpid_() or _waitid_() will not block or fail.

4.

The _system_() function will not cause a process' SIGCHLD handler to be called as a result of the _fork_()/ _exec_ executed within _system_() because _system_() will accept the SIGCHLD signal when it performs a _waitpid_() for its child process. This is a desirable behavior of _system_() so that it can be used in a library without causing side effects to the application linked with the library.

An implementation that does not permit the _wait_() family of functions to accept (discard) a pending SIGCHLD signal associated with a successfully waited-for child, cannot make the guarantees described above for the following reasons:

Guarantee #1

Although it might be assumed that reliable queuing of all SIGCHLD signals generated by the system can make this guarantee, the counter-example is the case of a process that blocks SIGCHLD and performs an indefinite loop of _fork_()/ _wait_() operations. If the implementation supports queued signals, then eventually the system will run out of memory for the queue. The guarantee cannot be made because there must be some limit to the depth of queuing.

Guarantees #2 and #3

These cannot be guaranteed unless the _wait_() family of functions accepts the SIGCHLD signal. Otherwise, a _fork_()/ _wait_() executed while SIGCHLD is blocked (as in the _system_() function) will result in an invocation of the handler when SIGCHLD is unblocked, after the process has disappeared.

Guarantee #4

Although possible to make this guarantee, _system_() would have to set the SIGCHLD handler to SIG_DFL so that the SIGCHLD signal generated by its _fork_() would be discarded (the SIGCHLD default action is to be ignored), then restore it to its previous setting. This would have the undesirable side effect of discarding all SIGCHLD signals pending to the process.

## Future Directions

None.

## See Also

_exec_(), _exit_(), _fork_(), _waitid_(), the Base Definitions volume of IEEE Std 1003.1-2001, _<[signal.h](https://linux.die.net/include/signal.h)>_, _<[sys/wait.h](https://linux.die.net/include/sys/wait.h)>_