/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:22:47 by mpons             #+#    #+#             */
/*   Updated: 2022/05/16 12:00:21 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_space_out_of_quotes_found(char *s, int *start, char *set)
{
	int	i;

	i = *start;
	while (s[i] && ft_c_vs_charset(s[i], set))
		i++;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			search_next_c(&s, &i, s[i]);
		if (ft_c_vs_charset(s[i], set))
		{
			*start = i;
			return (1);
		}
		i++;
	}
	*start = i;
	return (1);
}

static int	ft_words(char *s, char *set)
{	
	int	i;
	int	word;

	word = 0;
	i = -1;
	if (set == NULL)
		return (1);
	while (s[++i])
	{	
		if (ft_space_out_of_quotes_found(s, &i, set))
			word++;
		if (s[i] == 0)
			break ;
	}
	return (word);
}

static int	ft_w_copy(char **tab, char *s, char *set)
{	
	int	i;
	int	j;
	int	word;
	int	debut;

	word = 0;
	i = -1;
	j = -1;
	if (set == NULL)
		return (1);
	while (s[++i])
	{	
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		debut = i;
		if (ft_space_out_of_quotes_found(s, &i, set))
		{
			tab[++j] = ft_substr(s, debut, i - debut);
		}
		if (!s[i])
			break ;
	}
	return (0);
}

char	**ft_split_token(char *s, char *c)
{
	char	**tab;
	int		words;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	tab = malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	ft_w_copy(tab, s, c);
	tab[words] = NULL;
	return (tab);
}
