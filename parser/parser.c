#include "../minishell.h"

t_info	*init_info(t_info *info)
{
	info = malloc (sizeof(t_info));
	info->redir_in = 0; 
	info->redir_out = 0;
	info->q_in = 0; 
	info->q_out = 0; 
	info->cmd_i = 0;
	info->pipe_i = 0;
	info->input = malloc(sizeof(char));
	return (info);
}

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

char **get_tab_cmd(t_token *tk, int cmd_i)
{
	char	**full_cmd;
	int		i;

	full_cmd = malloc((cmd_i + 2) * sizeof(char *));
	if (!full_cmd)
		return (NULL);
	i = 0;
	while (i < cmd_i + 2)
	{
		full_cmd[i] = malloc(sizeof(char));
		full_cmd[i][0] = '\0';
		i++;
	}
	while (tk)
	{
		if (tk->type == CMD)
			full_cmd[tk->cmd_index] = ft_strjoin_whit_space(full_cmd[tk->cmd_index], tk->content);
		tk = tk->next;
	}
	full_cmd[cmd_i + 1] = NULL;
	return (full_cmd);
}

char ***get_cmd_split(char **full_cmd, int cmd_i)
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

t_info	*parser(t_env *liste, t_token *tk, char **envp, t_info *info)
{
	//t_info	*info;
	int 	i = 0;

	//info = NULL;
	//info = init_info(info);
	get_info_tk(tk, info);	
	info->full_cmd = get_tab_cmd(tk, info->cmd_i);
	info->split_cmd = get_cmd_split(info->full_cmd, info->cmd_i);
	info->tk = tk;
	info->liste = liste;
	info->envp = envp;
	printlist_tk(tk);
	while (i <= info->cmd_i)
	{
		printf("cmd_i %d = %s\n", i, info->full_cmd[i]);
		i++;
	}
	return (info);
}
