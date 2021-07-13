#ifndef COMMAND_READ_H
# define COMMAND_READ_H

# include "ft_list.h"

// enum as a bit mask
typedef enum e_blocktype
{
	B_ERROR = 1 << 29,
	B_TEXT = 1 << 28,
	B_GRAMMAR_RULE = 1 << 27,
	B_NO_CLOSING_QUOTE = B_ERROR | 1 << 0,
	B_END = 1 << 1,
	B_NORMAL = B_TEXT | 1 << 2,
	B_SINGLE_QUOTE = B_TEXT | 1 << 3,
	B_DOUBLE_QUOTE = B_TEXT | 1 << 4,
	B_DOUBLE_GREATER = B_GRAMMAR_RULE | 1 << 5,
	B_DOUBLE_LESSER = B_GRAMMAR_RULE | 1 << 6,
	B_GREATER = B_GRAMMAR_RULE | 1 << 7,
	B_LESSER = B_GRAMMAR_RULE | 1 << 8,
	B_PIPE_FD = B_GRAMMAR_RULE | 1 << 9,
	B_PIPE = B_GRAMMAR_RULE | 1 << 10,
}			t_blocktype;

typedef struct s_block
{
	char		*text;
	t_blocktype	type;
}		t_block;

typedef enum e_command_type
{
	C_EXECTUTABLE,
	C_ENV,
}			t_command_type;

t_list			command_read(void);
void			command_read_destroy(t_list *cmd);
int				run_command_as_executable(const t_list *cmd);
t_command_type	identify_command(const t_list *cmd);

// PRIVATE =====================================================================
typedef struct s_grammarinfo
{
	t_blocktype	type;
	size_t		len;
}				t_grammarinfo;

t_blocktype		goto_next_split(char **current, char **start, char **end);
void			expand_environment_variables(char **str);
t_blocktype		handle_quoted_block(char **current, char **start, char **end,
					t_blocktype blocktype);
void			remove_escape_characters(char *cmd);
t_grammarinfo	get_block_info(const char *str);
// END PRIVATE =================================================================

#endif
