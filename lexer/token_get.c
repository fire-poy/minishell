/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:54:15 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 13:22:54 by mpons            ###   ########.fr       */
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

char	*get_first(char *s, t_tk_info *z)
{
	int		add;

	if (z->type == 0 || z->type == 1)
		add = 1;
	if (z->type == 2 || z->type == 3)
		add = 2;
	z->st += add;
	z->mem = z->type;
	search_next_token(s, &z->st, &z->i, &z->type);
	return (get_content_tk(s, z->st - 1, z->i));
}

t_token	*get_tokens(char *s, t_token *tk)
{
	char		*content;
	t_tk_info	z;

	z.st = 0;
	z.i = 0;
	while ((unsigned long)z.i < ft_strlen(s))
	{
		search_next_token(s, &z.st, &z.i, &z.type);
		if (z.i == 0)
			content = get_first(s, &z);
		else
			content = get_content_tk(s, z.st, z.i);
		if (z.st == 0)
			tk_create_node(&tk, &content, CMD);
		else
			tk_create_node(&tk, &content, z.mem);
		z.st = z.i;
		z.mem = z.type;
	}
	return (tk);
}
