/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:37:04 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/27 23:14:23 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	get_map_coords(t_fdf *fdf, char *map_addr)
{
	char	**temp;
	char	*line;
	int		j;
	int		aux;
	int		map;

	init_vars(&j, &aux, &temp);
	map = open_map(map_addr);
	fdf->map = (t_coords *)malloc(sizeof(t_coords) * (fdf->map_size));
	if (!fdf->map)
		exit(1);
	line = get_next_line(map);
	while (j < fdf->map_H)
	{
		temp = format_line(line);
		aux = assign_coords(fdf, temp, j, aux);
		free_arr(temp);
		if (line)
			free(line);
		line = get_next_line(map);
		j++;
	}
	if (line)
		free(line);
	close(map);
}

void	set_position(t_fdf *fdf)
{
	int	i;
	int	j;
	int	index;
	int	aux_w;
	int	aux_h;

	i = 0;
	j = 0;
	index = 0;
	aux_w = -(fdf->map_W / 2);
	aux_h = -(fdf->map_H / 2);
	while (j < fdf->map_H)
	{
		i = 0;
		while (i < fdf->map_W)
		{
			fdf->map[index].x = aux_w + i;
			fdf->map[index].y = aux_h + j;
			fdf->map[index].z *= 0.2;
			i++;
			index++;
		}
		j++;
	}
}

void	set_map_dim(t_fdf *fdf, char *map_addr)
{
	get_map_width(fdf, map_addr);
	get_map_height(fdf, map_addr);
	fdf->map_size = fdf->map_H * fdf->map_W;
	fdf->map_edges_W = fdf->map_W - 1;
	fdf->map_edges_H = fdf->map_H - 1;
	fdf->spacing_W = (WINW * fdf->zoom) / (fdf->map_edges_W);
	fdf->spacing_H = (WINH * fdf->zoom) / (fdf->map_edges_H);
	if (fdf->map_edges_H == 0)
		fdf->spacing_H = 0;
}

void	process_map(t_fdf *fdf, char *map_addr)
{
	set_map_dim(fdf, map_addr);
	check_map(fdf, map_addr);
	draw_loading_screen(fdf, 0.22);
	set_mouse_delayer(fdf);
	draw_loading_screen(fdf, 0.34);
	get_map_coords(fdf, map_addr);
	draw_loading_screen(fdf, 0.46);
	get_z_diff(fdf);
	set_z_scaling(fdf);
	draw_loading_screen(fdf, 0.68);
	if (!fdf->color_flag)
		load_color_map(fdf);
	draw_loading_screen(fdf, 0.8);
	set_position(fdf);
	draw_loading_screen(fdf, 0.92);
	get_backup_map(fdf);
	draw_loading_screen(fdf, 1);
}
