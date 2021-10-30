---
lang: pt
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'Firmware alternativo'
---

# Comece

* A instalação cria o arquivo _/opt/etc/local.rc_que o firmware original inicia.


* _local.rc_ inicia _run.sh_ a partir do cartão SD.



# _run.sh_

  * desconecte a rede


  * parar _jco_servidor_ e _autorun.sh_.


  * desativa _/dev/watchdog_ e _/dev/watchdog0_


  * os LEDs e o motor são inicializados


  * inicialize o diretório etc. se necessário


  * redireciona _/bin/busybox_ , _/etc_ e _/root_ para o cartão SD.


  * padrão para _CRONTAB_ se necessário


  * iniciar serviços (em _config/autostart_)


  * começar a usar scripts (em _config/userscripts_)


