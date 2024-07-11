/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:40:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/11 11:07:56 by pmarkaid         ###   ########.fr       */
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
		return (1);
	}
	return (0);
}

void	eval_executable(t_data *data)
{
	int	local;

	local = 0;
	data->executable = ft_strdup(data->cmd[0]);
	if (data->executable == NULL)
		command_error_exit(data, "malloc error", -1);
	if (ft_str_empty(data->executable))
		command_error_exit(data, data->executable, COMMAND_NOT_FOUND);
	if (ft_strchr("./", data->executable[0]) != NULL)
		local = 1;
	if (local || data->paths == NULL)
	{
		if (!access(data->executable, F_OK))
		{
			if (cmd_is_directory(data->executable))
				command_error_exit(data, data->executable, IS_DIRECTORY);
			return (eval_executable_permissions(data));
		}
		command_error_exit(data, data->executable, EXEC_NOT_FOUND);
	}
	get_executable_path(data);
}

void	eval_executable_permissions(t_data *data)
{
	if (!access(data->executable, X_OK))
		return ;
	command_error_exit(data, data->executable, PERMISSION_DENIED);
}
