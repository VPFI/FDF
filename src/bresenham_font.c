/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_font.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:49:27 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 17:17:35 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	calculate_bresenham_font(t_img *img, t_bresenham *bres)
{
	int	res_x;
	int	res_y;

	res_x = bres->i_pt.x;
	res_y = bres->i_pt.y;
	while (!(res_x == bres->f_pt.x) || !(res_y == bres->f_pt.y))
	{
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
	my_mlx_pixel_put(img, res_x, res_y, bres->color);
}

void	init_bresenham_line_font(t_img *img, t_coords *i_pt, t_coords *f_pt)
{
	t_bresenham	bres;

	bres.i_pt.x = (int)round(i_pt->x);
	bres.i_pt.y = (int)round(i_pt->y);
	bres.i_pt.color = WHITE;
	bres.f_pt.x = (int)round(f_pt->x);
	bres.f_pt.y = (int)round(f_pt->y);
	bres.f_pt.color = WHITE;
	bres.color = DEF_COLOR_MAX;
	bres.i_one = -1;
	bres.i_two = -1;
	bres.dx = fabs(bres.f_pt.x - bres.i_pt.x);
	bres.dy = -fabs(bres.f_pt.y - bres.i_pt.y);
	if (bres.i_pt.x < bres.f_pt.x)
		bres.i_one = 1;
	if (bres.i_pt.y < bres.f_pt.y)
		bres.i_two = 1;
	bres.d = bres.dx + bres.dy;
	calculate_bresenham_font(img, &bres);
}
