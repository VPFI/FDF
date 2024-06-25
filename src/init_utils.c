/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:53:49 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 20:48:03 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init_fdf(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WINW, WINH, "FDF");
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	init_cube(&fdf->cube);
	fdf->mouse_delayer = 3;
	fdf->zoom = 0.7;
	fdf->z_factor = 1;
	fdf->increment = 1;
}