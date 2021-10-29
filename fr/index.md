---
lang: fr
lang-niv: fonto
lang-ref: 000-indekso
layout: page
title: 'Présentation'
---

Le but de ce projet est de créer un micrologiciel alternatif pour cette caméra :

marque = _WIFI CARAM_  
modèle : _WF-HD820-ZS_  
résolution : _1080P_

Informations affichées dans l'interface web :
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

processeur : _ingenic T21_
capteur vidéo : _GC2053_

# Micrologiciel alternatif

## Ce qui fonctionne dans le micrologiciel alternatif :

* _LAN_ et _WLAN_
* Serveur _RTSP_ double-flux : _1920x1080 H264_ et _640x360 MJPEG_ par défaut._
* Paramètres vidéo
* Serveur _HTTP_
* contrôle moteur
* étalonnage du moteur
* Paramètres _PTZ_
* Client _NTP_
* gestion des mots de passe _http_, _rtsp_ et système.
* contrôle DEL blanche et IR
* Serveur _ftp_
* Serveur _telnet_
* Serveur et client _ssh_
* détection de mouvement
* envoi de courriel
* envoi de _«telegram»_
* mode nocturne automatique

## Ce qui n'est pas implémenté dans le micrologiciel alternatif:

* systeme audio
* _OSD_
* mise à jour du micrologiciel
* _ir-cut_
* _mqtt_
* envoi des images et vidéos dans le cloud
* etc ...

## Installation du micrologiciel alternatif

* Copiez tout ce qui se trouve dans le dossier [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) à la racine de la carte microSD.
* éventuellement configurez le réseau ( _www/ipcam/config.dist/reto.conf_ )
* Insérez la carte _microSD_ dans la caméra.
* Connectez la caméra à votre réseau local et allumez la caméra.
* Trouvez l'adresse IP de la caméra. Vous pouvez aussi vous connecter au wifi de la caméra (SSID : _HSIPC-******_), dans ce cas l'IP est _172.25.0.1_.
* Connectez-vous à la caméra via `telnet IP 9527` (utilisateur _root_, mot de passe _jco66688_), dans les 5 minutes après avoir allumé la caméra.
* Faites `killall -9 auto_run.sh` pour éviter de perdre la connexion.
* Faites `cd /opt/media/mmcblk0p1;./install.sh`
* La caméra reboote, maintenant :
    * Vous pouvez vous connecter à l'URL _https://IP_ (utilisateur _admin_, mot de passe _ismart21_).
    * Vous pouvez vous connecter en ssh (utilisateur _admin_, mot de passe _ismart12_).
    * le flux vidéo primaire est accessible à _rtsp://admin:ismart21@IP/stream1_.
    * le flux vidéo secondaire est accessible à _rtsp://admin:ismart21@IP/stream2_.
    * le mode WiFi AP est activé par défaut :
    ** SSID : ipcam100-xxxxxx
    ** clé WPA2 : ismart21
    ** adresse IP de la caméra : 172.25.0.1

## Désinstallation du micrologiciel alternatif:

* lancez le service ssh sur la caméra par l'interface web (lancé par défaut).
* Connectez-vous à la caméra via `ssh root@IP` (mot de passe _ismart12_).
* Faites `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`

* Vous pouvez aussi simplement retirer la carte microSD.

# Documents intéressants

Beaucoup de travail a été fait pour les caméras équipées d'un processeur _ingenic T20_ :
* micrologiciel modifié : <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* sources du micrologiciel modifié : <https://github.com/Dafang-Hacks/Main>
* autre micrologiciel : <https://github.com/openmiko/openmiko>
* lancement de programmes sans changer le micrologiciel : <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>

