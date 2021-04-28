/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telron <telron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 01:13:51 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/27 07:42:01 by telron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int		ft_loop_tick(t_game *game)
{
	t_vector vector[game->param.screen.width];

	// printf("%d count sprite\n", ft_lstsize(game->sprite));
	ft_event_processing(game); //to do
	ft_background_rendering(game);
	ft_raycasting(game, vector); // to do
	ft_rendering(game,vector); //to do
	ft_sprite_preprocessing(game);
	ft_sprite_rendering(game, vector);
	// ft_rc2(game,&game->ray);
	// ft_minimap(game);
	// printf("%d count sprite\n", ft_lstsize(game->sprite));
	mlx_put_image_to_window(game->mlx,game->window , game->param.screen.mlx_obj , 0, 0);
	return (0);
}

int		main(void)
{
	t_game  game;

	ft_bzero(&game, sizeof(t_game));
	pars_processing(&game);
	game.mlx = mlx_init();
	ft_txtr_procesing(&game);
	ft_screen_image(&game);
	game.window = mlx_new_window(game.mlx, game.param.screen.width, game.param.screen.height, "Sanya Cub");
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.window, 2, 0, handle_pressed_key, &game);
	mlx_loop_hook(game.mlx, ft_loop_tick, &game);
	mlx_hook(game.window, 3, 0, handle_unpressed_key, &game);
	mlx_loop(game.mlx);
	return (0);
}
