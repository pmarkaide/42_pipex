/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:42:37 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/06 12:54:54 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_exit_code(int status)
{
	int	exit_code;

	exit_code = 0;
	if (WIFSIGNALED(status) && WTERMSIG(status))
		exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}

int	pipex(t_data *data, char **envp)
{
	pid_t	pid[2];
	int		status1;
	int		status2;
	int		exit_code;

	exit_code = 0;
	if (pipe(data->pipe_fd) == -1)
		free_data_and_exit(data, "pipe failed", -1);
	pid[0] = fork();
	if (pid[0] == -1)
		free_data_and_exit(data, "fork failed", -1);
	if (pid[0] == 0)
		execute_child1(data, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		free_data_and_exit(data, "fork failed", -1);
	if (pid[1] == 0)
		execute_child2(data, envp);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(pid[0], &status1, 0);
	waitpid(pid[1], &status2, 0);
	exit_code = get_exit_code(status2);
	return (exit_code);
}
