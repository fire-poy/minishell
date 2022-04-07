#include "../minishell.h"
#include "../libft/libft.h"

void	printlist(t_env *node)
{
	while (node != NULL)
	{
		printf("%s=", node->name);
		printf("%s\n", node->content);
		node = node->next;
	}
}

char	*ft_get_line(char *line)
{
	int	i;
	char	*res;

	i = 0;
	while(line[i] != '=')
		i++;
	res = ft_substr(line, i + 1, ft_strlen(line) - i);
	return (res);
}

char	*ft_get_name(char *line)
{
	int	i;
	char	*res;

	i = 0;
	while (line[i] != '=')
		i++;
	res = ft_substr(line, 0, i);
	return (res);
}

void	env_create_node(t_env **head, char *data)
{
	t_env	*newNode;
	t_env	*last;

	last = *head;
	newNode = (t_env *)malloc(sizeof (t_env));
	//printf("data = %s\n", data);
	newNode->initial_env = ft_strdup(data);
	newNode->name = ft_get_name(data);
	newNode->content = ft_get_line(data);
	newNode->next = NULL;
	if (*head == NULL)
	{
		*head = newNode;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	return ;
}

// supprimer 1er element liste

t_env *delete_first(t_env **head)
{
	t_env	*tmp;
	
	tmp = *head;
	if (*head != NULL)
	{
		if ((*head)->next)
			tmp = (*head)->next;
		free(*head);
		return (tmp);
	}
	else
		return (NULL) ;
}


void	create_env_list(t_env **head, char **envp)
{
	int				i;
	t_env *tmp;

	i = 2;
	while (envp[i]!= NULL)
	{
		env_create_node(head, envp[i]);
		i++;
	}
	tmp = *head;
	i = 0;
	while (tmp->next != NULL)
	{
		//printf("node Nr %d = %s\n", i++, tmp->content);
		tmp = tmp->next;
	}
	*head = delete_first(head);
}

// supprimer element en fin de liste
void	delete_last(t_env **head)
{
	t_env	*liste;
	t_env	*tmp;
	t_env	*ptmp;

	liste = *head;
	tmp = *head;
	ptmp = *head;
	if (liste == NULL)
		return ;
	if (liste->next == NULL)
	{
		free (liste);
		return ;
	}
	while (tmp->next != NULL)
	{
		ptmp = tmp;
		tmp = tmp->next;
	}
	ptmp->next = NULL;
	free(tmp);
	//return (*liste);
}

t_env	*find_last(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while(tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

/*int	main(int argc, char **envp)
 {
 	t_env *head;

	head = (t_env *)malloc(sizeof(t_env));
 	create_env_list(&head, envp);
  printlist(head);
  return (0);
}*/
