#ifndef T_COMMAND_H
# define T_COMMAND_H

# include "ft_list.h"

// A command is a the lowest building block of a line
// Just contains [echo, hello, "], everything is escaped and elements are just 
//a null terminated char*
// Also its file descriptor overrides when using pipes or file inputs/outputs
// And a list of fd's to close, good practice to close unused fd's

typedef struct s_command
{
	char	*executable_path;
	t_list	args;
	t_list	fd_overrides;
	t_list	child_close_fds;
}	t_command;

#endif