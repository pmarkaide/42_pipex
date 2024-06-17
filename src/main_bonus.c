/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:57:17 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/17 14:57:18 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		exit_code;

	data = {0};
	if (argc < 5)
	{
		ft_putstr_fd("Error: I need at least 5 arguments\n", 2);
		return (1);
	}
	init_struct(&data, argc, argv, envp);
	exit_code = pipex(&data);
	free_data(&data);
	return (exit_code);
}
