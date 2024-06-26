/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:41:08 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/26 18:41:52 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	loading_write(t_fdf *fdf)
{
	int	xy[2];

	xy[0] = WINW * 0.4;
	xy[1] = WINH * 0.819;
	write_str(fdf, "LOADI", xy, 3);
	xy[0] = WINW * 0.533;
	xy[1] = WINH * 0.819;
	write_str(fdf, "NG", xy, 3);
	xy[0] = WINW * 0.458;
	xy[1] = WINH * 0.877;
	write_str(fdf, "---", xy, 3);
}

void	animation_write(t_fdf *fdf)
{
	int	xy[2];

	xy[0] = WINW * 0.43;
	xy[1] = WINH * 0.819;
	write_str(fdf, "ENT", xy, 3);
	xy[0] = WINW * 0.513;
	xy[1] = WINH * 0.819;
	write_str(fdf, "ER", xy, 3);
	xy[0] = WINW * 0.458;
	xy[1] = WINH * 0.877;
	write_str(fdf, ">>>", xy, 3);
}

void	write_watermark(t_fdf *fdf)
{
	int	xy[2];

	xy[0] = WINW * 0.9;
	xy[1] = WINH * 0.06;
	write_str(fdf, "FDF", xy, 4);
	xy[0] = WINW * 0.901;
	xy[1] = WINH * 0.06;
	write_str(fdf, "_", xy, 1);
	xy[0] = WINW * 0.915;
	xy[1] = WINH * 0.14;
	write_str(fdf, "42", xy, 6);
}

void	write_score(t_fdf *fdf)
{
	char	*score;
	int		xy[2];

	score = ft_itoa(fdf->s_frame.score);
	xy[0] = WINW * 0.8;
	xy[1] = WINH * 0.05;
	write_str(fdf, "SCORE", xy, 7);
	if (fdf->s_frame.score < 10)
	{
		xy[0] = WINW * 0.87;
		xy[1] = WINH * 0.1;
		write_str(fdf, score, xy, 7);
		xy[0] = WINW * 0.855;
		write_str(fdf, "0", xy, 7);
	}
	else
	{
		xy[0] = WINW * 0.845;
		xy[1] = WINH * 0.1;
		write_str(fdf, score, xy, 7);
	}
	free(score);
}

void	snake_game_over(t_fdf *fdf)
{
	int	xy[2];

	snake_lstclear(&fdf->snake);
	xy[0] = CENTER_X - 270;
	xy[1] = CENTER_Y;
	write_str(fdf, "GAME", xy, 3);
	xy[0] = CENTER_X + 40;
	write_str(fdf, "OVER", xy, 3);
	fdf->snake_flag = 0;
}
