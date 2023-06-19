/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myayla <myayla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:19:56 by myayla            #+#    #+#             */
/*   Updated: 2023/06/15 16:19:59 by myayla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_map(char **map, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static char	*ft_strdup(char *a)
{
	int		i;
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(a));
	if (!ret)
		return (NULL);
	i = -1;
	while (a[++i])
		ret[i] = a[i];
	return (ret);
}

static int	check_path(t_game *temp, size_t y, size_t x)
{
	if (temp->map[y][x] == '1')
		return (0);
	if (temp->map[y][x] == 'C')
		temp->coins--;
	if (temp->map[y][x] == 'E')
	{
		temp->exit_is_possible = 1;
		return (0);
	}
	temp->map[y][x] = '1';
	if (check_path(temp, y + 1, x))
		return (1);
	if (check_path(temp, y - 1, x))
		return (1);
	if (check_path(temp, y, x + 1))
		return (1);
	if (check_path(temp, y, x - 1))
		return (1);
	return (0);
}

int	flood_fill(t_game *game)
{
	t_game	temp;
	int		i;

	temp.map_height = game->map_height;
	temp.map_width = game->map_width;
	temp.coins = game->coins;
	temp.player_x = game->player_x;
	temp.player_y = game->player_y;
	temp.exit_is_possible = 0;
	temp.map = (char **)malloc(temp.map_height * sizeof(char *));
	if (!temp.map)
		return (1);
	i = -1;
	while (++i < temp.map_height)
		temp.map[i] = ft_strdup(game->map[i]);
	check_path(&temp, temp.player_y, temp.player_x);
	if (!(temp.exit_is_possible == 1 && temp.coins == 0))
	{
		free_map(temp.map, temp.map_height);
		return (1);
	}
	free_map(temp.map, temp.map_height);
	return (0);
}
