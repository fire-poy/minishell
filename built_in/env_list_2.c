/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:19:33 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/04 18:21:11 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_env_list(t_env **head, char **envp)
{
	int				i;
	t_env			*tmp;

	i = 0;
	while (envp[i] != NULL)
	{
		env_create_node(head, envp[i]);
		i++;
	}
	tmp = *head;
	i = 0;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
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
}

t_env	*find_last(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
