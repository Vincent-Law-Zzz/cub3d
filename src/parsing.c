/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:11:39 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:18:17 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int	pars_processing(t_game *game)
{
	int			fd;
	int			i;

	i = 0;
	ft_path_map_is_valid(game);
	fd = open(game->path_map, O_RDONLY);
	if (fd == -1)
		ft_exit(game, "can not find a map", 1);
	pars_param(game, fd);
	ft_parsmap(game, fd);
	game->map.data = ft_calloc(game->map.width, game->map.height);
	if (!(game->map.data))
		ft_exit(game, "big map", 1);
	ft_map_creation(game);
	ft_checkwalls(game);
	ft_checktop(game);
	return (0);
}

void	ft_get_textur(t_game *game, char *path, t_texture *texture)
{
	int	n;

	texture->mlx_obj = mlx_xpm_file_to_image(game->mlx, path, \
		&texture->width, &texture->height);
	if (!(texture->mlx_obj))
		ft_exit(game, "texture error", 1);
	texture->data = (t_color *)mlx_get_data_addr(texture->mlx_obj, &n, &n, &n);
	if (!(texture->data))
		ft_exit(game, "texture data error", 1);
}

void	ft_txtr_procesing(t_game *game)
{
	ft_get_textur(game, game->param.pth_no, &game->param.no);
	ft_get_textur(game, game->param.pth_so, &game->param.so);
	ft_get_textur(game, game->param.pth_ea, &game->param.ea);
	ft_get_textur(game, game->param.pth_we, &game->param.we);
	ft_get_textur(game, game->param.pth_s, &game->param.s);
}

void	ft_screen_image(t_game *game)
{
	int	n;

	game->param.screen.mlx_obj = mlx_new_image(game->mlx, game->param.screen.width, \
		game->param.screen.height);
	if (!(game->param.screen.mlx_obj))
		ft_exit(game, "texture error      screenshot", 1);
	game->param.screen.data = (t_color *)mlx_get_data_addr(game->param.screen.mlx_obj, \
		&n, &n, &n);
	if (!(game->param.screen.data))
		ft_exit(game, "texture data error       screenshot", 1);
}

void	ft_make_color(t_color *color, int r, int g, int b)
{
	color->attributes = 1;
	color->R = r;
	color->B = b;
	color->G = g;
}
