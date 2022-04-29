#include "../minishell.h"

int	is_exec_file(char *name)
{
	return (ft_strncmp(name, "./", 2) == 0 || name[0] == '/');
}

/**
 * @brief retourne 1 si name est un répertoire 
 * 
 * @param name 
 * @return int 
 */
int	is_directory(char *name)
{
	struct stat	statbuf;

	if (stat(name, &statbuf) != 0)
		return (0);
	return ((S_ISDIR(statbuf.st_mode) && ft_strchr(name, '/') != 0));
}

/**
 * @brief retourne 1 si name n'a pas d'accès d'execution
 * 
 * @param name 
 * @return int 
 */
int	is_file_permission_denied(char *name)
{
	return (access(name, X_OK) == -1);
}

/**
 * @brief retourne 1 si name est un fichier executable et
 * qu'il n'est pas trouvé
 * 
 * @param name 
 * @return int 
 */
int	is_file_not_found(char *name)
{
	return (is_exec_file(name) && access(name, F_OK) == -1);
}

// /**
//  * @brief retourne 1 si la commande n'est pas trouvée
//  * 
//  * @param path liste des path de l'env PATH
//  * @param name 
//  * @param i 
//  * @return int 
//  */
// int	is_command_not_found(char *path, char **name, int i)
// {
// 	char	*pathname;
// 	char	**paths;

// 	if (is_exec_file(*name) && access(*name, F_OK) != -1)
// 		return (0);
// 	if (!path)
// 		return (1);
// 	paths = ft_split(path, ':');
// 	if (!paths)
// 		return (1);
// 	while (paths[i])
// 	{
// 		pathname = str_joins(paths[i++], (*name), "/");
// 		if (access(pathname, F_OK) != -1)
// 		{
// 			free((*name));
// 			free_array(paths);
// 			(*name) = pathname;
// 			return (0);
// 		}
// 		free(pathname);
// 	}
// 	free_array(paths);
// 	return (1);
// }




int	is_invalid_command(t_info *info, char *cmd_name)
{
	if (is_directory(cmd_name))
	{
		show_command_error(info, cmd_name, MSG_IS_DIRECTORY, 126);
		return (1);
	}
	else if (is_file_not_found(cmd_name))
	{
		show_command_error(info, cmd_name, MSG_FILE_NOT_FOUND, 127);
		return (1);
	}
	// else if (is_command_not_found(get_env(info, "PATH"), &cmd_name, 0))
	// 	show_command_error(info, cmd_name, MSG_COMMAND_NOT_FOUND, 127);
	// else if (is_file_permission_denied(cmd_name))
	// 	show_command_error(info, cmd_name, MSG_PERMISSION_DENIED, 126);
	return (0);
}