/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:53 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/06 21:34:57 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	if (x > WINW || y > WINH)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	init_img_data(t_img *img, void *mlx)
{	
	img->img_ptr = mlx_new_image(mlx, WINW, WINH);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WINW, WINH, "FDF");
}

int	trgb_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	t_color(int trgb)
{
	return ((trgb >> 24) & 0xFF);	
}

int	r_color(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	g_color(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	b_color(int trgb)
{
	return (trgb & 0xFF);
}

void	set_fade_circle(t_circle *circle, int og_color, int end_color, int fade_dist)
{
	circle->fade_comp[1] = (float)((r_color(end_color)) - (r_color(og_color)))/fade_dist;
	circle->fade_comp[2] = (float)((g_color(end_color)) - (g_color(og_color)))/fade_dist;
	circle->fade_comp[3] = (float)((b_color(end_color)) - (b_color(og_color)))/fade_dist;
	circle->n = 1;
	circle->max = fade_dist;
}

int	fade_color_circle(t_circle *circle)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (circle->n == circle->max)
		return (circle->color);
	t = t_color(circle->og_color);
	r = r_color(circle->og_color) + (circle->fade_comp[1] * circle->n);
	g = g_color(circle->og_color) + (circle->fade_comp[2] * circle->n);
	b = b_color(circle->og_color) + (circle->fade_comp[3] * circle->n);
	circle->n++;
	return (trgb_color(t, r, g, b));
}

void	set_fade(t_point *pt, int og_color, int end_color, int fade_dist)
{
	pt->fade_comp[1] = (float)((r_color(end_color)) - (r_color(og_color)))/fade_dist;
	pt->fade_comp[2] = (float)((g_color(end_color)) - (g_color(og_color)))/fade_dist;
	pt->fade_comp[3] = (float)((b_color(end_color)) - (b_color(og_color)))/fade_dist;
	pt->n = 1;
	pt->max = fade_dist;
}

int	fade_color(t_point *pt)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (pt->n == pt->max)
		return (pt->color);
	t = t_color(pt->og_color);
	r = r_color(pt->og_color) + (pt->fade_comp[1] * pt->n);
	g = g_color(pt->og_color) + (pt->fade_comp[2] * pt->n);
	b = b_color(pt->og_color) + (pt->fade_comp[3] * pt->n);
	pt->n++;
	return (trgb_color(t, r, g, b));
}

void	draw_circle_inward(float center_x, float center_y, int radius, int inner_radius, float smothness, int color1, int color2, float fade, t_img *img)
{
	t_circle circle;
	
	circle.x = 0;
	circle.y = 0;
	circle.center_x = center_x;
	circle.center_y = center_y;
	circle.radius = radius;
	circle.degree = 0;
	circle.smothness = smothness;
	circle.increment = PI / circle.smothness;
	circle.og_color = color1;
	fade = circle.radius * fade;
	set_fade_circle(&circle, circle.og_color, color2, (int)fade);
	while (inner_radius < circle.radius)
	{
		circle.degree = 0;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree < D_PI)
		{
			circle.x = circle.center_x + (circle.radius * cos(circle.degree));
			circle.y = circle.center_y + (circle.radius * sin(circle.degree));
			if ((circle.x < 0 || (WINW) <= circle.x) || (circle.y < 0 || (WINH) <= circle.y))
				circle.x = 0;
			else 
				my_mlx_pixel_put(img, circle.x, circle.y, circle.color);		
			//circle.color = fade_color_circle(&circle);
			circle.degree += circle.increment;
		}
		circle.radius--;
	}	
}

void	draw_circle_outward(float center_x, float center_y, int radius, int outer_radius, float smothness, int color1, int color2, float fade, t_img *img)
{
	t_circle circle;
	
	circle.x = 0;
	circle.y = 0;
	circle.center_x = center_x;
	circle.center_y = center_y;
	circle.radius = radius;
	circle.degree = 0;
	circle.smothness = smothness;
	circle.increment = PI / circle.smothness;
	circle.og_color = color1;
	fade = circle.radius * fade;
	set_fade_circle(&circle, circle.og_color, color2, (int)fade);
	while (circle.radius < outer_radius)
	{
		circle.degree = 0;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree < D_PI)
		{
			circle.x = circle.center_x + (circle.radius * cos(circle.degree));
			circle.y = circle.center_y + (circle.radius * sin(circle.degree));
			if ((circle.x < 0 || (WINW) <= circle.x) || (circle.y < 0 || (WINH) <= circle.y))
				circle.x = 0;
			else 
				my_mlx_pixel_put(img, circle.x, circle.y, circle.color);		
			//circle.color = fade_color_circle(&circle);
			circle.degree += circle.increment;
		}
		circle.radius++;
	}		
}

