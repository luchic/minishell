#include "ft_common.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	setup_rl(t_minishell *mnsh)
{
	if (mnsh->is_tty_in)
	{
		rl_instream = stdin;
		if (mnsh->is_tty_out)
		{
			rl_outstream = stdout;
		}
		else
		{
			if (!mnsh->tty_out)
			{
				if (mnsh->fd >= 0 && mnsh->fd != STDERR)
					mnsh->tty_out = fdopen(mnsh->fd, "w");
				if (!mnsh->tty_out)
					mnsh->tty_out = stderr;
			}
			rl_outstream = mnsh->tty_out;
		}
	}
}

static void	setup_shell_level(t_minishell *mnsh)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl_str;
	char	*full_var;

	shlvl_str = getenv("SHLVL");
	if (shlvl_str && ft_atoi(shlvl_str) > 0)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	new_shlvl_str = ft_itoa(shlvl);
	full_var = ft_strjoin("SHLVL=", new_shlvl_str);
	if (full_var)
	{
		update_env_var(full_var, &(mnsh->envp));
		free(full_var);
	}
	free(new_shlvl_str);
}

static int	setup_env(t_minishell *mnsh, char **envp)
{
	int	i;
	int	size;

	size = count_args(envp);
	mnsh->envp = ft_calloc((size + 1), sizeof(char *));
	if (!mnsh->envp)
		return (-1);
	i = -1;
	while (envp[++i])
	{
		mnsh->envp[i] = ft_strdup(envp[i]);
		if (!mnsh->envp[i])
			return (free_stack_minishell(mnsh), -1);
	}
	mnsh->envp[i] = NULL;
	setup_shell_level(mnsh);
	return (0);
}

int	init_minishell(t_minishell *mnsh, char **envp)
{
	ft_memset(mnsh, 0, sizeof(t_minishell));
	mnsh->is_tty_out = isatty(STDOUT);
	mnsh->is_tty_in = isatty(STDIN);
	if (!mnsh->is_tty_out)
	{
		mnsh->fd = open("/dev/tty", O_WRONLY | O_NOCTTY);
		if (mnsh->fd == -1)
			mnsh->fd = STDERR;
	}
	else
		mnsh->fd = STDOUT;
	setup_rl(mnsh);
	if (setup_env(mnsh, envp) == -1)
		return (close_tty(mnsh), -1);
	mnsh->script = ft_calloc(1, sizeof(t_script));
	if (!mnsh->script)
		return (close_tty(mnsh), free_stack_minishell(mnsh), -1);
	*get_mnsh() = mnsh;
	return (0);
}

void	close_tty(t_minishell *mnsh)
{
	if (mnsh->tty_out && mnsh->tty_out != stderr)
	{
		fclose(mnsh->tty_out);
		mnsh->tty_out = NULL;
	}
	if (mnsh->fd > 0 && mnsh->fd != STDERR)
	{
		close(mnsh->fd);
		mnsh->fd = -1;
	}
}
