/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:33:08 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/27 23:14:50 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	assign_coords(t_fdf *fdf, char **temp, int j, int aux)
{
	int		i;
	char	**temp_color;

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
	return (aux);
}

char	**format_line(char *line)
{
	char	**res;
	char	*temp_line;

	temp_line = ft_strtrim(line, "\n");
	res = ft_split(temp_line, ' ');
	free(temp_line);
	return (res);
}
