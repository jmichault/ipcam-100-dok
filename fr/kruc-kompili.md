---
lang: fr
lang-niv: fonto
lang-ref: 050-kruc-compili
layout: page
title: 'Compilation croisée'
---


Les outils de compilation croisée se trouvent dans _programada\_medio/toolchain_.
Ils ont été compilés pour _debian buster x64_.

les librairies partagées sont dans _programada\_medio/lib_

les _include_ sont dans _programada\_medio/include_.

Si vous avez besoin de recompiler une librairie, inspirez-vous des scripts suivants :
* _programada\_medio/fontoj/01-buildssl.sh_ , pour la librairie _openssl_.
* _programada\_medio/fontoj/02-buildlive.sh_ , pour la librairie _live555_.
* _programada\_medio/fontoj/03-pcre.sh_ , pour la librairie _pcre_.


Si jamais vous avez besoin de recompiler la _«toolchain»_, vous pouvez consulter le site suivant :
 * <https://github.com/anmaped/openfang>


