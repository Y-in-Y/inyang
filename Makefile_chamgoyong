NAME			=	cub3D
CC				=	gcc
CFLAGS_42		=	-Wall -Wextra -Werror
CLFAGS_ASAN		=	-g2 -fsanitize=address
CLFAGS_BUFF		=	-D BUFFER_SIZE=1024
CFLAGS_FRAME	=	-framework OpenGL -framework AppKit
CFLAGS			=	$(42FLAGS) $(CFLAGS_42) $(CLFAGS_BUFF) $(CFLAGS_FRAME)
AR				=	ar
ARFLAGS			=	rcs
RM				=	rm -rf

CUB3D_F			=	cub3d_utils\
					cub3d\
					dfs_map\
					dfs_utils\
					parse_map\
					parse_utils\
					parse_start\
					print_error\
					struct_init\
					map_into_int\
					mlx_start\
					texture\
					mlx_calc\
					mlx_calc_2\
					pl_view_n_key\
					sprite_sort\
					sprite_draw\
					bitmap\
					free\
					parse_exception

CUB3D_B_F		=	cub3d_utils_bonus\
					cub3d_bonus\
					dfs_map_bonus\
					dfs_utils_bonus\
					parse_map_bonus\
					parse_utils_bonus\
					parse_start_bonus\
					print_error_bonus\
					struct_init_bonus\
					map_into_int_bonus\
					mlx_start_bonus\
					texture_bonus\
					mlx_calc_bonus\
					mlx_calc_2_bonus\
					pl_view_n_key_bonus\
					sprite_sort_bonus\
					sprite_draw_bonus\
					bitmap_bonus\
					free_bonus\
					parse_exception_bonus\
					bgm_bonus


CUB3D_D			=	./sources/
CUB3D_C			=	$(addsuffix .c, $(addprefix $(CUB3D_D), $(CUB3D_F)))
CUB3D_O			=	$(addsuffix .o, $(addprefix $(CUB3D_D), $(CUB3D_F)))

CUB3D_B_D		=	./bonus/
CUB3D_B_C		=	$(addsuffix .c, $(addprefix $(CUB3D_B_D), $(CUB3D_B_F)))
CUB3D_B_O		=	$(addsuffix .o, $(addprefix $(CUB3D_B_D), $(CUB3D_B_F)))

GNL_F			=	get_next_line\
					get_next_line_utils

GNL_D			=	./assets/get_next_line/
GNL_H			=	./assets/get_next_line/get_next_line.h
GNL_C			=	$(addsuffix .c, $(addprefix $(GNL_D), $(GNL_F)))
GNL_O			=	$(addsuffix .o, $(addprefix $(GNL_D), $(GNL_F)))

LIBFT_D			=	./assets/libft/
LIBFT_A			=	./assets/libft/libft.a

OPENGL_D		=	./assets/mlx/
OPENGL_A		=	./assets/mlx/libmlx.a

.PHONY:	all clean fclean re bonus

$(NAME): $(CUB3D_O) $(GNL_O)
	make -C $(LIBFT_D)
	make -C $(OPENGL_D)
	$(CC) $(CFLAGS) $(LIBFT_A) $(OPENGL_A) $(CUB3D_O) $(GNL_O) $(GNL_H)
	mv a.out $(NAME)

bonus: $(CUB3D_B_O) $(GNL_O)
	make -C $(LIBFT_D)
	make -C $(OPENGL_D)
	$(CC) $(CFLAGS) $(LIBFT_A) $(OPENGL_A) $(CUB3D_B_O) $(GNL_O) $(GNL_H)
	mv a.out $(NAME)

.c.o:
	$(CC) $(CFLAGS_42) $(CLFAGS_BUFF) -c -o $@ $<

all: $(NAME)

clean:
	$(RM) $(CUB3D_O) $(CUB3D_B_O) $(GNL_O) $(NAME) save.bmp

fclean: clean
	make fclean -C $(LIBFT_D)
	make clean -C $(OPENGL_D)

re:	fclean all
