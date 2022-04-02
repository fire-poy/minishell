#include "../minishell.h"

void	trimer (char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n'
		|| s[*i] == '\v' || s[*i] == '\f' || s[*i] == '\r')
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

// lexer
// 1 quitamos espacio vacio
// 2 buscamos tokens -> < >> > ' " funciones
	// despues de > file
int	lexer(char *input, t_env *liste)
{
	int	i;
	char *input2;

	i = 0;
	trimer (input, &i);
	input2 = ft_strdup(input + i);
	input2 = search_and_replace_quotes(&input2, liste);
	printf("input = %s \ninput 2 = %s\n", input, input2);
	return (1);
	// i = 0;
	// while (input2[i])
	// {
	// 	search_and_create_token(input + i);
	// }
}

// void	search_type_token(char *input)
// {
// 	char *set;

// 	set = ft_strdup("<>|")
// 	if (input[i] && ft_c_vs_charset(input[i], set))
// 	{
// 		if (input[i] == '<')
// 			type = 0;
