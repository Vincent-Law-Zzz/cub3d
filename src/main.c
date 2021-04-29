/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:49 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/29 20:32:29 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

// void	ft_free_vctrs(t_game *game, t_vector *vectors)
// {
// 	int	i;

// 	i = 0;
// 	while (i < game->param.screen.width)
// 	{
// 		free(vectors[i].cord)
// 	}
// }
int	ft_loop_tick(t_game *game)
{
	game->vectors = malloc((size_t)game->param.screen.width* \
		sizeof(t_vector));
	if (!game->vectors)
		ft_exit(game, "No memory allocated for rays", 1);
	ft_event_processing(game);
	ft_background_rendering(game);
	ft_raycasting(game, game->vectors);
	ft_rendering(game, game->vectors);
	ft_sprite_preprocessing(game);
	ft_sprite_rendering(game, game->vectors);
	ft_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, \
		game->param.screen.mlx_obj, 0, 0);
	free(game->vectors);
	return (0);
}

void	ft_create_screen(t_game *game)
{
	ft_loop_tick(game);
	ft_bmp_create(game);
	ft_exit(game, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2)
		ft_exit(&game, "Put path to map", 1);
	ft_bzero(&game, sizeof(t_game));
	game.path_map = argv[1];
	pars_processing(&game);
	game.mlx = mlx_init();
	ft_txtr_procesing(&game);
	ft_screen_image(&game);
	if (game.param.screen.width >= 100 && game.param.screen.height >= 100)
		game.window = mlx_new_window(game.mlx, game.param.screen.width, \
			game.param.screen.height, "Sanya Cub");
	else
		ft_exit(&game, "small screen size parameters", 1);
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", 7))
			ft_create_screen(&game);
		ft_exit(&game, "Bad 3 param!", 1);
	}
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.window, 2, 0, handle_pressed_key, &game);
	mlx_loop_hook(game.mlx, ft_loop_tick, &game);
	mlx_hook(game.window, 3, 0, handle_unpressed_key, &game);
	mlx_hook(game.window, 17, 0, ft_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
