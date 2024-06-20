/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:27:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/19 17:16:25 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	get_exit_code(int status)
{
	int	exit_code;

	exit_code = 0;
	if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}

int	wait_processes(pid_t *pid, int cmds)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < cmds)
	{
		waitpid(pid[i], &status, 0);
		if (i == cmds - 1)
			exit_code = get_exit_code(status);
		i++;
	}
	return (exit_code);
}

int	execute_cmds(t_data *data, int read_end)
{
	int	i;

	i = 0;
	while (i < data->num_cmds)
	{
		if (pipe(data->pipe_fd) == -1)
			return (error_msg("pipe failed", i));
		data->pid[i] = fork();
		if (data->pid[i] == -1)
		{
			close(data->pipe_fd[1]);
			return (error_msg("fork failed", i));
		}
		if (data->pid[i] == 0)
			execute_child_process(data, i, read_end);
		if (read_end > 0)
			close(read_end);
		read_end = data->pipe_fd[0];
		close(data->pipe_fd[1]);
		i++;
	}
	if (read_end > 0)
		close(read_end);
	return (i);
}

void	here_doc(t_data *data)
{
	int		fd;
	char	*line;
	char	*delimiter_with_newline;

	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		free_data_and_exit(data, "here_doc file opening failed", -1);
	delimiter_with_newline = ft_strjoin(data->delimiter, "\n", NULL);
	if (!delimiter_with_newline)
		free_data_and_exit(data, "malloc error", -1);
	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strcmp(line, delimiter_with_newline) == 0)
		{
			free(line);
			free(delimiter_with_newline);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
}

int	pipex(t_data *data)
{
	int	exit_code;
	int	read_end;
	int	num_cmds_executed;

	read_end = 0;
	num_cmds_executed = execute_cmds(data, read_end);
	exit_code = wait_processes(data->pid, num_cmds_executed);
	close(read_end);
	close_open_fds(data);
	return (exit_code);
}
