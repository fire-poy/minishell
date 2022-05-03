#include "../minishell.h"

//avance  *i jusqu'il trouve quelque chose d'autre que un espace
void	trimer (char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n')
		(*i)++;
}

// lexer
// 1 quitamos espacio vacio
// 2 buscamos " ' y remplazamos $dentro
// 2 buscamos tokens -> < >> > ' " funciones
// 	despues de > file
int	lexer(char *input, t_env *liste, t_token **tk, t_info *info)
{
	int	i;
	char *input2;

	i = 0;
	//(void)tk;
	trimer (input, &i);
	input2 = ft_strdup(input + i);
	input2 = search_and_replace_quotes(&input2, liste, info);
	if (input2 == NULL)
	{
		free (input2);
		return (0);
	}
	input2 = remplacer_rest_of_dollar(&input2, liste, info);
	explore_tokens_err(&input2, info);
	// if (info->err == 1)
		// info->exit_status = show_command_error(info, NULL, "syntax error near unexpected token `newline'", 258);
	// else if (info->err == 2)
	*tk = get_tokens(input2, *tk);
	erase_quotes_tk(*tk);
	free (input2);
	// ft_builtin(*tk, liste);
	// parser(input2, liste, tk);
	//printf("token->content = %s\n", tk->tab_cmd[1]);
	return (1);
}