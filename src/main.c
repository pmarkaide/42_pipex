/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:19:19 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/16 16:29:43 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char const *argv[])
{
	if(argc != 5)
		exit_1("Incorrect number of arguments.\nUsage: ./pipex infile cmd1 cmd2 outfile");
	return 0;
}
	