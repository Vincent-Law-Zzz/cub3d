/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 21:36:34 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 21:36:36 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

static int	ft_get_size_block(t_game *game)
{
	int	min_side;

	min_side = game->param.screen.width / game->map.width;
	if (min_side > game->param.screen.height / game->map.height)
		min_side = game->param.screen.height / game->map.height;
	min_side /= 5;
	if (min_side < 4)
		return (4);
	return (min_side);
}

static void	print_block_npx(t_game *game, t_color color, t_cord cord, int n)
{
	int	x;
	int	y;
	int	h;
	int	w;

	h = cord.yy * n - cord.direction;
	w = cord.xx * n - cord.direction;
	y = 0;
	if (h >= 0 && w >= 0 && h + y <= game->param.screen.width * \
		game->param.screen.height)
	{
		while (y < n)
		{
			x = 0;
			while (x < n)
			{
				if (h + y > 0 && w + x < game->param.screen.width && \
					h + y < game->param.screen.height)
					game->param.screen.data[(w + x) + (h + y) * \
						game->param.screen.width] = color;
				x++;
			}
			y++;
		}
	}
}

static void	ft_plr_pos(t_game *game, t_cord *plr)
{
	plr->xx = game->player.xx - 0.5;
	plr->yy = game->player.yy - 0.5;
	plr->direction = ft_get_size_block(game) / 4;
}

void	ft_minimap(t_game *game)
{
	t_cord	map;
	t_cord	plr;
	t_color	color1;
	t_color	color2;

	ft_plr_pos(game, &plr);
	map.direction = 0;
	ft_make_color(&color1, 225, 17, 150);
	ft_make_color(&color2, 255, 255, 255);
	map.yy = 0;
	while (map.yy < (game->map.height))
	{
		map.xx = 0;
		while (map.xx < game->map.width)
		{
			if (ft_get_xy(&game->map, map.xx, map.yy) == '1')
				print_block_npx(game, color1, map, ft_get_size_block(game));
			map.xx++;
		}
		map.yy++;
	}
	print_block_npx(game, color2, plr, ft_get_size_block(game));
}