void	close_all(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
		mlx_destroy_display(fdf->mlx_ptr);
	exit(0);
}

void	draw_scene_one(t_fdf *fdf)
{
	//add img_ptr as param make it generic
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 1300, 6000, BLACK, ORANGE_GULF, 0.85, &fdf->b_ground);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	draw_scene_two(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 6000, BLACK, CYAN_GULF, 0.85, &fdf->b_ground);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	draw_scene_three(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 1300, 6000, BLACK, ORANGE_GULF, 0.85, &fdf->b_ground);	
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 6000, BLACK, CYAN_GULF, 0.85, &fdf->b_ground);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	draw_scene_four(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_inward(CENTER_X, CENTER_Y, 1500, 0, 1000, WHITE, BLACK, 0.7, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 300, BLACK, CYAN_GULF, 0.85, &fdf->b_ground);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	draw_scene_five(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y, 510, 1300, 900, ORANGE_GULF, ORANGE_GULF, 1, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 400, CYAN_GULF, CYAN_GULF, 1, &fdf->b_ground);
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 510, 4000, BLACK, ORANGE_GULF, 0.03, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 500, 490, 4000, BLACK, CYAN_GULF, 0.03, &fdf->b_ground);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	draw_scene_six(t_fdf *fdf)
{
	t_coords i_pt;
	t_coords f_pt;

	i_pt.x = WINW * 0.25;
	i_pt.y = WINH * 0.25;
	f_pt.x = WINW * 0.75;
	f_pt.y = WINH * 0.75;

	int n = 2;
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	init_bresenham_line(fdf, &i_pt, &f_pt);
	while (0 < n)
	{
		i_pt.x += 50;
		i_pt.y += 50;
		f_pt.x += 50;
		f_pt.y += 50;
		init_bresenham_line(fdf, &i_pt, &f_pt);
		n--;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

int	key_hook(int keycode, void *fdf)
{
	if (keycode == ESC_KEY)
		close_all(fdf);
	else if (keycode == ONE_KEY)
		draw_scene_one(fdf);
	else if (keycode == TWO_KEY)
		draw_scene_two(fdf);
	else if (keycode == THREE_KEY)
		draw_scene_three(fdf);
	else if (keycode == FOUR_KEY)
		draw_scene_four(fdf);
	else if (keycode == FIVE_KEY)
		draw_scene_five(fdf);
	else if (keycode == SIX_KEY)
		draw_scene_six(fdf);
	else if (keycode == M_KEY)
		draw_welcome_menu(fdf);
	return (0);
}

void	my_string_put(t_fdf *fdf, int x, int y, int color, char *msg)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y, color, msg);
}

void	draw_sides(t_fdf *fdf, float extent, float y_start, float y_finish, int color1, int color2)
{
	t_point	pt;
	float	x_base;
	float	y_base;
	
	x_base = 0;
	y_base = WINH * y_start;
	y_finish = WINH * y_finish;
	extent = WINW * extent;
	pt.x = x_base;
	pt.y = y_base;
	pt.og_color = color1;
	set_fade(&pt, pt.og_color, color2, WINW * 0.25);
	while (pt.x < extent)
	{
		pt.y = y_base;
		//set_fade(&pt, pt.og_color, BLACK, WINH * 0.25);
		//while (pt.y < WINH * 0.25)
		while (pt.y < y_finish)
		{
			my_mlx_pixel_put(&fdf->b_ground, pt.x, pt.y, pt.color);
			my_mlx_pixel_put(&fdf->b_ground, ((WINW - 1) - pt.x), ((WINH - 1) - pt.y), pt.color);
			pt.y++;
		}
		pt.color = fade_color(&pt);
		pt.x++;
	}	
}

void	draw_welcome_menu(t_fdf *fdf)
{
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_sides(fdf, 0.5, 0, 1, ORANGE_GULF, BLACK);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
	my_string_put(fdf, CENTER_X, CENTER_Y- 25, CYAN_GULF, "|");
	my_string_put(fdf, CENTER_X - 11, CENTER_Y, CYAN_GULF, "START");
	my_string_put(fdf, CENTER_X - 17, CENTER_Y + 20, CYAN_GULF, "=======");
}

