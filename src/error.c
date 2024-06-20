/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:25:34 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/20 17:00:17 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_string(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_array(char ***array)
{
	size_t	i;

	if (*array == NULL)
		return ;
	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	close_pipes(data);
	if (data->cmd1[0] == data->executable)
		data->executable = NULL;
	if (data->cmd2[0] == data->executable)
		data->executable = NULL;
	free_array(&data->cmd1);
	free_array(&data->cmd2);
	free_array(&data->paths);
	free_string(&data->executable);
	free_string(&data->shell);
}

void	free_data_and_exit(t_data *data, char *file, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (exit_code == COMMAND_NOT_FOUND)
		ft_putstr_fd("command not found\n", 2);
	else if (exit_code == NO_FILE)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (exit_code == FILE_PERMISSION)
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit_code = 1;
	}
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
