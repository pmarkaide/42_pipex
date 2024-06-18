/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:00:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/18 14:43:18 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

	if (*array == NULL || **array == NULL)
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
	int	i;

	i = 0;
	if (data == NULL)
		return ;
	close_open_fds(data);
	while (i < data->num_cmds)
	{
		if (data->cmds[i] != NULL)
		{
			free_array(&data->cmds[i]);
			data->cmds[i] = NULL;
		}
		i++;
	}
	free(data->cmds);
	data->cmds = NULL;
	free(data->pid);
	data->pid = NULL;
	free_array(&data->paths);
	free_string(&data->shell);
	free_string(&data->executable);
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
	free_data(data);
	exit(exit_code);
}

int	error_msg(char *msg, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	return (exit_code);
}
