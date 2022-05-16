/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:11:29 by mpons             #+#    #+#             */
/*   Updated: 2022/05/16 12:02:52 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_list_equal(t_env **head)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = *head;
	while (temp != NULL)
	{
		if (ft_equal(temp->initial_env))
			i++;
		temp = temp->next;
	}
	return (i);
}

char	**get_env_tab(t_env *node)
{
	int		i;
	int		size;
	char	**env;

	size = ft_count_list_equal(&node);
	env = malloc ((size + 1) * sizeof(char *));
	i = 0;
	while (i < size)
	{
		if (ft_equal(node->initial_env))
			env[i] = ft_strdup(node->initial_env);
		node = node->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
