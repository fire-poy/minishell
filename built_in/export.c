#include "../minishell.h"
#include "../libft/libft.h"

/* My export function needs to:
- create a var and save it
- print a sorted list of all the variables if <export> is arg
- export my var to the env if exported
*/

void	ft_replace_var(t_env **head, char **var, char *str)
{
	free((*head)->content);
	(*head)->content = ft_get_line(str);
	free((*head)->initial_env);
	(*head)->initial_env = ft_strdup(str);
	free((*head)->name);
	(*head)->name = ft_get_name(str);
	free (*var);
}

t_env	*add_var_to_env(t_env **head, char *var)
{
	t_env	*temp;
	char	*name;
	char	*content;

	temp = *head;
	name = ft_get_name(var);
	content = ft_get_line(var);
	temp = ft_create_node(name, content);
	temp->initial_env = ft_strdup(var);
	printf("name = %s\n", temp->name);
	printf("content = %s\n", temp->content);
	return (temp);
}

/*

// this main can add a new node with the var content and delete it

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


