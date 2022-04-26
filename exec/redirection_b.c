#include "../minishell.h"

int	find_last_in(t_token *tk, int i)
{
	int	last_in;

	last_in = 0;
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == IN_FILE || tk->type == HEREDOC)
			last_in = tk->in_index;
		tk = tk->next;
	}
	return (last_in);
}

int	find_last_out(t_token *tk, int i)
{
	int	last_out;

	last_out = 0;
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == OUT_FILE || tk->type == APPEND)
			last_out = tk->out_index;
		tk = tk->next;
	}
	return (last_out);
}

int	get_q_in(t_token *tk, int i)
{
	int	q_in;

	q_in = 0;
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == IN_FILE || tk->type == HEREDOC)
			q_in++;
		tk = tk->next;
	}
	return (q_in);
}

int	get_q_out(t_token *tk, int i)
{
	int	q_out;

	q_out = 0;
	while (tk && tk->cmd_index == i)
	{
		if (tk->type == OUT_FILE || tk->type == APPEND)
			q_out++;
		tk = tk->next;
	}
	return (q_out);
}

	// heredoc = ft_strjoin(heredoc, line);
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