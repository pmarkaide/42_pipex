/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:40:46 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/08 12:51:32 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_pipes(t_data *data)
{
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
}

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

	if (execve(data->executable, data->cmd, envp) == -1)
	{
		exit_code = execute_shell_cmd(data, envp);
		return (exit_code);
	}
	return (0);
}

void	execute_child1(t_data *data, char **envp)
{
	int	in_fd;

	close(data->pipe_fd[0]);
	in_fd = open(data->infile, O_RDONLY);
	if (errno == ENOENT)
		file_error_exit(data, data->infile, FILE_NOT_FOUND);
	if (errno == EACCES)
		file_error_exit(data, data->infile, FILE_PERMISSION_DENIED);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		command_error_exit(data, "dup2 error", -1);
	close(in_fd);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		command_error_exit(data, "dup2 error", -1);
	close(data->pipe_fd[1]);
	data->cmd = data->cmd1;
	eval_executable(data);
	execute_cmd(data, envp);
}

void	execute_child2(t_data *data, char **envp)
{
	int	out_fd;

	close(data->pipe_fd[1]);
	out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (errno == ENOENT)
		file_error_exit(data, data->outfile, FILE_NOT_FOUND);
	if (errno == EACCES)
		file_error_exit(data, data->outfile, FILE_PERMISSION_DENIED);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		command_error_exit(data, "dup2 error", -1);
	close(data->pipe_fd[0]);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		command_error_exit(data, "dup2 error", -1);
	close(out_fd);
	data->cmd = data->cmd2;
	eval_executable(data);
	execute_cmd(data, envp);
}
