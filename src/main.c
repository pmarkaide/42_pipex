/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:19:19 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/20 15:54:00 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


int main(int argc, char **argv, char **envp)
{
	t_data	data;

	if(argc != 5)
		exit_1("5 arguments needed\nUsage: ./pipex infile cmd1 cmd2 outfile");
	init_struct(&data, argv, envp);
	check_params(&data);
	pipex(&data, argv, envp);
	free_data(&data);
	//system("leaks -q pipex");
	return 0;
}
	