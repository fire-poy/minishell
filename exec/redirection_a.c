#include "../minishell.h"
// #define NAME ".heredoc_tmp"

char	*get_heredoc(char *flag, int i)
{
	char	*line;
	char	*name;
	int		len;
	int		file;

	name = ft_strjoin_whit_int(".heredoc_tmp", i);
	// name = ".heredoc_tmp";
	file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		err_msg("heredoc error", NULL, 1);
	len = ft_strlen(flag);
	while (1)
	{
		// ft_putstrl_fd(>, 1)
		write (STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(flag, line, len) == 0)
		{
			free (line);	
			close(file);
			return (name);
		}
		write(file , line, ft_strlen(line));
		free (line);	
	}
}

// heredoc(t_token *tk, int last_in)
// {
	// heredoc = get_heredoc(tk->content);
	// 	fd_in = open(heredoc, O_RDONLY, 0644);
	// 	if (last_in == tk->in_index)
	// 		break;
	// 	close(fd_in);
	// 	unlink(heredoc);
	// 	free (heredoc)
// }

int	redirect_in(t_info *info, int i)
{
	t_token *tk;
	int	fd_in;
	int	last_in;
	char *heredoc;

	tk = info->tk;
	last_in = find_last_in(tk, i);
	// fd_in = malloc(info->q_in * sizeof(int *));
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == IN_FILE)
		{
			fd_in = open(tk->content, O_RDONLY, 0644);
			if (last_in == tk->in_index)
				break;
			close(fd_in);
		}
		if (tk->type == HEREDOC)
		{
			heredoc = get_heredoc(tk->content, i);
			fd_in = open(heredoc, O_RDONLY, 0644);
			if (last_in == tk->in_index)
				break;
			close(fd_in);
			unlink(heredoc);
			free (heredoc);
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
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == OUT_FILE)
		{
		    fd_out = open(tk->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			// printf("last_out = %d\n", last_out);
			if (last_out == tk->out_index)
				break;
			else
				close(fd_out);
		}
		if (tk->type == APPEND)
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
	if (get_q_in(info->tk, i) > 0)//si redir on le fait
	{
		fd_in =	redirect_in(info, i);
		dup2(fd_in, STDIN_FILENO);
		close (fd_in);
	}
	else if (info->q_cmd > 1 && i != 0) //sinon si
		dup2(info->pipes[i - 1][0], STDIN_FILENO);
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