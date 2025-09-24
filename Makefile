#Name of the program
NAME = minishell


# Source directories
SRCS_DIR = src/

COMMON = $(SRCS_DIR)common/
EXEC = $(SRCS_DIR)executor/
LEXER = $(SRCS_DIR)lexer/
PARSER = $(SRCS_DIR)parser/
EXPANDER = $(SRCS_DIR)expander/


# Source files
SRCS = $(wildcard $(COMMON)*.c)
SRCS += $(wildcard $(EXEC)*.c)
SRCS += $(wildcard $(EXEC)cmd_assignments/*.c)
SRCS += $(wildcard $(EXEC)cmd_built_in/*.c)
SRCS += $(wildcard $(EXEC)cmd_external/*.c)
SRCS += $(wildcard $(EXEC)/pipe_utils/*.c)
SRCS += $(wildcard $(EXEC)redirections/*.c)
SRCS += $(wildcard $(LEXER)*.c)
SRCS += $(wildcard $(PARSER)*.c)
SRCS += $(wildcard $(PARSER)assignments/*.c)
SRCS += $(wildcard $(PARSER)parse/*.c)
SRCS += $(wildcard $(PARSER)pre_parsing/*.c)
SRCS += $(wildcard $(PARSER)utils/*.c)
SRCS += $(wildcard $(PARSER)validator/*.c)
SRCS += $(wildcard $(PARSER)token_stream/*.c)
SRCS += $(wildcard $(EXPANDER)variable/*.c)
SRCS += $(wildcard $(EXPANDER)wildcards/*.c)
SRCS += $(wildcard $(SRCS_DIR)core/*.c)
SRCS += $(SRCS_DIR)main.c

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
