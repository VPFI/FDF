/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:53 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/19 18:30:48 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void    free_arr(char **arr)
{
	int i;

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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *dst;

	if (x > WINW || y > WINH || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void    init_img_data(t_img *img, void *mlx)
{
	img->img_ptr = mlx_new_image(mlx, WINW, WINH);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
}

void    init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WINW, WINH, "FDF");
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	fdf->rot_deg[X] = 0;
	fdf->rot_deg[Y] = 0;
	fdf->rot_deg[Z] = 0;
	fdf->tras[X] = 0;
	fdf->tras[Y] = 0;
	fdf->is_left_mouse_pres = 0;
	fdf->is_right_mouse_pres = 0;
	fdf->mouse_tracker = 0;
	fdf->mouse_delayer = 3;
	fdf->mouse_x = 0;
	fdf->mouse_y = 0;
	fdf->zoom = 0.7;
	fdf->animate = 0;
	fdf->color_flag = 0;
	fdf->z_diff = 0;
	fdf->z_factor = 1;
	fdf->shift_tracker = 0;
	fdf->load_flag = 0;
	fdf->entered = 0;
	fdf->test = 0;
	init_cube(&fdf->cube);
}

int trgb_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int t_color(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int r_color(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int g_color(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int b_color(int trgb)
{
	return (trgb & 0xFF);
}

void    set_fade_circle(t_circle *circle, int og_color, int end_color, int fade_dist)
{
	circle->fade_comp[1] = (float)((r_color(end_color)) - (r_color(og_color)))/fade_dist;
	circle->fade_comp[2] = (float)((g_color(end_color)) - (g_color(og_color)))/fade_dist;
	circle->fade_comp[3] = (float)((b_color(end_color)) - (b_color(og_color)))/fade_dist;
	circle->n = 1;
	circle->max = fade_dist;
}

int fade_color_circle(t_circle *circle)
{
	int t;
	int r;
	int g;
	int b;

	if (circle->n == circle->max)
		return (circle->color);
	t = t_color(circle->og_color);
	r = r_color(circle->og_color) + (circle->fade_comp[1] * circle->n);
	g = g_color(circle->og_color) + (circle->fade_comp[2] * circle->n);
	b = b_color(circle->og_color) + (circle->fade_comp[3] * circle->n);
	circle->n++;
	return (trgb_color(t, r, g, b));
}

void    set_fade(t_point *pt, int og_color, int end_color, int fade_dist)
{
	pt->fade_comp[1] = (float)((r_color(end_color)) - (r_color(og_color)))/fade_dist;
	pt->fade_comp[2] = (float)((g_color(end_color)) - (g_color(og_color)))/fade_dist;
	pt->fade_comp[3] = (float)((b_color(end_color)) - (b_color(og_color)))/fade_dist;
	pt->n = 1;
	pt->max = fade_dist;
}

int fade_color(t_point *pt)
{
	int t;
	int r;
	int g;
	int b;

	if (pt->n == pt->max)
		return (pt->color);
	t = t_color(pt->og_color);
	r = r_color(pt->og_color) + (pt->fade_comp[1] * pt->n);
	g = g_color(pt->og_color) + (pt->fade_comp[2] * pt->n);
	b = b_color(pt->og_color) + (pt->fade_comp[3] * pt->n);
	pt->n++;
	return (trgb_color(t, r, g, b));
}

int		modulo(float v1, float v2)
{
	int	res;

	res = round(sqrtf((v1 * v1) + (v2 * v2)));
	return (res);
}

void    set_fade_bres(t_bresenham *bres)
{
	float	dist_x;
	float	dist_y;

	dist_x = bres->f_pt.x - bres->i_pt.x;
	dist_y = bres->f_pt.y - bres->i_pt.y;
	bres->max = modulo(dist_x, dist_y);
	bres->fade_comp[1] = (float)((r_color(bres->f_pt.color)) - (r_color(bres->i_pt.color))) / bres->max;
	bres->fade_comp[2] = (float)((g_color(bres->f_pt.color)) - (g_color(bres->i_pt.color))) / bres->max;
	bres->fade_comp[3] = (float)((b_color(bres->f_pt.color)) - (b_color(bres->i_pt.color))) / bres->max;
	bres->n = 1;
}

int fade_color_bres(t_bresenham *bres)
{
	int t;
	int r;
	int g;
	int b;

	if (bres->n == bres->max)
		return (bres->color);
	t = t_color(bres->i_pt.color);
	r = r_color(bres->i_pt.color) + (bres->fade_comp[1] * bres->n);
	g = g_color(bres->i_pt.color) + (bres->fade_comp[2] * bres->n);
	b = b_color(bres->i_pt.color) + (bres->fade_comp[3] * bres->n);
	bres->n++;
	return (trgb_color(t, r, g, b));
}

void    draw_circle_loading(float center_x, float center_y, int radius, int inner_radius, float smothness, int color1, int color2, float fade, t_img *img, float perc)
{
	t_circle circle;

	circle.x = 0;
	circle.y = 0;
	circle.center_x = center_x;
	circle.center_y = center_y;
	circle.radius = radius;
	circle.degree = 0;
	circle.smothness = smothness;
	circle.increment = PI / circle.smothness;
	circle.og_color = color1;
	fade = circle.radius * fade;
	set_fade_circle(&circle, circle.og_color, color2, (int)fade);
	while (inner_radius <= circle.radius)
	{
		circle.degree = H_PI;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (fabs(H_PI - circle.degree) <= D_PI * perc)
		{
			circle.x = circle.center_x + ((float)(circle.radius) * cos(circle.degree));
			circle.y = circle.center_y + ((float)(circle.radius) * sin(-circle.degree));
			my_mlx_pixel_put(img, circle.x, circle.y, circle.color);
			//circle.color = fade_color_circle(&circle);
			circle.degree -= circle.increment;
		}
		circle.radius--;
	}
}
void    draw_circle_inward(float center_x, float center_y, int radius, int inner_radius, float smothness, int color1, int color2, float fade, t_img *img, int mode)
{
	t_circle circle;

	circle.x = 0;
	circle.y = 0;
	circle.center_x = center_x;
	circle.center_y = center_y;
	circle.radius = radius;
	circle.degree = 0;
	circle.smothness = smothness;
	circle.increment = PI / circle.smothness;
	circle.og_color = color1;
	fade = circle.radius * fade;
	set_fade_circle(&circle, circle.og_color, color2, (int)fade);
	while (inner_radius <= circle.radius)
	{
		circle.degree = 0;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree <= H_PI)
		{
			circle.x = circle.center_x + ((float)(circle.radius) * cos(circle.degree));
			circle.y = circle.center_y + ((float)(circle.radius) * sin(circle.degree));
			if (mode > 0)
				my_mlx_pixel_put(img, circle.x, (center_y - (circle.y - center_y)), circle.color);
			if (mode > 1)
				my_mlx_pixel_put(img, circle.x, circle.y, circle.color);
			if (mode > 2)
				my_mlx_pixel_put(img, (center_x - (circle.x - center_x)), circle.y, circle.color);
			if (mode > 3)
				my_mlx_pixel_put(img, (center_x - (circle.x - center_x)), (center_y - (circle.y - center_y)), circle.color);
			//circle.color = fade_color_circle(&circle);
			circle.degree += circle.increment;
		}
		circle.radius--;
	}
}

void    draw_circle_outward(float center_x, float center_y, int radius, int outer_radius, float smothness, int color1, int color2, float fade, t_img *img)
{
	t_circle circle;

	circle.x = 0;
	circle.y = 0;
	circle.center_x = center_x;
	circle.center_y = center_y;
	circle.radius = radius;
	circle.degree = 0;
	circle.smothness = smothness;
	circle.increment = PI / circle.smothness;
	circle.og_color = color1;
	fade = circle.radius * fade;
	set_fade_circle(&circle, circle.og_color, color2, (int)fade);
	while (circle.radius <= outer_radius)
	{
		circle.degree = 0;
		circle.x = 0;
		circle.y = 0;
		circle.color = fade_color_circle(&circle);
		while (circle.degree <= H_PI)
		{
			circle.x = circle.center_x + (circle.radius * cos(circle.degree));
			circle.y = circle.center_y + (circle.radius * sin(circle.degree));
			my_mlx_pixel_put(img, circle.x, circle.y, circle.color);
			my_mlx_pixel_put(img, (center_x - (circle.x - center_x)), circle.y, circle.color);
			my_mlx_pixel_put(img, (center_x - (circle.x - center_x)), (center_y - (circle.y - center_y)), circle.color);
			my_mlx_pixel_put(img, circle.x, (center_y - (circle.y - center_y)), circle.color);
			//circle.color = fade_color_circle(&circle);
			circle.degree += circle.increment;
		}
		circle.radius++;
	}
}

int	close_all(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
		mlx_destroy_display(fdf->mlx_ptr);
	exit(0);
	return (0);
}

void    draw_scene_one(t_fdf *fdf)
{
	//add img_ptr as param make it generic
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 1300, 6000, BLACK, ORANGE_GULF, 0.85, &fdf->b_ground);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void    draw_scene_two(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 6000, BLACK, CYAN_GULF, 0.85, &fdf->b_ground, 4);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void    draw_scene_three(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 1300, 6000, BLACK, ORANGE_GULF, 0.85, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 6000, BLACK, CYAN_GULF, 0.85, &fdf->b_ground, 4);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void    draw_scene_four(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_inward(CENTER_X, CENTER_Y, 1500, 0, 1000, WHITE, BLACK, 0.7, &fdf->b_ground, 4);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 350, BLACK, CYAN_GULF, 0.85, &fdf->b_ground, 4);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void    draw_scene_five(t_fdf *fdf)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y, 510, 1300, 900, ORANGE_GULF, ORANGE_GULF, 1, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 490, 0, 400, CYAN_GULF, CYAN_GULF, 1, &fdf->b_ground, 4);
	draw_circle_outward(CENTER_X, CENTER_Y, 500, 510, 4000, BLACK, ORANGE_GULF, 0.03, &fdf->b_ground);
	draw_circle_inward(CENTER_X, CENTER_Y, 500, 490, 4000, BLACK, CYAN_GULF, 0.03, &fdf->b_ground, 4);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	scale_cube(t_fdf *fdf, t_cube *cube)
{
	int i;

	i = 0;
	fdf->shift_tracker = 0;
	while (i < 8)
	{
		cube->coord[i].x = (WINW * 0.05) + (cube->pad * cube->coord[i].x);
		cube->coord[i].y = (WINH * 0.075) + (cube->pad * cube->coord[i].y);
		i++;
	}
}

void	rotate_cube(t_fdf *fdf, t_cube *cube)
{
	int i;

	i = 0;
	while (i < 8)
	{
		rotate_x(&cube->coord[i], (fdf->rot_deg[X] * PI / 180));
		rotate_y(&cube->coord[i], (fdf->rot_deg[Y] * PI / 180));
		rotate_z(&cube->coord[i], (fdf->rot_deg[Z] * PI / 180));
		i++;
	}
}

void	reset_cube(t_cube *cube)
{
	int i;

	i = 0;
	while (i < 8)	
	{
		cube->coord[i] = cube->coord_backup[i];
		i++;		
	}
}

void	get_backup_cube(t_cube *cube)
{
	int i;

	i = 0;
	while (i < 8)
	{
		cube->coord_backup[i] = cube->coord[i];
		i++;
	}
}

void	init_cube(t_cube *cube)
{
	int i;

	i = 0;
	cube->pad = 80;
	while (i < 8)
	{
		cube->coord[i].x = 0.5;
		cube->coord[i].y = 0.5;
		cube->coord[i].z = 0.5;
		cube->coord[i].color = GRAY_LIGHT;
		i++;
	}
	cube->coord[0].x = -0.5;
	cube->coord[0].y = -0.5;
	cube->coord[0].z = -0.5;
	cube->coord[1].y = -0.5;
	cube->coord[1].z = -0.5;
	cube->coord[2].z = -0.5;
	cube->coord[3].x = -0.5;
	cube->coord[3].z = -0.5;
	cube->coord[4].x = -0.5;
	cube->coord[4].y = -0.5;
	cube->coord[5].y = -0.5;
	cube->coord[7].x = -0.5;
	get_backup_cube(cube);
}

void	set_color_cube(t_cube *cube, int a, int b)
{
	if (a == 0 && b == 1)
	{
		cube->coord[a].color = RED;
		cube->coord[b].color = RED;
	}
	else if (a == 3 && b == 0)
	{
		cube->coord[a].color = GREEN;
		cube->coord[b].color = GREEN;
	}
	else if (a == 0 && b == 4)
	{
		cube->coord[a].color = BLUE;
		cube->coord[b].color = BLUE;
	}
	else 
	{
		cube->coord[a].color = GRAY_LIGHT;
		cube->coord[b].color = GRAY_LIGHT;		
	}
}

void	bres_cube(t_fdf *fdf, t_cube *cube)
{
	int		i;
	int		aux;

	i = 0;
	aux = 1;
	while (i < 8)
	{
		if (i < 4)
			aux = aux % 4;
		else
			aux = (aux % 4) + 4;
		set_color_cube(cube, i, aux);
		init_bresenham_line(&fdf->b_ground, &cube->coord[i], &cube->coord[aux]);
		i++;
		aux++;
	}
	i = 0;
	while (i < 4)
	{
		set_color_cube(cube, i, i + 4);		
		init_bresenham_line(&fdf->b_ground, &cube->coord[i], &cube->coord[i + 4]);
		i++;
	}
}

void    draw_cube(t_fdf *fdf)
{
	reset_cube(&fdf->cube);
	rotate_cube(fdf, &fdf->cube);
	scale_cube(fdf, &fdf->cube);
	bres_cube(fdf, &fdf->cube);
}

void    draw_map(t_fdf *fdf)
{
	t_coords i_pt;
	t_coords f_pt;

	int i = 0;
	int j = 0;
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	while (j < fdf->map_edges_H)
	{
		while ((i % fdf->map_W) < fdf->map_edges_W)
		{
			i_pt = fdf->map[i];
			f_pt = fdf->map[i + 1];
			init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
			f_pt = fdf->map[i + fdf->map_W];
			init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
			i++;
		}
		i_pt = fdf->map[i];
		f_pt = fdf->map[i + fdf->map_W];
		init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
		i++;
		j++;
	}
	while ((i % fdf->map_W) < fdf->map_edges_W)
	{
		i_pt = fdf->map[i];
		f_pt = fdf->map[i + 1];
		init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
		i++;
	}
	/*
	i_pt.x = WINW / 2;
	i_pt.y = 0;
	f_pt.x = WINW / 2;
	f_pt.y = WINH;
	init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);
	i_pt.x = 0;
	i_pt.y = WINH / 2;
	f_pt.x = WINW;
	f_pt.y = WINH / 2;
	init_bresenham_line(&fdf->b_ground, &i_pt, &f_pt);*/
	draw_cube(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
}

void	reset_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map_size)
	{
		fdf->map[i].x = fdf->backup_map[i].x;
		fdf->map[i].y = fdf->backup_map[i].y;
		fdf->map[i].z = fdf->backup_map[i].z * fdf->z_factor;
		i++;
	}
}

