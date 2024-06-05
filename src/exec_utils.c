/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:40:35 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/05 11:53:33 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	cmd_is_directory(t_data *data)
{
	int	fd;

	fd = open(data->cmd[0], O_RDONLY | O_DIRECTORY);
	if (fd != -1)
	{
		free_data_and_exit(data, data->cmd[0], IS_DIRECTORY);
		close(fd);
	}
}

void	eval_executable(t_data *data)
{
	int		local;
	char	*exec_path;

	local = 0;
	exec_path = ft_strdup(data->cmd[0]);
	if (exec_path == NULL)
		free_data_and_exit(data, "malloc error", -1);
	data->exec_path = exec_path;
	if (ft_str_empty(data->exec_path))
		free_data_and_exit(data, data->exec_path, COMMAND_NOT_FOUND);
	if (ft_strncmp(data->cmd[0], "/", 1) == 0)
		local = 1;
	if (ft_strncmp(data->cmd[0], "./", 2) == 0)
		local = 1;
	if (ft_strncmp(data->cmd[0], "../", 3) == 0)
		local = 1;
	if (local || data->paths == NULL)
	{
		if (!access(data->exec_path, F_OK))
			return (eval_executable_permissions(data));
		else
			free_data_and_exit(data, data->exec_path, EXEC_NOT_FOUND);
	}
	else
		get_executable_path(data);
}

void	eval_executable_permissions(t_data *data)
{
	if (!access(data->exec_path, X_OK))
		return ;
	free_data_and_exit(data, data->exec_path, PERMISSION_DENIED);
}
