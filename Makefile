# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/05/24 19:15:26 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

END=\033[0m

NAME = fdf

CFILES = fdf_main.c

OFILES = $(CFILES:%.c=%.o)

OBJ = $(OFILES)

PATH_LFT = libft/libft.a

PATH_MLX = minilibx_macos/libmlx.a

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -L$(minilibx_macos/) -lmlx -lm -framework OpenGL -framework AppKit

CC = cc

ARLIB = ar rc

RM = rm -f

%.o: src/%.c $(PATH_LFT) $(PATH_MLX) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: extra_make $(NAME)

extra_make:
	@printf "LIBFT: COMPILING...\n$(END)"
	@$(MAKE) -C libft/ --no-print-directory
	@printf "MINILIBX: COMPILING...\n$(END)"
	@$(MAKE) -C minilibx_macos/ --no-print-directory

$(NAME): $(OFILES) $(PATH_LFT) $(PATH_MLX)
	@$(CC) $(CFLAGS) $(OFILES) $(PATH_LFT) $(PATH_MLX) $(MLXFLAGS) -o $(NAME)
	@printf "\n$(NAME) COMPILED!\n$(END)"

debug: $(OFILES) 
	@$(MAKE) -C libft/
	@$(MAKE) -C minilibx_macos/
	@$(CC) -g $(CFLAGS) $(OFILES) $(PATH_LFT) -o $(NAME)

clean:
	@$(MAKE) -C libft/ clean --no-print-directory
	@$(MAKE) -C minilibx_macos/ clean --no-print-directory
	@$(RM) $(OBJ)

fclean:	clean
	@$(MAKE) -C libft/ fclean --no-print-directory
	@$(MAKE) -C minilibx_macos/ fclean --no-print-directory
	@$(RM) $(NAME)

re:	fclean all

.PHONY = all clean fclean re