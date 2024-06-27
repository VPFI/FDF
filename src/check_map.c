/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:11:18 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/27 23:22:07 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	check_hex_num(char *line)
{
	int		i;
	int		flag;

	i = 2;
	flag = 0;
	if (line[0] != '0')
		flag = -1;
	else if (line[1] != 'x' && line[1] != 'X')
		flag = -1;
	else
	{
		while (line[i])
		{
			if (!ft_isalnum(line[i]))
				flag = -1;
			i++;
		}
	}
	return (flag);
}

int	check_line(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == ',')
		{
			flag = check_hex_num(&line[i + 1]);
			if (flag)
				return (-1);
			else
				return (0);
		}
		if (line[i] == '-')
			i++;
		flag = ft_isdigit(line[i]);
		if (!flag)
			return (-1);
		i++;
	}
	return (0);
}

void	check_err(char ***list)
{
	free_arr(*list);
	file_err("MAP ERROR1");
}

void	check_map(t_fdf *fdf, char *map_addr)
{
	int		i;
	int		map;
	char	*line;
	char	**list;

	map = open_map(map_addr);
	line = get_next_line(map);
	while (line)
	{
		list = format_line(line);
		free(line);
		i = 0;
		while (list[i] != NULL)
		{
			if (check_line(list[i]))
				check_err(&list);
			i++;
		}
		free_arr(list);
		if (i != fdf->map_W)
			file_err("MAP ERROR2");
		line = get_next_line(map);
	}
	close(map);
}
