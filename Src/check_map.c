/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:29:59 by yson              #+#    #+#             */
/*   Updated: 2022/06/15 16:03:04 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cub3d.h"

//바라보는 방향에 따라서 캐릭터가 처음에 시작할 때 방향 설정하기.
// void	handle_character(t_game *game, char c)
// {
// 	if (c == 'N')
// 	else if (c == 'S')
// 	else if (c == 'E')
// 	else if (c == 'W')
// }

int	count_source(t_game *game, char **map)
{
	int count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map[i] && i < game->map.map_height)
	{
		j = 0;
		while (map[i][j] && j < game->map.map_width)
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				(void)game;
				// handle_character(game, map[i][j]);
				count++;
			}
			j++;
		}
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	wall_surrounded(t_game *game, int row, int col)
{
	char **map;

	map = game->map.map;
	if (row <= 0 || row >= game->map.map_height - 1 || col <= 0 ||
		col >= game->map.map_width - 1)
		return (0);
	else if (map[row - 1][col] == ' ' || map[row - 1][col] == '\0')
		return (0);
	else if (map[row + 1][col] == ' ' || map[row - 1][col] == '\0')
		return (0);
	else if (map[row][col - 1] == ' ' || map[row - 1][col] == '\0')
		return (0);
	else if (map[row][col + 1] == ' ' || map[row - 1][col] == '\0')
		return (0);
	return (1);
}

int	wall_check(t_game *game, int i, int j, char **map)
{
	while (map[i] && i < game->map.map_height)
	{
		j = 0;
		while (map[i][j] && j < game->map.map_width)
		{
			if (ft_strchr("1 ", map[i][j]))
			{
				j++;
				continue;
			}
			else if (ft_strchr("NSFW0", map[i][j]))
			{
				if (!wall_surrounded(game, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	check_map(t_game *game)
{
	if (!count_source(game, game->map.map))
		err_exit("Wrong amount of character");
	if (!wall_check(game, 0, 0, game->map.map))
		err_exit("Wrong map");
}
