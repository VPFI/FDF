/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:27:20 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 19:35:01 by vperez-f         ###   ########.fr       */
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
# define ENEM 2 
# define FOOD 5

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
# define EIGHT_KEY 0xffb8

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

typedef struct s_enemy{
	t_coords	center;
	t_coords	target_pos;
	int			radius;
}           	t_enemy;

typedef struct s_snake{
	t_coords			self_pos;
	t_coords			prev_pos;
	struct s_snake		*next;
}           			t_snake;

typedef struct s_sframe{
	int				food;
	int				dir;
	int				s_delayer;
	int				score;
	int				f_radius;
	int				s_radius;
	struct s_enemy	enemy[ENEM];
	t_coords	food_pos[FOOD];
}			t_sframe;

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
	int			snake_flag;
	float		z_factor;
	float       spacing_W;
	float       spacing_H;
	float		zoom;
	t_coords    *map;
	t_coords    *backup_map;
	t_cube		cube;
	t_snake		*snake;
	t_sframe	s_frame;
}               t_fdf;

typedef struct s_circle{
	float   x;
	float   y;
	float   center_x;
	float   center_y;
	int     radius;
	float   degree;
	float   smoothness;
	float   increment;
	int     color;
	int     og_color;
	int		fin_color;
	float   fade_comp[4];
	int     n;
	int     max;
	t_img	*img;
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

/*///////////// FDF \\\\\\\\\\\\\*/

void	init_fdf(t_fdf *fdf);
void    init_img_data(t_img *img, void *mlx);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	my_mlx_putimg(t_fdf *fdf);

void	write_watermark(t_fdf *fdf);
void	animation_write(t_fdf *fdf);
void	loading_write(t_fdf *fdf);

void    init_bresenham_line(t_img *img, t_coords *i_pt, t_coords *f_pt);

void	init_circle_one(t_circle *circle, float x, float y, int radius);
void	init_circle_two(t_circle *circle, float smoothness, int color1, int color2);
void	init_circle_three(t_circle *circle,t_img *img);
void	draw_circle_inward(t_circle *c, int inner_radius, float fade, int mode);
void	draw_circle_outward(t_circle *c, int outer_radius, float fade);
void	draw_circle_loading(t_circle *c, int inner_radius, float fade, float perc);
void	draw_quadrants(t_img *img, t_circle *c, int mode);


void	rotate_x(t_coords *pt, float angle);
void	rotate_y(t_coords *pt, float angle);
void	rotate_z(t_coords *pt, float angle);
void	rotate_map(t_fdf *fdf, int deg_x, int deg_y, int deg_z);

int		key_hook(int keycode, void *fdf);
int		key_hook_release(int keycode, void *fdf);
int		loop_hook(t_fdf *fdf);

void	rotate_hook(t_fdf *fdf, int keycode);
void	scene_hook(t_fdf *fdf, int keycode);
void	perspective_hook(t_fdf *fdf, int keycode);
void	extrude_zoom_hook(t_fdf *fdf, int keycode);
void	move_hook(t_fdf *fdf, int keycode);

void	set_param_loading(t_fdf *fdf, float *fade, int *color_comp, int *color);
void	loading_animation(t_fdf *fdf);
void	draw_loading_screen(t_fdf *fdf, float perc);

void	draw_scene_four(t_fdf *fdf);
void	draw_scene_five(t_fdf *fdf);

void	draw_map(t_fdf *fdf);
void	scale_map(t_fdf *fdf);
void	reset_map(t_fdf *fdf);
void	reset_pos(t_fdf *fdf);
void	reset_zoom(t_fdf *fdf);
void	reset_all(t_fdf *fdf);

void	process_map(t_fdf *fdf, char *map_addr);
void	set_map_dim(t_fdf *fdf, char *map_addr);
void	set_position(t_fdf *fdf);
void	get_map_coords(t_fdf *fdf, char *map_addr);

void	load_color_map(t_fdf *fdf);
void	set_fade_map(float *fade, int color1, int color2, int dist);
int		get_color(char *hexa_num);
int		check_color(char *str);

void	get_backup_map(t_fdf *fdf);
void	get_z_diff(t_fdf *fdf);
void	set_z_scaling(t_fdf *fdf);
void	get_map_height(t_fdf *fdf, char *map_addr);
void	get_map_width(t_fdf *fdf, char *map_addr);

void	swap_persp(t_fdf *fdf, int p);
void	extrude(t_fdf *fdf, float dist);
void	zoom_map(t_fdf *fdf, float amount);
void	rotate_key(t_fdf *fdf, int angle_x, int angle_y, int angle_z);
void	move_key(t_fdf *fdf, int dist, int dir);

int		check_enter(t_fdf *fdf);
int		check_load(t_fdf *fdf);
void	shift_tracker(t_fdf *fdf);
void	animate(t_fdf *fdf);

void	set_color_cube(t_cube *cube, int a, int b);
void	bres_cube(t_fdf *fdf, t_cube *cb);
void	draw_cube(t_fdf *fdf);

void	scale_cube(t_cube *cube);
void	rotate_cube(t_fdf *fdf, t_cube *cube);
void	reset_cube(t_cube *cube);
void	get_backup_cube(t_cube *cube);
void	init_cube(t_cube *cube);

int		mouse_press(int button, int x, int y, void *fdf_B);
int		mouse_rel(int button, int x, int y, void *fdf_B);
int		mouse_move(int x, int y, void *fdf_B);
void	traslate_mouse(t_fdf *fdf, int x, int y);
void	set_mouse_delayer(t_fdf *fdf);

int		t_color(int trgb);
int		r_color(int trgb);
int		g_color(int trgb);
int		b_color(int trgb);
int		trgb_color(int t, int r, int g, int b);

int 	fade_color_bres(t_bresenham *bres);
void    set_fade_bres(t_bresenham *bres);

int		ft_modulo(float v1, float v2);
int		open_map(char *map_addr);
void	set_angles(int *angle);
void	file_err(char *addr);

int		assign_coords(t_fdf *fdf, char **temp, int j, int aux);
void	init_vars(int *j, int *aux, char ***temp);
char	**format_line(char *line);

int		close_all(t_fdf *fdf);
void	free_maps(t_coords **map);
void	free_arr(char **arr);

/*///////////// FONTS \\\\\\\\\\\\\*/

void	free_arr_font(char **arr);
void	draw_letter(t_fdf *fdf, char *points, int param[4]);
void	set_params(int x, int y, int size, int param[4]);
void	init_bresenham_line_font(t_img *img, t_coords *i_pt, t_coords *f_pt);
void	calculate_bresenham_font(t_img *img, t_bresenham *bres);
void	write_str(t_fdf *fdf, char *msg, int *xy, int size);

/*///////////// SNAKE \\\\\\\\\\\\\*/

void	init_snake(t_fdf *fdf);
void	start_snake(t_fdf *fdf);
void	set_enemies(t_sframe *sframe);
void	populate_food(t_sframe *s_frame);

void	snake_lstclear(t_snake **lst);
t_snake	*snake_last(t_snake	*lst);
t_snake	*new_body(int x1, int y1, int x2, int y2);
void	add_body(t_snake **lst, t_snake *new);

int		check_col_snake(t_fdf *fdf, t_snake *snake);
int		check_col_food(t_snake *snake, t_sframe *sframe);
int		enem_check_col_snake(t_fdf *fdf, t_snake *snake, t_sframe *sframe);
void	enem_check_col_food(t_sframe *sframe);

void	write_score(t_fdf *fdf);
void	snake_game_over(t_fdf *fdf);

void	draw_food(t_fdf *fdf, t_sframe *s_frame);
void	draw_enemies(t_fdf *fdf, t_sframe *sframe);
void	draw_snake(t_fdf *fdf, t_snake *snake, t_sframe *s_frame);
void	refresh_snake(t_fdf *fdf);

int		set_snake_dir(t_sframe *sframe, int dist, int dir);
void	get_enem_target(t_fdf *fdf, t_sframe *sframe);
void	move_enemies(t_fdf *fdf, t_sframe *sframe);
void	move_snake(t_fdf *fdf, t_snake *snake, int dist, int dir);
void	move_snake_loop(t_fdf *fdf, t_sframe *sframe);

#endif