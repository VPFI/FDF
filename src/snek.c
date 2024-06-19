/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:46:05 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/19 21:54:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_snake	*snake_last(t_snake	*lst)
{
	if (lst)
	{
		if (lst->next)
			return (snake_last(lst->next));
	}
	return (lst);
}

t_snake	*new_body(int x1, int y1, int x2, int y2)
{
	t_snake	*res;

	res = (t_snake *)malloc(sizeof(t_snake));
	if (!res)
		return (NULL);
	res->self_pos.x = x1;
	res->self_pos.y = y1;
	res->prev_pos.x = x2;
	res->prev_pos.y = y2;
	res->next = NULL;
	return (res);
}

void	add_body(t_snake **lst, t_snake *new)
{
	t_snake	*last_entry;

	if (lst)
	{
		if (*lst)
		{
			last_entry = snake_last(*lst);
			last_entry->next = new;
		}
		else
			*lst = new;
	}
}

void	init_snake(t_fdf *fdf)
{
	t_snake	*snake;
	int		i;
	int		s_radius;
	(void) 	fdf;

	i = 0;
	snake = NULL;
	s_radius = 40;
	if (fdf->b_ground.img_ptr)
			mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	while (i < 3)
	{
		add_body(&snake, new_body(CENTER_X + (i * (s_radius * 2)), CENTER_Y, 0, 0));
		i++;
	}
	while(snake)
	{
		printf("%f\n", snake->self_pos.x);
		draw_circle_inward(snake->self_pos.x, snake->self_pos.y, s_radius, 20, 1000, DEF_COLOR, BLACK, 0.5, &fdf->b_ground, 4);
		snake = snake->next;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}