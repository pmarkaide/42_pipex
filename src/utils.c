/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:19:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/20 15:47:16 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// typedef struct s_data
// {
// 	int pipe_fd[2];
// 	char **cmd1;
// 	char **cmd2;
// 	char **env;
// }				t_data;

void free_array(char **array)
{
	size_t i;

	i = 0;
	if (array == NULL || *array == NULL)
		return;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void free_data(t_data *data)
{
	size_t i;

	i = 0;
	if (data == NULL)
		return;
	free_array(data->cmd1);
	free_array(data->cmd2);
	free_array(data->paths);
}

char **parse_cmd_args(char *arg)
{
	int i;
	char **cmd;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isspace(arg[i]))
			arg[i] = ' ';
		i++;
	}
	cmd = ft_split(arg, ' ');
	return (cmd);
}

void get_executable_path(t_data *data)
{
	int i;
	char *exec_path;

	i = 0;
	while (data->paths[i])
	{
		exec_path = ft_strjoin(data->paths[i], data->cmd[0], "/");
		
		//access returns -1 and errno on error; 0 on sucess
		if (!access(exec_path, F_OK | X_OK))
			data->exec_path = exec_path;
		free(exec_path);
	}
	free_data_and_exit(data, "No executable found");
}

char open_outfile(char *file)
{
	int fd;
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return(fd);
}

int open_infile(char *file) {
    int fd;
    fd = open(file, O_RDONLY);
    return fd;
}

char **parse_paths(char **envp)
{
	int i;
	char **paths;

	i = 0;
	while (envp[i] != '\0')
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

void init_struct(t_data *data, char **argv, char **envp)
{
	if (pipe(data->pipe_fd) == -1)
		error_1("pipe failed");
	data->cmd1 = parse_cmd_args(argv[2]);
	data->cmd2 = parse_cmd_args(argv[3]);
	data->paths = parse_paths(envp);
	data->in_fd = open_infile(argv[1]);
	data->out_fd = open_outfile(argv[4]);

}

void check_params(t_data *data)
{
	if(data->cmd1 == NULL)
		free_data_and_exit(data, "Problem parsing arguments");
	if(data->cmd1 == NULL)
		free_data_and_exit(data, "Problem parsing arguments");
	if(data->paths == NULL)
		free_data_and_exit(data, "Problem with path parsing");
	if(data->in_fd == -1)
		free_data_and_exit(data, "Error opening infile");
	if(data->out_fd == -1)
		free_data_and_exit(data, "Error opening outfile");
}
