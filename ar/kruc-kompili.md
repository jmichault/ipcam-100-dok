---
lang: ar
lang-niv: auto
lang-ref: 005-kruc-compili
layout: page
title: 'عبر التجميع'
---



المصادر:
 * <https://znanev.github.io/Cross-compile-tools-for-Ingenic-T20/>  
 * <https://github.com/Dafang-Hacks/Main>




# تركيب المجمعات:
## الخيار 1: مع عامل إرساء (أسرع في التثبيت ، وأبطأ في البدء)

```
sudo apt install docker.io
sudo usermod -aG docker mia_uzanto
 se déconnecter puis se reconnecter
mkdir ~/dafang
cd ~/dafang
docker run --rm -ti -v $(pwd):/root/ daviey/dafang-cross-compile:latest
```

## الخيار 2: محليًا (أطول للتثبيت ، أسرع في التنفيذ)

```
sudo apt install build-essential git gcc-mips-linux-gnu autoconf libtool cmake ftp-upload u-boot-tools
mkdir -p ~/dafang/Main/mips-gcc472-glibc216-64bit
ln -s /usr/bin ~/dafang/Main/mips-gcc472-glibc216-64bit
```

# تجميع المكتبات و _v4l2rtspserver-master_

```
git clone --recurse-submodules https://github.com/Dafang-Hacks/Main.git
cd Main
./compile_libraries.sh
cd v4l2rtspserver-master
./compile.sh
```

