/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myayla <myayla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:20:43 by myayla            #+#    #+#             */
/*   Updated: 2023/06/15 16:20:46 by myayla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_data(t_game *sl);
static void	render_map(t_game *game);

static void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->wall_sprite, x * PIXEL, y * PIXEL);
			else if (game->map[y][x] == '0' || game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->floor_sprite, x * PIXEL, y * PIXEL);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->coin_sprite, x * PIXEL, y * PIXEL);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->exit_sprite, x * PIXEL, y * PIXEL);
			x++;
		}
		y++;
	}
}

static void	draw_data(t_game *sl)
{
	char	*str;

	str = ft_itoa(sl->moves);
	mlx_string_put(sl->mlx, sl->mlx_win, 0, PIXEL / 2, 0x00FFFFFF, "MOVES: ");
	mlx_string_put(sl->mlx, sl->mlx_win,
		PIXEL + (PIXEL / 3), PIXEL / 2, 0x00FFFFFF, str);
	free(str);
}

int	render(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	render_map(game);
	draw_data(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->cuphead_sprite, game->player_x * PIXEL, game->player_y * PIXEL);
	return (0);
}
