/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:51:22 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:51:24 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int	ft_elemsum(int *width, int y)
{
	int	res;

	res = 0;
	while (y > 0)
	{
		y--;
		if (width[y])
			res += width[y];
		else
			return (0);
	}
	return (res);
}

char	ft_get_xy(t_map *map, int x, int y)
{
	if (x >= map->width || x < 0)
		return ('\0');
	if (y >= map->height || y < 0)
		return ('\0');
	return (map->data[x + y * map->width]);
}

void	ft_parsmap(t_game *game, int fd)
{
	char	*tmp;
	char	*line;
	int		width;
	int		end;

	end = 1;
	while (!game->param.error && end > 0 && (end != -1))
	{
		end = get_next_line(fd, &tmp);
		line = ft_strjoin("    ", tmp);
		free(tmp);
		if (!ft_lstadd_back_content(&game->map.list, line))
			ft_exit(game, "Error", 1);
		width = (int)ft_strlen(line);
		if (width > game->map.width)
			game->map.width = width;
	}
	if (end == -1)
		ft_exit(game, "GNL error", 1);
	game->map.height = ft_lstsize(game->map.list);
}

void	ft_pars_pl_pos(t_game *game, t_cord cord, char *ptr, char *dir)
{
	if (game->player.xx)
		ft_exit(game, "more than one player", 1);
	game->player.direction = ((float)(ptr - dir)) / 4;
	game->map.data[(int)(cord.xx + cord.yy * game->map.width)] = '0';
	game->player.xx = cord.xx + 0.5;
	game->player.yy = cord.yy + 0.5;
}

void	ft_map_creation(t_game *game)
{
	t_list		*tmp;
	t_cord		cord;
	static char	dir[] = "NESW";
	char		*ptr;

	cord.yy = 0;
	tmp = game->map.list;
	while (tmp)
	{
		cord.xx = 0;
		while (((char *)tmp->content)[(int)cord.xx])
		{
			ptr = ft_strchr(dir, ((char *)tmp->content)[(int)cord.xx]);
			if (((char *)tmp->content)[(int)cord.xx] == '2')
				ft_sprite_init(game, cord.xx, cord.yy);
			if (ptr)
				ft_pars_pl_pos(game, cord, ptr, dir);
			else if (((char *)tmp->content)[(int)cord.xx] != ' ')
				game->map.data[(int)(cord.xx + cord.yy * game->map.width)] = \
					((char *)tmp->content)[(int)cord.xx];
			cord.xx++;
		}
		cord.yy++;
		tmp = tmp->next;
	}
}
