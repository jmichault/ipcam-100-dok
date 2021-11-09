---
lang: es
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Operación del firmware original.'
---

El firmware consta de 6 vándalos:  

| partición | Tipo | papel |  
 | ----------- | ---------------------- | ------------- |  
 |   _mtdblock0_   |   _u-boot_                 | Inicio |  
 |   _mtdblock1_   | Texto | Configuración |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | Núcleo   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

El primer programa ejecutado es   _/linuxrc_.    
 El lanza   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   lanza   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   Lanco   _/opt/etc/local.rc_   Antes de lanzar   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   es el programa principal: Sirve tanto el servidor   _rtsp_ , el servidor   _http_, ...  

