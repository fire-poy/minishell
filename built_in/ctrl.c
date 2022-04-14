#include "../minishell.h"

void  INThandler(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "yo\n", 1);
}

// int  main(void)
// {
//      signal(SIGINT, INThandler);
// 		 signal(SIGQUIT, INThandler);
//      while (1)
//           pause();
//      return 0;
// }

    //  2     SIGINT       terminate process    interrupt program
    //  3     SIGQUIT      create core image    quit program

		// The sig argument specifies which signal was received.  The func procedure allows a user to choose the action upon receipt of a signal.  
		// To set the default action of the signal to occur as listed above,
    //  func should be SIG_DFL.  A SIG_DFL resets the default action.  
		// To ignore the signal, func should be SIG_IGN.  This will cause subsequent instances of the signal to be ignored and pending instances to be
    //  discarded.  If SIG_IGN is not used, further occurrences of the signal are automatically blocked and func is called.