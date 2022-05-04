#include "../minishell.h"


void	signal_q(int sig)
{
	int	i;
	int	res;

	i = 0;
	res = kill(g_pid[i], sig);
	if (res == 0)
	{
		if (sig == 2)
			write(1, "^C\n", 4);
		else if (sig == 3)
			write(1, "^\\Quit: 3\n", 11);
	}
	else if (res == -1)
	{
		if (sig == 2)
			write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_here(int signal)
{
	if (signal == SIGINT)
	{
		g_pid[8] = 6;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line(": heredoc : >> press enter to exit <<", 30);
		rl_redisplay();
	}
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

void	ft_stop(char *input, int last_exit)
{
	if (input == 0)
	{
		write(1, "exit\n", 5);
		exit(last_exit);
	}
}

void	ft_stop2(char *input)
{
	if (input == 0)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
