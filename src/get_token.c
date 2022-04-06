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

// struct s_token
// {
// 	char		*data;//cmd
// 	//char		**tab_cmd; on fait le tab dans le pipe?
// 	int			type;
// 	int			tk_index;//ordre de token
// 	int			cmd_index;//nro de commande
// 	t_token	*next;
// };

// name
// A word consisting solely of letters, numbers, and underscores, 
// beginning with a letter or underscore. 
// Names are used as shell variable and function names. 
// Also referred to as an identifier.

// token
// A sequence of characters considered a single unit by the shell. 
// It is either a word or an operator.

// metacharacter
// A character that, when unquoted, separates words. 
// A metacharacter is a space, tab, newline, 
// or one of the following characters: ‘|’, ‘&’, ‘(’, ‘)’, ‘<’, or ‘>’. ‘;’, 
// set = ft_strdup("<>|");

// //copier token a_partir de i jusqu tk_i
// 	tk = get_first_token;
// t_token	*get_first_token(char *input, t_token *tk)
// {
// 	tk_create_node(&tk, input, CMD);
// }

#define IN_FILE 0
#define OUT_FILE 1
#define APPEND 2
#define HEREDOC 3
#define BUILT_IN 5
#define CMD 5

int	set_type(char *s, int i, char c)
{
	int	type;

	if (c == '<')
		type = IN_FILE;
	if (c == '<' && s[i + 1] == '<')
		type = HEREDOC;
	if (c == '>')
		type = OUT_FILE;
	if (c == '>' && s[i + 1] == '>')
		type = APPEND;
	if (c == '|')
		type = PIPE;
	return (type);
}

int	search_next_token(char *s, char *tk, int *type)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')//si hay quotes las salteo
			search_next_c(&s, &i, s[i]);
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')//si encuentro token 
		{
			*tk = s[i];
			*type = set_type(s, i, s[i]);
			// if (type == HEREDOC || type == APPEND)
				// return (i + 1);
			return (i);
		}
		i++;
	}
	*type = -1;
	return (-1);
}

// void	explore_tokens(char *s, t_env *liste, t_token *tk)
// {
// 	int	i;
// 	int	start_tk;
// 	int fin_tk;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' || s[i] == '\"')
// 			search_next_c(input, &i, s[i]);
// 		if (s[i] == '<')
// 		{
// 			if (s[i + 1] == '<')
// 			{
// 				i++;
// 				tk = save_token(s, &i, HEREDOC);
// 			}
// 			else
// 				tk = save_token(s, &i, IN_FILE);
// 		}	
// 		if (s[i] == '>')
// 		{
// 			if (s[i + 1] == '>')
// 				tk = save_token(s, &i, APPEND);
// 			else
// 				tk = save_token(s, &i, OUT_FILE);
// 		}	
// 		if (s[i] == '|')
// 			tk = save_token(s, &i, PIPE);
// 		i++;
// 	}
// 	return (*s); 	