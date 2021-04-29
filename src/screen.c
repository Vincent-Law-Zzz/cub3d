#include "cub_header.h"

void	ft_bmp_put_file_header(t_game *game, int fd)
{
	unsigned char	file_header[14];
	int				size;

	ft_bzero(file_header, 14);
	size = 54 + 4 * game->param.screen.height * game->param.screen.width;
	ft_memcpy(file_header, "BM", 2);
	ft_memcpy(file_header + 2, &size, 4);
	file_header[10] = 54;
	if ((write(fd, file_header, 14)) == -1)
		ft_exit(game, "Fail write!", 1);
}

void	ft_bmp_put_info_header(t_game *game, int fd)
{
	unsigned char	info_header[40];

	ft_bzero(info_header, 40);
	info_header[0] = 40;
	ft_memcpy(info_header + 4, &game->param.screen.width, 4);
	ft_memcpy(info_header + 8, &game->param.screen.height, 4);
	info_header[12] = 1;
	info_header[14] = 32;
	if ((write(fd, info_header, 40)) == -1)
		ft_exit(game, "Fail write!", 1);
}

void	ft_bmp_put_image(t_game *game, int fd)
{
	while (game->param.screen.height--)
		if ((write(fd, game->param.screen.data + game->param.screen.width *\
				game->param.screen.height, game->param.screen.width * 4)) == -1)
			ft_exit(game, "Fail write!", 1);
}

void	ft_bmp_create(t_game *game)
{
	int	fd;

	fd = open("Screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_exit(game, "Open error", 1);
	ft_bmp_put_file_header(game, fd);
	ft_bmp_put_info_header(game, fd);
	ft_bmp_put_image(game, fd);
	close(fd);
	ft_exit(game, 0, 0);
}
