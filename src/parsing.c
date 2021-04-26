/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:11:39 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/25 13:24:39 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

int		ft_exit(t_game __attribute__((unused)) *game, char *s, int mode)
{
	if (s && mode)
	{
		ft_putendl_fd("Error!",2);
		ft_putendl_fd(s,2);
	}
	if (!mode)
		ft_putendl_fd(s,2);
	exit(0);
	return (0);
}
 

/* v parsing settings v */


int		ft_strcount(char **res)
{
	int 	counter;

	counter = 0;
	while (res[counter])
		counter++;
	return (counter);
}

int 	ft_make_atr(t_game *game, char *res)
{
	int i;
	int ch;

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

static void		ft_free(char **res)
{
	size_t i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

void	ft_pars_color(t_game *game, char *str, t_color *color)
{
	char	**res;

	if (!(res = ft_split(str, ',')) || color->attributes || (ft_strcount(res) != 3))
	{
		ft_free(res);
		ft_exit(game, "Color must contain 3 args followed by \",\" as separator", 1);
	}
	color->R = ft_make_atr(game, res[0]);
	color->G = ft_make_atr(game, res[1]);
	color->B = ft_make_atr(game, res[2]);
	ft_free(res);
	color->attributes = 1;
}

void		ft_cpath(t_game *game, char *str, void **var)
{
	if(!(*var = ft_strdup(str)))
		ft_exit(game, "memory is not allocated in ft_cpath", 1);
}

void		ft_pars_screen(t_game *game, char *str, void __attribute__((unused)) *var)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
	{
		game->param.screen.width = game->param.screen.width * 10 + (str[i] - '0');
		i++;
	}
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]))
	{
		game->param.screen.height = game->param.screen.height * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && !game->param.screen.height)
		ft_exit(game, "Param error screen problems blyat", 1);
}

void		def_param_type(t_game *game, char *str)
{
	void *arr[9][3] = {{"NO ", ft_cpath, &game->param.pth_no}, {"SO ", ft_cpath, &game->param.pth_so},	\
	{"WE ", ft_cpath, &game->param.pth_we} , {"EA ", ft_cpath, &game->param.pth_ea}, {"S ", ft_cpath, &game->param.pth_s},	\
	{"F ", ft_pars_color, &game->param.floor}, {"C ", ft_pars_color, &game->param.ceil}, {"R ", ft_pars_screen, 0}, {0, 0, 0}};	\
	int counter = 0;
	if (str[0] == '\0')
		return;
	while (*arr[counter] != 0)
	{
		if (!ft_strncmp(*arr[counter], str, ft_strlen(*arr[counter])))
		{
			((void (*)(t_game *, char *, void *))arr[counter][1])(game, str + ft_strlen(*arr[counter]), arr[counter][2]);
			return ;
		}	
		counter++;
	}
	ft_exit(game, str, 1);
}

int		ft_ismap(t_game *game)
{
	if (game->param.screen.width && game->param.screen.height && game->param.pth_no && game->param.pth_so && game->param.pth_we
	&& game->param.pth_ea && game->param.pth_s && game->param.floor.attributes && game->param.ceil.attributes)
		return (1);
	return (0);
}

void		pars_param(t_game *game, int fd)
{
	char *line;

	while (!(game->param.ismap = ft_ismap(game)) && !game->param.error && get_next_line(fd, &line))
	{
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		// ft_paramerr(game, &line);
		def_param_type(game, line);
	}
	// while (get_next_line(fd, line) && *line == '\0')
	// 	continue;
	// return (1);
}

/* ^ parsing settings ^ */

/* v parsing a map v */

int	ft_elemsum(int *width, int y)
{
	int res;

	res = 0;
	while (y > 0)
	{
		y--;
		if (width[y])
			res += width[y];
		else
			return (0);
	}
	return (res);
}

char		ft_get_xy(t_map *map,int x,int y)
{
	if (x >= map->width || x < 0)
		return ('\0');
	if (y >= map->height || y < 0)
		return ('\0');
	return (map->data[x + y * map->width]);
}


void ft_parsmap(t_game *game, int fd)
{
	char *line;
	int width;
	int		end;

	end = 1;
	while (!game->param.error && end > 0 && (end = get_next_line(fd, &line)) != -1)
	{
		if(!ft_lstadd_back_content(&game->map.list, line))
			ft_exit(game, "Error", 1);
		width = (int)ft_strlen(line);
		if (width > game->map.width)
			game->map.width = width;
	}
	if (end == -1)
		ft_exit(game, "OSHIBKA GNL -1 BLYAT", 1);
	game->map.height = ft_lstsize(game->map.list);
}

