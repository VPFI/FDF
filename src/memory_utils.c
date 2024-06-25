/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:43:01 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 18:57:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
	}
}

void	free_maps(t_coords **map)
{
	if (map)
	{
		if (*map)
			free(*map);
	}
}

int	close_all(t_fdf *fdf)
{
	if (fdf->snake)
		snake_lstclear(&fdf->snake);
	if (fdf->map)
		free_maps(&fdf->map);
	if (fdf->backup_map)
		free_maps(&fdf->backup_map);
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		if (fdf->mlx_ptr)
			free(fdf->mlx_ptr);
	}
	exit(0);
	return (0);
}
