/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myayla <myayla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:20:04 by myayla            #+#    #+#             */
/*   Updated: 2023/06/15 16:20:07 by myayla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_ret(t_game *sl)
{
	char	**map;
	int		i;
	int		len;

	map = sl->map;
	i = 1;
	len = ft_strlen(map[0]);
	while (i < sl->map_height)
	{
		if (len != ft_strlen(map[i]))
			return (1);
		i++;
	}
	sl->map_width = len;
	return (0);
}

int	is_wall(char **map, int x, int y)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	i = 0;
	while (j < x)
	{
		if (map[0][j] != '1' || map[y - 1][j] != '1')
			return (1);
		j++;
	}
	i = 1;
	len = ft_strlen(map[i]);
	while (i < y - 1)
	{
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	is_pec(t_game *sl)
{
	int	i;
	int	j;

	i = 0;
	while (i < sl->map_height)
	{
		j = 0;
		while (j < sl->map_width)
		{
			if (sl->map[i][j] == 'P')
				sl->ply++;
			else if (sl->map[i][j] == 'E')
				sl->exit++;
			else if (sl->map[i][j] == 'C')
				sl->coins++;
			j++;
		}
		i++;
	}
	if (sl->ply != 1 || sl->exit != 1 || sl->coins == 0)
		return (1);
	return (0);
}

int	is_chr(t_game *sl)
{
	int	i;
	int	j;

	i = 0;
	while (i < sl->map_height)
	{
		j = 0;
		while (j < sl->map_width)
		{
			if (sl->map[i][j] != 'P' && sl->map[i][j] != 'E'
				&& sl->map[i][j] != 'C'
				&& sl->map[i][j] != '0' && sl->map[i][j] != '1')
				return (1);
			if (sl->map[i][j] == 'P')
			{
				sl->player_y = i;
				sl->player_x = j;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_validation(t_game *sl)
{
	if (is_ret(sl))
		return (1);
	if (is_pec(sl))
		return (1);
	if (is_chr(sl))
		return (1);
	if (is_wall(sl->map, sl->map_width, sl->map_height))
		return (1);
	if (flood_fill(sl))
		return (1);
	return (0);
}
