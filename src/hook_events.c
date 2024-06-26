/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:23:29 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 15:24:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	key_hook(int keycode, void *fdf)
{
	if (keycode == ESC_KEY)
		close_all(fdf);
	else if (!check_load(fdf))
		return (0);
	else if (keycode == ENTER_KEY)
		swap_persp(fdf, 3);
	else if (!check_enter(fdf))
		return (0);
	else if (keycode == FOUR_KEY || keycode == FIVE_KEY || keycode == SIX_KEY)
		scene_hook(fdf, keycode);
	else if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY
		|| keycode == D_KEY || keycode == Q_KEY || keycode == E_KEY
		|| keycode == SPACE_KEY || keycode == SHIFT_KEY)
		rotate_hook(fdf, keycode);
	else if (keycode == O_KEY || keycode == P_KEY || keycode == I_KEY)
		perspective_hook(fdf, keycode);
	else if (keycode == T_KEY || keycode == G_KEY || keycode == COMMA_KEY
		|| keycode == PERIOD_KEY || keycode == SLASH_KEY)
		extrude_zoom_hook(fdf, keycode);
	else if (keycode == UP_KEY || keycode == DOWN_KEY || keycode == R_KEY
		|| keycode == LEFT_KEY || keycode == RIGHT_KEY)
		move_hook(fdf, keycode);
	return (0);
}

int	key_hook_release(int keycode, void *fdf)
{
	if (keycode == SHIFT_KEY)
		shift_tracker(fdf);
	return (0);
}

int	loop_hook(t_fdf *fdf)
{
	if (fdf->s_frame.dir && fdf->snake_flag == 1)
		move_snake_loop(fdf, &fdf->s_frame);
	if (fdf->animate)
		rotate_key(fdf, 0, -1, 0);
	if (fdf->load_flag && !fdf->entered)
		loading_animation(fdf);
	return (0);
}
