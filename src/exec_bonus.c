/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:12:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/19 12:40:54 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	eval_executable_permissions(t_data *data)
{
	if (!access(data->executable, X_OK))
		return ;
	free_data_and_exit(data, data->executable, PERMISSION_DENIED);
}

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

void	eval_executable(t_data *data, char *cmd)
{
	int	local;

	local = 0;
	data->executable = cmd;
	if (data->executable == NULL)
		free_data_and_exit(data, "malloc error", -1);
	if (ft_str_empty(data->executable))
		free_data_and_exit(data, data->executable, COMMAND_NOT_FOUND);
	if (ft_strchr("./", data->executable[0]) != NULL)
		local = 1;
	if (local || data->paths == NULL)
	{
		if (!access(data->executable, F_OK))
		{
			if (cmd_is_directory(cmd))
				free_data_and_exit(data, cmd, IS_DIRECTORY);
			return (eval_executable_permissions(data));
		}
		free_data_and_exit(data, data->executable, EXEC_NOT_FOUND);
	}
	get_executable_path(data, cmd);
}

void	get_executable_path(t_data *data, char *cmd)
{
	int		i;

	i = 0;
	while (data->paths[i])
	{
		data->executable = ft_strjoin(data->paths[i], cmd, "/");
		if (data->executable == NULL)
			free_data_and_exit(data, "malloc error", -1);
		if (!access(data->executable, F_OK))
		{
			if (cmd_is_directory(data->executable))
				free_data_and_exit(data, cmd, COMMAND_NOT_FOUND);
			return (eval_executable_permissions(data));
		}
		free(data->executable);
		data->executable = NULL;
		i++;
	}
	free_data_and_exit(data, cmd, COMMAND_NOT_FOUND);
}

void	execute_child_process(t_data *data, int i, int read_end)
{
	dup_file_descriptors(data, i, read_end);
	eval_executable(data, data->cmds[i][0]);
	if (execve(data->executable, data->cmds[i], data->envp) == -1)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	exit(0);
}
