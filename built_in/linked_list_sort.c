/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:37:19 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/04 18:38:03 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list(t_env **head_a)
{
	t_env	*tmp;

	while ((*head_a) != NULL)
	{
		tmp = (*head_a);
		(*head_a) = (*head_a)->next;
		if (tmp->content)
			free(tmp->content);
		if (tmp->name)
			free(tmp->name);
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

t_env	*ft_copy_list(t_env *head)
{
	t_env	*temp;
	t_env	*newnode;
	t_env	*copy;

	temp = head;
	copy = NULL;
	if (head == NULL)
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
		tmp = temp->next->name;
		temp->next->name = temp->name;
		temp->name = tmp;
		tmp = temp->next->content;
		temp->next->content = temp->content;
		temp->content = tmp;
	}
}

t_env	*ft_sort_list(t_env *head)
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
// int main(int argc, char **argv, char **envp)