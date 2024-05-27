/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:19:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/05/27 22:35:21 by pmarkaid         ###   ########.fr       */
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

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL || *array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_array(data->cmd1);
	free_array(data->cmd2);
	free_array(data->paths);
	if(data->exec_path)
		free(data->exec_path);
	if(data->shell)
		free(data->shell);
}



char *remove_double_quotes(const char *arg)
{
    int i;
    int j;
    char *result;

    i = 0;
    j = 0;
    result = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char));
    if(result == NULL)
        return NULL;
    while (arg[i] != '\0')
    {
        if (arg[i] == '\"' && arg[i + 1] == '\"')
            i += 2;
        else
            result[j++] = arg[i++];
    }
    result[j] = '\0';
    return result;
}

int is_non_escape_char(char c)
{
    if (c == 'n' || c == 'r' || c == 't' ||
        c == 'v' || c == '\\' || c == '\'' ||
        c == '\"' || c == '0')
        return 0;
    else
        return 1;
}

char *allocate_result(const char *arg)
{
    int len = ft_strlen(arg);
    if (len == 0)
        return ft_strdup(arg);
    return (char *)malloc((len + 1) * sizeof(char));
}

char *remove_str_quotes_and_escape_chars(const char *arg)
{
	int i;
	int j;
	int in_double_quotes;
	char *result;

	i = 0;
	j = 0;
	in_double_quotes = 0;
	result = allocate_result(arg);
	if(result == NULL)
		return NULL;
	while(arg[i])
    {
        if(arg[i] == '\"')
        {
            in_double_quotes = !in_double_quotes;
            i++;
            continue;
        }
        if(arg[i] == '\\' && (!in_double_quotes || (in_double_quotes && !is_non_escape_char(arg[i+1]))))
            i++;
        result[j++] = arg[i++];
    }
    result[j] = '\0';
    return result;
}

void remove_array_quotes(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		char *new_str = remove_str_quotes_and_escape_chars(array[i]);
		if (new_str != NULL)
		{
			free(array[i]);
			array[i] = new_str;
		}
		i++;
	}
}

int count_args(char *arg)
{
    int count;
    int i;

	count = 0;
	i = 0;
    if (arg[i] != '\0')
        count = 1;
    while (arg[i] != '\0')
	{
        if (arg[i] == ' ' && (i == 0 || arg[i - 1] != '\\'))
            count++;
        i++;
    }
    return count;
}

char **handle_empty_arg(char *arg)
{
    char **cmd;

	cmd = malloc(sizeof(char *) * 2);
    if (cmd == NULL)
        return NULL;
    cmd[0] = ft_strdup(arg);
    if (cmd[0] == NULL)
	{
        free(cmd);
        return NULL;
    }
    cmd[1] = NULL;
    return cmd;
}

char **handle_non_empty_arg(char *arg)
{
    char **cmd;
    int i;
    int start;
    int arg_count;

    i = 0;
    arg_count = 0;
    start = 0;
    cmd = malloc(sizeof(char *) * (count_args(arg) + 1));
    if (cmd == NULL)
        return NULL;
    while (arg[i] != '\0') {
        if (arg[i] == ' ' && (i == 0 || arg[i - 1] != '\\')) {
            cmd[arg_count] = ft_substr(arg, start, i - start);
            start = i + 1;
            arg_count++;
        }
        i++;
    }
    cmd[arg_count] = ft_substr(arg, start, i - start);
    cmd[arg_count + 1] = NULL;
    return cmd;
}

char **parse_cmd_args(char *arg) {
    char **cmd;
    if (ft_str_empty(arg))
        cmd = handle_empty_arg(arg);
	else
        cmd = handle_non_empty_arg(arg);
    return cmd;
}

char **clean_arguments(char *arg)
{
	char *clean;
	char **args;

	clean = remove_double_quotes(arg);
	args = parse_cmd_args(clean);
	remove_array_quotes(args);
	free(clean);
	return args;
}

void cmd_is_directory(t_data *data)
{
	int fd;
	
	fd = open(data->cmd[0], O_RDONLY | O_DIRECTORY);
    if (fd != -1)
	{
        free_data_and_exit(data, data->cmd[0], IS_DIRECTORY);
        close(fd);
	}
}

void eval_executable(t_data *data)
{
	int local;
	char *exec_path;
	local = 0;

	exec_path = ft_strdup(data->cmd[0]);
	if (exec_path == NULL)
		free_data_and_exit(data, "malloc error", -1);
	data->exec_path = exec_path;
	if(ft_str_empty(data->exec_path))
		free_data_and_exit(data, data->exec_path, COMMAND_NOT_FOUND);
	if(ft_strncmp(data->cmd[0], "/", 1) == 0)
		local = 1;
	if(ft_strncmp(data->cmd[0], "./", 2) == 0)
		local = 1;
	if(ft_strncmp(data->cmd[0], "../", 3) == 0)
		local = 1;
	if(local || data->paths == NULL)
	{
		if (!access(data->exec_path, F_OK))
			return(eval_executable_permissions(data));
		else
			free_data_and_exit(data, data->exec_path, EXEC_NOT_FOUND);
	}
	else
		get_executable_path(data);
}

void	get_executable_path(t_data *data)
{
	int		i;
	char	*exec_path;

	exec_path = data->cmd[0];
	i = 0;
	while (data->paths[i])
	{
		exec_path = ft_strjoin(data->paths[i], data->cmd[0], "/");
		if (!access(exec_path, F_OK))
		{
			free(data->exec_path);
			data->exec_path = exec_path;
			return(eval_executable_permissions(data));
		}
		free(exec_path);
		i++;
	}
	free_data_and_exit(data, data->cmd[0], COMMAND_NOT_FOUND);
}

void eval_executable_permissions(t_data *data)
{
	if (!access(data->exec_path, X_OK))
		return;
	free_data_and_exit(data, data->exec_path, PERMISSION_DENIED);
}

char	**parse_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
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

char *parse_shell(char **envp)
{
	int		i;
	char *shell;

	i = 0;
    while (envp[i])
    {
        if (ft_strnstr(envp[i], "SHELL=", 6))
		{
            shell = ft_strdup(envp[i] + 6);
            return (shell);
        }
        i++;
    }
	shell = ft_strdup("/bin/sh");
	return (shell);
}

void	init_struct(t_data *data, char **argv, char **envp)
{
	data->infile = argv[1];
	data->outfile = argv[4];
	data->cmd1 = clean_arguments(argv[2]);
	data->cmd2 = clean_arguments(argv[3]);
	data->paths = parse_paths(envp);
	data->shell = parse_shell(envp);
	data->exec_path = NULL;
	if(data->cmd1 == NULL || data->cmd2 == NULL)
		free_data_and_exit(data, "malloc error", -1);
}
