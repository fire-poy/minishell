#include "../minishell.h"

void	printlist(t_the_env *node)
{
	while (node != NULL)
	{
		printf("%s\n", node->content);
		node = node->next;
	}
}


void	create_node(t_the_env **head, char *data)
{
	t_the_env	*newNode;
	t_the_env	*last;

	last = *head;
	newNode = (t_the_env *)malloc(sizeof(t_the_env));
	//newNode->content = NULL;
	newNode->content = data;
	if (*head == NULL)
	{
		*head = newNode;
			return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
}

void	create_env_list(t_the_env **head, char **envp)
{
	int				i;

	i = 2;
	while (envp[i]!= NULL)
	{
		create_node(head, envp[i]);
		i++;
	}
}

// supprimer 1er element liste

void	delete_first(t_the_env **head)
{
	t_the_env	*tmp;
	t_the_env *ttmp;
	
	tmp = *head;
	ttmp = *head;
	if (tmp != NULL)
	{
		ttmp = tmp->next;
		free(tmp);
	}
	else
		return ;
}
// supprimer element en fin de liste
void	delete_last(t_the_env **head)
{
	t_the_env	*liste;
	t_the_env	*tmp;
	t_the_env	*ptmp;

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

t_the_env	*find_last(t_the_env **head)
{
	t_the_env	*tmp;

	tmp = *head;
	while(tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	main(int argc, char **envp)
{
	t_the_env *head;
	t_the_env	*tmp;
	t_the_env *ttmp;

	head = (t_the_env *)malloc(sizeof(t_the_env));
	printf("env test = %s\n", head->next->content);
	create_env_list(&head, envp);
	tmp = head;
	printf("env 1 = %s\n", head->content);
	printf("env 2 = %s\n", head->next->content);
	printf("1 / first element list = %s\n", tmp->content);
	printf("1 / first element list = %s\n", tmp->next->content);
	delete_first(&head);
	tmp = head;
	printf("2 / first element list = %s\n", tmp->content);
	// //printlist(tmp);
	// tmp = find_last(&head);
	// printf("1 / last element list = %s\n", tmp->content);
	// delete_last(&head);
	// tmp = find_last(&head);
	// printf("2 / last element list = %s\n", tmp->content);
	// delete_last(&head);
	// tmp = find_last(&head);
	// printf("3 / last element list = %s\n", tmp->content);
	//delete_last(&tmp);
	// ttmp = head;
	// ttmp = find_last(&ttmp);
	// printf("2 / last element list = %s\n", ttmp->content);
	// delete_last(&head);
	// head = find_last(&head);
	// printf("3 / last element list = %s\n", head->content);
	// //printlist(head);
	return (0);
}