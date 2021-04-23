/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_header.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:55:02 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/23 23:38:37 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_HEADER_H
# define CUB_HEADER_H
# include "./mlx/mlx.h"
# include "./libft42/libft.h"
# include <sys/stat.h>
# include <math.h>

# define PLAYER_V 0.05
# define ROT_V 0.05

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

typedef	struct		s_player
{
	float 			xx;
	float 			yy;
	float 			direction;
}					t_player;

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

typedef	struct		s_reyprops
{
	float	depthX;
	float	depthY;
	int		vert;
	char	hit;
	int		stepX;
	int		stepY;
	int 	cosec_a;
	int		sec_a;
	int		xtomap;
	int		ytomap;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	dirX;
	double	dirY;
	float	planeX;
	float	planeY;
	float	dist;
}					t_props;

typedef	struct		s_vertical 
{
	float			distance;
	float			cord;
	char			dirtxtr;
}					t_vert;

typedef struct		s_game
{
	t_param			param;
	t_map			map;
	t_player		player;
	void			*mlx;
	void			*window;
	t_event			event;
}					t_game;
#endif
