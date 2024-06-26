/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:22:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 18:05:01 by vperez-f         ###   ########.fr       */
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

void	draw_circle_loading(t_circle *c, int i_radius, float fade, float perc)
{
	c->increment = PI / c->smoothness;
	fade = c->radius * fade;
	set_fade_circle(c, c->og_color, c->fin_color, (int)fade);
	while (i_radius <= c->radius)
	{
		c->degree = H_PI;
		c->x = 0;
		c->y = 0;
		c->color = fade_color_circle(c);
		while (fabs(H_PI - c->degree) <= D_PI * perc)
		{
			c->x = c->center_x + ((float)(c->radius) * cos(c->degree));
			c->y = c->center_y + ((float)(c->radius) * sin(-c->degree));
			my_mlx_pixel_put(c->img, c->x, c->y, c->color);
			c->degree -= c->increment;
		}
		c->radius--;
	}
}

void	draw_circle_inward(t_circle *c, int inner_radius, float fade, int mode)
{
	c->increment = PI / c->smoothness;
	fade = c->radius * fade;
	set_fade_circle(c, c->og_color, c->fin_color, (int)fade);
	while (inner_radius <= c->radius)
	{
		c->degree = 0;
		c->x = 0;
		c->y = 0;
		c->color = fade_color_circle(c);
		while (c->degree <= H_PI)
		{
			c->x = c->center_x + ((float)(c->radius) * cos(c->degree));
			c->y = c->center_y + ((float)(c->radius) * sin(c->degree));
			draw_quadrants(c->img, c, mode);
			c->degree += c->increment;
		}
		c->radius--;
	}
}

void	draw_circle_outward(t_circle *c, int outer_radius, float fade)
{
	c->increment = PI / c->smoothness;
	fade = c->radius * fade;
	set_fade_circle(c, c->og_color, c->fin_color, (int)fade);
	while (c->radius <= outer_radius)
	{
		c->x = 0;
		c->y = 0;
		c->degree = 0;
		c->color = fade_color_circle(c);
		while (c->degree <= H_PI)
		{
			c->x = c->center_x + (c->radius * cos(c->degree));
			c->y = c->center_y + (c->radius * sin(c->degree));
			draw_quadrants(c->img, c, 4);
			c->degree += c->increment;
		}
		c->radius++;
	}
}
