#include "../minishell.h"

int	get_heredoc_fd(int cmd_index)
{
	int		fd_in;
	char 	*heredoc;

	heredoc = ft_strjoin_whit_int(".heredoc_tmp", cmd_index);
	fd_in = open(heredoc, O_RDONLY, 0644);
	free (heredoc);
	return (fd_in);
}

// heredoc se ejecuta aun si hay un error antes OK
void	get_heredoc(char *flag, int i)
{
	char	*line;
	char	*name;
	int		len;
	int		file;

	name = ft_strjoin_whit_int(".heredoc_tmp", i);
	file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free (name);
	if (file < 0)
		err_msg("heredoc error", NULL, 1);
	len = ft_strlen(flag);
	while (1)
	{
		write (STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
		ft_stop2(line);
		signal(SIGINT, signal_here);
		signal(SIGQUIT, SIG_IGN);
		if (line == 0)
		{
			line = flag;
			return ;
		}
		if (g_pid[8] == 6) // to quit with ctrl+c
		{
			g_pid[8] = 0;
			line = flag;
			return ;
		}
		if (ft_strncmp(flag, line, len) == 0 && line != 0)
		{
			free (line);	
			line = NULL;
			close(file);
			return ;
		}
		write(file , line, ft_strlen(line));
		free (line);	
	}
}

int	create_heredocs(t_token *tk)
{
	int	q_hd;

	q_hd = 0;
	while (tk)
	{
		if (tk->type == HEREDOC)
		{
			get_heredoc(tk->content, tk->cmd_index);
			q_hd++;
		}
		tk = tk->next;
	}
	// if (q_hd > 0)
	// 	f(STDIN_FILENO);
	return (1);
}

int	destroy_heredocs(int q_cmd)
{
	char	*heredoc;
	int		i;

	i = -1;
	while (++i < q_cmd)
	{
		heredoc = ft_strjoin_whit_int(".heredoc_tmp", i);
		unlink(heredoc);
		free(heredoc);
	}
	return (1);
}

/*
char	*get_tempfilename(t_shell *shell)
{
	int		i;
	char	*base;
	char	*number;
	char	*filename;

	i = 1;
	base = ft_strjoin(shell->working_dir, "/.tmp/.minishell");
	number = ft_itoa(i);
	filename = str_joins(base, ".tmp", number);
	while (access(filename, F_OK) == 0)
	{	
		free(number);
		free(filename);
		number = ft_itoa(++i);
		filename = str_joins(base, ".tmp", number);
	}
	free(base);
	free(number);
	return (filename);
}

void	here_doc(t_shell *shell, t_cmd *cmd, char *eof)
{
	char	*tmp_file;
	char	*line;
	int		fd;

	tmp_file = get_tempfilename(shell);
	fd = open(tmp_file, O_WRONLY | O_CREAT, 0664);
	if (fd > -1)
	{
		line = here_doc_readline();
		while (!(ft_strncmp(eof, line, ft_strlen(eof)) == 0
				&& (ft_strlen(eof) + 1) == ft_strlen(line)))
		{
			write(fd, line, ft_strlen(line));
			free(line);
			line = here_doc_readline();
		}
		free(line);
	}
	close(fd);
	free(cmd->redirect_path);
	cmd->redirect_path = tmp_file;
	cmd->redirect_id = id_in_file;
}
*/