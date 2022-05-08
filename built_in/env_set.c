/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:39:38 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/08 16:29:22 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char *head)
{
	if (head != NULL)
		free(head);
	else
		head = NULL;
}

void	ft_env_set_content(t_env *env, char *name, char *new_content)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!ft_strcmp(head->name, name))
		{
			ft_free(head->content);
			head->content = NULL;
			if (new_content)
				head->content = ft_strdup(new_content);
			return ;
		}
		head = head->next;
	}
}

int	ft_count_list(t_env **head)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = *head;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
