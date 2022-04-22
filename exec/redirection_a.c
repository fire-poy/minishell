#include "../minishell.h"
#define NAME ".heredoc_tmp"

char	*get_heredoc(char *flag, int i)
{
	char	*line;
	char	*name;
	int		len;
	int		file;

	i = 0;
	// name = ft_strjoin(".heredoc_tmp", (char *)i);
	name = ".heredoc_tmp";
	file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		err_msg("heredoc error", NULL, 1);
	len = ft_strlen(flag);
	while (1)
	{
		// ft_putstrl_fd(>, 1)
		write (STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(flag, line, len))
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

int	redirect_out(t_info *info, int i)
{
	t_token *tk;
	int	fd_out;
	int	last_out;

	tk = info->tk;
	last_out = find_last_out(tk, i);
	// fd_out = malloc(info->q_out * sizeof(int *));
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == OUT_FILE)
		{
		    fd_out = open(tk->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (last_out == tk->in_index)
				break;
			else
				close(fd_out);
		}
		if (tk->type == APPEND)
		{
			fd_out = open(tk->content, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (last_out == tk->in_index)
				break;
			else
				close(fd_out);
		}
		tk = tk->next;
	}
	return (fd_out);
}

void	redirect_in_out(t_info *info, int i)
{
	int fd_in;
	int fd_out;

	if (info->q_in > 0)
	{
		fd_in =	redirect_in(info, i);
		close (fd_in);
		dup2(STDIN_FILENO, fd_in);
	}
	if (info->q_out > 0 )
	{
		fd_out = redirect_out(info, i);
		close (fd_out);
		dup2(STDOUT_FILENO, fd_out);
	}
}




// void	close_all_fd(t_info *info);

// redir_in = tk->content;
// fd[redir_i] = open(tk->content, O_RDONLY )
// if (fd = -1)
// 	err_msg;
//     fd[0][1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);

// void	handle_redirect_file(t_shell *shell, t_cmd *cmd)
// {
// 	if (cmd->redirect_id == id_in_std || cmd->redirect_id == id_in_file)
// 		redirect_input_file(shell, cmd);
// 	if (cmd->redirect_id == id_out_write || cmd->redirect_id == id_out_append)
// 		redirect_output_file(cmd);
// }

// void	redirect_input_file(t_shell *shell, t_cmd *cmd)
// {
// 	int	fd;

// 	(void)shell;
// 	fd = -2;
// 	if (cmd->redirect_id == id_in_file)
// 		fd = open(cmd->redirect_path, O_RDONLY, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Error: open() failed");
// 		exit(1);
// 	}
// 	else if (fd > 0)
// 	{
// 		dup2(fd, 0);
// 		close(fd);
// 	}
// }

// void	redirect_output_file(t_cmd *cmd)
// {
// 	int	fd;

// 	fd = -2;
// 	if (cmd->redirect_id == id_out_write)
// 		fd = open(cmd->redirect_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (cmd->redirect_id == id_out_append)
// 		fd = open(cmd->redirect_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Error: open() failed");
// 		exit(1);
// 	}
// 	else if (fd > 0)
// 	{
// 		dup2(fd, 1);
// 		close(fd);
// 	}
// }

// void	redirect_input(t_shell *shell, t_cmd *cmd, int num)
// {
// 	if (num > 0)
// 	{
// 		if (cmd->redirect_id == id_in_std || cmd->redirect_id == id_in_file)
// 			redirect_input_file(shell, cmd);
// 		else
// 			dup2(shell->pipes[num - 1][0], 0);
// 	}
// 	else if (num == 0)
// 		redirect_input_file(shell, cmd);
// }

// void	redirect_output(t_shell *shell, t_cmd *cmd, int num)
// {
// 	if (num < shell->num_cmds - 1)
// 	{
// 		if (cmd->redirect_id == id_out_write
// 			|| cmd->redirect_id == id_out_append)
// 			redirect_output_file(cmd);
// 		else
// 			dup2(shell->pipes[num][1], 1);
// 	}
// 	else if (num == shell->num_cmds - 1)
// 		redirect_output_file(cmd);
// }

// void	here_doc(char *argv, t_ppxb *pipex)
// {
// 	int		file;
// 	char	*buf;

// 	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
// 	if (file < 0)
// 		msg_error(ERR_HEREDOC);
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		if (get_next_line(0, &buf) < 0)
// 			exit(1);
// 		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
// 			break ;
// 		write(file, buf, ft_strlen(buf));
// 		write(file, "\n", 1);
// 		free(buf);
// 	}
// 	free(buf);
// 	close(file);
// 	pipex->infile = open(".heredoc_tmp", O_RDONLY);
// 	if (pipex->infile < 0)
// 	{
// 		unlink(".heredoc_tmp");
// 		msg_error(ERR_HEREDOC);
// 	}
// }

// int	redirect_in(t_info *info, int i)
// {
// 	t_token *tk;
// 	int	*fd_in;
// 	int	last_in;

// 	tk = info->tk;
// 	last_in = find_last_in(tk, i);
// 	fd_in = malloc(info->q_in * sizeof(int *));
// 	while (tk && tk->cmd_index == i)
// 	{
// 		if (tk->type == IN_FILE || tk->type == HEREDOC)
// 		{
// 			if (tk->type == HEREDOC);
// 			{
// 				fd_in = open(get_heredoc(tk->content), O_RDONLY, 0644);
// 			}
// 			else
// 				fd_in = open(tk->content, O_RDONLY, 0644);
// 			if (last_in == tk->in_index)
// 				break;
// 			close(fd_in);
// 			if (tk->type == HEREDOC)
// 				unlink(".heredoc_tmp");
// 		}
// 		tk = tk->next;
// 	}
// 	return (fd_in);
// }