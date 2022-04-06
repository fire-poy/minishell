#include "../minishell.h"

void	trimer (char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n')
		// || s[*i] == '\v' || s[*i] == '\f' || s[*i] == '\r')
		(*i)++;
}

char *chercher_env(t_env *liste, char *a_trouver)
{
	while (liste)
	{
		if (!ft_strncmp(a_trouver, liste->name , ft_strlen(a_trouver)))//si sont different je continue a chercher
			return (liste->content);
		else
			liste = liste->next;
	}
	return (NULL);
}


// lexer
// 1 quitamos espacio vacio
// 2 buscamos " ' y remplazamos $dentro
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
	// (void)tk;
	tk = get_tokens(input2, tk);
	// printf("token->content = %s\n", tk->content);
	printlist_tk(tk);

	return (1);
}
//ch_env debbug
// 	printf("liste name = %s\n", liste->name);
// 	printf("liste content = %s\n", liste->content);
// 	printf("a_trouver = %s\n", a_trouver);