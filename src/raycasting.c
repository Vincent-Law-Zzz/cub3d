/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:21:39 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/29 21:31:42 by aapollo          ###   ########.fr       */
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
	float result;

	result = floor(num);
	if (result == num && num >= 1)
		result -= 1;
	return (result);
}


float	ft_ceilf_or_add(float num)
{
	float result;

	result = ceilf(num);
	if (result == num)
		result += 1;
	return (result);
}

int		ft_is_wall(t_game *game, t_vector *vector)
{
	int		xx;
	int		yy;
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
	return (ft_get_xy(&game->map,xx, yy) == '1');
}

float	ft_get_distance(t_cord *dest, t_cord *source)
{
	return(sqrt(pow(source->xx - dest->xx, 2) + pow(source->yy - dest->yy, 2)));
}

void	raycast_025(t_cross *o, t_vector *vector, t_cord *cord)
{
	o->x1 = floor(vector->cord.xx); 
	o->y1 = ft_floor_or_min(vector->cord.yy);
	o->x2 = floor(vector->cord.xx);
	o->y2 = ft_floor_or_min(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[0], o);
	o->x1 = ft_ceilf_or_add(vector->cord.xx); 
	o->y1 = ft_floor_or_min(vector->cord.yy);
	o->x2 = ft_ceilf_or_add(vector->cord.xx);
	o->y2 = ft_ceilf_or_add(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[1], o);
	if (ft_get_distance(&vector->cord, cord) < ft_get_distance(&vector->cord, cord + 1))
	{
		ft_memcpy(&vector->cord, &cord[0], sizeof(float) * 2);
		vector->dirtxtr = 0;
	}
	else
	{
		ft_memcpy(&vector->cord, &cord[1], sizeof(float) * 2);
		vector->dirtxtr = 1;
	}
}

void	raycast_05(t_cross *o, t_vector *vector, t_cord *cord)
{
	o->x1 = ft_ceilf_or_add(vector->cord.xx); 
	o->y1 = floor(vector->cord.yy);
	o->x2 = ft_ceilf_or_add(vector->cord.xx);
	o->y2 = ft_ceilf_or_add(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[0], o);
	o->x1 = ft_ceilf_or_add(vector->cord.xx); 
	o->y1 = ft_ceilf_or_add(vector->cord.yy);
	o->x2 = floor(vector->cord.xx);
	o->y2 = ft_ceilf_or_add(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[1], o);
	if (ft_get_distance(&vector->cord, cord) < ft_get_distance(&vector->cord, cord + 1))
	{
		ft_memcpy(&vector->cord, &cord[0], sizeof(float) * 2);
		vector->dirtxtr = 1;
	}
	else
	{
		ft_memcpy(&vector->cord, &cord[1], sizeof(float) * 2);
		vector->dirtxtr = 2;
	}
}

void	raycast_075(t_cross *o, t_vector *vector, t_cord *cord)
{
	o->x1 = ceilf(vector->cord.xx); 
	o->y1 = ft_ceilf_or_add(vector->cord.yy);
	o->x2 = ft_floor_or_min(vector->cord.xx);
	o->y2 = ft_ceilf_or_add(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[0], o);
	o->x1 = ft_floor_or_min(vector->cord.xx); 
	o->y1 = ft_ceilf_or_add(vector->cord.yy);
	o->x2 = ft_floor_or_min(vector->cord.xx);
	o->y2 = ft_floor_or_min(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[1], o);
	if (ft_get_distance(&vector->cord, cord) < ft_get_distance(&vector->cord, cord + 1))
	{
		ft_memcpy(&vector->cord, &cord[0], sizeof(float) * 2);
		vector->dirtxtr = 2;
	}
	else
	{
		ft_memcpy(&vector->cord, &cord[1], sizeof(float) * 2);
		vector->dirtxtr = 3;
	}
}

void	raycast_1(t_cross *o, t_vector *vector, t_cord *cord)
{
	o->x1 = ft_floor_or_min(vector->cord.xx); 
	o->y1 = ceilf(vector->cord.yy);
	o->x2 = ft_floor_or_min(vector->cord.xx);
	o->y2 = ft_floor_or_min(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[0], o);
	o->x1 = ft_floor_or_min(vector->cord.xx); 
	o->y1 = ft_floor_or_min(vector->cord.yy);
	o->x2 = ceilf(vector->cord.xx);
	o->y2 = ft_floor_or_min(vector->cord.yy);
	o->x3 = vector->cord.xx;
	o->y3 = vector->cord.yy;
	ft_cross(&cord[1], o);
	if (ft_get_distance(&vector->cord, cord) < ft_get_distance(&vector->cord, cord + 1))
	{
		ft_memcpy(&vector->cord, &cord[0], sizeof(float) * 2);
		vector->dirtxtr = 3;
	}
	else
	{
		ft_memcpy(&vector->cord, &cord[1], sizeof(float) * 2);
		vector->dirtxtr = 0;
	}
}

void	ft_ray(t_game *game, t_vector *vector)
{
	t_cross	o;
	t_cord	cord[2];
	
	o.x4 = vector->cord.xx + 2 * 
	cosf(ft_to_diap(-0.25 + vector->cord.direction) * M_PI * 2);
	o.y4 = vector->cord.yy + 2 * 
	sinf(ft_to_diap(-0.25 + vector->cord.direction) * M_PI * 2);
	if (vector->cord.direction < 0.25)
		raycast_025(&o, vector, cord);
	else if (vector->cord.direction < 0.5)
		raycast_05(&o, vector, cord);
	else if (vector->cord.direction < 0.75)
		raycast_075(&o, vector, cord);
	else
		raycast_1(&o, vector, cord);
	if (!ft_is_wall(game, vector))
		ft_ray(game, vector);
	else
		vector->distance = (sqrt(pow(game->player.xx- vector->cord.xx, 2) +\
			pow(game->player.yy - vector->cord.yy, 2)));
	if (vector->distance < 0.2)
		game->stop = 1;
}

void	ft_raycasting(t_game *game, t_vector *vector)
{
	size_t	index;
	float	dir_angle;
	float	increment;

	index = 0;
	dir_angle = game->player.direction - 0.125;
	increment = 0.25 / (float)game->param.screen.width;
	while (dir_angle < game->player.direction + 0.125 && index < (size_t)game->param.screen.width)
	{
		ft_memcpy(&(vector + index)->cord, &game->player, sizeof(t_cord));
		vector[index].cord.direction = ft_to_diap(dir_angle);
		ft_ray(game, vector + index);
		vector[index].cord.direction = fabs((float)index / (float)game->param.screen.width - 0.5);
		index++;
		dir_angle += increment;
	}
}
