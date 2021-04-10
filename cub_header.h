/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_header.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapollo <aapollo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:55:02 by aapollo           #+#    #+#             */
/*   Updated: 2021/04/04 18:11:57 by aapollo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_HEADER_H
# define CUB_HEADER_H
# include "./mlx/mlx.h"
# include "./libft42/libft.h"
# include <sys/stat.h>

typedef	struct		s_param
{
	char	*rwidth;
	char	*rheight;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*fcolor;
	char	*ccolor;
	int		ismap;
	int		error;
}					t_param;

typedef	struct		s_map
{
	char	*str;
	int		*width;
	int		len;
}					t_map;

#endif
