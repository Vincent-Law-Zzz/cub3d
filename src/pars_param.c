/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:51:52 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:51:53 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

void	ft_pars_screen(t_game *game, char *str)
{
	int	i;

	i = 0;
	if (game->param.screen.width || game->param.screen.height)
		ft_exit(game, "screen is parsed", 1);
	while (ft_isdigit(str[i]))
	{
		game->param.screen.width = game->param.screen.width \
			* 10 + (str[i] - '0');
		i++;
	}
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]))
	{
		game->param.screen.height = game->param.screen.height \
			* 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && !game->param.screen.height)
		ft_exit(game, "Param error screen problems blyat", 1);
	ft_check_screen_size(game);
}

void	ft_init_var(t_game *game, void *arr[][3])
{
	arr[0][2] = &game->param.pth_no;
	arr[1][2] = &game->param.pth_so;
	arr[2][2] = &game->param.pth_we;
	arr[3][2] = &game->param.pth_ea;
	arr[4][2] = &game->param.pth_s;
	arr[5][2] = &game->param.floor;
	arr[6][2] = &game->param.ceil;
}

void	def_param_type(t_game *game, char *str)
{
	int			counter;
	static void	*arr[][3] = {{"NO ", ft_cpath, 0}, {"SO ", ft_cpath, 0}, \
		{"WE ", ft_cpath, 0}, {"EA ", ft_cpath, 0}, {"S ", ft_cpath, 0}, \
		{"F ", ft_pars_color, 0}, {"C ", ft_pars_color, 0}, \
	 	{"R ", ft_pars_screen, 0}, {0, 0, 0}};

	ft_init_var(game, arr);
	counter = 0;
	if (str[0] == '\0')
		return ;
	while (*arr[counter] != 0)
	{
		if (!ft_strncmp(*arr[counter], str, ft_strlen(*arr[counter])))
		{
			((void (*)(t_game *, char *, void *))arr[counter][1])(game, str + \
				ft_strlen(*arr[counter]), arr[counter][2]);
			return ;
		}	
		counter++;
	}
	ft_exit(game, "set the attributes", 1);
}

int	ft_ismap(t_game *game)
{
	if (game->param.screen.width && game->param.screen.height && game->param.pth_no && \
		game->param.pth_so && game->param.pth_we && game->param.pth_ea && game->param.pth_s \
			&& game->param.floor.attributes && game->param.ceil.attributes)
		return (1);
	return (0);
}

void	pars_param(t_game *game, int fd)
{
	char	*line;

	while (!ft_ismap(game) && get_next_line(fd, &line))
	{
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (!ft_ismap(game))
		{
			def_param_type(game, line);
			free(line);
		}
	}
}
