/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:37:04 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:13:38 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	get_map_coords(t_fdf *fdf, char *map_addr)
{
	char	**temp;
	char	**temp_color;
	char	*line;
	char	*temp_line;
	int		i;
	int		j;
	int		aux;
	int		map;

	i = 0;
	j = 0;
	temp = NULL;
	temp_line = NULL;
	temp_color = NULL;
	aux = 0;
	map = open(map_addr, O_RDONLY);
	if (map < 0)
		file_err(map_addr);
	fdf->map = (t_coords *)malloc(sizeof(t_coords) * (fdf->map_size));
	if (!fdf->map)
		exit(1);
	line = get_next_line(map);
	while (j < fdf->map_H)
	{
		free_arr(temp);
		temp_line = ft_strtrim(line, "\n");
		temp = ft_split(temp_line, ' ');
		free(temp_line);
		i = 0;
		while (temp[i] != NULL)
		{
			fdf->map[aux].x = i;
			fdf->map[aux].y = j;
			fdf->map[aux].z = ft_atoi(temp[i]);
			if (check_color(temp[i]))
			{
				fdf->color_flag = 1;
				temp_color = ft_split(temp[i], ',');
				fdf->map[aux].color = get_color(temp_color[1]);
				free_arr(temp_color);
			}
			else
				fdf->map[aux].color = DEF_COLOR;
			i++;
			aux++;
		}
		if (line)
			free(line);
		line = get_next_line(map);
		j++;
	}
	free_arr(temp);
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
}

void	process_map(t_fdf *fdf, char *map_addr)
{
	set_map_dim(fdf, map_addr);
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
