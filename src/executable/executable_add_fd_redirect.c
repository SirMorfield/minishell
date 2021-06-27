#include "executable.h"
#include "t_fd_override.h"
#include "ft_ternary.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// Handles things like [n]>&[n]

void	executable_add_fd_redirect(t_executable *executable, int base_fd,
	int new_fd)
{
	list_push(&executable->fd_overrides, &(t_fd_override){
		.new_fd = new_fd,
		.override_fd = base_fd
	});
}

// Handles things like [n]>test_file, [n]>>test_file and [n]<test_file

bool	executable_add_fd_file_redirect(t_executable *executable, int base_fd,
	char *
	file_path, t_file_redirect_mode redirect_mode)
{
	int	new_fd;

	if (redirect_mode & r_write)
		new_fd = open(file_path,
				O_CREAT | O_WRONLY | ter_int(redirect_mode & r_append, O_APPEND,
					O_TRUNC),
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
				);
	else
		new_fd = open(file_path, O_RDONLY);
	if (new_fd == -1)
		return (false);
	list_push(&executable->fd_overrides, &(t_fd_override){
		.new_fd = new_fd,
		.override_fd = base_fd
	});
	list_push(&executable->main_close_fds, &new_fd);
	list_push(&executable->child_close_fds, &new_fd);
	return (true);
}