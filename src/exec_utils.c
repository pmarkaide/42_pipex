/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:40:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/18 12:52:26 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	cmd_is_directory(char *cmd)
{
	int	fd;

	fd = open(cmd, O_RDONLY | O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return(1);
	}
	return(0);
}

void	eval_executable(t_data *data)
{
	int		local;

	local = 0;
	data->executable = data->cmd[0];
	if (data->executable == NULL)
		free_data_and_exit(data, "malloc error", -1);
	if (ft_str_empty(data->executable))
		free_data_and_exit(data, data->executable, COMMAND_NOT_FOUND);
	if (ft_strncmp(data->executable, "/", 1) == 0)
		local = 1;
	if (ft_strncmp(data->executable, "./", 2) == 0)
		local = 1;
	if (ft_strncmp(data->executable, "../", 3) == 0)
		local = 1;
	if (local || data->paths == NULL)
	{
		if (!access(data->executable, F_OK))
		{
			if(cmd_is_directory(data->executable))
				free_data_and_exit(data, data->executable, IS_DIRECTORY);
			return (eval_executable_permissions(data));
		}
			free_data_and_exit(data, data->executable, EXEC_NOT_FOUND);
	}
	get_executable_path(data);
}

void	eval_executable_permissions(t_data *data)
{
	if (!access(data->executable, X_OK))
		return ;
	free_data_and_exit(data, data->executable, PERMISSION_DENIED);
}
