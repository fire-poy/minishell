*flux = stream*
opendir, fdopendir - Ouvrir un répertoire  

## SYNOPSIS

**#include <[sys/types.h](file:/usr/include/sys/types.h)>**

**#include <[dirent.h](file:/usr/include/dirent.h)>**

**DIR *opendir(const char ***_name_**);**
**DIR *fdopendir(int** _fd_**);**

  

## DESCRIPTION

La fonction **opendir**() ouvre un flux répertoire correspondant au répertoire _name_, et renvoie un pointeur sur ce flux. Le flux est positionné sur la première entrée du répertoire.

La fonction **fdopendir**() est similaire à **opendir**(), mais renvoie un flux répertoire pour le répertoire référencé par le descripteur de fichier ouvert _fd_. Après un appel réussi à **fdopendir**(), _fd_ est utilisé par l'implémentation de manière interne et ne doit donc plus être utilisé par l'application.  

## VALEUR RENVOYÉE

Les fonctions **opendir**() et **fdopendir**() renvoient un pointeur sur le flux répertoire ou NULL si une erreur se produit, auquel cas _errno_ contient le code d'erreur.  

## ERREURS

**EACCES**

Accès interdit.

**EBADF**

_fd_ n'est pas un descripteur de fichier ouvert en lecture valide.

**EMFILE**

Trop de descripteurs de fichier pour le processus appelant.

**ENFILE**

Trop de fichiers ouverts simultanément sur le système.

**ENOENT**

Le répertoire n'existe pas, ou _name_ est une chaîne vide.

**ENOMEM**

Pas assez de mémoire pour terminer l'opération.

**ENOTDIR**

_name_ n'est pas un répertoire

  

## VERSIONS

**fdopendir**() est disponible dans la glibc depuis la version 2.4.  

## CONFORMITÉ

**opendir**() est présente sur SVr4 et BSD 4.3, et est spécifiée par POSIX.1-2001. **fdopendir**() est en attente d'inclusion dans la prochaine version de POSIX.1.  

## NOTES

Le descripteur sous-jacent à un flux répertoire peut être obtenu avec **[dirfd](http://manpagesfr.free.fr/man/man3/dirfd.3.html)**(3).

La fonction **opendir**() définit l'attribut « close-on-exec » pour le descripteur de fichier sous-jacent à _DIR *_. La fonction **fdopendir**() laisse inchangée la configuration de l'attribut « close-on-exec » pout le descripteur de fichier _fd_.  

## VOIR AUSSI

**[open](http://manpagesfr.free.fr/man/man2/open.2.html)**(2), **[closedir](http://manpagesfr.free.fr/man/man3/closedir.3.html)**(3), **[dirfd](http://manpagesfr.free.fr/man/man3/dirfd.3.html)**(3), **[readdir](http://manpagesfr.free.fr/man/man3/readdir.3.html)**(3), **[rewinddir](http://manpagesfr.free.fr/man/man3/rewinddir.3.html)**(3), **[scandir](http://manpagesfr.free.fr/man/man3/scandir.3.html)**(3), **[seekdir](http://manpagesfr.free.fr/man/man3/seekdir.3.html)**(3), **[telldir](http://manpagesfr.free.fr/man/man3/telldir.3.html)**(3)