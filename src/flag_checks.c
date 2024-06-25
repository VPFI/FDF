/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:50:36 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 19:10:43 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
