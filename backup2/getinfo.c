#include "main.h"

/**
 * clear_inf - reset inf_t struct
 * @inf: struct ptr
 * Return: void
 */

void clear_inf(inf_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes inf_t struct
 * @inf: struct ptr
 * @argv: argumens
 * Return: void
 */

void set_inf(inf_t *inf, char **argv)
{
	int i = 0;

	inf->fname = argv[0];
	/*check for additional args*/
	if (inf->arg)
	{
		/*split input*/
		inf->argv = _strtok1(inf->arg, " \t");
		if (!inf->argv) /*tokenisation failed*/
		{
			/*memory allocation*/
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{ /*assign arguments*/
				inf->argv[0] = strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		/*count args*/
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i; /*count*/
		/*Replace aliases with their corresponding values*/
		replace_alias(inf);
		/*Replace aliases with their corresponding values*/
		replace_vars(inf);
	}
}

/**
 * free_inf - frees inf_t struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void free_inf(inf_t *inf, int all)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_buffer)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
		inf->environ = NULL;
		bfree((void **)inf->cmd_buffer);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(FLUSH);
	}
}

