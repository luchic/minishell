
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"
/*
 * echo -n -n -n
 not double checked with minishell tester.
 need to check before submission
 */

// 0 for no -n, 1 for -n

int n_option(char *arg)
{
    int i;
    
    if (!arg || arg[0] != '-')
        return 0;
    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

int is_newline_option(char *arg)
{
    int is_n;

    is_n = n_option(arg);
    if (is_n == 1)
        return (0);
    return (1);
}

int ft_echo(t_command *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = is_newline_option(cmd->args[i]);
    while (n_option(cmd->args[i]) == 1)
    {
        i++;
    }
    while (cmd->args[i])
    {
        ft_printf_fd(cmd->fd_out, "%s", cmd->args[i]);
        if (cmd->args[i + 1])
			ft_printf_fd(cmd->fd_out, " ");
        i++;
    }
    if (newline)
		ft_printf_fd(cmd->fd_out, "\n");
    return (EXIT_SUCCESS);
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
