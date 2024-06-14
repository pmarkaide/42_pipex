/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:19:19 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/14 13:48:03 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		exit_code;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		return (1);
	}
	init_struct(&data, argv, envp);
	exit_code = pipex(&data, envp);
	free_data(&data);
	return (exit_code);
}
