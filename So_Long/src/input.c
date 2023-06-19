/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myayla <myayla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:20:28 by myayla            #+#    #+#             */
/*   Updated: 2023/06/15 16:20:30 by myayla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESC 53

static int	player_register_event(int movement, t_game *game);
static int	player_register_movement(int dir, t_game *game);
static void	ft_unsigned(unsigned int a);

static void	ft_unsigned(unsigned int a)
{
	if (a >= 10)
		ft_unsigned(a / 10);
	write(1, &"0123456789"[a % 10], 1);
}

static int	player_register_movement(int dir, t_game *game)
{
	if (dir == KEY_W)
		game->player_y--;
	else if (dir == KEY_A)
		game->player_x--;
	else if (dir == KEY_S)
		game->player_y++;
	else if (dir == KEY_D)
		game->player_x++;
	return (1);
}

static int	player_register_event(int movement, t_game *game)
{
	if (!movement)
		return (0);
	if (game->map[game->player_y][game->player_x] == 'C')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->coins--;
	}
	if (game->coins == 0 && game->map[game->player_y][game->player_x] == 'E')
		game_exit(game);
	game->moves++;
	ft_unsigned(game->moves);
	write(1, "\n", 1);
	return (0);
}

int	game_exit(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map_height)
		free(game->map[i]);
	free(game->map);
	mlx_destroy_image(game->mlx, game->cuphead_sprite);
	mlx_destroy_image(game->mlx, game->exit_sprite);
	mlx_destroy_image(game->mlx, game->coin_sprite);
	mlx_destroy_image(game->mlx, game->wall_sprite);
	mlx_destroy_image(game->mlx, game->floor_sprite);
	mlx_destroy_window(game->mlx, game->mlx_win);
	free(game);
	exit(0);
}

int	key_down(int keycode, t_game *game)
{
	int	movement;

	movement = 0;
	if (keycode == KEY_ESC)
		game_exit(game);
	else if (keycode == KEY_W
		&&game->map[game->player_y - 1][game->player_x] != '1')
		movement = player_register_movement(KEY_W, game);
	else if (keycode == KEY_S
		&& game->map[game->player_y + 1][game->player_x] != '1')
		movement = player_register_movement(KEY_S, game);
	else if (keycode == KEY_A
		&& game->map[game->player_y][game->player_x - 1] != '1')
		movement = player_register_movement(KEY_A, game);
	else if (keycode == KEY_D
		&& game->map[game->player_y][game->player_x + 1] != '1')
		movement = player_register_movement(KEY_D, game);
	player_register_event(movement, game);
	return (0);
}
