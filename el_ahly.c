#include "shell.h"

/**
 * hsh - elmain hell lop
 * @soha: the parameter returns soha
 * @avat: agument vector main
 *
 * Return: 0 on success, 1 on error
 */
int hsh(info_t *soha, char **avat)
{
	ssize_t g = 0;
	int built_ret = 0;

	while (g != -1 && built_ret != -2)
	{
		clear_info(soha);
		if (interactive(soha))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		g = get_input(soha);
		if (g != -1)
		{
			set_info(soha, avat);
			built_ret =  find_builtin(soha);
			if (built_ret == -1)
				find_cmd(soha);
		}
		else if (interactive(soha))
			_putchar('\n');
		free_info(soha, 0);
	}
	write_history(soha);
	free_info(soha, 1);
	if (!interactive(soha) && soha->status)
		exit(soha->status);
	if (built_ret == -2)
	{
		if (soha->err_num == -1)
			exit(soha->status);
		exit(soha->err_num);
	}
	return (built_ret);
}

/**
 * find_builtin - fnd abuiltin command
 * @soha: the parameter returns soha
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *soha)
{
	int u, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (u = 0; builtintbl[u].type; u++)
		if (_strcmp(soha->argv[0], builtintbl[u].type) == 0)
		{
			soha->line_count++;
			built_in_ret = builtintbl[u].func(soha);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - yaged elcomand fe elpath
 * @soha: the parameter returns soha
 *
 * Return: void
 */
void find_cmd(info_t *soha)
{
	char *vini = NULL;
	int u, c;
	char **path;

	soha->vini = soha->argv[0];
	if (soha->linecount_flag == 1)
	{
		soha->line_count++;
		soha->linecount_flag = 0;
	}
	for (u = 0, c = 0; soha->arg[u]; u++)
		if (!is_delim(soha->arg[u], " \t\n"))
			c++;
	if (!c)
		return;

	path = find_path(soha, _getenv(soha, "PATH="), soha->argv[0]);
	if (vini)
	{
		soha->vini = vini;
		fork_cmd(soha);
	}
	else
	{
		if ((interactive(soha) || _getenv(soha, "PATH="))
			|| (soha->argv[0][0] == ('/') && is_cmd(soha, soha->argv[0]))

			|| (soha->argv[0][0] == ('/') && is_cmd(soha,

soha->argv[0])))

			fork_cmd(soha);
		else if (*(soha->arg) != '\n')
		{
			soha->status = 127;
			print_error(soha, "not found\n");
		}
	}
}

/**
 * fork_cmd - forcs the file
 * @soha: the parameter returns soha
 *
 * Return: void
 */
void fork_cmd(info_t *soha)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(soha->path, soha->argv, get_environ(soha))
== -1)
		{
			free_info(soha, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(soha->status));
		if (WIFEXITED(soha->status))
		{
			soha->status = WEXITSTATUS(soha->status);
			if (soha->status == 126)
				print_error(soha, "Permission denied\n");
		}
	}
}
