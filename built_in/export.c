#include "../minishell.h"
#include "../libft/libft.h"

/* My export function needs to:
- create a var and save it
- print a sorted list of all the variables if <export> is arg
- export my var to the env if exported
*/

void	ft_replace_var(t_env **head, char *var, char *str)
{
	(*head)->content = NULL;
	(*head)->content = ft_get_line(str);
	free((*head)->initial_env);
	(*head)->initial_env = ft_strdup(str);
	free((*head)->name);
	(*head)->name = ft_get_name(str);
	free (var);
}

t_env	*add_var_to_env(t_env **head, char *var)
{
	t_env	*temp;
	char	*name;
	char	*content;

	temp = *head;
	if (!ft_equal(var))
	{
		name = "hello";
		content = "''";
	}
	else
	{
		name = ft_get_name(var);
		printf("add_var name = %s\n", name);
		content = ft_get_line(var);
		printf("add_var content = %s\n", content);
	}
	temp = ft_create_node(name, content);
	temp->initial_env = ft_strdup(var);
	return (temp);
}

t_env	*ft_export(char **argv, t_env *liste, t_token *token)
{
	t_token *vars;
	t_env	*newnode;
	t_env	*sort;
	char	*var;
	int		i;

	i = 0;
	vars = token;
	var = vars->tab_cmd[1];
	sort = liste;
	//head = (t_env *)malloc(sizeof(t_env));
	if (!argv[1])
		printlist((ft_sort_list(sort)));
	if (!ft_check_export_var(var))
	{
		if (var)
		{
			while(liste->next != NULL)
			{
				if (!ft_strcmp(liste->name, ft_get_name(var)))
				{
					printf("same var\n");
					ft_replace_var(&liste, var, var);
					return (liste);
				}
				liste = liste->next;
			}
			printf("different var\n");
			newnode = add_var_to_env(&liste, var);
			ft_add_to_list(&liste, newnode);
		}
	}
	// printf("********************************* \n");
	// ft_delete_from_list(&head, newnode->name);
	// printlist(head);
	return (liste);
}
