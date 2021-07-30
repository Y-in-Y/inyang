CC = gcc

CFLAGS = -Wall -Wextra #-Werror

FSNTZ = -g3 -fsanitize=address

NAME = minishell

SRCS = check_args.c\
	   envp_to_list.c\
	   ft_itoa.c\
	   find_env_value.c\
	   ft_strncmp.c\
	   parsing.c\
	   parsing_utils.c\
	   rearrange_args.c\
	   split_line_by_two.c

all : $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) $(FSNTZ) -Iinclude $(SRCS) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all

.PHONY : all clean fclean re
