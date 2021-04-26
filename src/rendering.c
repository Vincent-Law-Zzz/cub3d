/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:00:22 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/25 15:06:55 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

t_color	ft_get_pixel(t_game *game, t_vector *vector, float xx_otn, float yy_otn)
{
	t_texture *texture;

	if (vector->dirtxtr == 0)
		texture = &game->param.no;
	else if (vector->dirtxtr == 1)
		texture = &game->param.ea;
	else if (vector->dirtxtr == 2)
		texture = &game->param.so;
	else
		texture = &game->param.we;
	return (texture->data[(int)(yy_otn * (float)texture->height) * texture->width + (int)(xx_otn * (float)texture->width)]);
}

void	ft_set_xx_otn(t_vector *vector, float *xx_otn)
{
	if (vector->cord.xx == floor(vector->cord.xx))
		*xx_otn = vector->cord.yy - (int)vector->cord.yy;
	else
		*xx_otn = vector->cord.xx - (int)vector->cord.xx;
}

void	ft_render_vertical(t_game *game, t_vector *vector, size_t xx)
{
	float	coef_angle_h;
	int		pixel_count;
	int		counter;
	int		yy;
	float	xx_otn;

	coef_angle_h = atan(0.5 / vector->distance) * 2 / (M_PI / 3);
	pixel_count = game->param.screen.height * coef_angle_h;
	yy = (game->param.screen.height - pixel_count) / 2;
	counter = pixel_count;
	ft_set_xx_otn(vector, &xx_otn);
	while (yy < game->param.screen.height && counter--)
	{
		game->param.screen.data[yy * game->param.screen.width + xx] = ft_get_pixel(game, vector, xx_otn, (float)(pixel_count - counter) / (float)pixel_count);
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
