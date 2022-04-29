#include "../minishell.h"

pid_t	g_pid[255];

void	ft_get_pid(int id)
{
	if (id != 0)
	{
		g_pid[0] = id;
	}
}

void	signal_q(int sig)
{
	int	i;
	int	res;

	i = 0;
	res = kill(g_pid[i], sig);
	if (res == 0)
	{
		if (sig == 2)
		{
			write(1, "^C\n", 3);
		}
		else if (sig == 3)
		{
			write(1, "^\\Quit: 3\n", 11);
		}
	}
	else if (res == -1)
	{
		if (sig == 2)
		{
			write(1, "\n", 2);
		}
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_here(int signal)
{
	int a = -1;
	if (signal == SIGINT)
		write(0, &a, 1);
		//ilfaut write meme signaux de ctrl+D
}

void	signal_h(int signal)
{
	struct termios	save;

	tcgetattr(0, &save);
	save.c_lflag &= ~ECHOCTL;
	if (signal == 2)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	tcsetattr(0, TCSANOW, &save);
}

void	signal_2(int signal)
{
	struct termios	save;

	tcgetattr(0, &save);
	save.c_lflag &= ~ECHOCTL;
	if (signal == 2)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	tcsetattr(0, TCSANOW, &save);
}

void	ft_stop(char *input)
{
		if (input == 0)
		{
			write(1, "exit\n", 5);
			exit(1);
		}
}

void	ft_stop2(char *input)
{
		if (input == 0)
		{
			write(1, "^D", 2);
			exit(1);
		}
}

    //  2     SIGINT       terminate process    interrupt program
    //  3     SIGQUIT      create core image    quit program

		// The sig argument specifies which signal was received.  The func procedure allows a user to choose the action upon receipt of a signal.  
		// To set the default action of the signal to occur as listed above,
    //  func should be SIG_DFL.  A SIG_DFL resets the default action.  
		// To ignore the signal, func should be SIG_IGN.  This will cause subsequent instances of the signal to be ignored and pending instances to be
    //  discarded.  If SIG_IGN is not used, further occurrences of the signal are automatically blocked and func is called.