#include "../minishell.h"

void	ft_free_list(t_env **head_a)
{
	t_env	*tmp;

	while ((*head_a) != NULL)
	{
		tmp = (*head_a);
		(*head_a) = (*head_a)->next;
		free(tmp->initial_env);
		free(tmp);
	}
}

void	ft_replaceit(t_env **head, char *name, char *value)
{
	t_env	*temp;

	temp = ft_search_in_list(head, name);
	if (temp != NULL)
	{
		free(temp->content);
		temp->content = ft_strdup(value);
	}
}

t_env	*ft_copy_list(t_env **head)
{
	t_env	*temp;
	t_env	*newnode;
	t_env	*copy;

	temp = *head;
	copy = NULL;
	if (*head == NULL)
		return (NULL);
	while (temp != NULL)
	{
		newnode = ft_create_node(temp->name, temp->content);
		if (copy == NULL)
			copy = newnode;
		else
			ft_add_to_list(&copy, newnode);
		temp = temp->next;
	}
	return (copy);
}

void	ft_swap_nodes(t_env	*temp)
{
	char	*tmp;

	if (ft_strcmp(temp->name, temp->next->name) > 0)
	{
		tmp = ft_strdup(temp->next->name);
		free(temp->next->name);
		temp->next->name = ft_strdup(temp->name);
		free(temp->name);
		temp->name = tmp;
		tmp = ft_strdup(temp->next->content);
		free(temp->next->content);
		temp->next->content = ft_strdup(temp->content);
		free(temp->content);
		temp->content = tmp;
	}
}

t_env	*ft_sort_list(t_env **head)
{
	t_env	*temp;
	t_env	*sort_list;
	int		i;

	sort_list = ft_copy_list(head);
	i = ft_count_list(&sort_list);
	temp = sort_list;
	while (i > 0)
	{
		temp = sort_list;
		while (temp->next != NULL)
		{
			ft_swap_nodes(temp);
			temp = temp->next;
		}
		i--;
	}
	return (sort_list);
}

// this main will print a sorted list of the env if export is prompted
int main(int argc, char **argv, char **envp)
{
	t_env *head;

	head = (t_env *)malloc(sizeof(t_env));
	create_env_list(&head, envp);
	printlist(head);
	printf("//////////////////////////\n");
	// printf("%s\n", argv[1]);
	// printf("%d\n", ft_strcmp(argv[1], "export"));
	if (argv[1] && ft_strcmp(argv[1], "export") == 0)
		printlist(ft_sort_list(&head));
	return 0;
}