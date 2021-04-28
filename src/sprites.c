/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telron <telron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:58:54 by telron            #+#    #+#             */
/*   Updated: 2021/04/27 08:04:57 by telron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int		ft_cmp_sprite(t_sprite *sprite1, t_sprite *sprite2)
{
	return (sprite1->vector.distance < sprite2->vector.distance);
}

void 	ft_sprite_init(t_game *game, int xx, int yy)
{
	t_sprite	*sprite;

	if (!(sprite = ft_calloc(1,sizeof(t_sprite))))
		ft_exit(game, "sprite is soooo fucking deeep", 1);
	sprite->vector.cord.xx = (float)xx + 0.5;
	sprite->vector.cord.yy = (float)yy + 0.5;
	sprite->move.content = sprite;
	ft_lstadd_by_cond(&game->sprite, (t_list*)sprite, (int (*)(void*,void*))ft_cmp_sprite);
}

void	ft_sprite_preprocessing(t_game *game)
{
	t_list	*begin;
	t_list	*now;
	t_list	*next;

	begin = 0;
	now = game->sprite;
	while (now)
	{
		((t_sprite*)now)->vector.distance = ft_get_distance(&game->player, &((t_sprite*)now)->vector.cord);
		next = now->next;
		ft_lstadd_by_cond(&begin, now, (int (*)(void *, void *))ft_cmp_sprite);
		now = next;
	}
	game->sprite = begin;
}

void	ft_sprite_draw_pix(t_game *game, int xx, int yy, float xx_otn, float yy_otn)
{
	t_color	color;

	color = ft_get_pixel(game, 4, xx_otn, yy_otn);
	if (color.R || color.G || color.B)
		game->param.screen.data[yy * game->param.screen.width + xx] = color;
}

void	ft_sprite_vert_render(t_game *game, t_sprite *sprite, int xx, float xx_otn)
{
	int yy;
	int yy_centr;
	float coef_angle_h;
	size_t pixel_count;
	size_t	counter;
	float	yy_otn;

	counter = 0;
	coef_angle_h = atan(0.5 / sprite->vector.distance) * 2 / (M_PI / 3);
	pixel_count = game->param.screen.height * coef_angle_h;
	yy_centr = game->param.screen.height / 2;
	yy = yy_centr - pixel_count / 2;
	while (counter < pixel_count)
	{
		yy_otn = (float)counter / (float)pixel_count;
		if (0 <= yy && yy < game->param.screen.height)
			ft_sprite_draw_pix(game, xx, yy, xx_otn, yy_otn);
		yy++;
		counter++;
	}
}

void	ft_sprite_one_rendering(t_game *game, t_vector *vector, t_sprite *sprite)
{
	int		xx;
	int		xx_centr;
	float	xx_otn;
	float	direction;
	size_t	counter;
	float	coef_angle_w;
	size_t	pixel_count;

	counter = 0;
	direction = (1.0 - ft_to_diap(atan2(game->player.xx - sprite->vector.cord.xx,\
		game->player.yy - sprite->vector.cord.yy) / (M_PI * 2)));
	xx_centr = (direction - game->player.direction) / 0.125 * game->param.screen.width / 2 + game->param.screen.width / 2;
	coef_angle_w = atan(0.5 / sprite->vector.distance) * 2 / (M_PI / 2);
	pixel_count = game->param.screen.width * coef_angle_w;
	xx = xx_centr - pixel_count / 2;
	while (counter < pixel_count)
	{
		xx_otn = (float)counter / (float)pixel_count;
		if (0 <= xx && xx < game->param.screen.width && vector[xx].distance > sprite->vector.distance)
			ft_sprite_vert_render(game, sprite, xx, xx_otn);
		xx++;
		counter++;
	}
}

void	ft_sprite_rendering(t_game *game, t_vector *vector)
{
	t_list	*sprite;

	sprite = game->sprite;
	while (sprite)
	{
		ft_sprite_one_rendering(game, vector, (t_sprite *)sprite);
		sprite = sprite->next;
	}
}
