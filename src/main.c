/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/12 13:21:20 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_defines.h"
#include "libft.h"
#include "parser.h"
#include "ft_executor.h"
#include <readline/readline.h>
#include <readline/history.h>


void init_minishell(t_minishell *mnsh, int argc, char **argv, char **envp)
{
    int i;

    ft_memset(mnsh, 0, sizeof(t_minishell));
	
	int size = count_args(envp);
    mnsh->envp = ft_calloc((size + 1), sizeof(char *));
    if (!mnsh->envp)
        return;
    for (i = 0; envp[i]; i++)
    {
        mnsh->envp[i] = ft_strdup(envp[i]);
        if (!mnsh->envp[i])
            return;
    }
    mnsh->envp[i] = NULL;
	mnsh->script = ft_calloc(1, sizeof(t_script));
	if (!mnsh->script)
		return ;
}

void set_env(t_ast_node *node, t_minishell *mnsh)
{
	if (node->type == COMMAND)
	{
		node->command->mnsh = mnsh;
	}
	else if (node->type == PIPELINE)
	{
		for (int i = 0; i < node->pipeline->count; i++)
			set_env(node->pipeline->commands[i], mnsh);
	}
	else if (node->type == LOGICAL)
	{
		set_env(node->logical->left, mnsh);
		set_env(node->logical->right, mnsh);
	}
	else if (node->type == SUBSHELL)
	{
		set_env(node->subshell->script, mnsh);
	}

}

// TODO: handle minishell> kkjhg execve: No such file or directory
// TODO: change error messages to match bash ones

void ft_run_minishell(t_minishell *mnsh, int argc, char **argv, char **envp)
{
	char *input;
	
	while ((input = readline("minishell> ")))
	{

		t_list *tokens = run_lexer(input);
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
			continue;
		}
		t_ast_node *ast = run_parser(tokens, mnsh);
		mnsh->script->nodes = ast;
		if (!mnsh->script)
		{
			ft_printf_fd(STDERR, "Parser error\n");
			free(input);
			ft_lstclear(&tokens, free);
		}
		set_env(ast, mnsh);
		execute_script(mnsh, ast);
		add_history(input);
		ft_lstclear(&tokens, free);
		free_ast_tree(ast);
		free(input);
	}
	rl_clear_history();
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	mnsh;
    char        *input;

	init_minishell(&mnsh, argc, argv, envp);
	ft_run_minishell(&mnsh, argc, argv, envp);
    return (0);
}
