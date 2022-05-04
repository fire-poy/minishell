#include "../minishell.h"

int	redirect_in_bi(t_info *info, int i)
{
	t_token	*tk;
	int		fd_in;
	// int		last_in;

	tk = info->tk;
	while (tk && tk->cmd_index <= i)
	{
		if (tk->type == IN_FILE && tk->cmd_index == i)
		{
			fd_in = open(tk->content, O_RDONLY, 0644);
			if (fd_in == -1)
			{
				perror("Error: open() failed");
				info->exit_status = 1;
				return (0);
			}
			close(fd_in);
		}
		if (tk->type == HEREDOC && tk->cmd_index == i)
		{
			// if (last_in == tk->in_index)
				fd_in = get_heredoc_fd(i);
		}
		tk = tk->next;
	}
	return (1);
}

// return fd_out
int	redirect_out_bi(t_info *info, int i)
{
	t_token	*tk;
	int		fd_out;
	int		last_out;

	tk = info->tk;
	last_out = find_last_out(tk, i);
	while (tk)
	{
		if (tk->type == OUT_FILE && tk->cmd_index == i)
		{
			fd_out = open(tk->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (last_out == tk->out_index)
				break ;
			else
				close(fd_out);
		}
		if (tk->type == APPEND && tk->cmd_index == i)
		{
			fd_out = open(tk->content, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (last_out == tk->out_index)
				break ;
			else
				close(fd_out);
		}
		tk = tk->next;
	}
	return (fd_out);
}

// changer fd_in info?
int	redirect_in_out_bi(t_info *info, int i)
{
	int	fd_in;
	int	fd_out;
	int	last_cmd;

	last_cmd = info->cmd_i;
	if (get_q_in(info->tk, i) > 0)
	{
		fd_in = redirect_in_bi(info, i);
		if (fd_in == 0)
			return (0);
	}
	if (get_q_out(info->tk, i) > 0)
	{
		fd_out = redirect_out_bi(info, i);
			return (fd_out);
	}
	return (1);
}
