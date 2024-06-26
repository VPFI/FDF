/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:34:06 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 18:01:58 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init_img_data(t_img *img, void *mlx)
{
	img->img_ptr = mlx_new_image(mlx, WINW, WINH);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= WINW || y >= WINH || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

void	my_mlx_putimg(t_fdf *fdf)
{
	void	*img;

	img = fdf->b_ground.img_ptr;
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, img, 0, 0);
}
