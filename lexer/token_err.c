#include "../minishell.h"

void syntax_error(char **in, int *i)
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
		syntax_error(in, i);
	(*i)++;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '<' || s[*i] == '>' || s[*i] == '|')	
	{
		syntax_error(in, i);
	}
	if (s[*i] == '\0')
	{
		info->err = 1;
		// info->exit_status = show_command_error(info, NULL, "syntax error near unexpected token `newline'", 258);
		err_msg("syntax error near unexpected token `newline'", NULL, 258);
	}
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
		syntax_error(in, i);
	(*i)++;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '|')	
		syntax_error(in, i);
	if (s[*i] == '\0')
	{
		info->err = 2;
		// info->exit_status = show_command_error(info, NULL, "syntax error near unexpected token `newline'", 258);
		err_msg("syntax error near unexpected token `newline'", NULL, 258);
	}
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
		if (s[i] == '\'' || s[i] == '\"')//si hay quotes las salteo
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



