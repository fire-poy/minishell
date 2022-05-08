/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:36:13 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/08 16:47:55 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// return 1 if there is equal
int	ft_equal(char *var)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (!var)
		return (1);
	while (var[i])
	{
		if (var[i] == '=')
		{
			equal = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_export_var(char *var)
{
	int	i;
	int	equal;

	i = 0;
	equal = ft_equal(var);
	if (equal == 0)
	{
		while (var[i])
		{
			if (!ft_isalpha(var[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_varlen(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			return (i + 1);
		}
		i++;
	}
	return (i);
}

void	ft_replace_var(t_env **head, char *name, char *content, char *var)
{
	free((*head)->content);
	(*head)->content = ft_strdup(content);
	free((*head)->name);
	(*head)->name = ft_strdup(name);
	free ((*head)->initial_env);
	(*head)->initial_env = ft_strdup(var);
}

void	ft_free_flag(t_info *info, t_env *liste, char *var)
{
	int	flag;

	flag = ft_info_init(info, var);
	ft_update_var(liste, info, var);
	if (flag == 1)
	{
		if (info->tk->export_name)
			free (info->tk->export_name);
		if (info->tk->export_content)
			free(info->tk->export_content);
	}
}
