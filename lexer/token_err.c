/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:54:29 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 11:54:30 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(char **in, int *i)
{
	char	e[3];
	char	*s;

	s = *in;
	e[0] = s[*i];
	e[1] = '\'';
	e[2] = '\0';
	free (*in);
	err_msg(e, "syntax error near unexpected token `", 258);
}

// "syntax error near unexpected token `|'"
void	get_token_err(char **in, int *i, t_info *info)
{
	int		origin;
	char	*s;

	s = *in;
	origin = *i;
	if ((*i) == 0 && s[*i] == '|')
		info->err = 1;
	(*i)++;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '<' || s[*i] == '>' || s[*i] == '|')
		info->err = 1;
	if (s[*i] == '\0')
		info->err = 1;
	*i = origin;
}

// "syntax error near unexpected token `|'"
void	get_pipe_err(char **in, int *i, t_info *info)
{
	int		origin;
	char	*s;

	s = *in;
	origin = *i;
	if ((*i) == 0 && s[*i] == '|')
		info->err = 1;
	(*i)++;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '|')
		info->err = 1;
	if (s[*i] == '\0')
		info->err = 1;
	*i = origin;
}

void	explore_tokens_err(char **in, t_info *info)
{
	int		i;
	char	*s;

	s = *in;
	i = 0;
	while (s[i])
	{	
		if (s[i] == '\'' || s[i] == '\"')
			search_next_c(&s, &i, s[i]);
		if (s[i] == '<')
		{
			if (s[i + 1] == '<')
				i++;
			get_token_err(in, &i, info);
		}	
		if (s[i] == '>')
		{
			if (s[i + 1] == '>')
				i++;
			get_token_err(in, &i, info);
		}	
		if (s[i] == '|')
			get_pipe_err(in, &i, info);
		i++;
	}
}
