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
	   parsing_redir.c\
	   parsing_quote.c\
	   parsing_env.c\
	   parsing_init.c\
	   parsing_utils.c\
	   cutting_line.c\
	   env_to_str.c\
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
