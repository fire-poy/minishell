#include "../minishell.h"

// static inline char	**ft_malloc_error(char **tab, t_env *env_node)
// {
// 	unsigned int	i;

// 	(void)env_node;
// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		tab[i] = NULL;
// 		i++;
// 	}
// 	free(tab);
// 	tab = NULL;
// 	return (NULL);
// }

void	ft_free_env(void *env)
{
	t_env	*env_node;

	env_node = env;
	if (env_node->initial_env)
		free(env_node->initial_env);
	if (env_node->name)
		free(env_node->name);
	env_node->name = NULL;
	if (env_node->content)
		free(env_node->content);
	env_node->content = NULL;
	env_node->initial_env = NULL;
	if (env)
		free(env);
	env = NULL;
}

void	ft_listedelone(t_env *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

void	ft_listeclear(t_env **lst, void (*del)(void *))
{
	t_env	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_listedelone(*lst, del);
			(*lst) = tmp;
		}
	}
}
