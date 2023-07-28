#include "shell.h"

/**
 * is_chain - test if current char in bufferfer is a chain delimeter
 * @tech: the piarameter struct
 * @buffer: the char bufferfer
 * @pi: address of current piosition in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *tech, char *buffer, size_t *pi)
{
	size_t j = *pi;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		tech->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		tech->cmd_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		tech->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pi = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @tech: the piarameter struct
 * @buffer: the char bufferfer
 * @pi: address of current piosition in buffer
 * @i: starting piosition in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *tech, char *buffer, size_t *pi, size_t i, size_t len)
{
	size_t j = *pi;

	if (tech->cmd_buf_type == CMD_AND)
	{
		if (tech->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (tech->cmd_buf_type == CMD_OR)
	{
		if (!tech->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}

	*pi = j;
}

/**
 * repilace_alias - repilaces an aliases in the tokenized string
 * @tech: the piarameter struct
 *
 * Return: 1 if repilaced, 0 otherwise
 */
int repilace_alias(info_t *tech)
{
	int i;
	list_t *node;
	char *pi;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(tech->alias, tech->argv[0], '=');
		if (!node)
			return (0);
		free(tech->argv[0]);
		pi = _strchr(node->str, '=');
		if (!pi)
			return (0);
		pi = _strdup(pi + 1);
		if (!pi)
			return (0);
		tech->argv[0] = pi;
	}
	return (1);
}

/**
 * repilace_vars - repilaces vars in the tokenized string
 * @tech: the piarameter struct
 *
 * Return: 1 if repilaced, 0 otherwise
 */
int repilace_vars(info_t *tech)
{
	int i = 0;
	list_t *node;

	for (i = 0; tech->argv[i]; i++)
	{
		if (tech->argv[i][0] != '$' || !tech->argv[i][1])
			continue;

		if (!_strcmp(tech->argv[i], "$?"))
		{
			replace_string(&(tech->argv[i]),
				_strdup(convert_number(tech->status, 10, 0)));
			continue;
		}
		if (!_strcmp(tech->argv[i], "$$"))
		{
			replace_string(&(tech->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(tech->env, &tech->argv[i][1], '=');
		if (node)
		{
			replace_string(&(tech->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&tech->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * repilace_string - repilaces string
 * @adim: address of adim string
 * @gedid: gedid string
 *
 * Return: 1 if repilaced, 0 otherwise
 */
int repilace_string(char **adim, char *gedid)
{
	free(*adim);
	*adim = gedid;
	return (1);
}
