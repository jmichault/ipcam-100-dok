---
lang: hi
lang-niv: auto
lang-ref: 005-kruc-compili
layout: page
title: 'क्रॉस संकलन'
---



स्रोत:
 * <https://znanev.github.io/Cross-compile-tools-for-Ingenic-T20/>  
 * <https://github.com/Dafang-Hacks/Main>




# संकलक की स्थापना:
## विकल्प 1: डॉक के साथ (तेजी से स्थापित करने के लिए, संचालित करने के लिए धीमा)

```
sudo apt install docker.io
sudo usermod -aG docker mia_uzanto
 se déconnecter puis se reconnecter
mkdir ~/dafang
cd ~/dafang
docker run --rm -ti -v $(pwd):/root/ daviey/dafang-cross-compile:latest
```

## विकल्प 2: स्थानीय रूप से (लंबे समय तक स्थापित होना, तेजी से निष्पादित करने के लिए)

```
sudo apt install build-essential git gcc-mips-linux-gnu autoconf libtool cmake ftp-upload u-boot-tools
mkdir -p ~/dafang/Main/mips-gcc472-glibc216-64bit
ln -s /usr/bin ~/dafang/Main/mips-gcc472-glibc216-64bit
```

# पुस्तकालयों का संकलन और _v4l2rtspserver-master_

```
git clone --recurse-submodules https://github.com/Dafang-Hacks/Main.git
cd Main
./compile_libraries.sh
cd v4l2rtspserver-master
./compile.sh
```

