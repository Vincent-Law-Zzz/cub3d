/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:50:24 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:50:32 by aapollo          ###   ########.fr       */
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
		ft_exit(game, "big sprite", 1);
	sprite->vector.cord.xx = (float)xx + 0.5;
	sprite->vector.cord.yy = (float)yy + 0.5;
	sprite->move.content = sprite;
	ft_lstadd_by_cond(&game->sprite, (t_list *)sprite, (int (*)(void *, \
		void *))ft_cmp_sprite);
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

void	ft_sprite_draw_pix(t_game *game, int xx, int yy, t_cord otnos)
{
	t_color	color;

	color = ft_get_pixel(game, 4, otnos.xx, otnos.yy);
	if (color.R || color.G || color.B)
		game->param.screen.data[yy * game->param.screen.width + xx] = color;
}

void	ft_sprite_vert_render(t_game *game, t_sprite *sprite, \
	int xx, t_cord otnos)
{
	int		yy;
	int		yy_centr;
	float	coef_angle_h;
	size_t	pixel_count;
	size_t	counter;

	counter = 0;
	coef_angle_h = atan(0.5 / sprite->vector.distance) * 2 / (M_PI / 3);
	pixel_count = game->param.screen.height * coef_angle_h;
	yy_centr = game->param.screen.height / 2;
	yy = yy_centr - pixel_count * 0.5 / 2;
	while (counter < pixel_count)
	{
		otnos.yy = (float)counter / (float)pixel_count;
		if (0 <= yy && yy < game->param.screen.height)
			ft_sprite_draw_pix(game, xx, yy, otnos);
		yy++;
		counter++;
	}
}
