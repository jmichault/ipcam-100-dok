---
lang: pt
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Operação do firmware original'
---

O firmware consiste em 6 vândalos:  

| Partição. Tipo | Função  
 | ----------- | ---------------------- | ------------- |  
 |   _mtdblock0_   |   _u-boot_                 | Iniciando  
 |   _mtdblock1_   | Texto Configurações |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | Core   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

O primeiro programa executado é   _/linuxrc_.    
 Ele lança   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   lança   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   LANCO   _/opt/etc/local.rc_   antes de lançar   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   é o programa principal: serve tanto   _rtsp_  server, servidor   _http_, ...  

