[readline](https://tiswww.case.edu/php/chet/readline/readline.html "https://tiswww.case.edu/php/chet/readline/readline.html")
[Here doc](https://linuxize.com/post/bash-heredoc/)
[bash officiel](https://www.gnu.org/software/bash/manual/bash.html#Here-Documents)

Vous avez trouve un moyen de pas afficher ^\ quand on fait un control + \? Quand je catch le sigquit il m'affiche toujours ca, et j'ai teste different trucs j'arrive pas a faire qu'il ne s'affiche pas

Echoctl avec Termios bloque ce genre de symbol

Et avec ctrl \ tu peux juste faire un SIGIGN pas besoin de faire une fonction

Après faut mettre le terminal enfin «‘affichage à jour avec tcs set attribut je crois

pour enlever  `^C` du `ctrl-c`
```
tcsetattr(int, int, const struct termios *);
```

utilité pour isatty, ttyname et ttyslot? 
Je les utilise pour le path moi le opendir etc.
et pour le *

##### l'utilite de isatty : 
Pour tcgetattr tu dois lui passer un fd, mais tu dois verifier avant que c'est bien un terminal

Je suppose que cela peut avoir son utilité dans un process different

Car sinon le fd sera STDOUT FILENO

Faut check stderr, stdout et stdin

Parce que si je lance le minishell avec ca: `./minishell > out` ton truc va crash

*hajar*
!isatty(0) || isatty(1) donc exit failure

on savait juste pas qu'il y avait des cas ou on devais pas wait en effet, juste pour tester j'ai mis une petite condition `si c'est ls , fais pas wait` et ca reproduit la comportement de bash

[pipelines](https://www.gnu.org/software/bash/manual/bash.html#Pipelines "https://www.gnu.org/software/bash/manual/bash.html#Pipelines")

> If the pipeline is not executed asynchronously (see Lists), the shell waits for all commands in the pipeline to complete.

 *msegrans!*
hmm pas sur que ca aide vraiment comme on gere pas vraiment ces options la

J'ai decouvert d'ailleur que il faut fork les built-ins si on pipe

`exit | less` exit pas

par contre faut gérer les redirections d'EOF genre grep a << EOF

--
Vous avez fait comment avec les chaines entre guillemet qui ne sont pas fermé ? Vous affichez un message d'erreur ?
*hsabir*
Oui un message d'erreur

