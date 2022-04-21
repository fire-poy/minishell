#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		tab[i] = NULL;
		i++;
	}
	free (tab);
	tab = NULL;
}

void	free_tokens(t_token **tk)
{
	t_token *tmp;
	
	while (*tk)
	{
		tmp = (*tk)->next;
		free ((*tk)->content);
		free (*tk);
		*tk = NULL;
	}
}

void	free_all(t_info **info)
{
	// t_info *f;

	// f = *info;
	// free_tab(((*f)->full_cmd);
	// free_tab((f->split_cmd);
	// free_tokens(f->tk);
	free_tab((*info)->full_cmd);
	free_tab(*(*info)->split_cmd);
	free_tokens(&(*info)->tk);
	free (*info);
	*info = NULL;
}



