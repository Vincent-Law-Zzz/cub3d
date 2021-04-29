/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:11:34 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/29 20:37:05 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int	handle_pressed_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game, " game over ", 0);
	if (keycode == KEY_W)
		game->event.up = 1;
	if (keycode == KEY_S)
		game->event.down = 1;
	if (keycode == KEY_A)
		game->event.left = 1;
	if (keycode == KEY_D)
		game->event.right = 1;
	if ((keycode == KEY_LEFT || keycode == KEY_Q) && !game->event.left)
		game->event.q = 1;
	if ((keycode == KEY_RIGHT || keycode == KEY_E) && !game->event.right)
		game->event.e = 1;
	if ((game->event.down || game->event.left || game->event.right) \
		&& !game->event.up)
		game->stop = 0;
	return (0);
}

int	handle_unpressed_key(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->event.up = 0;
	if (keycode == KEY_S)
		game->event.down = 0;
	if (keycode == KEY_A)
		game->event.left = 0;
	if (keycode == KEY_D)
		game->event.right = 0;
	if (keycode == KEY_LEFT || keycode == KEY_Q)
		game->event.q = 0;
	if (keycode == KEY_RIGHT || keycode == KEY_E)
		game->event.e = 0;
	return (0);
}

void	ft_player_move(t_game *game)
{
	float	dir;
	float	xx_delta;
	float	yy_delta;

	dir = game->player.direction;
	xx_delta = (1 - game->stop) * cos((dir - 0.25) * M_PI * 2) * PLAYER_V * \
		(game->event.up - game->event.down);
	yy_delta = (1 - game->stop) * sin((dir - 0.25) * M_PI * 2) * PLAYER_V * \
		(game->event.up - game->event.down);
	if (ft_get_xy(&game->map, (int)(game->player.xx + xx_delta), \
		(int)(game->player.yy + yy_delta)) == '0')
	{
		game->player.xx += xx_delta;
		game->player.yy += yy_delta;
	}
	xx_delta = (1 - game->stop) * cos((dir - 0.5) * M_PI * 2) * PLAYER_V * \
		(game->event.left - game->event.right);
	yy_delta = (1 - game->stop) * sin((dir - 0.5) * M_PI * 2) * PLAYER_V * \
		(game->event.left - game->event.right);
	if (ft_get_xy(&game->map, (int)(game->player.xx + xx_delta), \
		(int)(game->player.yy + yy_delta)) == '0')
	{
		game->player.xx += xx_delta;
		game->player.yy += yy_delta;
	}
}

void	ft_event_processing(t_game *game)
{
	ft_player_move(game);
	if (game->event.q)
	{
		game->player.direction = ft_to_diap(game->player.direction - ROT_V);
		game->stop = 0;
	}
	if (game->event.e)
	{
		game->player.direction = ft_to_diap(game->player.direction + ROT_V);
		game->stop = 0;
	}
}
