/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:40:46 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 18:56:26 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	trgb_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	t_color(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	r_color(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	g_color(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	b_color(int trgb)
{
	return (trgb & 0xFF);
}
