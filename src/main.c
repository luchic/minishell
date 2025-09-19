/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/18 22:10:19 by mezhang          ###   ########.fr       */
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
	
	// 删除 OLDPWD
	// ft_array_remove(&(mnsh->envp), "OLDPWD");
	// // 如果没有 PWD，则补充
	// if (!get_env_var(mnsh->envp, "PWD"))
	// {
	// 	if (getcwd(cwd, sizeof(cwd)))
	// 	{
	// 		pwd_var = ft_strjoin("PWD=", cwd);
	// 		update_env_var(pwd_var, &(mnsh->envp));
	// 		free(pwd_var);
	// 	}
	// }
	mnsh->script = ft_calloc(1, sizeof(t_script));
	if (!mnsh->script)
		return ;
}

// TODO: handle minishell> kkjhg execve: No such file or directory
// TODO: change error messages to match bash ones

void	ft_run_minishell(t_minishell *mnsh)
{
	char		*input;
	t_list		*tokens;
	t_ast_node	*ast;
	int			exit_status;
	int			tmp;

	(void)mnsh;
	while ((input = readline("minishell> ")))
	{
		if (ft_strcmp(input, "echo $?") == 0)
		{
			ft_printf("%d\n", mnsh->last_exit_status);
			free(input);
			continue ;
		}
		tmp = run_lexer(&tokens, input);
		if (tmp)
		{
			ft_printf_fd(STDERR, "Lexer error\n");
			free(input);
			continue ;
		}
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
			continue ;
		}
		exit_status = execute_script(mnsh, ast);
		mnsh->last_exit_status = exit_status;
		add_history(input);
		ft_lstclear(&tokens, free);
		free_ast_tree(ast);
		free(input);
	}
	clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mnsh;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)mnsh;
	init_minishell(&mnsh, argc, argv, envp);
	ft_run_minishell(&mnsh);
	return (0);
}
