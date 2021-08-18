CC = gcc

CFLAGS = -Wall -Wextra #-Werror

FSNTZ = -g3 -fsanitize=address

NAME = minishell

SRCS = check_args.c\
	   envp_to_list.c\
	   find_env_value.c\
	   parsing.c\
	   parsing_redir.c\
	   parsing_quote.c\
	   parsing_env.c\
	   parsing_init.c\
	   parsing_utils.c\
	   parsing_utils_2.c\
	   cutting_line.c\
	   env_to_str.c\
	   rearrange_args.c\
	   split_line_by_two.c\
	   check_cmd_echo.c\
	   check_cmd_echo_2.c\
	   print_nyan.c\
	   print_nyan_2.c

all : $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) $(FSNTZ) -Iinclude $(SRCS) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all

.PHONY : all clean fclean re
