/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_writers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:41:08 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 17:11:01 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	write_score(t_fdf *fdf)
{
	char	*score;

	score = ft_itoa(fdf->s_frame.score);
	write_str(fdf, "SCORE", WINW * 0.8, WINH * 0.05, 7);
	if (fdf->s_frame.score < 10)
	{
		write_str(fdf, score, WINW * 0.87, WINH * 0.1, 7);
		write_str(fdf, "0", WINW * 0.855, WINH * 0.1, 7);
	}
	else
		write_str(fdf, score, WINW * 0.845, WINH * 0.1, 7);
	free(score);
}

void	snake_game_over(t_fdf *fdf)
{
	snake_lstclear(&fdf->snake);
	write_str(fdf, "GAME", CENTER_X - 270, CENTER_Y, 3);
	write_str(fdf, "OVER", CENTER_X + 40, CENTER_Y, 3);
	fdf->snake_flag = 0;
}
