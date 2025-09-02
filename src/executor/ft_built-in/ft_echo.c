
#include "../../../includes/ft_defines.h"
#include "../../../includes/minishell.h"
#include "../../../libft/includes/libft.h"

/*
 * echo -n -n -n
 not double checked with minishell tester.
 need to check before submission
 */

int ft_echo(t_command *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    cmd->fd_out = STDOUT_FILENO;  // Use standard output
    while (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (cmd->args[i])
    {
        ft_putstr_fd(cmd->args[i], cmd->fd_out);
        if (cmd->args[i + 1])
            ft_putstr_fd(" ", cmd->fd_out);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", cmd->fd_out);
    return (0);
}

/* int main()
{
    t_command cmd;
    char *args1[] = {"echo", "-n", "-n", "Hello,", "world!", NULL};
    // char  *args[] = {"echo", "\n", NULL};
    char *args2[] = {"echo", "if no -n then closely following the previoius,", "world!", NULL};

    // Initialize the command structure properly
    cmd.type = CMD_BUILTIN;
    cmd.fd_in = -1;
    cmd.fd_out = STDOUT_FILENO;  // Use standard output
    cmd.name = "echo";

    cmd.args = args1;
    ft_echo(&cmd);

    // cmd.args = args;
    // ft_echo(&cmd);

    cmd.args = args2;
    ft_echo(&cmd);

    return (0);
} */