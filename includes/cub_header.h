/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_header.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:55:02 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/30 02:02:33 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_HEADER_H
# define CUB_HEADER_H

# include "mlx.h"
# include "libft.h"
# include <sys/stat.h>
# include <math.h>

# define PLAYER_V 0.05
# define ROT_V 0.01

# define ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct		s_color
{
	unsigned char	B;
	unsigned char	G;
	unsigned char	R;
	unsigned char	attributes;
}					t_color;

typedef struct		s_texture
{
	t_color			*data;
	int				width;
	int				height;
	void			*mlx_obj;
}					t_texture;

typedef	struct		s_param
{
	t_texture			screen;
	char			*pth_no;
	char			*pth_so;
	char			*pth_we;
	char			*pth_ea;
	char			*pth_s;
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
	t_texture		s;
	t_color			floor;
	t_color			ceil;
	int				ismap;
	int				error;
}					t_param;

typedef	struct		s_map
{
	t_list			*list;
	char			*data;
	int				width;
	int				height;
}					t_map;

typedef	struct		s_cord
{
	float 			xx;
	float 			yy;
	float 			direction;
}					t_cord;

typedef	struct		s_icord
{
	int 			xx;
	int 			yy;
}					t_icord;

typedef	struct		s_line
{
	t_cord 			dot[2];
}					t_line;

typedef	struct		s_event 
{
	char			up;
	char			down;
	char			left;
	char			right;
	char			q;
	char			e;
	char			esc;
}					t_event;

typedef	struct		s_vertical 
{
	float			distance;
	t_cord			cord;
	char			dirtxtr;
}					t_vector;

typedef	struct		s_sprite
{
	t_list			move;
	t_vector		vector;
}					t_sprite;

typedef struct		s_game
{
	t_param			param;
	t_map			map;
	t_cord			player;
	char			*path_map;
	void			*mlx;
	void			*window;
	t_event			event;
	t_list			*sprite;
	t_vector		*vectors;
	float			stop;
}					t_game;

void 	ft_make_color(t_color *color,int r, int g, int b);

float	ft_to_diap(float value);

int		handle_pressed_key(int keycode, t_game *game);

int		handle_unpressed_key(int keycode, t_game *game);

void	ft_player_move(t_game *game);

void	ft_event_processing(t_game *game);

void	ft_background_rendering(t_game *game);

void	ft_txtr_procesing(t_game *game);

int		pars_processing(t_game *game);

void	ft_screen_image(t_game *game);

char	ft_get_xy(t_map *map,int x,int y);

void	ft_raycasting(t_game *game, t_vector *vector);

void	ft_rendering(t_game *game, t_vector *vector);

int		ft_exit(t_game __attribute__((unused)) *game, char *s, int mode);

float	ft_get_distance(t_cord *dest, t_cord *source);

void	ft_sprite_preprocessing(t_game *game);

void	ft_sprite_rendering(t_game *game, t_vector *vector);

void 	ft_sprite_init(t_game *game, int xx, int yy);

int		ft_cmp_sprite(t_sprite *sprite1, t_sprite *sprite2);

t_color	ft_get_pixel(t_game *game, char dirtxtr, float xx_otn, float yy_otn);

void	ft_bmp_create(t_game *game);

void	ft_minimap(t_game *game);

#endif
