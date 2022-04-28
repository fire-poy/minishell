#include "../minishell.h"

int	redirect_in(t_info *info, int i)
{
	t_token *tk;
	int	fd_in;
	int	last_in;

	tk = info->tk;
	last_in = find_last_in(tk, i);
	while (tk && tk->cmd_index <= i)
	{
		if (tk->type == IN_FILE && tk->cmd_index == i)
		{
			fd_in = open(tk->content, O_RDONLY, 0644);
			if (fd_in == -1)
			{
				perror("Error: open() failed");
				exit(1);
			}
			if (last_in == tk->in_index)
				break;
			close(fd_in);
		}
		if (tk->type == HEREDOC && tk->cmd_index == i)
		{
			if (last_in == tk->in_index)
				fd_in = get_heredoc_fd(i);
		}
		tk = tk->next;
	}
	return (fd_in);
}

// return fd_out
int	redirect_out(t_info *info, int i)
{
	t_token *tk;
	int	fd_out;
	int	last_out;

	tk = info->tk;
	last_out = find_last_out(tk, i);
	while (tk)
	{
		if (tk->type == OUT_FILE && tk->cmd_index == i)
		{
		    fd_out = open(tk->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			// printf("last_out = %d\n", last_out);
			if (last_out == tk->out_index)
				break;
			else
				close(fd_out);
		}
		if (tk->type == APPEND && tk->cmd_index == i)
		{
			fd_out = open(tk->content, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (last_out == tk->out_index)
				break;
			else
				close(fd_out);
		}
		tk = tk->next;
	}
	return (fd_out);
}

// changer fd_in info?
void	redirect_in_out(t_info *info, int i)
{
	int fd_in;
	int fd_out;
	int last_cmd;

	last_cmd = info->cmd_i;
	// printf("q_in = %d\n", get_q_in(info->tk, i));
	if (get_q_in(info->tk, i) > 0)//si redir on le fait
	{
		fd_in =	redirect_in(info, i);
		dup2(fd_in, STDIN_FILENO);
		close (fd_in);
	}
	else if (info->q_cmd > 1 && i != 0) //sinon si
	{
		dup2(info->pipes[i - 1][0], STDIN_FILENO);
		// printf("HOLAAAAA soy cmd:%d\n", i);
	}
	if (get_q_out(info->tk, i) > 0)
	{
		fd_out = redirect_out(info, i);
		dup2(fd_out, STDOUT_FILENO);
		close (fd_out);
	}
	else if (info->q_cmd > 1 && i != last_cmd) //if not the last cmd => 
		dup2(info->pipes[i][1], STDOUT_FILENO);
}

/*
void	here_doc(char *argv, t_ppxb *pipex)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		msg_error(ERR_HEREDOC);
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &buf) < 0)
			exit(1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	pipex->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile < 0)
	{
		unlink(".heredoc_tmp");
		msg_error(ERR_HEREDOC);
	}
}
/ heredoc = ft_strjoin(heredoc, line);
	// char	*heredoc;
	// heredoc = NULL;
// char	*get_heredoc(char *flag, int i)
// {
// 	char	*line;
// 	int		len;
// 	int		file;

// 	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (file < 0)
// 		msg_error(ERR_HEREDOC);
// 	len = ft_strlen(flag);
// 	while (1)
// 	{
// 		// ft_putstrl_fd(>, 1)
// 		write (1, '>', STDOUT_FILENO);
// 		line = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(flag, line, len)
// 		{
// 			free (line);	
// 			close(file);
// 			return (1);
// 		}
// 		write(file , line, ft_strlen(line));
// 		free (line);	
// 	}
// }


int	redirect_in(t_info *info, int i)
{
	t_token *tk;
	int	*fd_in;
	int	last_in;

	tk = info->tk;
	last_in = find_last_in(tk, i);
	fd_in = malloc(info->q_in * sizeof(int *));
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == IN_FILE || tk->type == HEREDOC)
		{
			if (tk->type == HEREDOC);
			{
				fd_in = open(get_heredoc(tk->content), O_RDONLY, 0644);
			}
			else
				fd_in = open(tk->content, O_RDONLY, 0644);
			if (last_in == tk->in_index)
				break;
			close(fd_in);
			if (tk->type == HEREDOC)
				unlink(".heredoc_tmp");
		}
		tk = tk->next;
	}
	return (fd_in);
}
*/