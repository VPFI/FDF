/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_controllers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:25:12 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 15:25:52 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	rotate_hook(t_fdf *fdf, int keycode)
{
	if (keycode == W_KEY)
		rotate_key(fdf, 5, 0, 0);
	else if (keycode == S_KEY)
		rotate_key(fdf, -5, 0, 0);
	else if (keycode == D_KEY)
		rotate_key(fdf, 0, 5, 0);
	else if (keycode == A_KEY)
		rotate_key(fdf, 0, -5,0);
	else if (keycode == Q_KEY)
		rotate_key(fdf, 0, 0, 5);
	else if (keycode == E_KEY)
		rotate_key(fdf, 0, 0, -5);
	else if (keycode == SPACE_KEY)
		animate(fdf);
	else if (keycode == SHIFT_KEY)
		shift_tracker(fdf);
}

void	scene_hook(t_fdf *fdf, int keycode)
{
	if (keycode == FOUR_KEY)
		draw_scene_four(fdf);
	else if (keycode == FIVE_KEY)
		draw_scene_five(fdf);
	else if (keycode == SIX_KEY)
		init_snake(fdf);
}

void	perspective_hook(t_fdf *fdf, int keycode)
{
	if (keycode == O_KEY)
		swap_persp(fdf, 1);
	else if (keycode == P_KEY)
		swap_persp(fdf, 2);
	else if (keycode == I_KEY)
		swap_persp(fdf, 3);
}

void	extrude_zoom_hook(t_fdf *fdf, int keycode)
{
	if (keycode == T_KEY)
		extrude(fdf, 1.1);
	else if (keycode == G_KEY)
		extrude(fdf, 0.9);
	else if (keycode == COMMA_KEY)
		zoom_map(fdf, 0.9);
	else if (keycode == PERIOD_KEY)
		zoom_map(fdf, 1.1);
	else if (keycode == SLASH_KEY)
		reset_zoom(fdf);
}

void	move_hook(t_fdf *fdf, int keycode)
{
	if (keycode == UP_KEY)
		move_key(fdf, -20, 1);
	else if (keycode == DOWN_KEY)
		move_key(fdf, 20, 1);
	else if (keycode == LEFT_KEY)
		move_key(fdf, -20, 0);
	else if (keycode == RIGHT_KEY)
		move_key(fdf, 20, 0);
	else if (keycode == R_KEY)
		reset_pos(fdf);
}
