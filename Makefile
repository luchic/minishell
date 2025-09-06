#Name of the program
NAME = minishell


# Source directories
SRCS_DIR = src/

COMMON = $(SRCS_DIR)common/
EXEC = $(SRCS_DIR)exec/
LEXER = $(SRCS_DIR)lexer/
PARSER = $(SRCS_DIR)parser/


# Source files
SRCS = $(wildcard $(COMMON)*.c)
SRCS += $(wildcard $(EXEC)*.c)
SRCS += $(wildcard $(LEXER)*.c)
SRCS += $(wildcard $(PARSER)*.c)
SRCS += $(SRCS_DIR)main.c

OBJS = $(SRCS:.c=.o)

# Libft
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
FT = ft

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_PATH)/includes

all : $(NAME)

bonus : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -l$(FT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean :
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus