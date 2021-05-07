/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:58:54 by telron            #+#    #+#             */
/*   Updated: 2021/05/03 20:46:33 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

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
	int		xx;
	int		xx_centr;
	t_cord	otnos;
	size_t	counter;
	size_t	pixel_count;

	counter = 0;
	xx_centr = ft_to_diap_05((1.0 - ft_to_diap(atan2(game->player.xx - \
		sprite->vector.cord.xx, game->player.yy - sprite->vector.cord.yy) \
			/ (M_PI * 2))) - game->player.direction) / 0.125 * \
				game->param.screen.width / 2 + game->param.screen.width / 2;
	pixel_count = game->param.screen.width * atan(0.5 / sprite->vector.distance) \
		* 2 / (M_PI / 2);
	xx = xx_centr - pixel_count / 2;
	while (counter < pixel_count)
	{
		otnos.xx = (float)counter / (float)pixel_count;
		if (0 <= xx && xx < game->param.screen.width)
			otnos.direction = vector[xx].distance;
		if (0 <= xx && xx < game->param.screen.width && \
			vector[xx].distance > sprite->vector.distance)
			ft_sprite_vert_render(game, sprite, xx, otnos);
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
	ft_lstclear(&sprite, free);
}
