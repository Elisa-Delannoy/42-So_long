/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:30:05 by edelanno          #+#    #+#             */
/*   Updated: 2025/02/18 17:52:51 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int loop_hook(t_var *var)
{
	var->i_loop = (var->i_loop + 1) % 10000;
	if (var->map->tab[var->santa.y / 80][var->santa.x / 80] == 'T')
	{
		if (var->i_loop < 2500 || (var->i_loop >= 5000 && var->i_loop < 7500))
			var->i = 0;
		else if ((var->i_loop >= 2500 && var->i_loop < 5000) || var->i_loop >= 7500)
			var->i = 1;
	}
	else if (var->i_loop >= 2500 && var->i_loop < 5000)
		var->i = 1;
	else if (var->i_loop >= 5000 && var->i_loop < 7500)
		var->i = 2;
	else if (var->i_loop >= 7500)
		var->i = 3;
	else if (var->i_loop == 0)
		var->i = 0;
	santa_anim(var, var->santa.x, var->santa.y);

	return (0);
}


int	main(int argc, char **argv)
{
	t_var		var;

	if (argc != 2)
		return (1);
	var.mlx = mlx_init();
	var.win = NULL;
	init_var(&var);
	init_santa(&var);
	if (init_map(&var) == 1)
		return (1);
	if (check_rectangular(argv, &var) == 1)
	{
		free_all(&var);
		return (1);
	}
	var.santa.x = var.santa.x * 80;
	var.santa.y = var.santa.y * 80;
	var.win = mlx_new_window(var.mlx, 80 * (var.map->width + 1),
			80 * (var.map->height), "Santa!");
	mlx_expose_hook(var.win, print_map, &var);
	mlx_key_hook(var.win, key_hook, &var);
	mlx_hook(var.win, DestroyNotify, KeyReleaseMask, exit_game, &var);
	mlx_loop_hook(var.mlx, loop_hook, &var);
	mlx_loop(var.mlx);
	return (0);
}
