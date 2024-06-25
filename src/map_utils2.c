/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:44:04 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:08:48 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	get_map_width(t_fdf *fdf, char *map_addr)
{
	char	*line;
	char	*temp_line;
	char	**list;
	int		i;
	int		map;

	i = 0;
	map = open(map_addr, O_RDONLY);
	if (map < 0)
		file_err(map_addr);
	line = get_next_line(map);
	temp_line = ft_strtrim(line, "\n");
	list = ft_split(temp_line, ' ');
	free(temp_line);
	while (list[i] != NULL)
		i++;
	fdf->map_W = i;
	if (line)
		free(line);
	free_arr(list);
	close(map);
}

void	get_map_height(t_fdf *fdf, char *map_addr)
{
	char	*line;
	int		i;
	int		map;

	i = 0;
	map = open(map_addr, O_RDONLY);
	if (map < 0)
		file_err(map_addr);
	line = get_next_line(map);
	while (line != NULL)
	{
		i++;
		if (line)
			free(line);
		line = get_next_line(map);
	}
	fdf->map_H = i;
	if (line)
		free(line);
	close(map);
}

void	set_z_scaling(t_fdf *fdf)
{
	if (0 < fdf->z_diff && fdf->z_diff < 500)
		fdf->z_factor = 1;
	else if (500 < fdf->z_diff && fdf->z_diff < 2000)
		fdf->z_factor = 0.2;
	else if (2000 < fdf->z_diff)
		fdf->z_factor = 0.1;
}

void	get_z_diff(t_fdf *fdf)
{
	int	i;
	int	z_min;
	int	z_max;

	i = 0;
	z_min = 0;
	z_max = 0;
	while (i < fdf->map_size)
	{
		if (fdf->map[i].z < z_min)
			z_min = fdf->map[i].z;
		if (fdf->map[i].z > z_max)
			z_max = fdf->map[i].z;
		i++;
	}
	fdf->z_min = z_min;
	fdf->z_max = z_max;
	fdf->z_diff = z_max - z_min;
}

void	get_backup_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->backup_map = (t_coords *)malloc(sizeof(t_coords) * (fdf->map_size));
	if (!fdf->backup_map)
		exit (1);
	while (i < fdf->map_size)
	{
		fdf->backup_map[i] = fdf->map[i];
		i++;
	}
}
