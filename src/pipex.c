/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:42:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/03/04 18:38:00 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_cmd(t_data *data, char **envp)
{
	if (execve(data->exec_path, data->cmd, envp) == -1)
	{
		exit_1("Execve error");
	}
}

void	execute_child1(t_data *data, char **envp)
{
	int	in_fd;

	close(data->pipe_fd[0]);
	in_fd = open(data->infile, O_RDONLY);
	if (in_fd == -1)
		free_data_and_exit(data, data->infile);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		free_data_and_exit(data, "dup2 error");
	close(in_fd);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		free_data_and_exit(data, "dup2 error");
	close(data->pipe_fd[1]);
	data->cmd = data->cmd1;
	get_executable_path(data);
	execute_cmd(data, envp);
}

void	execute_child2(t_data *data, char **envp)
{
	int	out_fd;

	close(data->pipe_fd[1]);
	out_fd = open(data->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		free_data_and_exit(data, data->outfile);
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		free_data_and_exit(data, "dup2 error");
	close(data->pipe_fd[0]);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		free_data_and_exit(data, "dup2 error");
	close(out_fd);
	data->cmd = data->cmd2;
	get_executable_path(data);
	execute_cmd(data, envp);
}

void	pipex(t_data *data, char **envp)
{
	pid_t	pid[2];
	int		status1;
	int		status2;

	if (pipe(data->pipe_fd) == -1)
		error_1("pipe failed");
	pid[0] = fork();
	if (pid[0] == -1)
		free_data_and_exit(data, "fork failed");
	if (pid[0] == 0)
		execute_child1(data, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		free_data_and_exit(data, "fork failed");
	if (pid[1] == 0)
		execute_child2(data, envp);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(pid[0], &status1, 0);
	waitpid(pid[1], &status2, 0);
}
