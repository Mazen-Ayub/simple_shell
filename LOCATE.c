#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - a function that locates a command in the PATH
 * @command: the command to locate
 * Return: if an error occurs or the command cannot be located - NULL
 * Otherwise : the full pathname of the command
 */

char *get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - a function that copies path but also replaces
 * leading/sandwiched/trailing
 * colons (:) with current working directory
 * @path: the colon-separated list of directories
 * Return: a copy of path with any leading/sandwiched/trailing colons replaced
 * with the current working directory
 */

char *fill_path_dir(char *path)
{
	int x, len = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (path[x + 1] == ':' || x == 0 || path[x + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (x == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[x + 1] == ':' || path[x + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[x], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - a function that tokenizes a colon-separated list of
 * directories into a list_s linked list
 * @path: the colon-separated list of directories
 * Return: a pointer to the initialized linked list
 */

list_t *get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}

