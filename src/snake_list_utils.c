/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:26:33 by vperez-f          #+#    #+#             */
/*   Updated: 2024/06/25 17:10:33 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	snake_lstclear(t_snake **lst)
{
	t_snake	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			free(*lst);
			*lst = temp;
		}
	}
}

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