void	get_map_width(t_fdf *fdf, char *map_addr)
{
	char	*line;
	char	**list;
	int		i;
	int		map;

	i = 0;
	map = open(map_addr, O_RDONLY);
	line = get_next_line(map);
	list = ft_split(line, ' ');
	while (list[i] != NULL)
		i++;
	fdf->map_W = i;
	close(map);
}

void	get_map_height(t_fdf *fdf, char *map_addr)
{
	char	*line;
	int		i;
	int		map;

	i = 0;
	map = open(map_addr, O_RDONLY);
	line = get_next_line(map);
	while (line != NULL)
	{
		i++;	
		line = get_next_line(map);
	}
	fdf->map_H = i;
	close(map);
}

int	check_color(char *str)
{
	while (*str != '\0')
	{
		if (*str == ',')
			return (1);
		str++;
	}
	return (0);
	
}

void	get_map_coords(t_fdf *fdf, char *map_addr)
{
	char	**temp;
	char	*line;
	int		i;
	int		j;
	int		aux;
	int		map;

	i = 0;
	j = 0;
	aux = 0;
	map = open(map_addr, O_RDONLY);
	fdf->coords = (t_coords *)malloc((fdf->map_W * fdf->map_H)); //??
	if (!fdf->coords)
		exit(1);
	line = get_next_line(map);
	while (j < fdf->map_H)
	{
		temp = ft_split(line, ' ');
		i = 0;
		while (temp[i] != NULL)
		{
			if (check_color(temp[i]))
			{
				//fdf->coords[i].color = ft_atoi((ft_split(temp[i], ',')[1]));
				//temp[i] = (ft_split(temp[i], ',')[0]);
			}
			fdf->coords[aux].x = i;
			fdf->coords[aux].y = j;
			fdf->coords[aux].z = ft_atoi(temp[i]);
			i++;
			aux++;
		}	
		line = get_next_line(map);
		j++;
	}
	close(map);
}

void	process_map(t_fdf *fdf, char *map_addr)
{
	get_map_width(fdf, map_addr);
	get_map_height(fdf, map_addr);
	get_map_coords(fdf, map_addr);
	/*
	int n = fdf->map_W * fdf->map_H;
	int i = 0;
	printf("%i -- %i\n", n, i);
	
	while (i < n)
	{
		printf("X:%f -- Y:%f -- Z:%f |||| %i\n", fdf->coords[i].x, fdf->coords[i].y, fdf->coords[i].z, i);
		i++;
	}*/
}

void	calculate_bresenham(t_img *img, t_bresenham *bres)
{
	t_coords res_pt;
	
	res_pt.x = bres->i_pt.x;
	res_pt.y = bres->i_pt.y;
	while (res_pt.x < bres->f_pt.x && res_pt.y < bres->f_pt.y)
	{
		if (bres->d >= 0)
		{
			my_mlx_pixel_put(img, res_pt.x, res_pt.y, CYAN_GULF);
			res_pt.y++;
			bres->d += bres->i_two;
		}
		else 
		{
			my_mlx_pixel_put(img, res_pt.x, res_pt.y, CYAN_GULF);
			bres->d += bres->i_one;
		}
		res_pt.x++;
	}
}

void	init_bresenham_line(t_fdf *fdf, t_coords *i_pt, t_coords *f_pt)
{
	t_bresenham	bres;

	bres.i_pt.x = i_pt->x;
	bres.i_pt.y = i_pt->y;
	bres.f_pt.x = f_pt->x;
	bres.f_pt.y = f_pt->y;
	bres.dx = bres.f_pt.x - bres.i_pt.x;
	bres.dy = bres.f_pt.y - bres.i_pt.y;
	bres.i_one = 2 * bres.dy;
	bres.i_two = 2 * (bres.dy - bres.dx);
	bres.d = bres.i_one - bres.dx;
	calculate_bresenham(&fdf->b_ground, &bres);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	//t_img	img;
	//int	img_width;
	//int	img_height;

	argc = 0;
	if (argv[0])
		init_fdf(&fdf);
	process_map(&fdf, argv[1]);
	draw_welcome_menu(&fdf);
	//img.img_ptr = mlx_xpm_file_to_image(fdf.mlx_ptr, "./test2.xpm", &img_width, &img_height);
	//mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, img.img_ptr, 0, 0);
	mlx_hook(fdf.win_ptr, KEYUP, (1L<<1), key_hook, (void *)&fdf);
	mlx_loop(fdf.mlx_ptr);
}