void	rotate_key(t_fdf *fdf, int angle_x, int angle_y, int angle_z)
{
	reset_map(fdf);
	rotate_map(fdf, angle_x, angle_y ,angle_z);
	scale_map(fdf);
	draw_map(fdf);
}

void	move_key(t_fdf *fdf, int dist, int dir)
{
	int	i;

	i = 0;
	if (!dist)
		return ;
	while (i < fdf->map_size)
	{
		if (dir)
			fdf->map[i].y += dist;
		else if (!dir)
			fdf->map[i].x += dist;
		i++;
	}
	if (dir)
		fdf->tras[Y] += dist;
	else if (!dir)
		fdf->tras[X] += dist;
	//printf("MOVE || X: %i -- Y: %i\n", fdf->tras[X], fdf->tras[Y]);
	draw_map(fdf);
}

void	set_angles(int *angle)
{
	angle[X] = 0;
	angle[Y] = 0;
	angle[Z] = 0;
}

void	swap_persp(t_fdf *fdf, int p)
{
	int	angle[3];

	fdf->entered = 1;
	set_angles(angle);
	if (p == 1)
	{
		angle[X] = -fdf->rot_deg[X];
		angle[Y] = -fdf->rot_deg[Y];
		angle[Z] = -fdf->rot_deg[Z];
	}
	if (p == 2)
	{
		angle[X] = 90 - fdf->rot_deg[X];
		angle[Y] = -fdf->rot_deg[Y];
		angle[Z] = -fdf->rot_deg[Z];
	}
	if (p == 3)
	{
		angle[X] = 45 - fdf->rot_deg[X];
		angle[Y] =  -fdf->rot_deg[Y];
		angle[Z] = -15 - fdf->rot_deg[Z];
	}
	reset_map(fdf);
	rotate_map(fdf, angle[X], angle[Y], angle[Z]);
	scale_map(fdf);
	draw_map(fdf);
}

