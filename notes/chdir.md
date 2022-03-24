## SYNOPSIS

**#include <[unistd.h](file:/usr/include/unistd.h)>**

**int chdir(const char ***_path_**);**  
**int fchdir(int** _fd_**);**

Exigences de macros de test de fonctionnalités pour la glibc (voir **[feature_test_macros](http://manpagesfr.free.fr/man/man7/feature_test_macros.7.html)**(7)) :

**fchdir**() : _BSD_SOURCE || _XOPEN_SOURCE >= 500  

## DESCRIPTION

**chdir**() remplace le répertoire de travail courant du processus appelant par celui indiqué dans le chemin _path_.

**fchdir**() est identique à **chdir**(), sauf que le répertoire cible est fourni sous forme de descripteur de fichier.  

## VALEUR RENVOYÉE

Ces appels renvoient 0 s'ils réussissent, ou -1 s'ils échouent, auquel cas _errno_ est renseignée en conséquence.  

## ERREURS

Suivant le type de système de fichiers, plusieurs erreurs peuvent être renvoyées, les plus courantes pour **chdir**() sont les suivantes :

**EACCES**

L'accès n'est pas autorisé sur un élément du chemin _._ (Voir aussi **[path_resolution](http://manpagesfr.free.fr/man/man7/path_resolution.7.html)**(7).)

**EFAULT**

_path_ pointe en dehors de l'espace d'adressage accessible.

**EIO**

Une erreur d'entrée-sortie s'est produite.

**ELOOP**

_path_ contient une référence circulaire (à travers un lien symbolique).

**ENAMETOOLONG**

_path_ est trop long.

**ENOENT**

Le fichier n'existe pas.

**ENOMEM**

Pas assez de mémoire pour le noyau.

**ENOTDIR**

Un élément du chemin d'accès _path_ n'est pas un répertoire.

Les erreurs courantes pour **fchdir**() sont :

**EACCES**

Le répertoire ouvert sur _fd_ n'autorise pas le parcours.

**EBADF**

_fd_ n'est pas un descripteur de fichier valide.

  

## CONFORMITÉ

SVr4, BSD 4.4, POSIX.1-2001.  

## NOTES

Le répertoire de travail actuel est le point de départ pour l'interprétation des noms de chemins relatifs (ceux qui ne commencent pas par « / »).

Un processus fils créé avec **[fork](http://manpagesfr.free.fr/man/man2/fork.2.html)**(2) hérite du répertoire de travail courant de son père. Le répertoire de travail courant n'est pas modifié par un **[execve](http://manpagesfr.free.fr/man/man2/execve.2.html)**(2).

Le prototype de **fchdir**() n'est disponible que si **_BSD_SOURCE** est définie ou si **_XOPEN_SOURCE** est définie avec la valeur 500.  

## VOIR AUSSI

**[chroot](http://manpagesfr.free.fr/man/man2/chroot.2.html)**(2), **[getcwd](http://manpagesfr.free.fr/man/man3/getcwd.3.html)**(3), **[path_resolution](http://manpagesfr.free.fr/man/man7/path_resolution.7.html)**(7)