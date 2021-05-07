/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:51:35 by aapollo           #+#    #+#             */
/*   Updated: 2021/05/03 20:51:36 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int	ft_strcount(char **res)
{
	int	counter;

	counter = 0;
	while (res[counter])
		counter++;
	return (counter);
}

int	ft_make_atr(t_game *game, char *res)
{
	int	i;
	int	ch;

	i = 0;
	ch = 0;
	while (ft_isdigit(res[i]))
	{
		ch = ch * 10 + (res[i] - '0');
		i++;
	}
	if (res[i] != '\0' || ch > 255)
		ft_exit(game, "Color must be < 255 && contain only digest", 1);
	return (ch);
}

void	ft_pars_color(t_game *game, char *str, t_color *color)
{
	char	**res;

	if (color->attributes)
		ft_exit(game, "colore is parsed", 1);
	res = ft_split(str, ',');
	if (!(res) || color->attributes || (ft_strcount(res) != 3))
	{
		ft_free(res);
		ft_exit(game, \
			"Color must contain 3 args followed by \",\" as separator", 1);
	}
	color->R = ft_make_atr(game, res[0]);
	color->G = ft_make_atr(game, res[1]);
	color->B = ft_make_atr(game, res[2]);
	ft_free(res);
	color->attributes = 1;
}

void	ft_cpath(t_game *game, char *str, void **var)
{
	if (*var)
		ft_exit(game, "double texture", 1);
	*var = ft_strdup(str);
	if (!(*var))
		ft_exit(game, "memory is not allocated in ft_cpath", 1);
}

void	ft_check_screen_size(t_game *game)
{
	int	width;
	int	height;

	mlx_get_screen_size(&width, &height);
	if (game->param.screen.width > width)
		game->param.screen.width = width;
	if (game->param.screen.height > height)
		game->param.screen.height = height;
}