void	reset_pos(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map_size)
	{
		fdf->map[i].x -= fdf->tras[X];
		fdf->map[i].y -= fdf->tras[Y];
		i++;
	}
	fdf->tras[X] = 0;
	fdf->tras[Y] = 0;
	draw_map(fdf);
}

void	extrude(t_fdf *fdf, float dist)
{
	int	i;

	i = 0;
	fdf->z_factor *= dist;
	reset_map(fdf);
	rotate_map(fdf, 0, 0, 0);
	scale_map(fdf);
	draw_map(fdf);
}

void	zoom_map(t_fdf *fdf, float amount)
{
	if (fdf->zoom < 0.05 && amount < 1)
		return ;
	if (50 < fdf->zoom && 1 < amount)
		return ;
	fdf->zoom *= amount;
	reset_map(fdf);
	rotate_map(fdf, 0, 0, 0);
	scale_map(fdf);
	draw_map(fdf);
	//printf("ZOOM || Z: %f\n", fdf->zoom);
}

void	reset_zoom(t_fdf *fdf)
{
	fdf->zoom = 0.7;
	reset_map(fdf);
	rotate_map(fdf, 0, 0, 0);
	scale_map(fdf);
	draw_map(fdf);
}

void	reset_all(t_fdf *fdf)
{
	int		i;

	i = 0;
	set_z_scaling(fdf);
	while (i < fdf->map_size)
	{
		fdf->map[i].x -= fdf->tras[X];
		fdf->map[i].y -= fdf->tras[Y];
		i++;
	}
	fdf->tras[X] = 0;
	fdf->tras[Y] = 0;
	fdf->zoom = 0.7;
	swap_persp(fdf, 3);
}

