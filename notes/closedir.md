closedir - Fermer un répertoire  

## SYNOPSIS

**#include <[sys/types.h](file:/usr/include/sys/types.h)>**

**#include <[dirent.h](file:/usr/include/dirent.h)>**

**int closedir(DIR ***_dir_**);**

  

## DESCRIPTION

La fonction **closedir**() ferme le flux de répertoire associé à _dir_. Après cette invocation, le descripteur _dir_ du flux de répertoire n'est plus disponible.  

## VALEUR RENVOYÉE

La fonction **closedir**() renvoie 0 si elle réussit, ou -1 si elle échoue, auquel cas _errno_ contient le code d'erreur.  

## ERREURS

**EBADF**

Le descripteur de flux de répertoire _dir_ n'est pas valide.

  

## CONFORMITÉ

SVr4, POSIX.1-2001, BSD 4.3.  

## VOIR AUSSI

**[close](http://manpagesfr.free.fr/man/man2/close.2.html)**(2), **[opendir](http://manpagesfr.free.fr/man/man3/opendir.3.html)**(3), **[readdir](http://manpagesfr.free.fr/man/man3/readdir.3.html)**(3), **[rewinddir](http://manpagesfr.free.fr/man/man3/rewinddir.3.html)**(3), **[scandir](http://manpagesfr.free.fr/man/man3/scandir.3.html)**(3), **[seekdir](http://manpagesfr.free.fr/man/man3/seekdir.3.html)**(3), **[telldir](http://manpagesfr.free.fr/man/man3/telldir.3.html)**(3)  

## TRADUCTION

Ce document est une traduction réalisée par Christophe Blaess <[http://www.blaess.fr/christophe/](http://www.blaess.fr/christophe/)> le 23 octobre 1996 et révisée le 17 juillet 2008.

L'équipe de traduction a fait le maximum pour réaliser une adaptation française de qualité. La version anglaise la plus à jour de ce document est toujours consultable via la commande : « **LANG=C man 3 closedir** ». N'hésitez pas à signaler à l'auteur ou au traducteur, selon le cas, toute erreur dans cette page de manuel.