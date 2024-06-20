/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:41:44 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/20 15:08:12 by vperez-f         ###   ########.fr       */
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

void    calculate_bresenham_font(t_img *img, t_bresenham *bres)
{
    int res_x;
    int res_y;

    res_x = bres->i_pt.x;
    res_y = bres->i_pt.y;
    while (!(res_x == bres->f_pt.x) || !(res_y == bres->f_pt.y))
    {
        //bres->color = fade_color_bres(bres);
        my_mlx_pixel_put(img, res_x, res_y, bres->color);
        bres->d2 = bres->d * 2;
        if (bres->d2 >= bres->dy)
        {
            bres->d += bres->dy;
            res_x += bres->i_one;
        }
        if (bres->d2 <= bres->dx)
        {
            bres->d += bres->dx;
            res_y += bres->i_two;
        }
    }
    //bres->color = fade_color_bres(bres);
    my_mlx_pixel_put(img, res_x, res_y, bres->color);
}

void    init_bresenham_line_font(t_img *img, t_coords *i_pt, t_coords *f_pt)
{
    t_bresenham bres;

    bres.i_pt.x = (int)round(i_pt->x);
    bres.i_pt.y = (int)round(i_pt->y);
    bres.i_pt.color = WHITE;
    bres.f_pt.x = (int)round(f_pt->x);
    bres.f_pt.y = (int)round(f_pt->y);
    bres.f_pt.color = WHITE;
    bres.color = DEF_COLOR_MAX;
    //set_fade_bres(&bres);
    bres.i_one = -1;
    bres.i_two = -1;
    bres.dx = fabs(bres.f_pt.x - bres.i_pt.x);
    bres.dy = -fabs(bres.f_pt.y - bres.i_pt.y);
    if (bres.i_pt.x < bres.f_pt.x)
        bres.i_one = 1;
    if (bres.i_pt.y < bres.f_pt.y)
        bres.i_two = 1;
    bres.d = bres.dx + bres.dy;
    calculate_bresenham_font(img, &bres);
}

void	draw_letter(t_fdf *fdf, char *points, int param[4])
{
	int			start;
	float		size;
	char		**list;
	t_coords	p1;
	t_coords	p2;

	list = ft_split(points, ' ');
	start = 0;
	size = 1 / (float)param[2];
	while (list[start])
	{
		p1.x = (((ft_atoi(list[start]) * size + param[0])) + (60 * param[3]));
		p1.y = ((ft_atoi(list[start + 1]) * size) + param[1]);
		p2.x = (((ft_atoi(list[start + 2]) * size + param[0])) + (60 * param[3]));
		p2.y = ((ft_atoi(list[start + 3]) * size) + param[1]);
		init_bresenham_line_font(&fdf->b_ground, &p1, &p2);
		start += 4;
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

void    write_str(t_fdf *fdf, char *msg, int x, int y, int size)
{
	int     l_file;
	int		param[4];
	char    path[2];
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
/*
void    font(void)
{
	FILE    *out;
	int     font;
	char    *line;
	char    *temp_line;
	char    c[2];

	font = open("font.txt", O_RDWR);
	c[0] = 32;
	c[1] = '\0';
	while (c[0] <= 126)
	{
		c[0]++;
		if (c[0] == '/' || c[0] == '.' )
			continue;
		out = fopen(c, "w+");
		temp_line = get_next_line(font);
		line = ft_strtrim((temp_line), "\n");
		fprintf(out, "%s", line + 2);
		fclose(out);
		free(temp_line);
		free(line);
	}
	close(font);
}*/
