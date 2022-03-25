      

**Minishell**

  

- [x] stat 

**how to obtain file status information for a file.**

[https://codeforwin.org/2018/03/c-program-find-file-properties-using-stat-function.html](https://codeforwin.org/2018/03/c-program-find-file-properties-using-stat-function.html)

**int stat(const char *path, struct stat *buf);**

stat() function is used to list properties of a file identified by path. It reads all file properties and dumps to buf structure. The function is defined in sys/stat.h header file.

Here *path is a [pointer to constant](https://codeforwin.org/2017/11/constant-pointer-and-pointer-to-constant-in-c.html) character pointing to file path. *buf is a stat type structure defined in sys/stat.h.

On success the function returns 0 and fills the buf structure with file properties. On error the function return -1 and sets error code. You can use this function to get various properties of a file.

  

- [x] lstat

The _lstat_() function shall be equivalent to [_stat_()](https://pubs.opengroup.org/onlinepubs/007904875/functions/stat.html), except when _path_ refers to a symbolic link. In that case _lstat_() shall return information about the link, while [_stat_()](https://pubs.opengroup.org/onlinepubs/007904875/functions/stat.html) shall return information about the file the link references.

[https://pubs.opengroup.org/onlinepubs/007904875/functions/lstat.html](https://pubs.opengroup.org/onlinepubs/007904875/functions/lstat.html)

  

- [x] fstat 

is used to get the status of the file. By status we mean all the useful information related to the file.

int fstat(int fd, struct stat *buf);

[https://www.go4expert.com/articles/understanding-linux-fstat-example-t27449/](https://www.go4expert.com/articles/understanding-linux-fstat-example-t27449/)

  

- [x] signal , 

[https://www.delftstack.com/fr/howto/c/sigint-in-c/](https://www.delftstack.com/fr/howto/c/sigint-in-c/)

SIGINT est l’un des signaux prédéfinis associés au caractère d’interruption du terminal (généralement Ctrl+C). Cela oblige le shell à arrêter le processus en cours et à revenir à sa boucle principale, affichant une nouvelle invite de commande à l’utilisateur

  

Notez que write est utilisé à la place de printf car le code du gestionnaire de signaux ne doit pas appeler des fonctions non réentrantes qui modifient les données globales du programme sous le capot. 

  

-[x] sigaction 

pour enregistrer les gestionnaires de signaux.

Il offre beaucoup plus d’options par rapport à l’appel signal, mais il fournit également des fonctionnalités de base qui sont nécessaires pour tout cas d’utilisation sérieux des signaux. sigaction prend des arguments spéciaux struct sigaction pour spécifier le pointeur de la fonction du gestionnaire et d’autres indicateurs avec lui.

  

- [x] isatty 

**Identifying whether a file descriptor is associated with a terminal** 

One common example is when a command interpreter has to issue prompts to the user. In that case, it is useful to know if the input is coming from the terminal or from a file or pipe. Another example is when the output might be formatted differently for a terminal, such as generating multi-column output or printing a header. The _ls_ command is an example of such behavior, where it generates multi-column output on a terminal but single-column output for a file. One may argue that this is bad design since the user does not have direct feedback on what the output would look like when piped to another command or saved to a file. 

[https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/isatty.html](https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/isatty.html)

  

  

- [x] ttyname, ttyslot, 

The _ttyname()_ function obtains the name of a terminal

char *ttyname(int fd);

The value returned from _ttyname()_ is a string representing terminal’s pathname.

[https://c-for-dummies.com/blog/?p=4385](https://c-for-dummies.com/blog/?p=4385)

  

**int ttyslot(void);**

returns the index of the current user's entry in some file

[https://man7.org/linux/man-pages/man3/ttyslot.3.html](https://man7.org/linux/man-pages/man3/ttyslot.3.html)

If successful, this function returns the slot number. On error

 (e.g., if none of the file descriptors 0, 1, or 2 is associated

 with a terminal that occurs in this data base) it returns 0

  

- [x] ioctl 

(an abbreviation of **input/output control**) is a [system call](https://en.wikipedia.org/wiki/System_call) for device-specific [input/output](https://en.wikipedia.org/wiki/Input/output) operations and other operations which cannot be expressed by regular system calls. For instance, a CD-ROM [device driver](https://en.wikipedia.org/wiki/Device_driver) which can instruct a physical device to eject a disc would provide an ioctl request code to do so. 

**#include <sys/ioctl.h>**

**int ioctl(int** _d_**, int** _request_**, ...);** 

[https://www.tutorialspoint.com/unix_system_calls/ioctl.htm](https://www.tutorialspoint.com/unix_system_calls/ioctl.htm)

  

- [x] getenv 

Great tool to get the “PATH” in the local environment.

#include <stdlib.h>

  

char *getenv(const char *varname);

Searches the table of environment variables for an entry corresponding to varname and returns a pointer to a buffer containing the current string value of varname.

[https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-getenv-get-value-environment-variables](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-getenv-get-value-environment-variables)

  

[https://www.oreilly.com/library/view/c-in-a/0596006977/re105.html](https://www.oreilly.com/library/view/c-in-a/0596006977/re105.html)

  

- [ ] tcsetattr, tcgetattr 

If trying to change baud rates, applications should call _tcsetattr_() then call [_tcgetattr_()](https://pubs.opengroup.org/onlinepubs/009696799/functions/tcgetattr.html) in order to determine what baud rates were actually selected.

  

#include <[termios.h](https://pubs.opengroup.org/onlinepubs/009696799/basedefs/termios.h.html)>

  

int tcsetattr(int _fd_, int _optional_actions_,

       const struct termios *_termios_p_);

[https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-tcsetattr-set-attributes-terminal](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-tcsetattr-set-attributes-terminal)

  

- [ ] tgetent, tgetflag, tgetnum, tgetstr 

- [ ] tgoto, tputs

  

[https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_2.html](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_2.html)

  

The termcap library is the application programmer's interface to the termcap data base. It contains functions for the following purposes: 

-   Finding the description of the user's terminal type (tgetent). 
-   Interrogating the description for information on various topics (tgetnum, tgetflag, tgetstr). 
-   Computing and performing padding (tputs). 
-   Encoding numeric parameters such as cursor positions into the terminal-specific form required for display commands (tparam, tgoto). 

**Those will be use for exemple to control the display of <ctrl+c> in my Minishell**