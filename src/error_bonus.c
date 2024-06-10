/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:00:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/10 15:55:21 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void close_pipes(t_data *data) {
    if (data == NULL || data->pipe_fd == NULL) {
        return; 
    }

    int i = 0;
    while (i < data->num_cmd - 1) {
        if (data->pipe_fd[i] != NULL) {
            close(data->pipe_fd[i][0]); 
            close(data->pipe_fd[i][1]); 
            free(data->pipe_fd[i]);      
            data->pipe_fd[i] = NULL;     
        }
        i++;
    }


    free(data->pipe_fd);
    data->pipe_fd = NULL;
}


void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	close_pipes(data);
	free_array(data->cmd1);
	free_array(data->cmd2);
	free_array(data->paths);
	if (data->exec_path)
		free(data->exec_path);
	if (data->shell)
		free(data->shell);
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