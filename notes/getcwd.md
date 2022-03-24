getcwd, getwd, get_current_dir_name - Obtenir le répertoire de travail courant  

## SYNOPSIS

**#include <[unistd.h](file:/usr/include/unistd.h)>**

**char \***getcwd(char \**_buf_*, size\_t** _size_**);

**char *getwd(char ***_buf_**);**

**char *get_current_dir_name(void);**

Exigences de macros de test de fonctionnalités pour la glibc (voir **[feature_test_macros](http://manpagesfr.free.fr/man/man7/feature_test_macros.7.html)**(7)) :

**getcwd**() : _BSD_SOURCE || _XOPEN_SOURCE >= 500  
**get_current_dir_name**() : _GNU_SOURCE  

## DESCRIPTION

==La fonction **getcwd**() copie le chemin d'accès absolu du répertoire de travail courant dans la chaîne pointée par _buf_, qui est de longueur _size_.==

Si le chemin du répertoire en cours nécessite un tampon plus long que _size_ octets, la fonction renvoie NULL, et _errno_ contient le code d'erreur **ERANGE**. Une application doit détecter cette erreur et allouer un tampon plus grand si besoin est.

Si _buf_ est NULL, le comportement de **getcwd**() est indéfini.

Comme extension de la norme POSIX.1-2001, la version Linux (libc4, libc5, glibc) de **getcwd**() alloue le tampon dynamiquement, en utilisant **[malloc](http://manpagesfr.free.fr/man/man3/malloc.3.html)**(3), si _buf_ est NULL lors de l'appel. Dans ce cas, le tampon alloué a la longueur _size_ à moins que _size_ soit égal à zéro, auquel cas _buf_ est alloué avec la taille nécessaire. Il est possible (et même fortement conseillé) de libérer le tampon avec **[free](http://manpagesfr.free.fr/man/man3/free.3.html)**(3) lorsqu'il a été obtenu ainsi.

**get_current_dir_name**() allouera avec **[malloc](http://manpagesfr.free.fr/man/man3/malloc.3.html)**(3) une chaîne suffisamment grande pour contenir le nom du répertoire. Si la variable d'environnement **PWD** est configurée, et correcte, cette valeur sera renvoyée.

**getwd**() n'allouera aucune mémoire. L'argument _buf_ doit être un pointeur sur une chaîne comportant au moins **PATH_MAX** octets. **getwd**() ne renverra que les **PATH_MAX** premiers octets du chemin. Notez que **PATH_MAX** n'est pas nécessairement une constante à la compilation. Elle peut dépendre du système de fichiers, voire être illimitée. Pour des raisons de portabilité et de sécurité, on déconseille l'utilisation de **getwd**().  

## VALEUR RENVOYÉE

NULL en cas d'échec, avec _errno_ contenant le code d'erreur. En cas de réussite _buf_ est renvoyé. Le contenu de la chaîne pointée par _buf_ est indéfini en cas d'erreur.  

## ERREURS

**EACCES**

Impossible de lire ou de parcourir un composant du chemin d'accès.

**EFAULT**

_buf_ pointe sur une adresse illégale.

**EINVAL**

L'argument _size_ vaut zéro et _buf_ n'est pas un pointeur NULL.

**ENOENT**

Le répertoire en cours a été supprimé.

**ERANGE**

L'argument _size_ est inférieur à la longueur du nom du répertoire. Allouez un tampon plus grand et réessayez.

  

## CONFORMITÉ

**getcwd**() est conforme à POSIX.1-2001. **getwd**() est présente dans POSIX.1-2001, mais marquée comme HISTORIQUE. **get_current_dir_name**() est une extension GNU.  

## NOTES

Sous Linux, la fonction **getcwd**() est un appel système (depuis le 2.1.92). Sur des systèmes plus anciens, elle interrogerait _/proc/self/cwd_. Si l'appel système et le système de fichiers proc sont absents, une implémentation générique est utilisée. Dans ce cas seulement la fonction peut renvoyer **EACCES** sous Linux.

Ces fonctions sont souvent utilisées pour sauver le répertoire de travail afin d'y revenir plus tard. Ouvrir le répertoire courant (« . ») et appeler **[fchdir](http://manpagesfr.free.fr/man/man2/fchdir.2.html)**(2) pour y revenir est habituellement une alternative plus rapide et plus fiable (surtout sur d'autres systèmes que Linux) si l'on dispose de suffisamment de descripteurs de fichier.  

## VOIR AUSSI

**[chdir](http://manpagesfr.free.fr/man/man2/chdir.2.html)**(2), **[fchdir](http://manpagesfr.free.fr/man/man2/fchdir.2.html)**(2), **[open](http://manpagesfr.free.fr/man/man2/open.2.html)**(2), **[unlink](http://manpagesfr.free.fr/man/man2/unlink.2.html)**(2), **[free](http://manpagesfr.free.fr/man/man3/free.3.html)**(3), **[malloc](http://manpagesfr.free.fr/man/man3/malloc.3.html)**(3),  

## TRADUCTION

Ce document est une traduction réalisée par Christophe Blaess <[http://www.blaess.fr/christophe/](http://www.blaess.fr/christophe/)> le 26 octobre 1996 et révisée le 17 juillet 2008.

L'équipe de traduction a fait le maximum pour réaliser une adaptation française de qualité. La version anglaise la plus à jour de ce document est toujours consultable via la commande : « **LANG=C man 3 getcwd** ». N'hésitez pas à signaler à l'auteur ou au traducteur, selon le cas, toute erreur dans cette page de manuel.