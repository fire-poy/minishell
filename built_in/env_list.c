/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:15:27 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/11 14:35:10 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	printlist(t_env *node, int fd)
{
	while (node != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(node->name, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(node->content, fd);
		ft_putstr_fd("\"\n", fd);
		node = node->next;
	}
}

char	*ft_get_line(char *line)
{
	int		i;
	int		equal;
	char	*res;

	i = 0;
	equal = 0;
	while (line[i])
	{
		if (line[i] == '=')
		{
			equal = 1;
			break ;
		}
		i++;
	}
	if (equal == 0)
		i = 0;
	res = ft_substr(line, i + 1, ft_strlen(line));
	return (res);
}

char	*ft_get_name(char *line)
{
	int		i;
	int		equal;
	char	*res;

	i = 0;
	equal = 0;
	while (line[i])
	{
		if (line[i] == '=')
		{
			equal = 1;
			break ;
		}
		i++;
	}
	if (equal == 0)
		i = 0;
	res = ft_substr(line, 0, i);
	return (res);
}

void	env_create_node(t_env **head, char *data)
{
	t_env	*newnode;
	t_env	*last;

	last = *head;
	newnode = (t_env *)malloc(sizeof (t_env));
	newnode->initial_env = ft_strdup(data);
	newnode->name = ft_get_name(data);
	newnode->content = ft_get_line(data);
	newnode->next = NULL;
	if (*head == NULL)
	{
		*head = newnode;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newnode;
	return ;
}

// supprimer 1er element liste

t_env	*delete_first(t_env **head)
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
		return (NULL);
}
