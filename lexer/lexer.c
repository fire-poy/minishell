/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:54:58 by mpons             #+#    #+#             */
/*   Updated: 2022/05/10 17:25:27 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//avance  *i jusqu'il trouve quelque chose d'autre que un espace
void	trimer(char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n')
		(*i)++;
}

// lexer
// 1 quitamos espacio vacio
// 2 buscamos " ' y remplazamos $dentro
// 2 buscamos tokens -> < >> > ' " funciones
// 	despues de > file
int	lexer(char *input, t_info *info)
{
	int		i;
	char	*input2;

	i = 0;
	trimer (input, &i);
	input2 = ft_strdup(input + i);
	input2 = search_and_replace_quotes(&input2, info->liste, info);
	if (input2 == NULL)
	{
		free (input2);
		return (0);
	}
	input2 = remplacer_rest_of_dollar(&input2, info->liste, info);
	explore_tokens_err(&input2, info);
	if (info->err == 1)
	{
		cmd_err(info, NULL, "syntax error near unexpected token", 258);
		free (input2);
		return (0);
	}
	info->tk = get_tokens(input2, info->tk);
	erase_quotes_tk(info->tk);
	free (input2);
	return (1);
}
