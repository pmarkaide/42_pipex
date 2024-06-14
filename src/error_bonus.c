/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:00:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/14 12:02:06 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void free_string(char **str)
{
    if (str != NULL && *str != NULL)
    {
        free(*str);
        *str = NULL;
    }
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL || *array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void close_open_fds(t_data *data)
{
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	if(data->in_fd != -1)
		close(data->in_fd);
	if(data->out_fd != -1)
		close(data->out_fd);
}


void	free_data(t_data *data)
{
	int i;

	i = 0;
	if (data == NULL)
		return ;
	close_open_fds(data);
	while(i < data->num_cmds)
	{
		if (data->cmds[i] != NULL)
		{
			free_array(data->cmds[i]);
			data->cmds[i] = NULL;
		}
		i++;
	}
	free(data->cmds);
    data->cmds = NULL;
    free_array(data->paths);
    data->paths = NULL;
    free_string(&data->exec_path);
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

int	error_msg(char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	return (-1);
}