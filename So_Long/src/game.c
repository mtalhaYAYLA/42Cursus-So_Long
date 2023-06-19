/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myayla <myayla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:20:35 by myayla            #+#    #+#             */
/*   Updated: 2023/06/15 16:20:38 by myayla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_sprite(t_game *game)
{
	int	tmp_x;
	int	tmp_y;

	game->cuphead_sprite = mlx_xpm_file_to_image(game->mlx,
			"./res/cuphead.xpm", &tmp_x, &tmp_y);
	game->wall_sprite = mlx_xpm_file_to_image(game->mlx,
			"./res/wall.xpm", &tmp_x, &tmp_y);
	game->floor_sprite = mlx_xpm_file_to_image(game->mlx,
			"./res/floor.xpm", &tmp_x, &tmp_y);
	game->coin_sprite = mlx_xpm_file_to_image(game->mlx,
			"./res/coin.xpm", &tmp_x, &tmp_y);
	game->exit_sprite = mlx_xpm_file_to_image(game->mlx,
			"./res/exit.xpm", &tmp_x, &tmp_y);
}

static int	filename_check(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i] == 'r' && str[i - 1] == 'e'
		&& str[i - 2] == 'b' && str[i - 3] == '.')
	{
		return (1);
	}
	return (0);
}

static t_game	*game_init(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	game->coins = 0;
	game->exit = 0;
	game->ply = 0;
	game->moves = 0;
	return (game);
}

void	start_game(char *map_name)
{
	t_game	*game;
	int		fd;

	if (!filename_check(map_name))
		return ;
	game = game_init();
	fd = open(map_name, O_RDONLY);
	game->map = map_constractor(game, fd);
	close(fd);
	if (map_validation(game))
	{
		write(1, "ERROR\n", 6);
		free(game);
		exit(1);
	}
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->map_width * PIXEL,
			game->map_height * PIXEL, "so_long");
	load_sprite(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_down, game);
	mlx_hook(game->mlx_win, 17, 0L << 0, game_exit, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
