#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - a function that partitions a line read from standard input
 * as needed
 * @line: a pointer to a line read from standard input
 * @read: the length of line
 * Description: spaces are inserted to separate ";", "||", and "&&"
 * Replaces "#" with '\0'
 */

void handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char previous, current, next;
	size_t x, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *line;
	for (x = 0; old_line[x]; x++)
	{
		current = old_line[x];
		next = old_line[x + 1];
		if (x != 0)
		{
			previous = old_line[x - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (x != 0 && old_line[x - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[x];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len - a function that gets the new length of a line partitioned
 * by ";", "||", "&&&", or "#"
 * @line: the line to check
 * Return: The new length of the line
 * Description: Cuts short lines containing '#' comments with '\0'
 */

ssize_t get_new_len(char *line)
{
	size_t y;
	ssize_t new_len = 0;
	char current, next;

	for (y = 0; line[y]; y++)
	{
		current = line[y];
		next = line[y + 1];
		if (current == '#')
		{
			if (y == 0 || line[y - 1] == ' ')
			{
				line[y] = '\0';
				break;
			}
		}
		else if (y != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[y - 1] != ' ' && line[y - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[y - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[y - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[y], &new_len);
		}
		else if (current == ';')
		{
			if (y != 0 && line[y - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - a function that checks a line for logical operators
 * "||" or "&&"
 * @line: a pointer to the character to check in the line
 * @new_len: pointer to new_len in get_new_len function
 */

void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}

