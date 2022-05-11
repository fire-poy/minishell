/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:18:33 by mpons             #+#    #+#             */
/*   Updated: 2022/05/11 14:40:11 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_heredoc_fd(int cmd_index)
{
	int		fd_in;
	char	*heredoc;

	heredoc = ft_strjoin_whit_int(".heredoc_tmp", cmd_index);
	fd_in = open(heredoc, O_RDONLY, 0644);
	free (heredoc);
	return (fd_in);
}

void	here_boucle(int file, char *flag, int len)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, signal_here);
		if (g_pid[8] == 6)
		{
			g_pid[8] = 0;
			return ;
		}
		write (STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
		ft_stop2(line);
		if (line == 0)
			return ;
		if (ft_strncmp(flag, line, len) == 0
			&& (len + 1) == (int)ft_strlen(line))// && line != 0)
		{
			free (line);
			line = NULL;
			close(file);
			return ;
		}
		write(file, line, ft_strlen(line));
		free (line);
	}
}

// heredoc se ejecuta aun si hay un error antes OK
void	get_heredoc(char *flag, int i)
{
	char	*name;
	int		len;
	int		file;

	name = ft_strjoin_whit_int(".heredoc_tmp", i);
	file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free (name);
	if (file < 0)
		err_msg("heredoc error", NULL, 1);
	len = ft_strlen(flag);
	here_boucle(file, flag, len);
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
