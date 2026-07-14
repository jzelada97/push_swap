NAME		= push_swap
BONUS		= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes -I libft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SHARED_SRCS	= srcs/parsing/parsing.c \
			  srcs/utils/utils.c \
			  srcs/utils/stack/stack.c \
			  srcs/utils/stack/stack_index.c \
			  srcs/operations/operations_push.c \
			  srcs/operations/operations_rotate.c \
			  srcs/operations/operations_reverse_rotate.c \
			  srcs/operations/operations_swap.c \
			  srcs/algorithms/sort_simple.c \
			  srcs/algorithms/sort_simple_small.c \
			  srcs/algorithms/sort_simple_utils.c

SRCS		= srcs/main/main.c \
			  $(SHARED_SRCS) \
			  srcs/utils/disorder/disorder.c \
			  srcs/utils/bench/bench.c \
			  srcs/algorithms/sort_medium.c \
			  srcs/algorithms/sort_complex.c \
			  srcs/algorithms/sort_adaptive.c

BONUS_SRCS	= srcs/main/checker_bonus.c \
			  $(SHARED_SRCS)

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
