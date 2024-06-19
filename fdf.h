/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:27:20 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/19 20:26:16 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include   "minilibx_linux/mlx.h"
# include   "libft/libft.h"
# include	"printf/ft_printf.h"
# include   <math.h>
# include   <float.h>
# include   <stdio.h>
# include   <stdlib.h>

# define X  0
# define Y  1
# define Z  2
# define C  3
# define WINW   2000
# define WINH   1300
# define D_PI   6.2831
# define PI     3.1416
# define H_PI   1.5708
# define CENTER_X WINW / 2
# define CENTER_Y WINH / 2

# define DEF_COLOR 0x1A1A1A
# define DEF_COLOR_MAX 0xC9DFEC
# define DEF_COLOR_MIN 0xFF6720
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

# define ESC_KEY 0xff1b
# define PLUS_KEY 0x45
# define MINUS_KEY 0x4E
# define ONE_KEY 0x31
# define TWO_KEY 0x32
# define THREE_KEY 0x33
# define FOUR_KEY 0x34
# define FIVE_KEY 0x35
# define SIX_KEY 0x36
# define SEVEN_KEY 0x37
# define ENTER_KEY 0xff0d
# define LEFT_KEY 0xff51
# define UP_KEY 0xff52
# define RIGHT_KEY 0xff53
# define DOWN_KEY 0xff54
# define DOWN_KEY 0xff54
# define DOWN_KEY 0xff54
# define DOWN_KEY 0xff54
# define W_KEY 0x0077
# define A_KEY 0x0061
# define S_KEY 0x0073
# define D_KEY 0x0064
# define M_KEY 0x6d
# define Q_KEY 0x71
# define E_KEY 0x65
# define T_KEY 0x74
# define G_KEY 0x67
# define I_KEY 0x69
# define O_KEY 0x6f
# define P_KEY 0x70
# define R_KEY 0x72
# define COMMA_KEY 0x2c
# define PERIOD_KEY 0x2e
# define SLASH_KEY 0x2f
# define SPACE_KEY 0x20
# define SHIFT_KEY 0xffe1

# define KEYPRESS_M (1L<<0)
# define KEYRELEASE_M (1L<<1)
# define MOUSEPRESS_M (1L<<2)
# define MOUSERELEASE_M (1L<<3)
# define MOUSEMOVE_M (1L<<6)
# define STRUCTNOTIFY_M (1L<<17)

# define KEYDOWN 2
# define KEYUP 3
# define MOUSEDOWN 4
# define MOUSEUP 5
# define MOUSEMOVE 6
# define EXPOSE 12
# define DESTROY 17

typedef struct s_snake{

}           t_snake;

typedef struct  s_img {
	void    *img_ptr;
	char    *addr;
	int     bpp;
	int     line_length;
	int     endian;
}           t_img;

typedef struct s_coords{
	float   x;
	float   y;
	float   z;
	int 	color;
}       	t_coords;

typedef struct s_cube{
	t_coords    coord[8];
	t_coords    coord_backup[8];
	int     	pad;
}           	t_cube;

typedef struct s_fdf{
	void        *mlx_ptr;
	void        *win_ptr;
	t_img       b_ground;
	int         map_W;
	int         map_H;
	int         map_edges_W;
	int         map_edges_H;
	int         map_size;
	int			tras[2];
	int			rot_deg[3];
	int			is_left_mouse_pres;
	int			is_right_mouse_pres;
	int			mouse_x;
	int			mouse_y;
	int			mouse_tracker;
	int			mouse_delayer;
	int			shift_tracker;
	int			animate;
	int			color_flag;
	int			z_max;
	int			z_min;
	int			z_diff;
	int			load_flag;
	int			entered;
	int			animation_steps;
	int			increment;
	float		z_factor;
	float       spacing_W;
	float       spacing_H;
	float		zoom;
	t_coords    *map;
	t_coords    *backup_map;
	t_cube		cube;
}               t_fdf;

typedef struct s_point{
	float   x;
	float   y;
	float   z;
	int     color;
	int     og_color;
	float   fade_comp[4];
	int     n;
	int     max;
}           t_point;

typedef struct s_circle{
	float   x;
	float   y;
	float   center_x;
	float   center_y;
	int     radius;
	float   degree;
	float   smothness;
	float   increment;
	int     color;
	int     og_color;
	float   fade_comp[4];
	int     n;
	int     max;
}           t_circle;

typedef struct s_bresenham{
	t_coords    i_pt;
	t_coords    f_pt;
	int 		d;
	int 		d2;
	int 		dx;
	int 		dy;
	int 		i_one;
	int 		i_two;
	int     	n;
	int     	max;
	int			color;
	float   	fade_comp[4];
}           	t_bresenham;

void    draw_welcome_menu(t_fdf *fdf);
void    init_bresenham_line(t_img *img, t_coords *i_pt, t_coords *f_pt);
void    fancy_circle(t_img *img, int xm, int ym, int r);
void	rotate_x(t_coords *pt, float angle);
void	rotate_y(t_coords *pt, float angle);
void	rotate_z(t_coords *pt, float angle);
void	rotate_map(t_fdf *fdf, int deg_x, int deg_y, int deg_z);
void	scale_map(t_fdf *fdf);
void	set_z_scaling(t_fdf *fdf);
void	rotate_cube(t_fdf *fdf, t_cube *cube);
void	init_cube(t_cube *cube);
void    write_str(t_fdf *fdf, char *msg, int x, int y, int size);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    init_img_data(t_img *img, void *mlx);
int		check_load(t_fdf *fdf);
int		check_enter(t_fdf *fdf);

#endif