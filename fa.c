#include "shell.h"
/**
* _myexit - exits the shell
* @tach: var kankhadmo bih
*  Return: katkherej bchi hakawe bchi haka
*/
int _myexit(info_t *tach)
{
int exit;
if (tach->argv[1])
{
exit = _erratoi(tach->argv[1]);
if (exit == -1)
{
tach->status = 2;
print_error(tach, "Illegal number: ");
_eputs(tach->argv[1]);
_eputchar('\n');
return (1);
}
tach->err_num = _erratoi(tach->argv[1]);
return (-2);
}
tach->err_num = -1;
return (-2);
}

/**
* _mycd - changes the current directory of the process
* @tach: S variable ma7tot hena
*  Return: dima 0
*/
int _mycd(info_t *tach)
{
char *es, *diro, buffer[1024];
int chdir_ret;

es = getcwd(buffer, 1024);
if (!es)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!tach->argv[1])
{
diro = _getenv(tach, "HOME=");
if (!diro)
chdir_ret = /* TODO: what should this be? */
chdir((diro = _getenv(tach, "PWD=")) ? diro : "/");
else
chdir_ret = chdir(diro);
}
else if (_strcmp(tach->argv[1], "-") == 0)
{
if (!_getenv(tach, "OLDPWD="))
{
_puts(es);
_putchar('\n');
return (1);
}
_puts(_getenv(tach, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((diro = _getenv(tach, "OLDPWD=")) ? diro : "/");
}
else
chdir_ret = chdir(tach->argv[1]);
if (chdir_ret == -1)
{
print_error(tach, "can't cd to ");
_eputs(tach->argv[1]), _eputchar('\n');
}
else
{
_setenv(tach, "OLDPWD", _getenv(tach, "PWD="));
_setenv(tach, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* _myhelp - changes the current directory of the process
* @tach: nefss l variable
*  Return: dima 0
*/
int _myhelp(info_t *tach)
{
char **arg_array;

arg_array = tach->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
