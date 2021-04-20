/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 01:13:51 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/20 08:20:09 by aapollo          ###   ########.fr       */
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

static char		**ft_free(char **res)
{
	size_t i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
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

// int	ft_paramerr(t_game * game, char **str)
// {
// 	game->param.error = (str[0][0] == 'R' && game->param.r_width) ? 24 :game->param.error;
// 	game->param.error= (str[0][0] == 'R' && game->param.r_height) ? 25 : game->param.error;
// 	game->param.error = (str[0][0] == 'N' && str[0][1] == 'O' && game->param.pth_no) ? 26 : game->param.error;
// 	game->param.error = (str[0][0] == 'S' && str[0][1] == 'O' && game->param.pth_so) ? 27 : game->param.error;
// 	game->param.error = (str[0][0] == 'W' && str[0][1] == 'E' && game->param.pth_we) ? 28 : game->param.error;
// 	game->param.error = (str[0][0] == 'E' && str[0][1] == 'A' && game->param.pth_ea) ? 29 : game->param.error;
// 	game->param.error = (str[0][0] == 'S' && !str[0][1] && game->param.pth_s) ? 30 : game->param.error;
// 	game->param.error = (str[0][0] == 'F' && game->param.fcolor) ? 31 : game->param.error;
// 	game->param.error = (str[0][0] == 'C' && game->param.ccolor) ? 32 : game->param.error;
// 	return (0);
// }
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

// int *ft_parswidthval(int *res, t_param *param, char **width,int len)
// {
// 	int i;

// 	i = 0;
// 	while (*res == 0)
// 		res++;
// 	while (i < len)
// 	{
// 		if(!(res[i] = (int)malloc(sizeof(int))))
// 			ft_exit(game, "Error");
// 		res[i] = ft_atoi(width[i]);
// 		i++;
// 	}
// 	return (res);
// }

// void ft_parswidth(t_map *map, t_param *param,char *width)
// {
// 	char	**arr;
// 	int		*res;
// 	int		len;
// 	int     pading;

// 	pading = 0;
// 	len = 0;
// 	arr = ft_split(width, ' ');
// 	res = NULL;
// 	while (arr[len][0] == '0')
// 		len++;
// 	pading = len;
// 	if (arr[len][0] != '0' && arr[len][0])
// 		game->param.ismap = -1;
// 	while (arr[len] != NULL)
// 	{
// 		if (arr[len][0] == '0')
// 			ft_exit(game, "Error");
// 		len++;
// 	}
// 	if (!(res = (int *)ft_calloc((len-pading), sizeof(int))))
// 		ft_exit(game, "Error");
// 	res[len - pading] = '\0';
// 	map->len = len - pading;
// 	map->width = ft_parswidthval(res, param, arr, len - pading);
// }


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
	static char dir[] = "NWSE";
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
		if (!ft_strchr("NWES102", game->map.data[i]))
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

void prepare_direction(t_game *game)
{
	if (game->player.direction == 0)
		game->player.direction = M_PI_2;
	if (game->player.direction == 0.25)
		game->player.direction = 0;
	if (game->player.direction == 0.5)
		game->player.direction = - M_PI_2;
	if (game->player.direction == 0.75)
		game->player.direction = M_PI;
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
	prepare_direction(game);
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

void	ft_screenshot(t_game *game)
{
	int n;

	if(!(game->param.screen.mlx_obj = mlx_new_image(game->mlx,game->param.screen.width,game->param.screen.height)))
		ft_exit(game, "texture error      screenshot", 1);
	if(!(game->param.screen.data = (t_color*)mlx_get_data_addr(game->param.screen.mlx_obj, &n, &n, &n)))
		ft_exit(game, "texture data error       screenshot", 1);
}

void	ft_background_rendering(t_game *game)
{
	int w;
	int h;

	w = 0;
	h = 0;
	while(h < game->param.screen.height)
	{
		w = 0;
		while(w < game->param.screen.width)
		{
			if(h < game->param.screen.height / 2)
				game->param.screen.data[h*game->param.screen.width + w] = game->param.ceil;
			else
				game->param.screen.data[h*game->param.screen.width + w] = game->param.floor;
			w++;
		}
		h++;
	}
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

void	ft_vertical(t_game *game, t_vert *vector, float cos_a,float sin_a)
{
	float	depth;
	float	newY= 0;
	float	newX;
	int 	x;
	char ptr = '0';
	t_color	color;
	x = 1;
	ft_make_color(&color,255,255,255);

	while (ptr != '1'&&ptr != '\0' && x < 10)
	{
		if (cos_a >= 0)
		{
			depth = (game->player.xx - (x + floor(game->player.xx))) / cos_a;
			vector->dirtxtr = 'W';
		}
		else
		{
			depth = ((x + floor(game->player.xx)) - game->player.xx) / cos_a;
			vector->dirtxtr = 'E';
		}
		newY = fabs(game->player.yy + depth * sin_a);
		newX = fabs(game->player.xx + depth * cos_a);
		ptr = ft_get_xy(&game->map, (int)newX, (int)(newY));
		x++;
		if (ptr != '\0')
			print_block_npx(game, color, (int)((newX)*10), (int)((newY)*10), 1);
	}
	vector->distance = fabs(depth);
	vector->cord = newX;
	printf(" vert txtr %c dist %f cor %f \n", vector->dirtxtr, vector->distance, vector->cord);
	// printf("hor %f", cos_a);
	// return (newY);
}

void	ft_horizontal(t_game *game, t_vert *vector, float cos_a, float sin_a)
{
	float	depth;
	float	newY;
	float	newX;
	int 	y;
	char ptr = '0';
	t_color	color;
	y = 1;
	ft_make_color(&color,255,255,255);

	while (ptr != '1' && ptr != '\0' && y < 10)
	{
		if (sin_a >= 0)
		{
			depth = (game->player.yy - (y + floor(game->player.yy))) / sin_a;
			vector->dirtxtr = 'S';
		}
		else
		{
			depth = (y + floor(game->player.yy) - game->player.yy) / sin_a;
			vector->dirtxtr = 'N';
		}
		newY = fabs(game->player.yy + depth*sin_a);
		newX = fabs(game->player.xx + depth*cos_a);
		if ((ptr = ft_get_xy(&game->map, (int)(newX), (int)newY)) == '1')
			break;
		y++;
		if (ptr != '\0')
			print_block_npx(game, color, (int)((newX)*10), (int)((newY)*10), 1);
	}
	vector->distance = fabs(depth);
	vector->cord = newX;
	printf(" hors txtr %c dist %f cor %f \n", vector->dirtxtr, vector->distance, vector->cord);
	// printf("hor %f", sin_a);
	// return (depth);
}
void	ft_raycasting(t_game *game, t_vert *vector)
{
	float cos_a;
	float sin_a;
	// float newX;
	// float newY;
	t_color	color;
	t_vert vh;
	t_vert vw;
	ft_make_color(&color,255,255,255);
	cos_a = cos(game->player.direction);
	sin_a = sin(game->player.direction);
	ft_vertical(game,&vw, cos_a, sin_a);
	ft_horizontal(game,&vh, cos_a,sin_a);
	if (vh.distance < vw.distance)
	{
		vector->distance = vh.distance;
		vector->cord = vh.cord;
		vector->dirtxtr = vh.dirtxtr;
	}
	else
	{
		vector->distance =vw.distance;
		vector->cord = vw.cord;
		vector->dirtxtr = vw.dirtxtr;
	}
	// print_block_npx(game, color, (int)(newX*10-2), (int)(i*10-2), 4);
	// print_block_npx(game, color, (int)(i*10-2), (int)(newY*10-2), 4);
}
int	handle_pressed_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game," game over ", 0);
	if (keycode == KEY_W)
		game->event.up = 1;
	if (keycode == KEY_S)
		game->event.down = 1;
	if (keycode == KEY_A)
		game->event.left = 1;
	if (keycode == KEY_D)
		game->event.right = 1;
	if (keycode == KEY_LEFT || keycode == KEY_Q)
		game->event.q = 1;
	if (keycode == KEY_RIGHT || keycode == KEY_E)
		game->event.e = 1;
	return (0);
}

int	handle_unpressed_key(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->event.up = 0;
	if (keycode == KEY_S)
		game->event.down = 0;
	if (keycode == KEY_A)
		game->event.left = 0;
	if (keycode == KEY_D)
		game->event.right = 0;
	if (keycode == KEY_LEFT || keycode == KEY_Q)
		game->event.q = 0;
	if (keycode == KEY_RIGHT || keycode == KEY_E)
		game->event.e = 0;
	return (0);
}

void ft_player_move(t_game *game)
{
	float dir;

	dir = game->player.direction;
	if (game->event.up)
	{
		game->player.xx += -cos(dir) * PLAYER_V;
		game->player.yy += -sin(dir) * PLAYER_V;
	}
	if (game->event.down)
	{
		game->player.xx += cos(dir) * PLAYER_V;
		game->player.yy += sin(dir) * PLAYER_V;
	}
	if (game->event.left)
	{
		game->player.xx += cos(dir + M_PI_2) * PLAYER_V;
		game->player.yy += sin(dir + M_PI_2) * PLAYER_V;
	}
	if (game->event.right)
	{
		game->player.xx += cos(dir + 1.5*M_PI) * PLAYER_V;
		game->player.yy += sin(dir + 1.5*M_PI) * PLAYER_V;
	}
}

void	ft_event_processing(t_game *game)
{
	ft_player_move(game); //todo: условие ограничивающее хождение сквозь стены
	if (game->event.q)
		game->player.direction -= 1 * ROT_V;
	if (game->event.e)
		game->player.direction += 1 * ROT_V;
}

int		ft_loop_tick(t_game *game)
{
	// t_vert vector[game->param.screen.width];
	t_vert vector;

	ft_event_processing(game); //to do
	ft_background_rendering(game);
	ft_minimap(game);
	ft_raycasting(game, &vector); // to do
	//ft_rendering(game,vector); //to do
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
	ft_screenshot(&game);
	game.window = mlx_new_window(game.mlx, game.param.screen.width, game.param.screen.height, "Sanya Cub");
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.window, 2, 0, handle_pressed_key, &game);
	mlx_loop_hook(game.mlx, ft_loop_tick, &game);
	mlx_hook(game.window, 3, 0, handle_unpressed_key, &game);
	mlx_loop(game.mlx);
	return (0);
}
