
/*
get the relative , absolute path of a command
get env variables
*/

# include "../../includes/minishell.h"
# include "../../includes/ft_defines.h"

int main (int argc, char **argv, char **envp)
{
    char *all = getenv("PATH");
    printf("PATH: %s\n", all);

    while (*envp)
    {
        printf("env: %s\n", *envp);
        envp++;
    }
    return (0);
}