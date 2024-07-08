/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:12:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/08 12:55:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	execute_shell_cmd(t_data *data)
{
	char	*shell_cmd[4];

	shell_cmd[0] = data->shell;
	shell_cmd[1] = "-c";
	shell_cmd[2] = data->executable;
	shell_cmd[3] = NULL;
	if (execve(data->shell, shell_cmd, data->envp) == -1)
	{
		ft_putstr_fd("execve failed\n", 2);
		return (EXIT_FAILURE);
	}
	return (0);
}

void	eval_executable_permissions(t_data *data)
{
	if (!access(data->executable, X_OK))
		return ;
	command_error_exit(data, data->executable, PERMISSION_DENIED);
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
		command_error_exit(data, "malloc error", -1);
	if (ft_str_empty(data->executable))
		command_error_exit(data, data->executable, COMMAND_NOT_FOUND);
	if (ft_strchr("./", data->executable[0]) != NULL)
		local = 1;
	if (local || data->paths == NULL)
	{
		if (!access(data->executable, F_OK))
		{
			if (cmd_is_directory(cmd))
				command_error_exit(data, cmd, IS_DIRECTORY);
			return (eval_executable_permissions(data));
		}
		command_error_exit(data, data->executable, EXEC_NOT_FOUND);
	}
	get_executable_path(data, cmd);
}

void	execute_child_process(t_data *data, int i, int read_end)
{
	int	exit_code;

	dup_file_descriptors(data, i, read_end);
	eval_executable(data, data->cmds[i][0]);
	if (execve(data->executable, data->cmds[i], data->envp) == -1)
	{
		exit_code = execute_shell_cmd(data);
		free_data(data);
		exit(exit_code);
	}
	exit(0);
}
