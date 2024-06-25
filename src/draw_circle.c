/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:22:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 21:07:15 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_fade_circle(t_circle *circle, int i_col, int f_col, int f_dt)
{
	circle->fade_comp[1] = (float)((r_color(f_col)) - (r_color(i_col))) / f_dt;
	circle->fade_comp[2] = (float)((g_color(f_col)) - (g_color(i_col))) / f_dt;
	circle->fade_comp[3] = (float)((b_color(f_col)) - (b_color(i_col))) / f_dt;
	circle->n = 1;
	circle->max = f_dt;
}

int	fade_color_circle(t_circle *circle)
{
	int t;
	int r;
	int g;
	int b;

	if (circle->n == circle->max)
		return (circle->color);
	t = t_color(circle->og_color);
	r = r_color(circle->og_color) + (circle->fade_comp[1] * circle->n);
	g = g_color(circle->og_color) + (circle->fade_comp[2] * circle->n);
	b = b_color(circle->og_color) + (circle->fade_comp[3] * circle->n);
	circle->n++;
	return (trgb_color(t, r, g, b));
}

void	draw_circle_loading(float center_x, float center_y, int radius, int inner_radius, float smothness, int color1, int color2, float fade, t_img *img, float perc)
{
	t_circle c;

	c.center_x = center_x;
	c.center_y = center_y;
	c.radius = radius;
	c.smothness = smothness;
	c.increment = PI / c.smothness;
	c.og_color = color1;
	fade = c.radius * fade;
	set_fade_circle(&c, c.og_color, color2, (int)fade);
	while (inner_radius <= c.radius)
	{
		c.degree = H_PI;
		c.x = 0;
		c.y = 0;
		c.color = fade_color_circle(&c);
		while (fabs(H_PI - c.degree) <= D_PI * perc)
		{
			c.x = c.center_x + ((float)(c.radius) * cos(c.degree));
			c.y = c.center_y + ((float)(c.radius) * sin(-c.degree));
			my_mlx_pixel_put(img, c.x, c.y, c.color);
			c.degree -= c.increment;
		}
		c.radius--;
	}
}
void	draw_circle_inward(float center_x, float center_y, int radius, int inner_radius, float smothness, int color1, int color2, float fade, t_img *img, int mode)
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
	while (inner_radius <= circle.radius)
	{
		circle.degree = 0;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree <= H_PI)
		{
			circle.x = circle.center_x + ((float)(circle.radius) * cos(circle.degree));
			circle.y = circle.center_y + ((float)(circle.radius) * sin(circle.degree));
			if (mode > 0)
				my_mlx_pixel_put(img, circle.x, (center_y - (circle.y - center_y)), circle.color);
			if (mode > 1)
				my_mlx_pixel_put(img, circle.x, circle.y, circle.color);
			if (mode > 2)
				my_mlx_pixel_put(img, (center_x - (circle.x - center_x)), circle.y, circle.color);
			if (mode > 3)
				my_mlx_pixel_put(img, (center_x - (circle.x - center_x)), (center_y - (circle.y - center_y)), circle.color);
			circle.degree += circle.increment;
		}
		circle.radius--;
	}
}

void	draw_circle_outward(float x, float y, int radius, int outer_radius, float smothness, int color1, int color2, float fade, t_img *img)
{
	t_circle circle;

	circle.radius = radius;
	circle.smothness = smothness;
	circle.increment = PI / circle.smothness;
	fade = circle.radius * fade;
	circle.og_color = color1;
	set_fade_circle(&circle, color1, color2, (int)fade);
	while (circle.radius <= outer_radius)
	{
		circle.degree = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree <= H_PI)
		{
			circle.x = x + (circle.radius * cos(circle.degree));
			circle.y = y + (circle.radius * sin(circle.degree));
			my_mlx_pixel_put(img, circle.x, circle.y, circle.color);
			my_mlx_pixel_put(img, (x - (circle.x - x)), circle.y, circle.color);
			my_mlx_pixel_put(img, (x - (circle.x - x)), (y - (circle.y - y)), circle.color);
			my_mlx_pixel_put(img, circle.x, (y - (circle.y - y)), circle.color);
			circle.degree += circle.increment;
		}
		circle.radius++;
	}
}
