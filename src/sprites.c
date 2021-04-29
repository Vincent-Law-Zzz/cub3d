/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:58:54 by telron            #+#    #+#             */
/*   Updated: 2021/04/29 23:03:29 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int	ft_cmp_sprite(t_sprite *sprite1, t_sprite *sprite2)
{
	return (sprite1->vector.distance < sprite2->vector.distance);
}

void 	ft_sprite_init(t_game *game, int xx, int yy)
{
	t_sprite	*sprite;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!(sprite))
		ft_exit(game, "sprite is soooo fucking deeep", 1);
	sprite->vector.cord.xx = (float)xx + 0.5;
	sprite->vector.cord.yy = (float)yy + 0.5;
	sprite->move.content = sprite;
	ft_lstadd_by_cond(&game->sprite, (t_list *)sprite, \
		(int (*)(void *, void *))ft_cmp_sprite);
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
		((t_sprite *)now)->vector.distance = ft_get_distance(&game->player, \
			&((t_sprite *)now)->vector.cord);
		next = now->next;
		ft_lstadd_by_cond(&begin, now, (int (*)(void *, void *))ft_cmp_sprite);
		now = next;
	}
	game->sprite = begin;
}

void	ft_sprite_draw_pix(t_game *game, t_icord icord, \
	float xx_otn, float yy_otn)
{
	t_color	color;

	color = ft_get_pixel(game, 4, xx_otn, yy_otn);
	if (color.R || color.G || color.B)
		game->param.screen.data[icord.yy * game->param.screen.width \
			+ icord.xx] = color;
}

void	ft_sprite_vert_render(t_game *game, t_sprite *sprite, \
	t_icord icord, float xx_otn)
{
	int		yy_centr;
	size_t	pixel_count;
	size_t	counter;
	float	yy_otn;

	counter = 0;
	pixel_count = game->param.screen.height / sprite->vector.distance;
	yy_centr = game->param.screen.height / 2;
	icord.yy = yy_centr - pixel_count / 2;
	while (counter < pixel_count)
	{
		yy_otn = (float)counter / (float)pixel_count;
		if (0 <= icord.yy && icord.yy < game->param.screen.height)
			ft_sprite_draw_pix(game, icord, xx_otn, yy_otn);
		icord.yy++;
		counter++;
	}
}

float	ft_to_diap_05(float digit)
{
	if (digit > 0.5)
		return (digit - 1);
	if (digit < -0.5)
		return (digit + 1);
	return (digit);
}

void	ft_sprite_one_rendering(t_game *game, t_vector *vector, \
	t_sprite *sprite)
{
	t_icord	icord;
	int		xx_centr;
	float	xx_otn;
	size_t	counter;
	size_t	pixel_count;

	counter = 0;
	xx_centr = ft_to_diap_05((1.0 - ft_to_diap(atan2(game->player.xx - sprite->vector.cord.xx, \
		game->player.yy - sprite->vector.cord.yy) / (M_PI * 2))) - game->player.direction) / 0.125 * \
		game->param.screen.width / 2 + game->param.screen.width / 2;
	pixel_count = game->param.screen.width * atan(0.5 / sprite->vector.distance) \
		* 2 / (M_PI / 2);
	icord.xx = xx_centr - pixel_count / 2 ;
	while (counter < pixel_count)
	{
		xx_otn = (float)counter / (float)pixel_count;
		if (0 <= icord.xx && icord.xx < game->param.screen.width && vector[icord.xx].distance > \
			 sprite->vector.distance)
			ft_sprite_vert_render(game, sprite, icord, xx_otn);
		icord.xx++;
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
