---
lang: ms
lang-niv: auto
lang-ref: 005-kruc-compili
layout: page
title: 'Penyusunan silang'
---



sumber:
 * <https://znanev.github.io/Cross-compile-tools-for-Ingenic-T20/>  
 * <https://github.com/Dafang-Hacks/Main>




# pemasangan penyusun:
## pilihan 1: dengan docker (lebih cepat dipasang, lebih perlahan untuk memulakan)

```
sudo apt install docker.io
sudo usermod -aG docker mia_uzanto
 se déconnecter puis se reconnecter
mkdir ~/dafang
cd ~/dafang
docker run --rm -ti -v $(pwd):/root/ daviey/dafang-cross-compile:latest
```

## pilihan 2: secara tempatan (lebih lama untuk dipasang, lebih cepat dilaksanakan)

```
sudo apt install build-essential git gcc-mips-linux-gnu autoconf libtool cmake ftp-upload u-boot-tools
mkdir -p ~/dafang/Main/mips-gcc472-glibc216-64bit
ln -s /usr/bin ~/dafang/Main/mips-gcc472-glibc216-64bit
```

# penyusunan perpustakaan dan _v4l2rtspserver-master_

```
git clone --recurse-submodules https://github.com/Dafang-Hacks/Main.git
cd Main
./compile_libraries.sh
cd v4l2rtspserver-master
./compile.sh
```