void	ft_map_creation(t_game *game)
{
	t_list *tmp;
	int yy;
	int xx;
	char cell;
	static char dir[] = "NESW";
	char *ptr;

	yy = 0;
	tmp = game->map.list;
	if (!(game->map.data = ft_calloc(game->map.width,game->map.height)))
		ft_exit(game, "Error", 1);
	while (tmp)
	{
		xx = 0;
		while((cell = ((char *)tmp->content)[xx]))
		{
			if ((ptr = ft_strchr(dir, cell)))
			{
				if (game->player.xx)
					ft_exit(game, "Error", 1);
				game->player.direction = ((float)(ptr - dir)) / 4;
				game->map.data[xx + yy * game->map.width] = '0';
				game->player.xx = (float)xx + 0.5;
				game->player.yy = (float)yy + 0.5;
			}
			else if (cell != ' ')
				game->map.data[xx + yy * game->map.width] = cell;
			xx++;
		}
		yy++;
		tmp = tmp->next;
	}	
}
/* ^ parsing a map ^ */

void	ft_checkwalls(t_game *game)
{
	int		i;
	int		len;

	i = 0;
	len = game->map.height * game->map.width;
	while (i < len)
	{
		if (!ft_strchr("NESW102", game->map.data[i]))
			ft_exit(game, "Error", 1);
		i++;
	}
}

void		ft_checkrules(t_game *game, int x, int y)
{
	static int arr[][2] = {{-1,-1}, {0, -1}, {1, -1},	\
		{-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int counter;

	counter = 0;
	while (counter < 8)
	{
		if (!ft_get_xy(&game->map, x + arr[counter][0], y + arr[counter][1]))
			game->param.error =  37;
		counter++;
	}
}


void	ft_checktop(t_game *game)
{
	int x;
	int y;
	char c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = ft_get_xy(&game->map, x, y);
			if (c == '2' || c == '0')
				ft_checkrules(game, x, y);
			x++;
		}
		y++;
	}
}

int		pars_processing(t_game *game)
{

	int			fd;
	int			i;

	i = 0;
	fd = open("./map.cub", O_RDONLY);
	pars_param(game, fd);
	if(game->param.ismap != 1)
		ft_exit(game, "OSHIBKA", 1);
	ft_parsmap(game, fd);
	ft_map_creation(game);
	ft_checkwalls(game);
	ft_checktop(game);
	// prepare_direction(game);
	return (0);
}

void	ft_get_textur(t_game *game, char *path, t_texture *texture)
{
	int n;

    if(!(texture->mlx_obj = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height)))
		ft_exit(game, "texture error", 1);
	if(!(texture->data = (t_color*)mlx_get_data_addr(texture->mlx_obj, &n, &n, &n)))
		ft_exit(game, "texture data error", 1);
}

void ft_txtr_procesing(t_game *game)
{
	ft_get_textur(game, game->param.pth_no, &game->param.no);
	ft_get_textur(game, game->param.pth_so, &game->param.so);
	ft_get_textur(game, game->param.pth_ea, &game->param.ea);
	ft_get_textur(game, game->param.pth_we, &game->param.we);
	ft_get_textur(game, game->param.pth_s, &game->param.s);
}

void	ft_screen_image(t_game *game)
{
	int n;

	if(!(game->param.screen.mlx_obj = mlx_new_image(game->mlx,game->param.screen.width,game->param.screen.height)))
		ft_exit(game, "texture error      screenshot", 1);
	if(!(game->param.screen.data = (t_color*)mlx_get_data_addr(game->param.screen.mlx_obj, &n, &n, &n)))
		ft_exit(game, "texture data error       screenshot", 1);
}

void 	ft_make_color(t_color *color,int r, int g, int b)
{
	color->attributes = 1;
	color->R = r;
	color->B = b;
	color->G = g;
}

void	print_block_npx(t_game *game,t_color color, int w, int h, int n)
{
	int	x;
	int	y;
	
	y = 0;
	if (h >= 0 && w >= 0 && h+y <= game->param.screen.width * game->param.screen.height)
		while (y < n)
		{
			x = 0;
			while (x < n)
			{
				if ( h+y > 0)
					game->param.screen.data[(h+y)*game->param.screen.width + (w+x)] = color;
				x++;
			}
			y++;
		}
}

void	ft_minimap(t_game *game)
{
	int x;
	int y;
	char c;
	t_color	color1;
	t_color	color2;

	ft_make_color(&color1,225,17,150);
	ft_make_color(&color2,255,255,255);
	y = 0;
	while (y < (game->map.height))
	{
		x = 0;
		while (x < game->map.width)
		{
			c = ft_get_xy(&game->map, x, y);
			if (c == '1')
				print_block_npx(game, color1, x*10, y*10, 10);
			x++;
		}
		y++;
	}
	print_block_npx(game, color2, (int)(game->player.xx*10-2.5), (int)(game->player.yy*10-2.5), 5);
}

