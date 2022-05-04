/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:52:17 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 11:52:18 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cherche string a_trouver dans la liste de ENV
char	*chercher_env(t_env *liste, char *a_trouver)
{
	while (liste)
	{
		if (!ft_strncmp(a_trouver, liste->name, ft_strlen(a_trouver)))
			return (liste->content);
		else
			liste = liste->next;
	}
	return (NULL);
}

void	printlist_tk(t_token *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		printf("%d %s = type %d\n", i, node->content, node->type);
		node = node->next;
		i++;
	}
}

char	*erase_quotes(char *s)
{
	char	dst[1000];
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			dst[j++] = s[i++];
		else
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				dst[j++] = s[i++];
			i++;
		}
	}
	dst[j] = '\0';
	free (s);
	return (ft_substr(dst, 0, ft_strlen(dst)));
}

void	erase_quotes_tk(t_token *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		node->content = erase_quotes(node->content);
		node = node->next;
		i++;
	}
}
