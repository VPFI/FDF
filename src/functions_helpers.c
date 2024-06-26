/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:56:51 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 19:37:23 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_angles(int *angle)
{
	angle[X] = 0;
	angle[Y] = 0;
	angle[Z] = 0;
}

int	ft_modulo(float v1, float v2)
{
	int	res;

	res = round(sqrtf((v1 * v1) + (v2 * v2)));
	return (res);
}

void	file_err(char *addr)
{
	ft_printf(STDERR_FILENO, "\n    Unexpected error opening: (%s)\n", addr);
	ft_printf(2, "  Please make sure the input follows correct formatting:\n");
	ft_printf(STDERR_FILENO, "         --|| ./fdf map_address.fdf ||--\n\n");
	exit(2);
}

void	draw_quadrants(t_img *img, t_circle *c, int mode)
{
	int		col;
	float	x1;
	float	y1;
	float	x2;
	float	y2;

	x1 = c->x;
	y1 = c->y;
	x2 = c->center_x;
	y2 = c->center_y;
	col = c->color;
	if (mode > 0)
		my_mlx_pixel_put(img, x1, (y2 - (c->y - y2)), col);
	if (mode > 1)
		my_mlx_pixel_put(img, x1, c->y, col);
	if (mode > 2)
		my_mlx_pixel_put(img, (x2 - (x1 - x2)), c->y, col);
	if (mode > 3)
		my_mlx_pixel_put(img, (x2 - (x1 - x2)), (y2 - (c->y - y2)), col);
}

int	open_map(char *map_addr)
{
	int	map;

	map = open(map_addr, O_RDONLY);
	if (map < 0)
		file_err(map_addr);
	return (map);
}
