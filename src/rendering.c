/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:00:22 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/28 08:29:48 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

t_color	ft_get_pixel(t_game *game, char dirtxtr, float xx_otn, float yy_otn)
{
	t_texture *texture;

	if (dirtxtr == 0)
		texture = &game->param.no;
	else if (dirtxtr == 1)
		texture = &game->param.ea;
	else if (dirtxtr == 2)
		texture = &game->param.so;
	else if (dirtxtr == 3)
		texture = &game->param.we;
	else
		texture = &game->param.s;
	return (texture->data[(int)(yy_otn * (float)texture->height) * texture->width + (int)(xx_otn * (float)texture->width)]);
}

void	ft_set_xx_otn(t_vector *vector, float *xx_otn)
{
	if (vector->cord.xx == floor(vector->cord.xx))
		*xx_otn = vector->cord.yy - (int)vector->cord.yy;
	else
		*xx_otn = vector->cord.xx - (int)vector->cord.xx;
}

float	ft_del_fish_eye(float coef_screen,float player_dir)
{
	return (cos(player_dir - coef_screen));
}

void	ft_render_vertical(t_game *game, t_vector *vector, size_t xx)
{
	float	coef_angle_h;
	int		pixel_count;
	int		counter;
	int		yy;
	float	xx_otn;
	float	yy_otn;

	// printf( "%f\n", game->player.direction - vector->cord.direction);
	// vector->distance = vector->distance * cos(vector->cord.direction - M_PI / 36);
	// coef_angle_h = (game->param.no.width / vector->distance) * (game->param.screen.width / 2 / tan(M_PI / 3 / 2));
	coef_angle_h = atan(1.0 / vector->distance) / (M_PI / 3) ;
	pixel_count = (game->param.screen.height * coef_angle_h);
	// pixel_count = game->param.screen.height / vector->cord.xx * cos(vector->cord.direction - game->player.direction);
	// pixel_count = (game->param.no.width / vector->distance) * (game->param.screen.width / 2 / tan(M_PI / 2/ 2));
	yy = (game->param.screen.height - pixel_count) / 2;
	counter = pixel_count;
	ft_set_xx_otn(vector, &xx_otn);
	while (yy < game->param.screen.height && counter--)
	{
		yy_otn = (float)(pixel_count - counter) / (float)pixel_count;
		if (xx_otn >= 0 && xx_otn < 1 && yy_otn >= 0 && yy_otn < 1)
			game->param.screen.data[yy * game->param.screen.width + xx] = ft_get_pixel(game, vector->dirtxtr, xx_otn, yy_otn);
		yy++;
	}
}

void	ft_rendering(t_game *game, t_vector *vector)
{
	size_t xx;

	xx = 0;
	while (xx < (size_t)game->param.screen.width)
	{
		ft_render_vertical(game, vector + xx, xx);
		xx++;
	}
}
