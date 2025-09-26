#Name of the program
NAME = minishell


# Source directories
SRCS_DIR = src/

COMMON = $(SRCS_DIR)common/
CORE = $(SRCS_DIR)core/
EXEC = $(SRCS_DIR)executor/
CMD_AGMT = $(EXEC)cmd_assignments/
CMD_BLTN = $(EXEC)cmd_built_in/
CMD_EXT = $(EXEC)cmd_external/
PIPE_UTILS = $(EXEC)pipe_utils/
REDIR = $(EXEC)redirections/
LEXER = $(SRCS_DIR)lexer/
PARSER = $(SRCS_DIR)parser/
PARSER_AGMT = $(PARSER)assignments/
PARSER_PRS = $(PARSER)parse/
PARSER_PP = $(PARSER)pre_parsing/
PARSER_TS = $(PARSER)token_stream/
PARSER_UT = $(PARSER)utils/
EXPANDER = $(SRCS_DIR)expander/
EXPANDER_VAR = $(EXPANDER)variable/
EXPANDER_WLD = $(EXPANDER)wildcards/


# Source files
SRCS =	$(SRCS_DIR)main.c \
		$(COMMON)dir_utils.c \
		$(COMMON)ft_array_append.c \
		$(COMMON)ft_free_tools2.c \
		$(COMMON)ft_strchr.c \
		$(COMMON)ft_str_utils.c \
		$(COMMON)signal1.c \
		$(COMMON)env.c \
		$(COMMON)ft_array_remove.c \
		$(COMMON)ft_free_tools.c \
		$(COMMON)ft_strdup_array.c \
		$(COMMON)get_mnsh.c \
		$(COMMON)signal.c \
		$(COMMON)exit_code.c \
		$(COMMON)ft_free_tools1.c \
		$(COMMON)ft_get_array_counts.c \
		$(COMMON)ft_str_utils1.c \
		$(COMMON)is_qoute.c \
		$(COMMON)unexpected_token.c \
		$(CORE)read.c \
		$(CORE)run.c \
		$(CORE)setup.c \
		$(EXEC)exe_cmd.c \
		$(EXEC)exe_cmd_utils.c \
		$(EXEC)exe_logic.c \
		$(EXEC)exe_subsh.c \
		$(EXEC)exe_cmd_pipe.c \
		$(EXEC)executor.c \
		$(EXEC)exe_pipe.c \
		$(CMD_AGMT)handle_assignments.c \
		$(CMD_AGMT)handle_assignments_and_run.c \
		$(CMD_BLTN)ft_cd.c \
		$(CMD_BLTN)ft_echo.c \
		$(CMD_BLTN)ft_exit.c \
		$(CMD_BLTN)ft_export_print_env.c \
		$(CMD_BLTN)ft_unset.c \
		$(CMD_BLTN)ft_cd_utils.c \
		$(CMD_BLTN)ft_env.c \
		$(CMD_BLTN)ft_export.c \
		$(CMD_BLTN)ft_pwd.c \
		$(CMD_BLTN)run_built_in.c \
		$(CMD_EXT)get_cmd_path.c \
		$(CMD_EXT)run_external.c \
		$(PIPE_UTILS)fork_and_exe.c \
		$(REDIR)ft_write_data.c \
		$(REDIR)handle_output_redir.c \
		$(REDIR)preprocess_heredoc.c \
		$(REDIR)handle_heredoc.c \
		$(REDIR)handle_redirections.c \
		$(REDIR)utils.c \
		$(REDIR)handle_input_redir.c \
		$(REDIR)heredoc_expander.c \
		$(LEXER)get_token.c \
		$(LEXER)token_assignment.c \
		$(LEXER)token_type.c \
		$(LEXER)utils.c \
		$(LEXER)lexer.c \
		$(LEXER)token_spliter.c \
		$(LEXER)utils1.c \
		$(PARSER)parser.c \
		$(PARSER_AGMT)assignments.c \
		$(PARSER_AGMT)handle_expander.c \
		$(PARSER_PRS)parse_cmd.c \
		$(PARSER_PRS)parse_pipeline.c \
		$(PARSER_PRS)parse_subshell.c \
		$(PARSER_PRS)parse_main.c \
		$(PARSER_PRS)parse_redirection.c \
		$(PARSER_PP)exp_info.c \
		$(PARSER_PP)wld_utlis.c \
		$(PARSER_TS)cloen_stream.c \
		$(PARSER_TS)token_stream.c \
		$(PARSER_UT)assignments_utils.c \
		$(PARSER_UT)create_ast_nodes.c \
		$(PARSER_UT)redirection_utils.c \
		$(PARSER_UT)cmd_utils.c \
		$(PARSER_UT)parse_utils.c \
		$(EXPANDER_VAR)extracter.c \
		$(EXPANDER_VAR)var_expansion.c \
		$(EXPANDER_WLD)expand_recursion.c \
		$(EXPANDER_WLD)handle_files.c \
		$(EXPANDER_WLD)wld_utils1.c \
		$(EXPANDER_WLD)wld_utils.c \
		$(EXPANDER_WLD)expand_redirection.c \
		$(EXPANDER_WLD)wildcard_expansion.c \
		$(EXPANDER_WLD)wld_utils2.c

OBJS = $(SRCS:.c=.o)

# Libft
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
FT = ft

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
DFLAGS = -Iincludes -g -D DEBUG_LEVEL=0 -fsanitize=address

all : $(NAME)

bonus : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -l$(FT) -o $(NAME) -lreadline

debug:
	$(MAKE) -C $(LIBFT_PATH) debug
	$(MAKE) CFLAGS="$(DFLAGS)" $(NAME)

debug-re: fclean
	$(MAKE) -C $(LIBFT_PATH) debug-re
	$(MAKE) CFLAGS="$(DFLAGS)" $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean :
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus debug
