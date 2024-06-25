/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:56:51 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 20:39:12 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_angles(int *angle)
{
	angle[X] = 0;
	angle[Y] = 0;
	angle[Z] = 0;
}

int	ft_modulo(float v1, float v2)
{
	int	res;

	res = round(sqrtf((v1 * v1) + (v2 * v2)));
	return (res);
}

void	file_err(char *addr)
{
	ft_printf(STDERR_FILENO, "\n    Unexpected error opening: (%s)\n", addr);
	ft_printf(2, "  Please make sure the input follows correct formatting:\n");
	ft_printf(STDERR_FILENO, "         --|| ./fdf map_address.fdf ||--\n\n");
	exit(2);
}
