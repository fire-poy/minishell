#include "../minishell.h"

char	*ft_str_join(char *s1, char const *s2)
{
	char	*dst;
	size_t	len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	dst = malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	dst[i++] = ' ';
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free (s1);
	return (dst);
}
//compter   INPUT
			// OUTPUT
			// CMD
			// PIPE
// dernier input va etre celui de la redirection entrée
// dernier output va etre celui de la redirection sortie avant un pipe
// si il y a plusieurs inputs on ouvre en mode read et ferme jusq'au dernier
// si il y a plusieurs inputs on ouvre en mode write et ferme
//  fd[0][0] = open(av[1], O_RDONLY);cmd
//     fd[0][1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
t_info	*init_info(t_info *info)
{
	info = malloc (sizeof(t_info));
	info->redir_in = 0; 
	info->redir_out = 0;
	info->q_in = 0; 
	info->q_out = 0; 
	info->cmd_i = 0;
	info->pipe_i = 0;
	return (info);
}
			// redir_in = tk->content;
			// fd[redir_i] = open(tk->content, O_RDONLY )
			// if (fd = -1)
			// 	err_msg;
	// t_token	*head;
	// head = tk;
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
			info->q_in++;
		if (tk->type == OUT_FILE || tk->type == APPEND)
			info->q_out++;
		tk->cmd_index = info->cmd_i;
		tk = tk->next;
	}
}

	// i = ft_strlen(full_cmd[0]);
	// (void)tk;
//cmd_i pour q_cmd
char **get_tab_cmd(t_token *tk, int cmd_i)
{
	char	**full_cmd;
	int		i;

	full_cmd = malloc((cmd_i + 2) * sizeof(char *));
	i = 0;
	while (i < cmd_i + 2) //peut-etre remplaçable par full_cmd[i] = NULL; et strjoin normal
	{
		full_cmd[i] = malloc(sizeof(char));
		full_cmd[i][0] = '\0';
		i++;
	}
	if (!full_cmd)
		return (NULL);
	while (tk)
	{
		if (tk->type == CMD)
			full_cmd[tk->cmd_index] = ft_str_join(full_cmd[tk->cmd_index], tk->content);
		tk = tk->next;
	}
	full_cmd[cmd_i + 1] = NULL;
	return (full_cmd);
}

void	parser(t_env *liste, t_token *tk, char **envp)
{
	t_info	*info;
	int 	i = 0;

	info = NULL;
	info = init_info(info);
	get_info_tk(tk, info);	
	printlist_tk(tk);
	info->full_cmd = get_tab_cmd(tk, info->cmd_i);
	while (i <= info->cmd_i)
	{
		printf("cmd%i = %s\n", i, info->full_cmd[i]);
		i++;
	}
	find_path(info->full_cmd[0], envp, liste);
	// pipe pipe_i fois
	// compter BUILT_IN cmd from full_cmd
	// fork cmd_i fois + 1  - B_in cmd
	// faire redirection par raport au cmd_i
	// executer cmd_i
}











