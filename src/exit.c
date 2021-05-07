/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:47:56 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/07 04:35:37 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

void	ft_free(char **res)
{
	size_t	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static void	ft_free_image(t_game *game, t_texture *texture)
{
	if (texture->mlx_obj)
		mlx_destroy_image(game->mlx, texture->mlx_obj);
}

static void	ft_game_clear(t_game *game)
{
	free(game->map.data);
	ft_lstclear(&game->sprite, 0);
	ft_free_image(game, &game->param.ea);
	ft_free_image(game, &game->param.no);
	ft_free_image(game, &game->param.so);
	ft_free_image(game, &game->param.we);
	free(game->param.pth_ea);
	free(game->param.pth_no);
	free(game->param.pth_so);
	free(game->param.pth_we);
	ft_free_image(game, &game->param.s);
	ft_free_image(game, &game->param.screen);
	ft_lstclear(&game->map.list, free);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
}

int	ft_exit(t_game *game, char *s, int mode)
{
	if (s && mode)
	{
		ft_putendl_fd("Error!", 2);
		ft_putendl_fd(s, 2);
	}
	if (!mode)
		ft_putendl_fd(s, 2);
	if (game->event.f == 1)
		system("killall afplay");
	ft_game_clear(game);
	exit(0);
	return (0);
}
