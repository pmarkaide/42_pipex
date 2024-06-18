/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:57:55 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/18 10:27:16 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/libft/libft.h" /* libft library */
# include <errno.h>              /* for errno */
# include <fcntl.h>              /* for open, O_DIRECTORY */
# include <stdlib.h>             /* for malloc, free, exit */
# include <sys/wait.h>           /* for waitpid, wait, */
# include <unistd.h>             /* for file r/w, dup2, execve, fork, pipe */

# define NO_FILE 1
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define SEGFAULT 139
# define IS_DIRECTORY -1
# define EXEC_NOT_FOUND -2

typedef struct s_data
{
	int		pipe_fd[2];
	char	*infile;
	char	*outfile;
	int		here_doc;
	char	*delimiter;
	int		in_fd;
	int		out_fd;
	int		num_cmds;
	pid_t	*pid;
	char	***cmds;
	char	*executable;
	char	**envp;
	char	**paths;
	char	*shell;
}			t_data;

void		free_data(t_data *data);
void		free_data_and_exit(t_data *data, char *file, int exit_code);
void		init_struct(t_data *data, int argc, char **argv, char **envp);
char		**parse_cmd_args(char *arg);
int			pipex(t_data *data);
void		dup_file_descriptors(t_data *data, int cmd, int read_end);
void		execute_child_process(t_data *data, int i, int read_end);
void		get_executable_path(t_data *data, char *cmd);
void		eval_executable(t_data *data, char *cmd);
int			cmd_is_directory(char *cmd);
char		**clean_arguments(char *arg);
char		*allocate_result(const char *arg);
char		*remove_str_quotes(char *arg);
int			error_msg(char *msg, int exit_code);
void		close_open_fds(t_data *data);
void		open_infile(t_data *data);
void		open_outfile(t_data *data);
void		here_doc(t_data *data);

#endif /* PIPEX_BONUS_H */