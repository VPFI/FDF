/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:48:08 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:10:33 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_color(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	get_color(char *hexa_num)
{
	int		i;
	int		j;
	int		parsed_num;
	char	c;
	char	*base;

	i = 0;
	parsed_num = 0;
	hexa_num = hexa_num + 2;
	base = "0123456789abcdef";
	while (hexa_num[i])
	{
		c = ft_tolower(hexa_num[i]);
		j = 0;
		while (base[j] && c != base[j])
			j++;
		if (j >= 16)
			break ;
		parsed_num = (parsed_num * 16) + j;
		i++;
	}
	return (parsed_num);
}

void	set_fade_map(float *fade, int color1, int color2, int dist)
{
	fade[0] = (float)((r_color(color1)) - (r_color(color2))) / dist;
	fade[1] = (float)((g_color(color1)) - (g_color(color2))) / dist;
	fade[2] = (float)((b_color(color1)) - (b_color(color2))) / dist;
}

void	load_color_map(t_fdf *fdf)
{
	int		i;
	int		n;
	int		c[4];
	float	fade[3];

	i = 0;
	while (i < fdf->map_size)
	{
		c[0] = t_color(DEF_COLOR);
		if (fdf->map[i].z > 0)
		{
			n = fdf->z_max - (fdf->z_max - fdf->map[i].z);
			set_fade_map(fade, DEF_COLOR_MAX, DEF_COLOR, fdf->z_max);
		}
		else
		{
			n = abs(fdf->z_min) - (abs(fdf->z_min) - fabs(fdf->map[i].z));
			set_fade_map(fade, DEF_COLOR_MIN, DEF_COLOR, abs(fdf->z_min));
		}
		c[1] = r_color(DEF_COLOR) + (fade[0] * n);
		c[2] = g_color(DEF_COLOR) + (fade[1] * n);
		c[3] = b_color(DEF_COLOR) + (fade[2] * n);
		fdf->map[i].color = trgb_color(c[0], c[1], c[2], c[3]);
		i++;
	}
}
