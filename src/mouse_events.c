/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:46:27 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 17:58:40 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_mouse_delayer(t_fdf *fdf)
{
	if (20000 < fdf->map_size && fdf->map_size < 100000)
		fdf->mouse_delayer = 5;
	else if (100000 < fdf->map_size && fdf->map_size < 1000000)
		fdf->mouse_delayer = 7;
	else if (1000000 < fdf->map_size)
		fdf->mouse_delayer = 13;
}

int	mouse_press(int button, int x, int y, void *fdf_B)
{
	t_fdf	*fdf;

	fdf = fdf_B;
	if (!check_enter(fdf) || !check_load(fdf))
		return (0);
	if (button == 1)
	{
		fdf->is_left_mouse_pres = 1;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	else if (button == 2)
		reset_all(fdf);
	else if (button == 3)
	{
		fdf->is_right_mouse_pres = 1;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	else if (button == 4)
		zoom_map(fdf, 1.1);
	else if (button == 5)
		zoom_map(fdf, 0.9);
	return (0);
}

int	mouse_rel(int button, int x, int y, void *fdf_B)
{
	t_fdf	*fdf;

	fdf = fdf_B;
	if (button == 1)
	{
		fdf->is_left_mouse_pres = 0;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	else if (button == 3)
	{
		fdf->is_right_mouse_pres = 0;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	return (0);
}

void	traslate_mouse(t_fdf *fdf, int x, int y)
{
	int	i;

	i = 0;
	while (i < fdf->map_size)
	{
		if (y)
			fdf->map[i].y += y;
		if (x)
			fdf->map[i].x += x;
		i++;
	}
	if (y)
		fdf->tras[Y] += y;
	if (x)
		fdf->tras[X] += x;
	draw_map(fdf);
}

int	mouse_move(int x, int y, void *fdf_B)
{
	t_fdf	*fdf;
	int		dist_x;
	int		dist_y;

	fdf = fdf_B;
	if (!check_enter(fdf) || (!fdf->is_right_mouse_pres
			&& !fdf->is_left_mouse_pres))
		return (0);
	if (!check_load(fdf) || (fdf->mouse_tracker++ % fdf->mouse_delayer))
		return (0);
	dist_x = (x - fdf->mouse_x);
	dist_y = (y - fdf->mouse_y);
	if (fdf->is_right_mouse_pres)
		traslate_mouse(fdf, dist_x, dist_y);
	if (fdf->is_left_mouse_pres && fdf->shift_tracker)
		rotate_key(fdf, 0, 0, dist_x / 4 + dist_y / 4);
	else if (fdf->is_left_mouse_pres)
		rotate_key(fdf, dist_y / 2, dist_x / 2, 0);
	fdf->mouse_x = x;
	fdf->mouse_y = y;
	return (0);
}
