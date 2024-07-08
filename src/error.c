/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:25:34 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/08 12:51:32 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	file_error_exit(t_data *data, char *file, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (exit_code == FILE_NOT_FOUND)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (exit_code == FILE_PERMISSION_DENIED)
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit_code = 1;
	}
	else if (exit_code == IS_DIRECTORY)
	{
		ft_putstr_fd("Is a directory\n", 2);
		exit_code = 126;
	}
	else
		ft_putstr_fd(strerror(errno), 2);
	free_data(data);
	exit(exit_code);
}

void	command_error_exit(t_data *data, char *file, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (exit_code == COMMAND_NOT_FOUND)
		ft_putstr_fd("command not found\n", 2);
	else if (exit_code == PERMISSION_DENIED)
		ft_putstr_fd("Permission denied\n", 2);
	else if (exit_code == IS_DIRECTORY)
	{
		ft_putstr_fd("Is a directory\n", 2);
		exit_code = 126;
	}
	else if (exit_code == EXEC_NOT_FOUND)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		exit_code = 127;
	}
	else
		ft_putstr_fd(strerror(errno), 2);
	free_data(data);
	exit(exit_code);
}

int	error_msg(char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	return (-1);
}
