#include "../minishell.h"

void	trimer (char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n')
		// || s[*i] == '\v' || s[*i] == '\f' || s[*i] == '\r')
		(*i)++;
}

char *chercher_env(t_env *liste, char *a_trouver)
{
	if (!liste)
		return (NULL);
	while (liste->next)
	{
		if (ft_strncmp(a_trouver, liste->name , ft_strlen(a_trouver)))//si sont different je continue a chercher
			return (liste->content);
	}
	return (NULL);
}

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

// #define U_TOKEN "syntax error near unexpected token `"
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

// t_token *get_token(char *s, int *i, int type)
// {
// 	t_token *tk;

// 	tk = malloc(sizeof(t_token));
// 	tk->info
	
// }

		// if (s[i] == '\'' || s[i] == '\"')//si hay quotes las salteo
// void	get_tokens(char *s, t_env *liste, t_token *tk)
// {
// 	int		i;
// 	int		type;

// 	i = 0;
// 	type = CMD;
// 	while (s[i])
// 	{
// 		if (s[i] == '<')
// 		{
// 			type = IN_FILE;
// 			if (s[i + 1] == '<')
// 			{
// 				i++;
// 				type = HEREDOC;
// 			}
// 		}
// 		if (s[i] == '>')
// 		{
// 			type = OUT_FILE;
// 			if (s[i + 1] == '>')

// 				type = APPEND;
// 		}	
// 		if (s[i] == '|')
// 			type = PIPE;
// 		i++;
// 	}
// 	return (*s); 	
// void	explore_tokens(char *s, t_env *liste, t_token *tk)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' || s[i] == '\"')
// 			tk = save_token(s, &i, CMD);
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


	// if (ft_c_vs_charset(s[i], "<>|\0") != ft_strlen(s + i)) //on est pas a la fin
	// {
	// 	c = s[i + ft_c_vs_charset(s[i], "<>|\0")];
	// 	if (c == '<'
	// 		type = 0;

#define IN_FILE 0
#define OUT_FILE 1
#define APPEND 2
#define HEREDOC 3
#define BUILT_IN 5
#define CMD 5
// lexer
// 1 quitamos espacio vacio
// 2 buscamos tokens -> < >> > ' " funciones
// 	despues de > file
int	lexer(char *input, t_env *liste, t_token *tk)
{
	int	i;
	char *input2;

	i = 0;
	(void)tk;
	trimer (input, &i);
	input2 = ft_strdup(input + i);
	input2 = search_and_replace_quotes(&input2, liste);
	input2 = remplacer_rest_of_dollar(&input2, liste);
	explore_tokens_err(&input2);
	// printf("input = %s \ninput 2 = %s\n", input, input2);

	return (1);
}


// void	search_type_token(char *input)
// {
// 	char *set;

// 	set = ft_strdup("<>|");
// 	if (input[i] && ft_c_vs_charset(input[i], set))
// 	{
// 		if (input[i] == '<')
// 			type = 0;



	// i = 0;
	// while (input2[i])
	// {
	// 	search_and_create_token(input + i);
	// }