/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:47:33 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:47:36 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

void	ft_background_rendering(t_game *game)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (h < game->param.screen.height)
	{
		w = 0;
		while (w < game->param.screen.width)
		{
			if (h < game->param.screen.height / 2)
				game->param.screen.data[h * game->param.screen.width + w] \
					= game->param.ceil;
			else
				game->param.screen.data[h * game->param.screen.width + w] \
					= game->param.floor;
			w++;
		}
		h++;
	}
}

float	ft_to_diap(float value)
{
	while (value < 0)
		value += 1.0;
	while (value > 1)
		value -= 1.0;
	return (value);
}

int	ft_cross(t_cord *cord, t_cross *o)
{
	float	q;
	float	n;
	float	sn;
	float	fn;

	if (o->y2 - o->y1 != 0)
	{
		q = (o->x2 - o->x1) / (o->y1 - o->y2);
		sn = (o->x3 - o->x4) + (o->y3 - o->y4) * q;
		if (!sn)
			return (0);
		fn = (o->x3 - o->x1) + (o->y3 - o->y1) * q;
		n = fn / sn;
	}
	else
	{
		if (!(o->y3 - o->y4))
			return (0);
		n = (o->y3 - o->y1) / (o->y3 - o->y4);
	}
	cord->xx = o->x3 + (o->x4 - o->x3) * n;
	cord->yy = o->y3 + (o->y4 - o->y3) * n;
	return (1);
}

float	ft_floor_or_min(float num)
{
	float	result;

	result = floor(num);
	if (result == num && num >= 1)
		result -= 1;
	return (result);
}

float	ft_ceilf_or_add(float num)
{
	float	result;

	result = ceilf(num);
	if (result == num)
		result += 1;
	return (result);
}
