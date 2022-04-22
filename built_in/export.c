#include "../minishell.h"
#include "../libft/libft.h"

/* My export function needs to:
- create a var and save it
- print a sorted list of all the variables if <export> is arg
- export my var to the env if exported
*/

void	ft_replace_var(t_env **head, char *name, char *content, char *var)
{
	(*head)->content = NULL;
	(*head)->content = content;
	free((*head)->initial_env);
	(*head)->initial_env = ft_strdup(var);
	free((*head)->name);
	(*head)->name = name;
	//free (var);
}

t_env	*add_var_to_env(t_env **head, char *var, t_token *token)
{
	t_env	*temp;

	temp = *head;
	if (!ft_equal(var))
	{
		while (temp->next != NULL && ft_strcmp(temp->name, token->export_name) != 0)
			temp = temp->next;
		if (ft_strcmp(temp->name, token->export_name) == 0)
			return (0);
	}
	if (token->export_content)
		temp = ft_create_node(token->export_name, token->export_content);
	else
		temp = ft_create_node(token->export_name, token->export_content);
	temp->initial_env = ft_strdup(var);
	return (temp);
}

t_env	*ft_export(char **argv, t_env *liste, t_info *info)
{
	t_env	*temp;
	t_env	*newnode;
	t_env	*sort;
	char	*var;

	sort = liste;
	temp = liste;
	//head = (t_env *)malloc(sizeof(t_env));
	if (!argv[1])
		printlist((ft_sort_list(sort)));
	var = argv[1];
	if (!ft_check_export_var(var))
	{
		if (var != NULL)
		{
			if (!ft_equal(var))
			{
				info->tk->export_name = var;
				info->tk->export_content = "";
			}
			else
			{
				info->tk->export_name = ft_get_name(var);
				info->tk->export_content = ft_get_line(var);
			}
			while (temp->next != NULL && ft_strcmp(temp->name, info->tk->export_name) != 0)
				temp = temp->next;
			if (ft_strcmp(temp->name, info->tk->export_name) == 0)
			{
				ft_replace_var(&temp, info->tk->export_name, info->tk->export_content, var);
				return (temp);
			}
			newnode = add_var_to_env(&temp, var, info->tk);
			ft_add_to_list(&temp, newnode);
			return (temp);
		}
	}
	return (temp);
}
