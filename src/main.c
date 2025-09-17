/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/17 19:44:31 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <readline/history.h>
#include <readline/readline.h>

void	setup_shell_level(t_minishell *mnsh)
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

void	init_minishell(t_minishell *mnsh, int argc, char **argv, char **envp)
{
	int	i;
	int	size;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)mnsh;

	ft_memset(mnsh, 0, sizeof(t_minishell));
	size = count_args(envp);
	mnsh->envp = ft_calloc((size + 1), sizeof(char *));
	if (!mnsh->envp)
		return ;
	for (i = 0; envp[i]; i++)
	{
		mnsh->envp[i] = ft_strdup(envp[i]);
		if (!mnsh->envp[i])
			return ;
	}
	mnsh->envp[i] = NULL;

	// setup shell level variables
	// SHLVL
	setup_shell_level(mnsh);
	
	mnsh->script = ft_calloc(1, sizeof(t_script));
	if (!mnsh->script)
		return ;
}

// TODO: handle minishell> kkjhg execve: No such file or directory
// TODO: change error messages to match bash ones

void	ft_run_minishell(t_minishell *mnsh, int argc, char **argv, char **envp)
{
	char		*input;
	t_list		*tokens;
	t_ast_node	*ast;
	int			exit_status;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)mnsh;

	while ((input = readline("minishell> ")))
	{
		tokens = run_lexer(input);
		if (!tokens)
		{
			ft_printf_fd(STDERR, "Lexer error\n");
			free(input);
			continue ;
		};
		if (mnsh->script == NULL)
		{
			ft_printf_fd(STDERR, "Memory allocation error\n");
			free(input);
			ft_lstclear(&tokens, free);
			continue ;
		}
		ast = run_parser(tokens, mnsh);
		mnsh->script->nodes = ast;
		if (!mnsh->script)
		{
			ft_printf_fd(STDERR, "Parser error\n");
			free(input);
			ft_lstclear(&tokens, free);
		}
		exit_status = execute_script(mnsh, ast);
		mnsh->last_exit_status = exit_status;
		add_history(input);
		ft_lstclear(&tokens, free);
		free_ast_tree(ast);
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mnsh;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)mnsh;

	init_minishell(&mnsh, argc, argv, envp);
	ft_run_minishell(&mnsh, argc, argv, envp);
	return (0);

}
