/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:11:34 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/25 15:51:51 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int	handle_pressed_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game," game over ", 0);
	if (keycode == KEY_W)
		game->event.up = 1;
	if (keycode == KEY_S)
		game->event.down = 1;
	if (keycode == KEY_A)
		game->event.left = 1;
	if (keycode == KEY_D)
		game->event.right = 1;
	if (keycode == KEY_LEFT || keycode == KEY_Q)
		game->event.q = 1;
	if (keycode == KEY_RIGHT || keycode == KEY_E)
		game->event.e = 1;
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

void ft_player_move(t_game *game)
{
	float dir;

	dir = game->player.direction;
	if (game->event.up)
	{
		game->player.xx += cos((dir - 0.25) * M_PI * 2) * PLAYER_V;
		game->player.yy += sin((dir - 0.25) * M_PI * 2) * PLAYER_V;
		// if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx + ray->dirX * PLAYER_V),(int)(game->player.yy))))
		// 	game->player.xx += ray->dirX * PLAYER_V;
		// if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx),(int)(game->player.yy + ray->dirY * PLAYER_V))))
		// 	game->player.yy += ray->dirY * PLAYER_V;
	}
	if (game->event.down)
	{
		game->player.xx -= cos((dir - 0.25) * M_PI * 2) * PLAYER_V;
		game->player.yy -= sin((dir - 0.25) * M_PI * 2) * PLAYER_V;
		// if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx - ray->dirX * PLAYER_V),(int)(game->player.yy))))
		// 	game->player.xx -= ray->dirX * PLAYER_V;
		// if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx),(int)(game->player.yy - ray->dirY * PLAYER_V))))
		// 	game->player.yy -= ray->dirY * PLAYER_V;
	}
// 	if (game->event.left)
// 	{
// 		if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx + cos(dir + M_PI_2) * PLAYER_V),(int)(game->player.yy))))
// 			game->player.xx += cos(dir + M_PI_2) * PLAYER_V;
// 		if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx),(int)(game->player.yy + sin(dir + M_PI_2) * PLAYER_V))))
// 			game->player.yy += sin(dir + M_PI_2) * PLAYER_V;
// 	}
// 	if (game->event.right)
// 	{
// 		if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx + cos(dir - M_PI_2) * PLAYER_V),(int)(game->player.yy))))
// 			game->player.xx += cos(dir - M_PI) * PLAYER_V;
// 		if (ft_strchr("02",ft_get_xy(&game->map,(int)(game->player.xx),(int)(game->player.yy + sin(dir + 1.5 * M_PI_2) * PLAYER_V))))
// 			game->player.yy += sin(dir - M_PI) * PLAYER_V;
// 	}
}

void	ft_event_processing(t_game *game)
{
	ft_player_move(game); //todo: условие ограничивающее хождение сквозь стены
	// double oldDirX = ray->dirX;
	// double oldPlaneX = ray->planeX;
	if (game->event.q)
	{
		game->player.direction = ft_to_diap(game->player.direction - ROT_V);
		// ray->dirX = ray->dirX * cos(-ROT_V) - ray->dirY * sin(-ROT_V);
		// ray->dirY = oldDirX * sin(-ROT_V) + ray->dirY * cos(-ROT_V);
		// ray->planeX = ray->planeX * cos(-ROT_V) - ray->planeY * sin(-ROT_V);
		// ray->planeY = oldPlaneX * sin(-ROT_V) + ray->planeY * cos(-ROT_V);
	}
	if (game->event.e)
	{
		game->player.direction = ft_to_diap(game->player.direction + ROT_V);
		// ray->dirX = ray->dirX * cos(ROT_V) - ray->dirY * sin(ROT_V);
		// ray->dirY = oldDirX * sin(ROT_V) + ray->dirY * cos(ROT_V);
		// ray->planeX = ray->planeX * cos(ROT_V) - ray->planeY * sin(ROT_V);
		// ray->planeY = oldPlaneX * sin(ROT_V) + ray->planeY * cos(ROT_V);
	}
}
