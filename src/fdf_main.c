/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:53 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/31 04:13:54 by vperez-f         ###   ########.fr       */
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

int	main(void)
{
	t_fdf	fdf;
	t_img	img;
	t_point	pt;
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
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 1300, 6000, BLACK, ORANGE_GULF, 0.85, &img);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 6000, BLACK, CYAN_GULF, 0.85, &img);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, img.img_ptr, 0, 0);
	mlx_loop(fdf.mlx_ptr);
}
