#include "../minishell.h"
#include "../libft/libft.h"

/* My export function needs to:
- create a var and save it
- print a sorted list of all the variables if <export> is arg
- export my var to the env if exported
*/

void	ft_replace_var(t_env *head, char **var, char *str)
{
	free((head)->content);
	(head)->content = ft_get_line(str);
	free((head)->initial_env);
	(head)->initial_env = ft_strdup(str);
	free((head)->name);
	(head)->name = ft_get_name(str);
	free (*var);
}

t_env	*add_var_to_env(t_env *head, char *var)
{
	t_env	*temp;
	char	*name;
	char	*content;

	temp = head;
	name = ft_get_name(var);
	content = ft_get_line(var);
	temp = ft_create_node(name, content);
	temp->initial_env = ft_strdup(var);
	// printf("name = %s\n", temp->name);
	// printf("content = %s\n", temp->content);
	return (temp);
}

int	ft_equal(char *var)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			equal = 1;
			return (i);
		}
		i++;
	}
	return (0);
}
int	ft_check_export_var(char *var)
{
	int	i;
	int	equal;

	i = 0;
	equal = ft_equal(var);
	if (equal == 0)
	{
		while (var[i])
		{
			if (!ft_isalpha(var[i]))
			{
				printf("export: not an identifier: %s\n", var);
				return (1);
			}
			i++;
		}
		// I need to take a new arg even without a value !!!!!! 
		// how to collect a var even without export?
	}
return (0);
}
// this main can add a new node with the var content and delete it

int	ft_export(char **argv, t_env *liste, t_token *token)
{
	t_token *vars;
	t_env	*newnode;
	char	*var;
	int		i;

	i = 0;
	vars = token;
	var = vars->tab_cmd[1];
	//head = (t_env *)malloc(sizeof(t_env));
	if (!argv[1])
		printlist((ft_sort_list(liste)));
	if (!ft_check_export_var(var))
	{
		if (vars->tab_cmd[1])
		{
			// printf ("Hello\n");
			if (ft_strcmp(liste->initial_env, var) == 0 )
			{
				ft_replace_var(liste, &var, var);
				return (0);
			}
			newnode = add_var_to_env(liste, var);
			ft_add_to_list(&liste, newnode);
			printlist(liste);
		}
	}
	// while (head != NULL)
	// {
	// 	if (ft_strcmp(head->initial_env, var) == 0 )
	// 	{
	// 		ft_replace_var(&head, &var, var);
	// 		return ;
	// 	}
	// // }
	// newnode = add_var_to_env(&head, var);
	// ft_add_to_list(&head, newnode);
	// printlist(head);
	// printf("********************************* \n");
	// ft_delete_from_list(&head, newnode->name);
	// printlist(head);
	return 0;
}
/*
int main(int argc, char **argv, char **envp)
{
	t_env *head;
	t_env	*newnode;
	char	*var;

	// (void)argv;
	// (void)argc;
	var = "var=42";
	head = (t_env *)malloc(sizeof(t_env));
	create_env_list(&head, envp);
	// while (head != NULL)
	// {
	// 	if (ft_strcmp(head->initial_env, var) == 0 )
	// 	{
	// 		ft_replace_var(&head, &var, var);
	// 		return ;
	// 	}
	// }
	newnode = add_var_to_env(&head, var);
	ft_add_to_list(&head, newnode);
	printlist(head);
	printf("********************************* \n");
	ft_delete_from_list(&head, newnode->name);
	printlist(head);
	return 0;
}
*/


