NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

SRCS_DIR = src
SRCS := $(wildcard $(SRCS_DIR)/*.c)

OBJS = $(SRCS:.c=.o)

LIBFT_PATH = libft

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/libft.a
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -o $(NAME)

$(LIBFT_PATH)/libft.a:
	$(MAKE) -C $(LIBFT_PATH)

%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re