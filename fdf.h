/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:27:20 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/31 08:40:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include	"minilibx_macos/mlx.h"
# include	<math.h>
# include	<float.h>
# include	<stdio.h>
# include	<stdlib.h>

# define WINW 	1920
# define WINH 	1080
# define D_PI	6.2831
# define PI		3.1416
# define CENTER_X WINW / 2
# define CENTER_Y WINH / 2

# define WHITE 0xFFFFFF
# define BLACK 0x0
# define GRAY_DARK 0x1A1A1A
# define ACQUA 0x36FFDD
# define PINK 0xFF19A7
# define ORANGE 0xE03E00
# define ORANGE_GULF 0xFF6720
# define CYAN_GULF 0xC9DFEC
# define GREEN 0x12D42A
# define ACQUA_DARK 0x05828E
# define BLUE 0x2286F5
# define BLUE_DARK 0x04018F
# define BROWN 0x8F7027
# define RED 0xFA2828
# define GRAY_LIGHT 0xC7C7C7
# define YELLOW 0xF4DD5B
# define DARK_GOLD 0xDAA520
# define GOLD 0xFFD700

# define ESC_KEY 0x35
# define PLUS_KEY 0x45
# define MINUS_KEY 0x4E
# define ONE_KEY 0x12
# define TWO_KEY 0x13
# define THREE_KEY 0x14
# define O_KEY 0x1F
# define P_KEY 0x23
# define A_KEY 0x00
# define S_KEY 0x01
# define D_KEY 0x02
# define W_KEY 0x0D
# define T_KEY 0x11
# define X_KEY 0x07
# define Y_KEY 0x10
# define Z_KEY 0x06
# define N_KEY 0x2D
# define M_KEY 0x2E
# define G_KEY 0x05
# define C_KEY 0x08
# define I_KEY 0x22
# define H_KEY 0x04

# define KEYDOWN 2
# define KEYUP 3
# define MOUSEDOWN 4
# define MOUSEUP 5
# define MOUSEMOVE 6
# define EXPOSE 12
# define DESTROY 17

typedef struct	s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_fdf{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	b_ground;
	int		map_W;
	int		map_H;
}			t_fdf;

typedef struct s_point{
	float	x;
	float	y;
	float	z;
	int		color;
	int		og_color;
	float	fade_comp[4];
	int		n;
	int		max;
}			t_point;

typedef struct s_circle{
	float	x;
	float	y;
	float	center_x;
	float	center_y;
	int		radius;
	float	degree;
	float	smothness;
	float	increment;
	int		color;
	int		og_color;
	float	fade_comp[4];
	int		n;
	int		max;
}			t_circle;

void	draw_welcome_menu(t_fdf *fdf);

#endif