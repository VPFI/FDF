/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:53 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 21:07:42 by vperez-f         ###   ########.fr       */
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
	else if (keycode == FOUR_KEY)
		draw_scene_four(fdf);
	else if (keycode == FIVE_KEY)
		draw_scene_five(fdf);
	else if (keycode == SIX_KEY)
		init_snake(fdf);
	else if (keycode == W_KEY)
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
	else if (keycode == R_KEY)
		reset_pos(fdf);
	else if (keycode == O_KEY)
		swap_persp(fdf, 1);
	else if (keycode == P_KEY)
		swap_persp(fdf, 2);
	else if (keycode == I_KEY)
		swap_persp(fdf, 3);
	else if (keycode == T_KEY)
		extrude(fdf, 1.1);
	else if (keycode == G_KEY)
		extrude(fdf, 0.9);
	else if (keycode == COMMA_KEY)
		zoom_map(fdf, 0.9);
	else if (keycode == PERIOD_KEY)
		zoom_map(fdf, 1.1);
	else if (keycode == SLASH_KEY)
		reset_zoom(fdf);
	else if (keycode == UP_KEY)
		move_key(fdf, -20, 1);
	else if (keycode == DOWN_KEY)
		move_key(fdf, 20, 1);
	else if (keycode == LEFT_KEY)
		move_key(fdf, -20, 0);
	else if (keycode == RIGHT_KEY)
		move_key(fdf, 20, 0);
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

int	main(int argc, char **argv)
{
	t_fdf   fdf;

	if (argc != 2 || !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
		file_err(argv[1]);
	init_fdf(&fdf);
	draw_loading_screen(&fdf, 0.1);
	process_map(&fdf, argv[1]);
	mlx_hook(fdf.win_ptr, KEYDOWN, KEYPRESS_M, key_hook, (void *)&fdf);
	mlx_hook(fdf.win_ptr, KEYUP, KEYRELEASE_M, key_hook_release, (void *)&fdf);
	mlx_hook(fdf.win_ptr, DESTROY, STRUCTNOTIFY_M, close_all, &fdf);
	mlx_hook(fdf.win_ptr, MOUSEDOWN, MOUSEPRESS_M, mouse_press, (void *)&fdf);
	mlx_hook(fdf.win_ptr, MOUSEUP, MOUSERELEASE_M, mouse_rel, (void *)&fdf);
	mlx_hook(fdf.win_ptr, MOUSEMOVE, MOUSEMOVE_M, mouse_move, (void *)&fdf);
	mlx_loop_hook(fdf.mlx_ptr, loop_hook, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
