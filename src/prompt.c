#include "../minishell.h"

void    loop_prompt(int ac, char **av, char **envp)
{
    char *input;

    if (!ac || !av || !envp)
        return ;    
    while (1)
    {
        input = readline("Minishell >");
        if (ft_strlen(input) > 0)
            add_history(input);
        /*
        if (!strcmp(string, "wc"))
        {
            foijtjefjooifasoij
        }
        if (cd -> )
*/
    }
}