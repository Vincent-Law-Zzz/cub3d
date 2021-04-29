#include "cub_header.h"

void	print_block_npx(t_game *game,t_color color,t_cord cord, int n)
{
	int	x;
	int	y;
	int h;
	int w;

	h = cord.yy * n - cord.direction;
	w = cord.xx * n - cord.direction;
	y = 0;
	if (h >= 0 && w >= 0 && h+y <= game->param.screen.width * game->param.screen.height)
		while (y < n)
		{
			x = 0;
			while (x < n)
			{
				if ( h+y > 0)
					game->param.screen.data[(h+y)*game->param.screen.width + (w+x)] = color;
				x++;
			}
			y++;
		}
}

void	ft_minimap(t_game *game)
{
	t_cord map;
	t_cord plr;
	char c;
	t_color	color1;
	t_color	color2;

	plr.xx = game->player.xx * 2;
	plr.yy = game->player.yy * 2;
	plr.direction = 2.5;
	map.direction = 0;
	ft_make_color(&color1,225,17,150);
	ft_make_color(&color2,255,255,255);
	map.yy = 0;
	while (map.yy < (game->map.height))
	{
		map.xx = 0;
		while (map.xx < game->map.width)
		{
			c = ft_get_xy(&game->map, map.xx, map.yy);
			if (c == '1')
				print_block_npx(game, color1, map, 10);
			map.xx++;
		}
		map.yy++;
	}
	print_block_npx(game, color2, plr, 5);
}

