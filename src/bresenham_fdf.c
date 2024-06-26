/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_fdf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:36:07 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 18:07:26 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_fade_bres(t_bresenham *bres)
{
	float	dist_x;
	float	dist_y;
	int		c1;
	int		c2;

	c1 = bres->i_pt.color;
	c2 = bres->f_pt.color;
	dist_x = bres->f_pt.x - bres->i_pt.x;
	dist_y = bres->f_pt.y - bres->i_pt.y;
	bres->max = ft_modulo(dist_x, dist_y);
	bres->fade_comp[1] = (float)((r_color(c2)) - (r_color(c1))) / bres->max;
	bres->fade_comp[2] = (float)((g_color(c2)) - (g_color(c1))) / bres->max;
	bres->fade_comp[3] = (float)((b_color(c2)) - (b_color(c1))) / bres->max;
	bres->n = 1;
}

int	fade_color_bres(t_bresenham *bres)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (bres->n == bres->max)
		return (bres->color);
	t = t_color(bres->i_pt.color);
	r = r_color(bres->i_pt.color) + (bres->fade_comp[1] * bres->n);
	g = g_color(bres->i_pt.color) + (bres->fade_comp[2] * bres->n);
	b = b_color(bres->i_pt.color) + (bres->fade_comp[3] * bres->n);
	bres->n++;
	return (trgb_color(t, r, g, b));
}

int	bres_check(t_coords *i_pt, t_coords *f_pt)
{
	if ((i_pt->x < 0 && f_pt->x < 0) || (WINW < i_pt->x && WINW < f_pt->x))
		return (1);
	if ((i_pt->y < 0 && f_pt->y < 0) || (WINH < i_pt->y && WINH < f_pt->y))
		return (1);
	return (0);
}

void	calculate_bresenham(t_img *img, t_bresenham *bres)
{
	int	res_x;
	int	res_y;

	res_x = bres->i_pt.x;
	res_y = bres->i_pt.y;
	while (!(res_x == bres->f_pt.x) || !(res_y == bres->f_pt.y))
	{
		bres->color = fade_color_bres(bres);
		my_mlx_pixel_put(img, res_x, res_y, bres->color);
		bres->d2 = bres->d * 2;
		if (bres->d2 >= bres->dy)
		{
			bres->d += bres->dy;
			res_x += bres->i_one;
		}
		if (bres->d2 <= bres->dx)
		{
			bres->d += bres->dx;
			res_y += bres->i_two;
		}
	}
	bres->color = fade_color_bres(bres);
	my_mlx_pixel_put(img, res_x, res_y, bres->color);
}

void	init_bresenham_line(t_img *img, t_coords *i_pt, t_coords *f_pt)
{
	t_bresenham	bres;

	if (bres_check(i_pt, f_pt))
		return ;
	bres.i_pt.x = (int)round(i_pt->x);
	bres.i_pt.y = (int)round(i_pt->y);
	bres.i_pt.color = i_pt->color;
	bres.f_pt.x = (int)round(f_pt->x);
	bres.f_pt.y = (int)round(f_pt->y);
	bres.f_pt.color = f_pt->color;
	set_fade_bres(&bres);
	bres.i_one = -1;
	bres.i_two = -1;
	bres.dx = fabs(bres.f_pt.x - bres.i_pt.x);
	bres.dy = -fabs(bres.f_pt.y - bres.i_pt.y);
	if (bres.i_pt.x < bres.f_pt.x)
		bres.i_one = 1;
	if (bres.i_pt.y < bres.f_pt.y)
		bres.i_two = 1;
	bres.d = bres.dx + bres.dy;
	calculate_bresenham(img, &bres);
}
