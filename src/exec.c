/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:40:46 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/10 15:06:39 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	execute_shell_cmd(t_data *data, char **envp)
{
	char	*shell_cmd[4];

	shell_cmd[0] = data->shell;
	shell_cmd[1] = "-c";
	shell_cmd[2] = data->cmd[0];
	shell_cmd[3] = NULL;
	if (execve(data->shell, shell_cmd, envp) == -1)
	{
		ft_putstr_fd("execve failed\n", 2);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	execute_cmd(t_data *data, char **envp)
{
	int	exit_code;

	if (execve(data->exec_path, data->cmd, envp) == -1)
	{
		exit_code = execute_shell_cmd(data, envp);
		return (exit_code);
	}
	return (0);
}

int	execute_child1(t_data *data, char **envp)
{
	int	in_fd;
	int	exit_code;

	exit_code = 0;
	close(data->pipe_fd[0]);
	in_fd = open(data->infile, O_RDONLY);
	if (errno == ENOENT)
		free_data_and_exit(data, data->infile, NO_FILE);
	if (errno == EACCES)
		free_data_and_exit(data, data->infile, PERMISSION_DENIED);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(in_fd);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(data->pipe_fd[1]);
	data->cmd = data->cmd1;
	cmd_is_directory(data);
	eval_executable(data);
	exit_code = execute_cmd(data, envp);
	return (exit_code);
}

void	execute_child2(t_data *data, char **envp)
{
	int	out_fd;

	close(data->pipe_fd[1]);
	out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (errno == ENOENT)
		free_data_and_exit(data, data->outfile, NO_FILE);
	if (errno == EACCES)
		free_data_and_exit(data, data->outfile, PERMISSION_DENIED);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(data->pipe_fd[0]);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		free_data_and_exit(data, "dup2 error", -1);
	close(out_fd);
	data->cmd = data->cmd2;
	cmd_is_directory(data);
	eval_executable(data);
	execute_cmd(data, envp);
}
