/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 01:13:51 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/10 16:57:27 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_header.h"

void		del_structs(t_map *map, t_param *param)
{
	ft_bzero(param,sizeof(t_param));
	ft_bzero(map,sizeof(t_map));
}

/* v parsing settings v */

int		ft_checkerr(t_param *param, char **str)
{
	if (str[0] && str[1] && str[2] && (str[0][0] == 'R'))
		return (0);
	if (str[0] && str[1])
		return (0);
	// printf("%s\n", str[0]);
	param->error = 1;
	return (1);
}

int		def_param_type(t_param *param, char **str)
{
	if (ft_checkerr(param, str))
		return (1);
	param->rwidth = (str[0][0] == 'R') ? str[1] : param->rwidth;
	param->rheight = (str[0][0] == 'R') ? str[2] : param->rheight;
	param->no = (str[0][0] == 'N' && str[0][1] == 'O') ? str[1] : param->no;
	param->so = (str[0][0] == 'S' && str[0][1] == 'O') ? str[1] : param->so;
	param->we = (str[0][0] == 'W' && str[0][1] == 'E') ? str[1] : param->we;
	param->ea = (str[0][0] == 'E' && str[0][1] == 'A') ? str[1] : param->ea;
	param->s = (str[0][0] == 'S' && !str[0][1]) ? str[1] : param->s;
	param->fcolor = (str[0][0] == 'F') ? str[1] : param->fcolor;
	param->ccolor = (str[0][0] == 'C') ? str[1] : param->ccolor;
	free(str[0]);
	return (0);
}

int	ft_paramerr(t_param *param, char **str)
{
	param->error = (str[0][0] == 'R' && param->rwidth) ? 1 :param->error;
	param->error= (str[0][0] == 'R' && param->rheight) ? 1 : param->error;
	param->error = (str[0][0] == 'N' && str[0][1] == 'O' && param->no) ? 1 : param->error;
	param->error = (str[0][0] == 'S' && str[0][1] == 'O' && param->so) ? 1 : param->error;
	param->error = (str[0][0] == 'W' && str[0][1] == 'E' && param->we) ? 1 : param->error;
	param->error = (str[0][0] == 'E' && str[0][1] == 'A' && param->ea) ? 1 : param->error;
	param->error = (str[0][0] == 'S' && !str[0][1] && param->s) ? 1 : param->error;
	param->error = (str[0][0] == 'F' && param->fcolor) ? 1 : param->error;
	param->error = (str[0][0] == 'C' && param->ccolor) ? 1 : param->error;
	return (0);
}
int		ft_ismap(t_param *param)
{
	if (param->rwidth && param->rheight && param->no && param->so && param->we
	&& param->ea && param->s && param->fcolor && param->ccolor)
		return (1);
	return (0);
}

int		pars_param(t_param *param, int fd, char **line)
{
	while (!param->ismap && !param->error && get_next_line(fd, line))
	{
		if (*line[0] == '\n' || *line[0] == '\0')
		{
			free(*line);
			continue;
		}
		ft_paramerr(param, line);
		def_param_type(param, ft_split(*line, ' '));
		param->ismap = ft_ismap(param);
	}
	while (get_next_line(fd, line) && (*line[0] == '\n' || *line[0] == '\0'))
		continue;
	return (1);
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
	char	c;
	if (y > map->len || x > map->width[y] || x < 0 || y < 0)
		return ('\0');
	if (y != 1 && y != 0)
		y = ft_elemsum(map->width,y);
	if (y == 1)
		y = map->width[0];
	c = (map->str[x + y]);
	return (c);
}

int *ft_parswidthval(int *res, t_param *param, char **width,int len)
{
	int i;

	i = 0;
	while (*res == 0)
		res++;
	while (i < len)
	{
		if(!(res[i] = (int)malloc(sizeof(int))))
			param->error = 1;
		res[i] = ft_atoi(width[i]);
		i++;
	}
	return (res);
}

void ft_parswidth(t_map *map, t_param *param,char *width)
{
	char	**arr;
	int		*res;
	int		len;
	int     pading;

	pading = 0;
	len = 0;
	arr = ft_split(width, ' ');
	res = NULL;
	while (arr[len][0] == '0')
		len++;
	pading = len;
	if (arr[len][0] != '0' && arr[len][0])
		param->ismap = -1;
	while (arr[len] != NULL)
	{
		if (arr[len][0] == '0')
			param->error = 1;
		len++;
	}
	if (!(res = (int*)ft_calloc((len-pading),sizeof(int))))
		param->error = 1;
	res[len - pading] = '\0';
	map->len = len - pading;
	map->width = ft_parswidthval(res, param, arr, len - pading);
}

int		pars_map(t_map *map, t_param *param, int fd, char *line)
{
	char *width;
	char *str;
	int	end;

	width = NULL;
	str = NULL;
	end = 1;
	width = (width) ? ft_strjoin_gnl(width, ft_itoa(ft_strlen(line))) : ft_strdup("\0");
	width = ft_strjoin_gnl(width, " ");
	str = ft_strdup("\0");
	while (!param->error && end)
	{
		width = (width) ? ft_strjoin_gnl(width, ft_itoa(ft_strlen(line))) : ft_strdup("\0");
		width = ft_strjoin_gnl(width, " ");
		str = (str) ? ft_strjoin_gnl(str, line) : ft_strdup("\0");
		end = get_next_line(fd, &line);
	}
	width = (width != NULL) ? ft_strjoin_gnl(width, ft_itoa(ft_strlen(line))) : ft_strdup("\0");
	width = ft_strjoin_gnl(width, " ");
	str = (str) ? ft_strjoin_gnl(str, line) : ft_strdup("\0");
	map->str = str;
	ft_parswidth(map, param, width);
	return (1);
}

