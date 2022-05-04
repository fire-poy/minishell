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

void	free_tokens(t_token **tk)
{
	t_token	*tmp;
	t_token	*a;

	a = *tk;
	while (a)
	{
		if (a->content)
			free (a->content);
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
		free (info);
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
