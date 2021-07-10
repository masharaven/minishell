#include "process.h"

int	move_descriptors(char *relink_path, int write_mode, int *stdout_fd)
{
	int	fd;

	*stdout_fd = -1;
	if (write_mode == 0)
		fd = open(relink_path, O_CREAT | O_RDWR, 0644);
	else
		fd = open(relink_path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	*stdout_fd = dup(1);
	dup2(fd, 1);
	return (1);
}

int	move_descriptors_back(int stdout_fd)
{
	close(1);
	dup2(stdout_fd, 1);
	return (1);
}

int	process_run(char *path, char **args, char *relink_path, int write_mode)
{
	pid_t	pid;
	int		stdout_fd;
	int		ret;

	ret = 0;
	if (!is_f_ex(path))
		return (-1);
	if (relink_path != NULL \
	&& move_descriptors(relink_path, write_mode, &stdout_fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		ft_error_my_exit("fork() error.\n", 42);
	if (pid == 0)
	{
		execve(path, args, g_minishell.environ);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &ret, 0);
	if (relink_path != NULL)
		move_descriptors_back(stdout_fd);
	return (ret % 255);
}

void	child_body(int fd[], char *text, pid_t *pid)
{
	if (pipe(fd) < 0)
		ft_error_my_exit("pipe() error.\n", 42);
	*pid = fork();
	if (*pid < 0)
		ft_error_my_exit("fork() error.\n", 42);
	if (*pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (text != NULL)
			printf("%s\n", text);
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	if (text != NULL)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	*pid = wait(NULL);
}

int	process_run_smart(char *path, char **args, t_relink_info relinkInfo, \
char *text)
{
	int		fd[2];
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid < 0)
		ft_error_my_exit("fork() error.\n", 42);
	if (pid == 0)
	{
		child_body(fd, text, &pid);
		exit(process_run(path, args, relinkInfo.relink_path, \
		relinkInfo.write_mode));
	}
	waitpid(pid, &ret, 0);
	return (ret % 255);
}
