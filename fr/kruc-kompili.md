---
lang: fr
lang-niv: fonto
lang-ref: 005-kruc-compili
layout: page
title: 'Compilation croisée'
---


Les outils de compilation croisés se trouvent dans programada_medio/toolchain.
Ils ont été compilés pour debian buster x64.

les librairies partagées sont dans programada_medio/lib

les include sont dans programada_medio/include.

Si vous avez besoin de recompiler une librairie, inspirez-vous des scripts suivants :
* programada_medio/fontoj/01-buildssl.sh , pour la librairie openssl.
* programada_medio/fontoj/02-buildlive.sh , pour la librairie live555.
* programada_medio/fontoj/03-pcre.sh , pour la librairie pcre.


Si jamais vous avez besoin de recompiler la _«toolchain»_, vous pouvez consulter le site suivant :
 * https://github.com/anmaped/openfang


