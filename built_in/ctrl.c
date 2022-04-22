#include "../minishell.h"

void	signal_h(int signal)
{
	struct termios	new;

	if (signal == SIGINT)
	{
		//printf("\n");
		write(1, "\nMinishell ~ ", 13);
	}
	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}
// void	ft_INThandler(int sig)
// {
// 	(void)sig;
// 	signal(SIGILL, ft_INThandler);
// 	g_exit_status = 0;
// }
	// int	i;

	// i = getpid();
	// kill(i, sig);
	// if (sig == 3)
	// 	write(1, "\nQuit\n", 6);
	// else
	// 	write(1, "\n", 1);
	// signal(SIGQUIT, ft_INThandler);
	// write(1, "\nctrl\n", 6);
	// fflush(stdout);
	// printf("getpid = %d\n", getpid());
	// if (sig == 2)
	// {
	// 	write(1, "\nMinishell > ", 13);
	// 	fflush(stdout);
	// }
	// if (sig == 3)
	// {
	// 	//write(1, "\nMinishell > ", 14);
	// 	write(1, "\nctrld = sig3", 13);
	// 	exit (0);
	// }
// 	else
// 	{
// 		fflush(stdout);
// 		exit(0);
// 	}
// }

// int  main(void)
// {
//   signal(SIGINT, INThandler);
// 	signal(SIGQUIT, INThandler);
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