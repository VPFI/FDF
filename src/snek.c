/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:46:05 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/20 20:59:58 by vperez-f         ###   ########.fr       */
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

void	draw_snake(t_fdf *fdf, t_snake *snake, t_sframe *s_frame)
{
	draw_circle_inward((snake)->self_pos.x, (snake)->self_pos.y, s_frame->s_radius, 0, 200, DEF_COLOR_MIN, DEF_COLOR, 0.8, &fdf->b_ground, 4);
	(snake) = (snake)->next;
	while(snake)
	{
		draw_circle_inward((snake)->self_pos.x, (snake)->self_pos.y, s_frame->s_radius, 0, 200, DEF_COLOR_MAX, DEF_COLOR, 0.8, &fdf->b_ground, 4);
		(snake) = (snake)->next;
	}
}
void	populate_food(t_sframe *s_frame)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	if (0 < s_frame->food)
		return ;
	s_frame->food = 5;
	while (i < s_frame->food)
	{
		x = rand() % WINW - 1;
		y = rand() % WINH - 1;
		s_frame->food_pos[i].x = x;
		s_frame->food_pos[i].y = y;
		i++;
	}
}

int	set_snake_dir(t_sframe *sframe, int dist, int dir)
{
	if (0 < dist && !dir)
	{
		if (sframe->dir == 2 || sframe->dir == 0)
			return (1);
		sframe->dir = 1;
	}
	else if (dist < 0 && !dir)
	{
		if (sframe->dir == 1)
			return (1);
		sframe->dir = 2;
	}
	if (0 < dist && dir)
	{
		if (sframe->dir == 4)
			return (1);
		sframe->dir = 3;
	}
	else if (dist < 0 && dir)
	{
		if (sframe->dir == 3)
			return (1);
		sframe->dir = 4;
	}
	return (0);
}

int	check_col_snake(t_fdf *fdf, t_snake *snake)
{
	t_coords head;
	int		diff;

	diff = 0;
	head = snake->self_pos;
	snake = snake->next;
	while (snake)
	{
		diff = fabs(head.x - snake->self_pos.x) + fabs(head.y - snake->self_pos.y);
		if (diff < (fdf->s_frame.s_radius * 2))
		{
			printf("col snake\n");
			return (1);
		}
		snake = snake->next;
	}
	return (0);
}

void	snake_game_over(t_fdf *fdf)
{
	write_str(fdf, "GAME", CENTER_X - 270, CENTER_Y, 3);
	write_str(fdf, "OVER", CENTER_X + 40, CENTER_Y, 3);
	fdf->snake_flag = 0;
}

int	check_col_food(t_snake *snake, t_sframe *sframe)
{
	t_coords head;
	int		diff;
	int		i;

	i = 0;
	diff = 0;
	head = snake->self_pos;
	while (i < 5)
	{
		diff = fabs(head.x - sframe->food_pos[i].x) + fabs(head.y - sframe->food_pos[i].y);
		if (diff < ((sframe->f_radius * 2)))
		{
			sframe->food_pos[i].x = -1000;
			sframe->food_pos[i].y = -1000;
			sframe->food--;
			return (1);
		}
		i++;
	}	
	return (0);
}

void	draw_food(t_fdf *fdf, t_sframe *s_frame)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		draw_circle_inward(s_frame->food_pos[i].x, s_frame->food_pos[i].y, s_frame->f_radius, 0, 300, GREEN, DEF_COLOR, 0.8, &fdf->b_ground, 4);
		i++;
	}
}
void	move_snake_loop(t_fdf *fdf, t_sframe *sframe)
{
	while (fdf->s_frame.s_delayer % 90000000)
		fdf->s_frame.s_delayer++;
	fdf->s_frame.s_delayer = 1;
	if (sframe->dir == 1)
		move_snake(fdf, fdf->snake, 40, 0);
	else if (sframe->dir == 2)
		move_snake(fdf, fdf->snake, -40, 0);
	else if (sframe->dir == 3)
		move_snake(fdf, fdf->snake, 40, 1);
	else if (sframe->dir == 4)
		move_snake(fdf, fdf->snake, -40, 1);
}
void	refresh_snake(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	populate_food(&fdf->s_frame);
	draw_food(fdf, &fdf->s_frame);
	draw_snake(fdf, fdf->snake, &fdf->s_frame);
	if (check_col_snake(fdf, fdf->snake))
		snake_game_over(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	move_snake(t_fdf *fdf, t_snake *snake, int dist, int dir)
{
	t_coords	aux;

	if (set_snake_dir(&fdf->s_frame, dist, dir))
		return ;
	aux = snake->self_pos;
	if (!dir)
		snake->self_pos.x += dist;
	else if (dir)
		snake->self_pos.y += dist;
	if (snake->self_pos.x < 0)
		snake->self_pos.x = WINW - 1;
	if (snake->self_pos.y < 0)
		snake->self_pos.y = WINH - 1;
	snake->self_pos.x = (int)snake->self_pos.x % WINW;
	snake->self_pos.y = (int)snake->self_pos.y % WINH;
	snake = snake->next;
	while (snake)
	{
		snake->prev_pos = aux;
		aux = snake->self_pos;
		snake->self_pos = snake->prev_pos;
		snake = snake->next;
	}
	if (check_col_food(fdf->snake, &fdf->s_frame))
		add_body(&fdf->snake, new_body(aux.x, aux.y, 0, 0));
	refresh_snake(fdf);
}

void	init_snake(t_fdf *fdf)
{
	int		i;

	i = 0;
	fdf->snake = NULL;
	fdf->snake_flag = 1;
	fdf->s_frame.s_radius = 20;
	fdf->s_frame.dir = 0;
	fdf->s_frame.food = 0;
	fdf->s_frame.f_radius = 20;
	fdf->s_frame.s_delayer = 1;
	while (i < 10)
	{
		add_body(&fdf->snake, new_body(CENTER_X + (i * (20.5 * 2)), CENTER_Y, 0, 0));
		i++;
	}
	refresh_snake(fdf);
}