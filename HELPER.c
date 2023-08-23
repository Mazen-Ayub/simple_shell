#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - a function that frees up memory taken by args
 * @args: a null-terminated double pointer containing commands/arguments
 * @front: a double pointer to the beginning of args
 */

void free_args(char **args, char **front)
{
	size_t x;

	for (x = 0; args[x] || args[x + 1]; x++)
		free(args[x]);

	free(front);
}

/**
 * get_pid - a function that gets the current process ID
 * Description: it opens the stat file, a space-delimited file containing
 * information about the current process. The PID is the
 * first word in the file. The function reads the PID into
 * a buffer and replace the space at the end with a \0 byte
 * Return: the current process ID or NULL on failure
 */

char *get_pid(void)
{
	size_t y = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[y] != ' ')
		y++;
	buffer[y] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - a function that gets the value corresponding to an environmental variable
 * @beginning: the environmental variable to search for
 * @len: the length of the environmental variable to search for
 * Return: if the variable is not found - an empty string
 * Otherwise : the value of the environmental variable
 * Description: variables are stored in the format VARIABLE=VALUE
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - a function that handles variable replacement
 * @line: a double pointer containing the command and arguments
 * @exe_ret: a pointer to the return value of the last executed command
 * Description: it replaces $$ with the current PID, $? with the return value
 * of the last executed program, and envrionmental variables
 * preceded by $ with their corresponding value
 */

void variable_replacement(char **line, int *exe_ret)
{
	int s, j = 0, length;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (s = 0; old_line[s]; s++)
	{
		if (old_line[s] == '$' && old_line[s + 1] &&
				old_line[s + 1] != ' ')
		{
			if (old_line[s + 1] == '$')
			{
				replacement = get_pid();
				j = s + 2;
			}
			else if (old_line[s + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				j = s + 2;
			}
			else if (old_line[s + 1])
			{
				/* extract the variable name to search for */
				for (j = s + 1; old_line[j] &&
						old_line[j] != '$' &&
						old_line[j] != ' '; j++)
					;
				length = j - (s + 1);
				replacement = get_env_value(&old_line[s + 1], length);
			}
			new_line = malloc(s + _strlen(replacement)
					  + _strlen(&old_line[j]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, s);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[j]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			s = -1;
		}
	}
}