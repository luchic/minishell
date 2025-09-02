
#include "../../../includes/ft_defines.h"
#include "../../../includes/minishell.h"
#include "../../../libft/includes/libft.h"

int ft_cd(t_command *cmd)
{   
    char *home;
    char *pwd;
    char *oldpwd;

    if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
    
}