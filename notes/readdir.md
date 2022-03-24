readdir, readdir_r - Consulter un répertoire  

## SYNOPSIS

**#include <[dirent.h](file:/usr/include/dirent.h)>**

**struct dirent *readdir(DIR ***_dir_**);**

**int readdir(DIR ***_dir_**, struct dirent ***_entry_**, struct dirent ****_result_**);**

  

## DESCRIPTION

La fonction **readdir**() renvoie un pointeur sur une structure _dirent_ représentant l'entrée suivante du flux répertoire pointé par _dir_. Elle renvoie NULL à la fin du répertoire, ou en cas d'erreur.

Sous Linux, la structure _dirent_ est définie de la façon suivante :

struct dirent {
    ino_t          d_ino;       /* numéro d'inœud */
    off_t          d_off;       /* décalage jusqu'à la dirent suivante */
    unsigned short d_reclen;    /* longueur de cet enregistrement */
    unsigned char  d_type;      /* type du fichier */
    char           d_name[256]; /* nom du fichier */
};

D'après POSIX, la structure _dirent_ contient un champ _char d_name[]_ de taille non spécifiée, avec au plus **NAME_MAX** caractères avant l'octet nul final. POSIX.1-2001 documente aussi le champ _ino_t d_ino_ comme une extension XSI. Les autres champs ne sont pas normalisés et ne sont pas présents sur tous les systèmes ; voir la section NOTES plus loin pour plus de détails.

Les données renvoyées par **readdir**() sont écrasées lors de l'appel suivant à **readdir**() sur le même flux répertoire.

La fonction **readdir_r**() est la version réentrante de **readdir**(). Elle lit la prochaine entrée de répertoire à partir du flux de répertoire _dir_, et la renvoie dans le tampon de l'appelant pointé par _entry_. (Voir la section NOTES pour des informations sur l'allocation de ce tampon.) Un pointeur vers l'élément renvoyé est placé dans _*result_ ; si la fin du flux de répertoire est rencontrée, NULL est renvoyé dans _*result_.  

## VALEUR RENVOYÉE

La fonction **readdir**() renvoie un pointeur sur une structure _dirent_, ou NULL lorsqu'une erreur se produit, ou lorsque la fin du répertoire est atteinte. Si une erreur se produit, _errno_ contient le code d'erreur.

La fonction **readdir_r**() renvoie 0 si elle réussit. Si elle échoue, elle renvoie un code d'erreur positif. Si la fin du répertoire est atteinte, **readdir_r**() renvoie 0 et renvoie NULL dans _*result_.  

## ERREURS

**EBADF**

Le descripteur de flux répertoire _dir_ n'est pas valide.

  

## CONFORMITÉ

SVr4, BSD 4.3, POSIX.1-2001.  

## NOTES

Seuls les champs _d_name_ et _d_ino_ sont spécifiés par POSIX.1-2001. Les autres champs sont disponibles sur beaucoup de systèmes, mais pas sur tous. Avec la glibc, les programmes peuvent vérifier la disponibilité des champs non définis par POSIX.1 en testant si les macros **_DIRENT_HAVE_D_NAMLEN**, **_DIRENT_HAVE_D_RECLEN**, **_DIRENT_HAVE_D_OFF** ou **_DIRENT_HAVE_D_TYPE** sont définies.

Ailleurs que sous Linux, le champ _d_type_ n'est principalement disponible que sur les systèmes BSD. Ce champ permet d'éviter de devoir appeler **[stat](http://manpagesfr.free.fr/man/man2/stat.2.html)**(2) si d'autres actions dépendent du type de fichier. Si la macro de test de fonctionnalités **_BSD_SOURCE** est définie, la glibc définit les constantes suivantes pour la valeur renvoyée dans _d_type_ :

**DT_BLK**

C'est un périphérique de blocs.

**DT_CHR**

C'est un périphérique de caractères.

**DT_DIR**

C'est un répertoire.

**DT_FIFO**

C'est un tube nommé (FIFO).

**DT_LNK**

C'est un lien symbolique.

**DT_REG**

C'est un fichier ordinaire.

**DT_SOCK**

C'est une socket de domaine Unix.

**DT_UNKNOWN**

Le type de fichier est inconnu.

Si le type de fichier ne peut pas être déterminé, la valeur **DT_UNKNOWN** est renvoyée dans _d_type_.

Puisque POSIX.1 ne spécifie pas la taille du champ _d_name_, et que d'autres champs non standard peuvent précéder ce champ dans la structure _dirent_, les applications portables utilisant **readdir_r**() devraient allouer le tampon dont l'adresse est passée dans _entry_ de la façon suivante :

len = offsetof(struct dirent, d_name) +
          pathconf(dirpath, _PC_NAME_MAX) + 1
entryp = malloc(len);

(POSIX.1 demande que _d_name_ soit le dernier champ d'une structure _dirent_.)