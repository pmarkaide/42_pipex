/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:12:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/14 11:59:57 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	eval_executable_permissions(t_data *data)
{
	if (!access(data->exec_path, X_OK))
		return ;
	free_data_and_exit(data, data->exec_path, PERMISSION_DENIED);
}

void	cmd_is_directory(t_data *data, char *cmd)
{
	int	fd;

	fd = open(cmd, O_RDONLY | O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		free_data_and_exit(data, cmd, IS_DIRECTORY);
	}
}

void	eval_executable(t_data *data, char *cmd)
{
	int		local;
	char	*exec_path;

	local = 0;
	exec_path = ft_strdup(cmd);
	if (exec_path == NULL)
		free_data_and_exit(data, "malloc error", -1);
	data->exec_path = exec_path;
	if (ft_str_empty(data->exec_path))
		free_data_and_exit(data, data->exec_path, COMMAND_NOT_FOUND);
	if (ft_strncmp(cmd, "/", 1) == 0)
		local = 1;
	if (ft_strncmp(cmd, "./", 2) == 0)
		local = 1;
	if (ft_strncmp(cmd, "../", 3) == 0)
		local = 1;
	if (local || data->paths == NULL)
	{
		if (!access(data->exec_path, F_OK))
			eval_executable_permissions(data);
		else
			free_data_and_exit(data, data->exec_path, EXEC_NOT_FOUND);
	}
	else
		get_executable_path(data, cmd);
}

int	execute_cmd(t_data *data, char **cmd, char **envp)
{
	int	exit_code;

	exit_code = 0;

	if (execve(data->exec_path, cmd, envp) == -1)
	{
		free_data(data);
		return (EXIT_FAILURE);
	}
	return (exit_code);
}

void	get_executable_path(t_data *data, char *cmd)
{
	int		i;
	char	*exec_path;

	i = 0;
	while (data->paths[i])
	{
		exec_path = ft_strjoin(data->paths[i], cmd, "/");
		if (!access(exec_path, F_OK))
		{
			free(data->exec_path);
			data->exec_path = exec_path;
			eval_executable_permissions(data);
			return;
		}
		free(exec_path);
		i++;
	}
	free_data_and_exit(data, cmd, COMMAND_NOT_FOUND);
}
