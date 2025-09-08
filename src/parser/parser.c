/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:30:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 13:30:11 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

t_ast_node	*run_parser(t_list *tokens, char *input)
{
	t_tokenstream	ts;
	t_ast_node	*ast;

	ts.cur = tokens;
	ast = parse_script(&ts);
	return (ast);
}
