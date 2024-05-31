/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:53 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/31 02:29:38 by vperez-f         ###   ########.fr       */
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

int	main(void)
{
	t_fdf	fdf;
	t_img	img;
	t_point	pt;
	t_circle	circle;
	float	x_base;
	float	y_base;
	float	ratio;

	init_fdf(&fdf);
	init_img_data(&img, fdf.mlx_ptr);
	x_base = 0;
	y_base = 0;
	pt.x = x_base;
	pt.y = y_base;
	pt.og_color = ORANGE_GULF;
	ratio = WINW * 0.25;
	/*set_fade(&pt, pt.og_color, BLACK, WINW * 0.25);
	while (pt.x < WINW * 0.25)
	{
		pt.y = y_base;
		while (pt.y < WINH)
		{
			my_mlx_pixel_put(&img, pt.x, pt.y, pt.color);
			my_mlx_pixel_put(&img, ((WINW - 1) - pt.x), ((WINH - 1) - pt.y), pt.color);
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
			my_mlx_pixel_put(&img, pt.x, pt.y, pt.color);
			my_mlx_pixel_put(&img, ((WINW - 1) - pt.x), ((WINH - 1) - pt.y), pt.color);
			pt.color = fade_color(&pt);
			pt.y++;
		}
		pt.x++;
	}*/
	circle.x = 0;
	circle.y = 0;
	circle.center_x = WINW / 2;
	circle.center_y = WINH / 2;
	circle.radius = 500;
	circle.degree = 0;
	circle.smothness = 10000;
	circle.increment = PI / circle.smothness;
	circle.og_color = BLACK;
	int hipo = (int)sqrt((WINW * WINW) + (WINH * WINH));
	set_fade_circle(&circle, circle.og_color, ORANGE_GULF, circle.radius * 0.85);
	//circle.radius + circle.center_x < (WINW) || circle.radius + circle.center_y < (WINH)
	while (circle.radius < hipo)
	{
		circle.degree = 0;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree < D_PI)
		{
			circle.x = circle.center_x + (circle.radius * cos(circle.degree));
			circle.y = circle.center_y + (circle.radius * sin(circle.degree));
			if (circle.x < 0)
				circle.x = 0;
			else if ((WINW) <= circle.x)
				circle.x = WINW - 1;
			if (circle.y < 0)
				circle.y = 0;
			else if ((WINH) <= circle.y)
				circle.y = WINH - 1;
			my_mlx_pixel_put(&img, circle.x, circle.y, circle.color);		
			circle.degree += circle.increment;
		}
		circle.radius++;
	}
	circle.x = 0;
	circle.y = 0;
	circle.center_x = WINW / 2;
	circle.center_y = WINH / 2;
	circle.radius = 490;
	circle.degree = 0;
	circle.smothness = 3000;
	circle.increment = PI / circle.smothness;
	circle.og_color = BLACK;
	set_fade_circle(&circle, circle.og_color, CYAN_GULF, circle.radius * 0.9);
	while (0 < circle.radius)
	{
		circle.degree = 0;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree < D_PI)
		{
			circle.x = circle.center_x + (circle.radius * cos(circle.degree));
			circle.y = circle.center_y + (circle.radius * sin(circle.degree));
			if (circle.x < 0)
				circle.x = 0;
			else if ((WINW) <= circle.x)
				circle.x = WINW - 1;
			if (circle.y < 0)
				circle.y = 0;
			else if ((WINH) <= circle.y)
				circle.y = WINH - 1;
			//circle.color = fade_color_circle(&circle);
			my_mlx_pixel_put(&img, circle.x, circle.y, circle.color);		
			circle.degree += circle.increment;
		}
		circle.radius--;
	}
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, img.img_ptr, 0, 0);
	mlx_loop(fdf.mlx_ptr);
}
