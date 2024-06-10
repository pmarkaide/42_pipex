/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:27:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/10 17:01:51 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

	if (pipe(data->pipe_fd) == -1)
		return (error_msg("pipe failed"));
	pid[0] = fork();
	if (pid[0] == -1)
		return (error_msg("fork failed"));
	if (pid[0] == 0)
	{
		execute_child1(data, envp);
		ft_putstr_fd("Child1 executed\n",2);
	}
	pid[1] = fork();
	if (pid[1] == -1)
	{
		waitpid(pid[0], &status1, 0);
		return (error_msg("fork failed"));
	}
	if (pid[1] == 0)
		execute_child2(data, envp);
	close_pipes(data);
	waitpid(pid[0], &status1, 0);
	waitpid(pid[1], &status2, 0);
	return (get_exit_code(status2));
}

int	pipex(t_data *data, char **envp)
{
	int i;
	int	exit_code;
	int	in;
	pid_t	pid[2];

	i = 0;
	exit_code = 0;
	in = 0;
	while(i < data->num_cmd -1)
	{
		pipe(data->pipe_fd);
		pid[0] = fork();
		if (pid[0] == -1)
			return (error_msg("fork failed"));
		if (pid[0] == 0)
		{
			dup_file_descriptors(data, i);
			cmd_is_directory(data);
			eval_executable(data);
			exit_code = execute_cmd(data, envp);
			close_pipes(data);
		}
	}
	close_pipes(data);
	//waitpid
	return (exit_code);
}

//TODO: create a dup2 oneliner: execute > eval > exit
void dup_file_descriptors(t_data *data, int cmd)
{
	if(cmd == 0)
	{
		open_infile(data);
		if(dup2(data->in_fd, STDIN_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(data->in_fd);
	}
	else if(cmd == data->num_cmd -1)
	{
		open_outfile(data);
		if(dup2(data->pipe_fd[0], STDOUT_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(data->pipe_fd[0]);
	}
	else
	{
		if(dup2(data->pipe_fd, STDIN_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		if(dup2(data->pipe_fd, STDOUT_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
	}
}



