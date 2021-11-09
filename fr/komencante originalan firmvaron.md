---
lang: fr
lang-niv: fonto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Fonctionnement du micrologiciel originel'
---

le micrologiciel est constitué de 6 partitions :

| partition   | type                   | rôle          |
| ----------- | ---------------------- | ------------- |
| _mtdblock0_ | _u-boot_               | démarrage     |
| _mtdblock1_ | texte                  | paramètres    |
| _mtdblock2_ | _u-boot legacy uImage_ | noyau _linux_ |
| _mtdblock3_ | _squashfs_             | _/_           |
| _mtdblock4_ | _squashfs_             | _/ipc_        |
| _mtdblock5_ | _jffs1_                | _/opt_        |

Le premier programme exécuté est _/linuxrc_.  
Il lance _/etc/init.d/rcS_.  
_/etc/init.d/rcS_ lance _/ipc/etc/auto\_run.sh_.  
_/ipc/etc/auto\_run.sh_ lance _/opt/etc/local.rc_ avant de lancer _/ipc/app/jco\_server_.  
_/ipc/app/jco\_server_ est le programme principal : il sert à la fois de serveur _rtsp_, de serveur _http_, ...

