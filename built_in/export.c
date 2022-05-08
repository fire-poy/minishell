/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:34:48 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/08 16:47:15 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*add_var_to_env(t_env **head, char *var, t_token *token)
{
	t_env	*temp;

	temp = *head;
	if (!ft_equal(var))
	{
		while (temp->next != NULL && ft_strcmp
			(temp->name, token->export_name) != 0)
			temp = temp->next;
		if (ft_strcmp(temp->name, token->export_name) == 0)
			return (0);
	}
	if (token->export_content)
		temp = ft_create_node(token->export_name, token->export_content);
	else
		temp = ft_create_node(token->export_name, token->export_content);
	temp->initial_env = ft_strdup(var);
	return (temp);
}

void	ft_print_export(t_env *liste, int fd)
{
	t_env	*sort;

	sort = ft_sort_list(liste);
	printlist(sort, fd);
	if (sort)
		ft_free_list(&sort);
}

//si no assignation ex_name = var    cont = "" , else malloc export_name y cont
int	ft_info_init(t_info *info, char *var)
{
	if (!ft_equal(var))
	{
		info->tk->export_name = var;
		info->tk->export_content = "";
		return (0);
	}
	else
	{
		info->tk->export_name = ft_get_name(var);
		info->tk->export_content = ft_get_line(var);
		return (1);
	}
}

//var = a= ou a=2
void	ft_update_var(t_env *liste, t_info *info, char *var)
{
	t_env	*newnode;

	while (liste->next != NULL && ft_strcmp
		(liste->name, info->tk->export_name) != 0)
		liste = liste->next;
	if (ft_strcmp(liste->name, info->tk->export_name) == 0)
	{
		ft_replace_var(&liste, info->tk->export_name,
			info->tk->export_content, var);
	}
	else
	{
		newnode = add_var_to_env(&liste, var, info->tk);
		ft_add_to_list(&liste, newnode);
	}
}

void	ft_export(char **argv, t_env *liste, t_info *info, int fd)
{
	char	*var;

	if (!argv[1])
		ft_print_export(liste, fd);
	else
	{
		var = argv[1];
		if (!ft_strncmp(var, "=", 1))
			return ;
		if (!ft_check_export_var(var))
		{
			if (var != NULL)
				ft_free_flag(info, liste, var);
		}
	}
}
