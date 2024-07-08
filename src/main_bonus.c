/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:57:17 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/08 13:00:05 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		here_doc;
	int		exit_code;

	if (argc > 1)
		here_doc = ft_strncmp(argv[1], "here_doc", 8) == 0;
	if (argc == 1 || (here_doc && argc < 6) || argc < 5)
	{
		ft_putstr_fd("Usage:\n", 2);
		ft_putstr_fd("\t./pipex infile CMD1 CMD2 [CMDN] outfile\n", 2);
		ft_putstr_fd("\t./pipex here_doc DEL CMD1 CMD2 [CMDN] outfile\n", 2);
		return (1);
	}
	init_struct(&data, argc, argv, envp);
	exit_code = pipex(&data);
	free_data(&data);
	return (exit_code);
}
