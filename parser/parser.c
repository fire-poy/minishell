#include "../minishell.h"

void	get_info_tk(t_token *tk, t_info *info)
{
	while (tk)
	{
		if (tk->type == PIPE)
		{
			info->cmd_i++;
			info->pipe_i++;
			tk->type = CMD;
		}
		if (tk->type == IN_FILE || tk->type == HEREDOC)
		{
			tk->in_index = info->q_in;
			info->q_in++;
		}
		if (tk->type == OUT_FILE || tk->type == APPEND)
		{
			tk->out_index = info->q_out;
			info->q_out++;
		}
		tk->cmd_index = info->cmd_i;
		tk = tk->next;
	}
	info->q_cmd = info->pipe_i + 1;
}

char	**get_tab_cmd(t_token *tk, int q_cmd)
{
	char	**full_cmd;
	int		i;

	full_cmd = malloc((q_cmd + 1) * sizeof(char *));
	if (!full_cmd)
		return (NULL);
	i = 0;
	while (i < q_cmd)
	{
		full_cmd[i] = malloc(sizeof(char));
		full_cmd[i][0] = '\0';
		i++;
	}
	while (tk)
	{
		if (tk->type == CMD && tk->content[0] != '\0')
			full_cmd[tk->cmd_index] = ft_strjoin_whit_space
				(full_cmd[tk->cmd_index], tk->content);
		tk = tk->next;
	}
	full_cmd[q_cmd] = NULL;
	return (full_cmd);
}

char	***get_cmd_split(char **full_cmd, int cmd_i)
{
	char	***cmd_split;
	int		i;

	cmd_split = malloc((cmd_i + 2) * sizeof(char **));
	if (!cmd_split)
		return (NULL);
	i = -1;
	while (++i < cmd_i + 2)
		cmd_split[i] = NULL;
	i = -1;
	while (full_cmd[++i])
		cmd_split[i] = ft_split(full_cmd[i], ' ');
	return (cmd_split);
}

void	parser(t_info *info)
{
	get_info_tk(info->tk, info);
	info->full_cmd = get_tab_cmd(info->tk, info->q_cmd);
	info->split_cmd = get_cmd_split(info->full_cmd, info->cmd_i);
}
/*
	int 	i = 0;
	printlist_tk(info->tk);
	while (i <= info->cmd_i)
	{
		printf("cmd_i %d = %s\n", i, info->full_cmd[i]);
		i++;
	}
	// */
// }