/* ^ parsing a map ^ */

void	ft_findeplayer(t_map *map, t_param *param)
{
	char	*tmp;
	int		counter;

	tmp = NULL;
	counter = 0;
	counter = (tmp = ft_strchr(map->str,'N')) ? counter + 1 : counter;
	counter = (tmp && ft_strchr((tmp + 1),'N')) ? counter + 1 : counter;
	counter = (tmp = ft_strchr(map->str,'E')) ? counter + 1 : counter;
	counter = (tmp && ft_strchr((tmp + 1),'E')) ? counter + 1 : counter; 
	counter = (tmp = ft_strchr(map->str,'W')) ? counter + 1 : counter;
	counter = (tmp && ft_strchr((tmp + 1),'W')) ? counter + 1 : counter;
	counter = (tmp = ft_strchr(map->str,'S')) ? counter + 1 : counter;
	counter = (tmp && ft_strchr((tmp + 1),'S')) ? counter + 1 : counter;
	if (counter >= 2 || counter == 0)
		param->error = 1;
}

void	ft_checkwalls(t_map *map, t_param *param)
{
	int		i;

	i = 0;
	while (map->str[i])
	{
		if (map->str[i] != '\0' && map->str[i] != 'N' & map->str[i] != 'W'
			&& map->str[i] != 'E' && map->str[i] != 'S' && map->str[i] != '1'
			&& map->str[i] != '0' && map->str[i] != '2' && map->str[i] != '\n'
			&& map->str[i] != ' ')
			param->error = 1;
		i++;
	}
}

void		ft_checkrules(t_map *map, t_param *param, int x, int y, char *end)
{
	while (*end)
	{
	if (ft_get_xy(map, x + 1, y) == *end)
		param->error =  1;
	if (ft_get_xy(map, x + 1, y + 1) == *end)
		param->error =  1;
	if (ft_get_xy(map, x + 1, y - 1)== *end)
		param->error =  1;
	if (ft_get_xy(map, x - 1, y) == *end)
		param->error =  1;
	if (ft_get_xy(map, x - 1, y -1) == *end)
		param->error =  1;
	if (ft_get_xy(map, x, y + 1) == *end)
		param->error =  1;
	if (ft_get_xy(map, x, y - 1) == *end)
		param->error =  1;
	if (ft_get_xy(map, x - 1, y + 1) == *end)
		param->error =  1;
	end++;
	}
}

void	ft_isalone(t_map *map, t_param *param, int x, int y)
{
	int  counter;

	counter = 0;
	counter = (ft_get_xy(map, x + 1, y) == ' ') ? counter + 1 : counter;
	counter = (ft_get_xy(map, x + 1, y + 1) == ' ') ? counter + 1 : counter;
	counter = (ft_get_xy(map, x + 1, y - 1)== ' ') ? counter + 1 : counter;
	counter = (ft_get_xy(map, x - 1, y) == ' ') ? counter + 1 : counter;
	counter = (ft_get_xy(map, x - 1, y -1) == ' ') ? counter + 1 : counter;
	counter = (ft_get_xy(map, x, y + 1) == ' ') ? counter + 1 : counter;
	counter = (ft_get_xy(map, x, y - 1) == ' ') ? counter + 1 : counter;
	counter = (ft_get_xy(map, x - 1, y + 1) == ' ') ? counter + 1 : counter;
	if (counter == 8)
		param->error = 1;
}

void	ft_checktop(t_map *map, t_param *param)
{
	int x;
	int y;
	char c;

	y = 0;
	while (y < map->len)
	{
		x = 0;
		while (x < map->width[y])
		{	
			c = ft_get_xy(map,x,y);
			if (c == '2' || c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E')
			{
				if (ft_get_xy(map,x - 1,y) != '\0' && (x + 1) != map->width[y + 1] && y > 0 && ft_get_xy(map,x,y + 1) != '\0')
					ft_checkrules(map,param,x,y,"\n ");
				else 
					param->error = 1;
			}
			if (c == '1')
				ft_isalone( map, param, x, y);
			x++;
		}
		y++;
	}
}

int		pars_processing(void)
{
	t_param	param;
	t_map	map;
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("./map.cub", O_RDONLY);
	line = NULL;
	del_structs(&map, &param);
	pars_param(&param, fd, &line);
	pars_map(&map, &param, fd, line);
	ft_findeplayer(&map, &param);
	ft_checkwalls(&map, &param);
	ft_checktop(&map, &param);
	printf("R w%s h%s\n", param.rwidth, param.rheight);
	printf("NO %s\nSO %s\nWE %s\nEA %s\nS %s\nF %s\nC %s\nERR %d\nMAP %d\n", param.no, param.so, param.we, param.ea, param.s, param.fcolor, param.ccolor, param.error, param.ismap);
	printf("%s\n\n", map.str);
	printf("nnn %d %d %d\n",map.width[0], map.width[1], map.width[2]);
	printf("coordinate 1 == |%c| width[y] %d \n",ft_get_xy(&map,20,10),map.width[2]);
	printf("coordinate 2 == |%c| width[y] %d\n",ft_get_xy(&map,9,9),map.width[0]);
	printf("coordinate N == |%c|\n",ft_get_xy(&map,11,8));
	printf("%d\n", map.len);
	return (0);
}

int		main(void)
{
	pars_processing();
	return (0);
}
