/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:53 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/31 09:18:10 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
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
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WINW, WINH, "TEST");
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
	mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_destroy(fdf->mlx_ptr);
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

int	key_hook(int keycode, void *fdf)
{
	if (keycode == 53)
		close_all(fdf);
	else if (keycode == ONE_KEY)
		draw_scene_one(fdf);
	else if (keycode == TWO_KEY)
		draw_scene_two(fdf);
	else if (keycode == THREE_KEY)
		draw_scene_three(fdf);
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
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_sides(fdf, 0.5, 0, 1, ORANGE_GULF, BLACK);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
	my_string_put(fdf, CENTER_X, CENTER_Y- 25, CYAN_GULF, "|");
	my_string_put(fdf, CENTER_X - 20, CENTER_Y, CYAN_GULF, "START");
	my_string_put(fdf, CENTER_X - 30, CENTER_Y + 20, CYAN_GULF, "=======");
}

int	main(void)
{
	t_fdf	fdf;
	t_point	pt;
	t_img	img;
	float	x_base;
	float	y_base;
	int		img_width;
	int		img_height;

	init_fdf(&fdf);
	//draw_welcome_menu(&fdf);
	img.img_ptr = mlx_xpm_file_to_image(fdf.mlx_ptr, "./test2.xpm", &img_width, &img_height);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, img.img_ptr, 0, 0);
		
	x_base = 0;
	y_base = 0;
	pt.x = x_base;
	pt.y = y_base;
	pt.og_color = ORANGE_GULF;
	/*set_fade(&pt, pt.og_color, BLACK, WINW * 0.25);
	while (pt.x < WINW * 0.25)
	{
		pt.y = y_base;
		while (pt.y < WINH)
		{
			my_mlx_pixel_put(&fdf.b_ground, pt.x, pt.y, pt.color);
			my_mlx_pixel_put(&fdf.b_ground, ((WINW - 1) - pt.x), ((WINH - 1) - pt.y), pt.color);
			pt.y++;
		}
		pt.color = fade_color(&pt);
		pt.x++;
	}*/
	/*
	pt.x = 0;
	pt.y = 0;
	while (pt.x < WINW)
	{
		pt.y = y_base;
		set_fade(&pt, pt.og_color, BLACK, WINH * 0.25);
		while (pt.y < WINH * 0.25)
		{
			my_mlx_pixel_put(&fdf.b_ground, pt.x, pt.y, pt.color);
			my_mlx_pixel_put(&fdf.b_ground, ((WINW - 1) - pt.x), ((WINH - 1) - pt.y), pt.color);
			pt.color = fade_color(&pt);
			pt.y++;
		}
		pt.x++;
	}*/
	//draw_circle_outward(CENTER_X, CENTER_Y, 500, 1300, 6000, BLACK, ORANGE_GULF, 0.85, &fdf.b_ground);
	//draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 6000, BLACK, CYAN_GULF, 0.85, &fdf.b_ground);
	//mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.b_ground.img_ptr, 0, 0);
	mlx_hook(fdf.win_ptr, KEYUP, 0, key_hook, (void *)&fdf);
	mlx_loop(fdf.mlx_ptr);
}
