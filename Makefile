# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/06/14 20:45:00 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

END=\033[0m

NAME = fdf

CFILES = fdf_main.c

OFILES = $(CFILES:%.c=%.o)

OBJ = $(OFILES)

DIR_LIBFT = libft/ 

PATH_LFT = libft/libft.a

DIR_PTF = printf/

PATH_PTF = printf/libftprintf.a

DIR_MLX = minilibx_linux/

PATH_MLX = minilibx_linux/libmlx.a

CFLAGS = -Wall -Wextra -Werror -O2 #-fsanitize=address -fsanitize=leak

MLXFLAGS = -L -lmlx -lXext -lX11 -lm

CC = cc

ARLIB = ar rc

RM = rm -f

%.o: src/%.c $(DIR_LFT) $(DIR_PTF) $(DIR_MLX) fdf.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: extra_make $(NAME)

extra_make:
	@printf "LIBFT: COMPILING...\n$(END)"
	@$(MAKE) -C libft/ --no-print-directory
	@printf "PRINTF: COMPILING...\n$(END)"
	@$(MAKE) -C printf/ --no-print-directory
	@printf "MINILIBX: COMPILING...\n$(END)"
	@$(MAKE) -C minilibx_linux/ --no-print-directory

$(NAME): $(OFILES) $(PATH_LFT) $(PATH_MLX)
	@$(CC) $(CFLAGS) $(OFILES) $(PATH_LFT) $(PATH_PTF) $(PATH_MLX) $(MLXFLAGS) -o $(NAME)
	@printf "\n$(NAME) COMPILED!\n$(END)"

clean:
	@$(MAKE) -C libft/ clean --no-print-directory
	@$(MAKE) -C printf/ clean --no-print-directory
	@$(MAKE) -C minilibx_linux/ clean --no-print-directory
	@$(RM) $(OBJ)

fclean:	clean
	@$(MAKE) -C libft/ fclean --no-print-directory
	@$(MAKE) -C printf/ fclean --no-print-directory
	@$(RM) $(NAME)

re:	fclean all

.PHONY = all clean fclean re