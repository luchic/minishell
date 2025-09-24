/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/24 14:49:56 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "lexer.h"
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
	int		i;
	int		size;
	// char	cwd[255];
	// char	*pwd_var;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)mnsh;
	ft_memset(mnsh, 0, sizeof(t_minishell));

	ft_memset(mnsh, 0, sizeof(t_minishell));
	mnsh->is_interactive = isatty(STDOUT);
	if (!mnsh->is_interactive)
	{
		char *name = ttyname(STDOUT);
		mnsh->fd = open(name, O_WRONLY);
	}
	size = count_args(envp);
	mnsh->envp = ft_calloc((size + 1), sizeof(char *));
	if (!mnsh->envp)
		return ;
	for (i = 0; envp[i]; i++)
	{
		mnsh->envp[i] = ft_strdup(envp[i]);
	}
	mnsh->envp[i] = NULL;
	setup_shell_level(mnsh);
	mnsh->script = ft_calloc(1, sizeof(t_script));
	if (!mnsh->script)
		return ;
}

char	*ft_read_line(t_minishell *mnsh)
{
	char	*line;

	if (mnsh->is_interactive)
		return(readline("minishell> "));
	ft_printf_fd(mnsh->fd, "minishell> ");
	line = get_next_line(STDIN);
	if (line)
	{
		int len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	return (line);
}
// TODO: handle minishell> kkjhg execve: No such file or directory
// TODO: change error messages to match bash ones

int	ft_run_minishell(t_minishell *mnsh)
{
	char		*input;
	t_list		*tokens;
	t_ast_node	*ast;
	int			exit_status;
	int			tmp;

	(void)mnsh;
	while ((input = ft_read_line(mnsh)))
	{
		if (mnsh->is_interactive)
			add_history(input);
		tmp = run_lexer(&tokens, input);
		if (tmp)
		{
			ft_log_fd(LOG_ERROR, STDERR, "Lexer error\n");
			free(input);
			continue ;
		}
		if (mnsh->script == NULL)
		{
			ft_log_fd(LOG_ERROR, STDERR, "Memory allocation error\n");
			free(input);
			ft_lstclear(&tokens, free_tokens);
			continue ;
		}
		ast = run_parser(tokens, mnsh);
		mnsh->script->nodes = ast;
		if (mnsh->last_exit_status == SYNTAX_ERROR && !ast)
		{
			ft_log_fd(LOG_INFO, STDERR, "Exit code: %d\n", mnsh->last_exit_status);
			ft_log_fd(LOG_ERROR, STDERR, "Parser error\n");
			free(input);
			ft_lstclear(&tokens, free_tokens);
			continue ;
		}
		ft_lstclear(&tokens, free_tokens);
		free(input);
		exit_status = execute_node(mnsh, ast);
		mnsh->last_exit_status = exit_status;
		free_ast_tree(ast);
		mnsh->script->nodes = NULL;
	}
	if (mnsh->is_interactive)
		rl_clear_history();
	free_stack_minishell(mnsh);
	return (mnsh->last_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mnsh;
	int exit_code;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)mnsh;
	init_minishell(&mnsh, argc, argv, envp);
	exit_code = ft_run_minishell(&mnsh);
	return (exit_code);
}
