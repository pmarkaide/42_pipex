/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:27:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/12 12:46:45 by pmarkaid         ###   ########.fr       */
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

//TODO: create a dup2 oneliner: execute > eval > exit
void dup_file_descriptors(t_data *data, int cmd, int read_end)
{
	if(cmd == 0)
	{
		open_infile(data);
		if(dup2(data->in_fd, STDIN_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(data->in_fd);
		if(dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(data->pipe_fd[1]);
	}
	else if(cmd == data->num_cmds -1)
	{
		open_outfile(data);
		if(dup2(read_end, STDIN_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(read_end);
		if(dup2(data->out_fd, STDOUT_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(data->out_fd);
	}
	else
	{
		if(dup2(read_end, STDIN_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(read_end);
		if(dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			free_data_and_exit(data, "dup2 error", -1);
		close(data->pipe_fd[1]);
	}
}

int	pipex(t_data *data, char **envp)
{
	int i;
	int	exit_code;
	int	read_end;
	pid_t	pid[2];

	i = 0;
	exit_code = 0;
	read_end = 0;
	while(i < data->num_cmds -1)
	{
		pipe(data->pipe_fd);
		pid[0] = fork();
		if (pid[0] == -1)
			return (error_msg("fork failed"));
		if (pid[0] == 0)
		{
			dup_file_descriptors(data, i, read_end);
			data->cmd = data->cmds[i];
			cmd_is_directory(data);
			eval_executable(data);
			exit_code = execute_cmd(data, envp);
			exit(exit_code);
		}
		else
		{
			waitpid(pid[0], &exit_code, 0);
			close(data->pipe_fd[1]);
			if (read_end != 0)
				close(read_end);
			read_end = data->pipe_fd[0];
		}
		i++;
	}
	close(read_end);
	close_open_fds(data);
	return (exit_code);
}