int	mouse_press(int button, int x, int y, void *fdf_B)
{
	t_fdf *fdf;

	fdf = fdf_B;
	if (!check_enter(fdf) || !check_load(fdf))
		return (0);
	if (button == 1)
	{
		fdf->is_left_mouse_pres = 1;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	else if (button == 2)
		reset_all(fdf);
	else if (button == 3)
	{
		fdf->is_right_mouse_pres = 1;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	else if (button == 4)
		zoom_map(fdf, 1.1);
	else if (button == 5)
		zoom_map(fdf, 0.9);
	return (0);
}

int	mouse_rel(int button, int x, int y, void *fdf_B)
{
	t_fdf *fdf;

	fdf = fdf_B;
	if (button == 1)
	{
		fdf->is_left_mouse_pres = 0;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	else if (button == 3)
	{
		fdf->is_right_mouse_pres = 0;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	//printf("RRRR%i --- %i--- %i\n", button, x, y);
	return (0);
}

int	mouse_move(int x, int y, void *fdf_B)
{
	t_fdf	*fdf;
	int		dist_x;
	int		dist_y;

	fdf = fdf_B;
	if (!check_enter(fdf) || (!fdf->is_right_mouse_pres && !fdf->is_left_mouse_pres))
		return (0);
	if (!check_load(fdf) || (fdf->mouse_tracker++ % fdf->mouse_delayer))
		return (0);
	dist_x = (x - fdf->mouse_x);
	dist_y = (y - fdf->mouse_y);
	if (fdf->is_right_mouse_pres)
	{
		if (dist_x)
			move_key(fdf, dist_x, 0);
		if (dist_y)
			move_key(fdf, dist_y, 1);
	}
	if (fdf->is_left_mouse_pres && fdf->shift_tracker)
		rotate_key(fdf, 0, 0, dist_x / 4 + dist_y / 4);
	else if (fdf->is_left_mouse_pres)
		rotate_key(fdf, dist_y / 2, dist_x / 2, 0);
	fdf->mouse_x = x;
	fdf->mouse_y = y;
	return (0);
}

void	animate(t_fdf *fdf)
{
	if (!fdf->animate)
		fdf->animate = 1;
	else
		fdf->animate = 0;
}

void	shift_tracker(t_fdf *fdf)
{
	if (!fdf->shift_tracker)
		fdf->shift_tracker = 1;
	else
		fdf->shift_tracker = 0;
}

int	check_load(t_fdf *fdf)
{
	if (fdf->load_flag == 1)
		return (1);
	else
		return (0);
}

int	check_enter(t_fdf *fdf)
{
	if (fdf->entered == 1)
		return (1);
	else
		return (0);
}

int key_hook(int keycode, void *fdf)
{
	if (keycode == ESC_KEY)
		close_all(fdf);
	else if (!check_load(fdf))
		return (0);
	else if (keycode == ENTER_KEY)
		swap_persp(fdf, 3);
	else if (!check_enter(fdf))
		return (0);
	else if (keycode == ONE_KEY)
		draw_scene_one(fdf);
	else if (keycode == TWO_KEY)
		draw_scene_two(fdf);
	else if (keycode == THREE_KEY)
		draw_scene_three(fdf);
	else if (keycode == FOUR_KEY)
		draw_scene_four(fdf);
	else if (keycode == FIVE_KEY)
		draw_scene_five(fdf);
	else if (keycode == SIX_KEY)
		write_str(fdf, "hola", CENTER_X - 200, CENTER_Y, 3);
	else if (keycode == M_KEY)
		draw_welcome_menu(fdf);
	else if (keycode == W_KEY)
		rotate_key(fdf, 5, 0, 0);
	else if (keycode == S_KEY)
		rotate_key(fdf, -5, 0, 0);
	else if (keycode == D_KEY)
		rotate_key(fdf, 0, 5, 0);
	else if (keycode == A_KEY)
		rotate_key(fdf, 0, -5,0);
	else if (keycode == Q_KEY)
		rotate_key(fdf, 0, 0, 5);
	else if (keycode == E_KEY)
		rotate_key(fdf, 0, 0, -5);
	else if (keycode == SPACE_KEY)
		animate(fdf);
	else if (keycode == SHIFT_KEY)
		shift_tracker(fdf);
	else if (keycode == R_KEY)
		reset_pos(fdf);
	else if (keycode == O_KEY)
		swap_persp(fdf, 1);
	else if (keycode == P_KEY)
		swap_persp(fdf, 2);
	else if (keycode == I_KEY)
		swap_persp(fdf, 3);
	else if (keycode == T_KEY)
		extrude(fdf, 1.1);
	else if (keycode == G_KEY)
		extrude(fdf, 0.9);
	else if (keycode == COMMA_KEY)
		zoom_map(fdf, 0.9);
	else if (keycode == PERIOD_KEY)
		zoom_map(fdf, 1.1);
	else if (keycode == SLASH_KEY)
		reset_zoom(fdf);
	else if (keycode == UP_KEY)
		move_key(fdf, -20, 1);
	else if (keycode == DOWN_KEY)
		move_key(fdf, 20, 1);
	else if (keycode == LEFT_KEY)
		move_key(fdf, -20, 0);
	else if (keycode == RIGHT_KEY)
		move_key(fdf, 20, 0);
	return (0);
}

int	key_hook_release(int keycode, void *fdf)
{
	if (keycode == SHIFT_KEY)
		shift_tracker(fdf);
	
	return (0);
}

int	loop_hook(t_fdf *fdf)
{
	int		color;
	float	fade[3];
	int		r;
	int		g;
	int		b;

	if (fdf->animate)
		rotate_key(fdf, 0, -1, 0);
	if (fdf->load_flag && !fdf->entered)
	{
		if (fdf->b_ground.img_ptr)
			mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
		init_img_data(&fdf->b_ground, fdf->mlx_ptr);
		color = 0;
		fdf->test = fdf->test % 360;
		fade[0] = (float)((r_color(DEF_COLOR_MAX)) - (r_color(BLACK))) / 360;
		fade[1] = (float)((g_color(DEF_COLOR_MAX)) - (g_color(BLACK))) / 360;
		fade[2] = (float)((b_color(DEF_COLOR_MAX)) - (b_color(BLACK))) / 360;
		r = r_color(BLACK) + (fade[0] * fdf->test);
		g = g_color(BLACK) + (fade[1] * fdf->test);
		b = b_color(BLACK) + (fade[2] * fdf->test);
		color = trgb_color(0, r, g, b);
		draw_circle_inward(CENTER_X, CENTER_Y - 100, 400, 0, 3000, color, BLACK, 0.8, &fdf->b_ground, 4);
		draw_circle_outward(CENTER_X, CENTER_Y - 100, 400, 410, 3000, CYAN_GULF, BLACK, 0.03, &fdf->b_ground);
		write_str(fdf, "ENT", 860, 1065, 3);
		write_str(fdf, "ER", 1025, 1065, 3);
		write_str(fdf, ">>>", 915, 1140, 3);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
		fdf->test++;
	}
	return (0);
}

void    my_string_put(t_fdf *fdf, int x, int y, int color, char *msg)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y, color, msg);
}

void    draw_sides(t_fdf *fdf, float extent, float y_start, float y_finish, int color1, int color2)
{
	t_point pt;
	float   x_base;
	float   y_base;

	x_base = 0;
	y_base = WINH * y_start;
	y_finish = WINH * y_finish;
	extent = WINW * extent;
	pt.x = x_base;
	pt.y = y_base;
	pt.og_color = color1;
	set_fade(&pt, pt.og_color, color2, WINW * 0.25);
	while (pt.x < extent)
	{
		pt.y = y_base;
		//set_fade(&pt, pt.og_color, BLACK, WINH * 0.25);while (pt.y < WINH * 0.25)
		while (pt.y < y_finish)
		{
			my_mlx_pixel_put(&fdf->b_ground, pt.x, pt.y, pt.color);
			my_mlx_pixel_put(&fdf->b_ground, ((WINW) - pt.x), ((WINH) - pt.y), pt.color);
			pt.y++;
		}
		pt.color = fade_color(&pt);
		pt.x++;
	}
}

void    draw_loading_screen(t_fdf *fdf, float perc)
{
	if (fdf->b_ground.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->b_ground.img_ptr);
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_circle_outward(CENTER_X, CENTER_Y - 100, 400, 410, 3000, CYAN_GULF, BLACK, 0.03, &fdf->b_ground);
	draw_circle_loading(CENTER_X, CENTER_Y - 100, 400, 0, 3000, CYAN_GULF, BLACK, 0.7, &fdf->b_ground, perc);
	write_str(fdf, "LOADI", 800, 1065, 3);
	write_str(fdf, "NG", 1065, 1065, 3);
	write_str(fdf, "---", 915, 1140, 3);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
	if (perc == 1)
		fdf->load_flag = 1;
}

void    draw_welcome_menu(t_fdf *fdf)
{
	init_img_data(&fdf->b_ground, fdf->mlx_ptr);
	draw_sides(fdf, 0.5, 0, 1, ORANGE_GULF, BLACK);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->b_ground.img_ptr, 0, 0);
	my_string_put(fdf, CENTER_X, CENTER_Y- 25, CYAN_GULF, "|");
	my_string_put(fdf, CENTER_X - 11, CENTER_Y, CYAN_GULF, "START");
	my_string_put(fdf, CENTER_X - 17, CENTER_Y + 20, CYAN_GULF, "=======");
}

void	file_err(char *addr)
{
	ft_printf(STDERR_FILENO, "\n    Unexpected error opening: (%s)\n", addr);
	ft_printf(2, "  Please make sure the input follows correct formatting:\n");
	ft_printf(STDERR_FILENO, "         --|| ./fdf map_address.fdf ||--\n\n");
	exit(2);
}

void    get_map_width(t_fdf *fdf, char *map_addr)
{
	char    *line;
	char    *temp_line;
	char    **list;
	int     i;
	int     map;

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

void    get_map_height(t_fdf *fdf, char *map_addr)
{
	char    *line;
	int     i;
	int     map;

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

int check_color(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			return (1);
		i++;
	}
	return (0);
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

void    get_map_coords(t_fdf *fdf, char *map_addr)
{
	char    **temp;
	char    *line;
	char	*temp_line;
	int     i;
	int     j;
	int     aux;
	int     map;

	i = 0;
	j = 0;
	temp = NULL;
	temp_line = NULL;
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
				fdf->map[aux].color = get_color((ft_split(temp[i], ',')[1]));
				//free this split
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

void	rotate_x(t_coords *pt, float angle)
{
	float	temp_y;
	float	temp_z;

	if (!angle)
		return ;
	temp_y = pt->y;
	temp_z = pt->z;
	pt->y = (temp_y * cos(angle)) + (temp_z * (-sin(angle)));
	pt->z = (temp_y * sin(angle)) + (temp_z * cos(angle));
}

void	rotate_y(t_coords *pt, float angle)
{
	float	temp_x;
	float	temp_z;

	if (!angle)
		return ;
	temp_x = pt->x;
	temp_z = pt->z;
	pt->x = (temp_x * cos(angle)) + (temp_z * sin(angle));
	pt->z = (temp_x * (-sin(angle))) + (temp_z * cos(angle));
}

void	rotate_z(t_coords *pt, float angle)
{
	float	temp_x;
	float	temp_y;

	if (!angle)
		return ;
	temp_x = pt->x;
	temp_y = pt->y;
	pt->x = (temp_x * cos(angle)) + (temp_y * (-sin(angle)));
	pt->y = (temp_x * sin(angle)) + (temp_y * cos(angle));
}

void	rotate_map(t_fdf *fdf, int deg_x, int deg_y, int deg_z)
{
	int	i;
	float	angle_x;
	float	angle_y;
	float	angle_z;

	i = 0;
	fdf->rot_deg[X] = (fdf->rot_deg[X] + deg_x) % 360;
	fdf->rot_deg[Y] = (fdf->rot_deg[Y] + deg_y) % 360;
	fdf->rot_deg[Z] = (fdf->rot_deg[Z] + deg_z) % 360;
	//printf("ROTATE || x: %i -- y: %i -- z: %i\n", fdf->rot_deg[X], fdf->rot_deg[Y], fdf->rot_deg[Z]);
	angle_x = fdf->rot_deg[X] * PI / 180;
	angle_y = fdf->rot_deg[Y] * PI / 180;
	angle_z = fdf->rot_deg[Z] * PI / 180;
	while (i < fdf->map_size)
	{
		rotate_x(&fdf->map[i], angle_x);
		rotate_y(&fdf->map[i], angle_y);
		rotate_z(&fdf->map[i], angle_z);
		i++;
	}
}

void	set_position(t_fdf *fdf)
{
	int	i;
	int	j;
	int	index;
	int	aux_W;
	int	aux_H;

	i = 0;
	j = 0;
	index = 0;
	aux_W = -(fdf->map_W / 2);
	aux_H = -(fdf->map_H / 2);
	while (j < fdf->map_H)
	{
		i = 0;
		while (i < fdf->map_W)
		{
			fdf->map[index].x = aux_W + i;
			fdf->map[index].y = aux_H + j;
			fdf->map[index].z *= 0.2;
			i++;
			index++;
		}
		j++;
	}
}

void	scale_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->spacing_W = (WINW * fdf->zoom) / (fdf->map_edges_W);
	fdf->spacing_H = (WINH * fdf->zoom) / (fdf->map_edges_H);
	while (i < fdf->map_size)
	{
		fdf->map[i].x = (CENTER_X) + (fdf->spacing_W * fdf->map[i].x) + fdf->tras[X];
		fdf->map[i].y = (CENTER_Y) + (fdf->spacing_H * fdf->map[i].y) + fdf->tras[Y];
		i++;
	}
}
void	set_mouse_delayer(t_fdf *fdf)
{
	if (20000 < fdf->map_size && fdf->map_size < 100000)
		fdf->mouse_delayer = 5;
	else if (100000 < fdf->map_size && fdf->map_size < 1000000)
		fdf->mouse_delayer = 7;
	else if (1000000 < fdf->map_size)
		fdf->mouse_delayer = 13;
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

void    process_map(t_fdf *fdf, char *map_addr)
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
	/*
	int i = 0;
	printf("%i\n", i);
	while (i < fdf->map_size)
	{
		printf("---------- X:%f -- Y:%f -- Z:%f ||COLOR: %x|| %i\n", fdf->map[i].x, fdf->map[i].y, fdf->map[i].z, fdf->map[i].color, i);
		printf("BACKUP --- X:%f -- Y:%f -- Z:%f ||COLOR: %x|| %i\n", fdf->backup_map[i].x, fdf->backup_map[i].y, fdf->backup_map[i].z, fdf->backup_map[i].color, i);
		i++;
	}*/
}

void    fancy_circle(t_img *img, int xm, int ym, int r)
{
   int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */
   do {
	  my_mlx_pixel_put(img, xm-x, ym+y, WHITE); /*   I. Quadrant */
	  my_mlx_pixel_put(img, xm-y, ym-x, WHITE); /*  II. Quadrant */
	  my_mlx_pixel_put(img, xm+x, ym-y, WHITE); /* III. Quadrant */
	  my_mlx_pixel_put(img, xm+y, ym+x, WHITE); /*  IV. Quadrant */
	  r = err;
	  if (r >  x) err += ++x*2+1; /* e_xy+e_x > 0 */
	  if (r <= y) err += ++y*2+1; /* e_xy+e_y < 0 */
   } while (x < 0);
}

void    calculate_bresenham(t_img *img, t_bresenham *bres)
{
	int res_x;
	int res_y;

	res_x = bres->i_pt.x;
	res_y = bres->i_pt.y;
	while (!(res_x == bres->f_pt.x) || !(res_y == bres->f_pt.y))
	{
		bres->color = fade_color_bres(bres);
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
	bres->color = fade_color_bres(bres);
	my_mlx_pixel_put(img, res_x, res_y, bres->color);
}

void	init_bresenham_line(t_img *img, t_coords *i_pt, t_coords *f_pt)
{
	t_bresenham bres;

	bres.i_pt.x = (int)round(i_pt->x);
	bres.i_pt.y = (int)round(i_pt->y);
	bres.i_pt.color = i_pt->color;
	bres.f_pt.x = (int)round(f_pt->x);
	bres.f_pt.y = (int)round(f_pt->y);
	bres.f_pt.color = f_pt->color;
	set_fade_bres(&bres);
	bres.i_one = -1;
	bres.i_two = -1;
	bres.dx = fabs(bres.f_pt.x - bres.i_pt.x);
	bres.dy = -fabs(bres.f_pt.y - bres.i_pt.y);
	if (bres.i_pt.x < bres.f_pt.x)
		bres.i_one = 1;
	if (bres.i_pt.y < bres.f_pt.y)
		bres.i_two = 1;
	bres.d = bres.dx + bres.dy;
	calculate_bresenham(img, &bres);
}

int main(int argc, char **argv)
{
	t_fdf   fdf;

	if (argc != 2 || !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
		file_err(argv[1]);
	init_fdf(&fdf);
	draw_loading_screen(&fdf, 0.1);
	process_map(&fdf, argv[1]);
	mlx_hook(fdf.win_ptr, KEYDOWN, KEYPRESS_M, key_hook, (void *)&fdf);
	mlx_hook(fdf.win_ptr, KEYUP, KEYRELEASE_M, key_hook_release, (void *)&fdf);
	mlx_hook(fdf.win_ptr, DESTROY, STRUCTNOTIFY_M, close_all, &fdf);
	mlx_hook(fdf.win_ptr, MOUSEDOWN, MOUSEPRESS_M, mouse_press, (void *)&fdf);
	mlx_hook(fdf.win_ptr, MOUSEUP, MOUSERELEASE_M, mouse_rel, (void *)&fdf);
	mlx_hook(fdf.win_ptr, MOUSEMOVE, MOUSEMOVE_M, mouse_move, (void *)&fdf);
	mlx_loop_hook(fdf.mlx_ptr, loop_hook, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
