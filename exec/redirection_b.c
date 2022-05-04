/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:28:22 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 17:45:33 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_last_in(t_token *tk, int i)
{
	int	last_in;

	last_in = 0;
	while (tk)
	{
		if ((tk->type == IN_FILE || tk->type == HEREDOC) && tk->cmd_index == i)
			last_in = tk->in_index;
		tk = tk->next;
	}
	return (last_in);
}

int	find_last_out(t_token *tk, int i)
{
	int	last_out;

	last_out = 0;
	while (tk)
	{
		if (tk->cmd_index == i && (tk->type == OUT_FILE || tk->type == APPEND))
			last_out = tk->out_index;
		tk = tk->next;
	}
	return (last_out);
}

int	get_q_in(t_token *tk, int i)
{
	int	q_in;

	q_in = 0;
	while (tk)
	{
		if (tk->cmd_index == i && (tk->type == IN_FILE || tk->type == HEREDOC))
			q_in++;
		tk = tk->next;
	}
	return (q_in);
}

int	get_q_out(t_token *tk, int i)
{
	int	q_out;

	q_out = 0;
	while (tk)
	{
		if (tk->cmd_index == i && (tk->type == OUT_FILE || tk->type == APPEND))
			q_out++;
		tk = tk->next;
	}
	return (q_out);
}
