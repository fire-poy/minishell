#include "../minishell.h"

int	is_exec_file(char *name)
{
	return (ft_strncmp(name, "./", 2) == 0 || name[0] == '/');
}

// retourne 1 si name est un répertoire 
int	is_directory(char *name)
{
	struct stat	statbuf;

	if (stat(name, &statbuf) != 0)
		return (0);
	return ((S_ISDIR(statbuf.st_mode) && ft_strchr(name, '/') != 0));
}

// retourn 1 si name n'a pas d'accès d'execution
int	is_file_permission_denied(char *name)
{
	return (access(name, X_OK) == -1);
}

// retourn 1 si name est un fichier executable et qu'il n'est pas trouvé
int	is_file_not_found(char *name)
{
	return (is_exec_file(name) && access(name, F_OK) == -1);
}

int	is_invalid_command(t_info *info, char *cmd_name)
{
	if (is_directory(cmd_name))
	{
		cmd_err(info, cmd_name, MSG_IS_DIRECTORY, 126);
		return (1);
	}
	else if (is_file_not_found(cmd_name))
	{
		cmd_err(info, cmd_name, MSG_FILE_NOT_FOUND, 127);
		return (1);
	}
	return (0);
}
	// else if (is_file_permission_denied(cmd_name))
	// 	cmd_err(info, cmd_name, MSG_PERMISSION_DENIED, 126);
