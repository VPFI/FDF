/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:41:44 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 17:15:26 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_arr_font(char **arr)
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
		free(arr[i]);
		free(arr);
	}
}

void	draw_letter(t_fdf *fdf, char *points, int prm[4])
{
	int			strt;
	float		size;
	char		**list;
	t_coords	p1;
	t_coords	p2;

	list = ft_split(points, ' ');
	strt = 0;
	size = 1 / (float)prm[2];
	while (list[strt])
	{
		p1.x = (((ft_atoi(list[strt]) * size + prm[0])) + (60 * prm[3]));
		p1.y = ((ft_atoi(list[strt + 1]) * size) + prm[1]);
		p2.x = (((ft_atoi(list[strt + 2]) * size + prm[0])) + (60 * prm[3]));
		p2.y = ((ft_atoi(list[strt + 3]) * size) + prm[1]);
		init_bresenham_line_font(&fdf->b_ground, &p1, &p2);
		strt += 4;
	}
	free_arr_font(list);
}

void	set_params(int x, int y, int size, int param[4])
{
	param[0] = x;
	param[1] = y;
	param[2] = size;
	param[3] = 0;
}

void	write_str(t_fdf *fdf, char *msg, int x, int y, int size)
{
	int		l_file;
	int		param[4];
	char	path[2];
	char	*points;
	char	*temp_line;

	path[1] = '\0';
	set_params(x, y, size, param);
	while (msg[param[3]])
	{
		path[0] = msg[param[3]];
		temp_line = ft_strjoin("fonts/", path);
		l_file = open(temp_line, O_RDONLY);
		free(temp_line);
		temp_line = get_next_line(l_file);
		points = ft_strtrim(temp_line, "\n");
		free(temp_line);
		draw_letter(fdf, points, param);
		free(points);
		close(l_file);
		param[3]++;
	}
}
