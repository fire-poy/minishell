#include "../minishell.h"

// "syntax error near unexpected token `|'"
void	get_token_err(char **in, int *i)
{
	char	e[3];
	int		origin;
	char	*s;

	s = *in;
	origin = *i;
	(*i)++;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')	
	{
		e[0] = s[*i];
		e[1] = '\'';
		e[2] = '\0';
		free (*in);
		err_msg(e, "syntax error near unexpected token `", 258);
	}
	if (s[*i] == 0)
		err_msg("syntax error near unexpected token `newline'", NULL, 258);
	*i = origin;
}

void	explore_tokens_err(char **in)
{
	int		i;
	char	*s;

	s = *in;
	i = 0;
	while (s[i])
	{	
		if (s[i] == '\'' || s[i] == '\"')//si hay quotes las salteo
				search_next_c(&s, &i, s[i]);
		if (s[i] == '<')
		{
			if (s[i + 1] == '<')
				i++;
			get_token_err(in, &i);
		}	
		if (s[i] == '>')
		{
			if (s[i + 1] == '>')
				i++;
			get_token_err(in, &i);			
		}	
		if (s[i] == '|')
			get_token_err(in, &i);			
		i++;
	}
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