/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:47:40 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:50:54 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

static void	raycast_025(t_cross *o, t_vector *vector, t_cord *cord)
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
	if (ft_get_distance(&vector->cord, cord) < \
		ft_get_distance(&vector->cord, cord + 1))
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

static void	raycast_05(t_cross *o, t_vector *vector, t_cord *cord)
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
	if (ft_get_distance(&vector->cord, cord) < \
		ft_get_distance(&vector->cord, cord + 1))
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

static void	raycast_075(t_cross *o, t_vector *vector, t_cord *cord)
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
	if (ft_get_distance(&vector->cord, cord) < \
		ft_get_distance(&vector->cord, cord + 1))
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

static void	raycast_1(t_cross *o, t_vector *vector, t_cord *cord)
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
	if (ft_get_distance(&vector->cord, cord) < \
		ft_get_distance(&vector->cord, cord + 1))
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

	o.x4 = vector->cord.xx + 2 * \
		cosf(ft_to_diap(-0.25 + vector->cord.direction) * M_PI * 2);
	o.y4 = vector->cord.yy + 2 * \
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
		vector->distance = (sqrt(pow(game->player.xx - vector->cord.xx, 2) + \
			pow(game->player.yy - vector->cord.yy, 2)));
	if (vector->distance < 0.2)
		game->stop = 1;
}
