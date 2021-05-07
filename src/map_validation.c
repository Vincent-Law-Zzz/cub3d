/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:51:05 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:51:07 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

void	ft_checkwalls(t_game *game)
{
	int		i;
	int		len;

	i = 0;
	len = game->map.height * game->map.width;
	while (i < len)
	{
		if (!ft_strchr("NESW102", game->map.data[i]))
			ft_exit(game, "Map contains forbiden chars", 1);
		i++;
	}
}

void	ft_checkrules(t_game *game, int x, int y)
{
	static int	arr[][2] = {{-1, -1}, {0, -1}, {1, -1},	\
		{-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int			counter;

	counter = 0;
	while (counter < 8)
	{
		if (!ft_get_xy(&game->map, x + arr[counter][0], y + arr[counter][1]))
			ft_exit(game, "Map is not ", 1);
		counter++;
	}
}

void	ft_checktop(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = ft_get_xy(&game->map, x, y);
			if (c == '2' || c == '0')
				ft_checkrules(game, x, y);
			x++;
		}
		y++;
	}
}

void	ft_path_map_is_valid(t_game *game)
{
	size_t	counter;

	counter = 0;
	while (game->path_map[counter])
		counter++;
	if (counter < 4 || ft_strncmp(game->path_map + counter - 4, ".cub", 5))
		ft_exit(game, ".cub error", 1);
}
