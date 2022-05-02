#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free (tab[i]);
			tab[i] = NULL;
			i++;
		}
		free (tab);
		tab = NULL;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			printf("tab[i] = %s\n", tab[i]);
			i++;
		}
	}
}


void	free_tab_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				free (tab[i][j]);
				tab[i][j] = NULL;
				j++;
			}
			free (tab[i]);
			tab[i] = NULL;
			i++;
		}
		free (tab);
		tab = NULL;
	}
}

void	print_tab_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				printf("tab[i][j] = %s\n", tab[i][j]);
				j++;
			}
			printf("tab[i]++\n");
			i++;
		}
	}
}

void	free_tokens(t_token **tk)
{
	t_token *tmp;
	t_token *a;
	
	a = *tk;
	while (a)
	{
		if (a->content)
			free (a->content);
		// if (a->export)
		// {
		// 	// free (a->export);
		// 	// a->export = NULL;
		// }
		// if (a->export_name)
		// 	free (a->export_name);
		// if (a->export_content)
		// 	free (a->export_content);
		tmp = a->next;
		free (a);
		a = tmp;
	}
	*tk = NULL;
}

void	free_all(t_info *info)
{
	if (info)
	{
		if (info->full_cmd)
			free_tab(info->full_cmd);
		if (info->split_cmd)
			free_tab_tab(info->split_cmd);
		if (info->tk)
			free_tokens(&info->tk);
		// if (info->input)
		// 	free (info->input);
		free (info);
		// print_tab(info->full_cmd);
		// print_tab_tab(info->split_cmd);
		// printlist_tk(info->tk);
	}
	info = NULL;
}

void	free_info_simple(t_info *info)
{
	if (info)
	{
		free (info);
		info = NULL;
	}
}


// void	free_all(t_info **info)
// {
// 	// t_info *f;

// 	// f = *info;
// 	// free_tab(((*f)->full_cmd);
// 	// free_tab((f->split_cmd);
// 	// free_tokens(f->tk);
// 	free_tab((*info)->full_cmd);
// 	// free_tab_tab((*info)->split_cmd);
// 	//free pointeur des tableaux split_cmd
// 	free_tokens(&(*info)->tk);
// 	free (*info);
// 	*info = NULL;
// }

// void	free_cmds(t_cmd **cmds)
// {
// 	t_cmd	*last;
// 	t_cmd	*cmd;

// 	cmd = *cmds;
// 	while (cmd)
// 	{
// 		last = cmd;
// 		free(cmd->name);
// 		free(cmd->redirect_path);
// 		free_array(cmd->args);
// 		cmd = cmd->next;
// 		free(last);
// 	}
// 	*cmds = 0;
// }


// while (*tk)
// 	{
// 		tmp = (*tk)->next;
// 		free ((*tk)->content);
// 		free (*tk);
// 		*tk = NULL;
// 	}
// }

// void	free_tokens(t_token *tk)
// {
// 	t_token *tmp;
	
// 	while (tk)
// 	{
// 		tmp = tk->next;
// 		if (tk->content)
// 			free (tk->content);
// 		// if (tk->export)
// 		// 	free (tk->export);
// 		// if (tk->export_name)
// 		// 	free (tk->export_name);
// 		// if (tk->export_content)
// 		// 	free (tk->export_content);
// 		if (tk)
// 			free (tk);
// 		tk = tmp;
// 	}
// }
