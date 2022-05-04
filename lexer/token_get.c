/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:54:15 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 11:54:18 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// return 1 si trouve `metachar`
// return -1 s'il n'y a pas de meta
// avance *idx jusq meta si trouve
// sinon avance jusq strlen
void	search_next_token(char *s, int *start, int *tk_idx, int *type)
{
	int	i;

	if (*start != 0)
	{
		if ((s[(*start) + 1] == '<' || s[(*start) + 1] == '>')
			&& s[(*start)] != '|')
			(*start) += 2;
		else
			(*start)++;
	}
	i = *start;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			search_next_c(&s, &i, s[i]);
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		{
			*type = set_type(s, i, s[i]);
			*tk_idx = i;
			return ;
		}
		i++;
	}
	*type = -1;
	*tk_idx = i;
}

//trime spaces and send data to create node
char	*get_content_tk(char *s, int start, int tk_i)
{
	char	dst[1000];
	int		i;
	int		j;

	i = start;
	j = 0;
	while (s[i] && i < tk_i)
		dst[j++] = s[i++];
	dst[j] = '\0';
	return (ft_strtrim(dst, " \t"));
}

char	*get_first(char *s, int *st, int *i, int *mem, int *type)
{
	int		add;

	if (*type == 0 || *type == 1)
		add = 1;
	if (*type == 2 || *type == 3)
		add = 2;
	(*st) += add;
	*mem = *type;
	search_next_token(s, st, i, type);
	return (get_content_tk(s, (*st) - 1, *i));
}

t_token	*get_tokens(char *s, t_token *tk)
{
	char	*content;
	int		type;
	int		mem;
	int		i;
	int		st;

	st = 0;
	i = 0;
	while ((unsigned long)i < ft_strlen(s))
	{
		search_next_token(s, &st, &i, &type);
		if (i == 0)
			content = get_first(s, &st, &i, &mem, &type);
		else
			content = get_content_tk(s, st, i);
		if (st == 0)
			tk_create_node(&tk, &content, CMD);
		else
			tk_create_node(&tk, &content, mem);
		st = i;
		mem = type;
	}
	return (tk);
}
