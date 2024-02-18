/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:19:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/02/18 15:38:52 by pmarkaid         ###   ########.fr       */
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






char **parse_cmd_args(char *arg)
{

	int i;
	char **cmd;

	i = 0;
	while (arg[i] != '\0')
	{
		if(ft_isspace(arg[i]))
			arg[i] = ' ';
	}
	cmd = ft_split(arg, ' ');
	ft_print_array(cmd);
	return(cmd);	
}

void init_struct(t_data	*data, char **argv, char **envp)
{
	if (pipe(data->pipe_fd) == -1)
		error_1("pipe failed");
	data ->cmd1 = parse_cmd_args(argv[1]);
	data ->cmd2 = parse_cmd_args(argv[2]);
	//data->paths = parse_paths(envp)
	ft_printf("%c\n",envp[0][0]);
	
}
