/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:21:39 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:31:17 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int	ft_is_wall(t_game *game, t_vector *vector)
{
	int	xx;
	int	yy;

	if (vector->dirtxtr == 0)
	{
		xx = floor(vector->cord.xx);
		yy = ft_floor_or_min(vector->cord.yy);
	}
	else if (vector->dirtxtr == 1 || vector->dirtxtr == 2)
	{
		xx = (int)vector->cord.xx;
		yy = (int)vector->cord.yy;
	}
	else
	{
		xx = ft_floor_or_min(vector->cord.xx);
		yy = (int)vector->cord.yy;
	}
	return (ft_get_xy(&game->map, xx, yy) == '1');
}

float	ft_get_distance(t_cord *dest, t_cord *source)
{
	return (sqrt(pow(source->xx - dest->xx, 2) + \
		pow(source->yy - dest->yy, 2)));
}

void	ft_raycasting(t_game *game, t_vector *vector)
{
	size_t	index;
	float	dir_angle;
	float	increment;

	index = 0;
	dir_angle = game->player.direction - 0.125;
	increment = 0.25 / (float)game->param.screen.width;
	while (dir_angle < game->player.direction + 0.125 && \
		index < (size_t)game->param.screen.width)
	{
		ft_memcpy(&(vector + index)->cord, &game->player, sizeof(t_cord));
		vector[index].cord.direction = ft_to_diap(dir_angle);
		ft_ray(game, vector + index);
		vector[index].cord.direction = fabs((float)index / \
			(float)game->param.screen.width - 0.5);
		index++;
		dir_angle += increment;
	}
}
