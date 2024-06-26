/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:53 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 15:27:36 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
