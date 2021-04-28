/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:41:03 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/28 07:22:09 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

void	ft_background_rendering(t_game *game)
{
	int w;
	int h;

	w = 0;
	h = 0;
	while(h < game->param.screen.height)
	{
		w = 0;
		while(w < game->param.screen.width)
		{
			if(h < game->param.screen.height / 2)
				game->param.screen.data[h*game->param.screen.width + w] = game->param.ceil;
			else
				game->param.screen.data[h*game->param.screen.width + w] = game->param.floor;
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


int		ft_cross(float *n_xx, float *n_yy, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	float	q;
	float	n;
	float	sn;
	float	fn;

	if (y2 - y1 != 0)
	{
		q = (x2 - x1) / (y1 - y2);
		sn = (x3 - x4) + (y3 - y4) * q;
		if (!sn)
			return (0);
		fn = (x3 - x1) + (y3 - y1) * q;
		n = fn / sn;
	}
	else
	{
		if (!(y3 - y4))
			return (0);
		n = (y3 - y1) / (y3 - y4);
	}
	*n_xx = x3 + (x4 - x3) * n;
	*n_yy = y3 + (y4 - y3) * n;
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

void	ft_ray(t_game *game, t_vector *vector)
{
	t_cord	cord[3];

	if (vector->cord.xx >= 0)
		cord[2].xx = vector->cord.xx + 2 * cosf(ft_to_diap(-0.25 + vector->cord.direction) * M_PI * 2);
	if (vector->cord.yy >= 0)
		cord[2].yy = vector->cord.yy + 2 * sinf(ft_to_diap(-0.25 + vector->cord.direction) * M_PI * 2);
	if (vector->cord.direction < 0.25)
	{
		ft_cross(&cord[0].xx, &cord[0].yy, floor(vector->cord.xx), ft_floor_or_min(vector->cord.yy), floor(vector->cord.xx), ft_floor_or_min(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
		ft_cross(&cord[1].xx, &cord[1].yy, ft_ceilf_or_add(vector->cord.xx), ft_floor_or_min(vector->cord.yy), ft_ceilf_or_add(vector->cord.xx), ft_ceilf_or_add(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
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
	else if (vector->cord.direction < 0.5)
	{
		ft_cross(&cord[0].xx, &cord[0].yy, ft_ceilf_or_add(vector->cord.xx), floor(vector->cord.yy), ft_ceilf_or_add(vector->cord.xx), ft_ceilf_or_add(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
		ft_cross(&cord[1].xx, &cord[1].yy, ft_ceilf_or_add(vector->cord.xx), ft_ceilf_or_add(vector->cord.yy), floor(vector->cord.xx), ft_ceilf_or_add(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
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
	else if (vector->cord.direction < 0.75)
	{
		ft_cross(&cord[0].xx, &cord[0].yy, ceilf(vector->cord.xx), ft_ceilf_or_add(vector->cord.yy), ft_floor_or_min(vector->cord.xx), ft_ceilf_or_add(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
		ft_cross(&cord[1].xx, &cord[1].yy, ft_floor_or_min(vector->cord.xx), ft_ceilf_or_add(vector->cord.yy), ft_floor_or_min(vector->cord.xx), ft_floor_or_min(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
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
	else
	{
		ft_cross(&cord[0].xx, &cord[0].yy, ft_floor_or_min(vector->cord.xx), ceilf(vector->cord.yy), ft_floor_or_min(vector->cord.xx), ft_floor_or_min(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
		ft_cross(&cord[1].xx, &cord[1].yy, ft_floor_or_min(vector->cord.xx), ft_floor_or_min(vector->cord.yy), ceilf(vector->cord.xx), ft_floor_or_min(vector->cord.yy), vector->cord.xx, vector->cord.yy, cord[2].xx, cord[2].yy);
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
	if (!ft_is_wall(game, vector))
		ft_ray(game, vector);
	// if (ft_get_xy(&game->map,\
	// 		(int)(floor(vector->cord.xx)),\
	// 		(int)(floor(vector->cord.yy))) != '1')
	// 	ft_ray(game, vector);
	else
		vector->distance = sqrt(pow(game->player.xx- vector->cord.xx, 2) +\
							pow(game->player.yy - vector->cord.yy, 2));
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
