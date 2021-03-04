---
lang: pa
lang-niv: auto
lang-ref: 005-kruc-compili
layout: page
title: 'ਪਾਰ ਸੰਕਲਨ'
---



ਸਰੋਤ:
 * <https://znanev.github.io/Cross-compile-tools-for-Ingenic-T20/>  
 * <https://github.com/Dafang-Hacks/Main>




# ਕੰਪਾਈਲਰ ਲਗਾਉਣਾ:
## ਵਿਕਲਪ 1: ਡੌਕਰ ਦੇ ਨਾਲ (ਤੇਜ਼ੀ ਨਾਲ ਸਥਾਪਤ ਕਰਨ ਲਈ, ਹੌਲੀ ਹੌਲੀ ਚਾਲੂ)

```
sudo apt install docker.io
sudo usermod -aG docker mia_uzanto
 se déconnecter puis se reconnecter
mkdir ~/dafang
cd ~/dafang
docker run --rm -ti -v $(pwd):/root/ daviey/dafang-cross-compile:latest
```

## ਵਿਕਲਪ 2: ਸਥਾਨਕ ਤੌਰ ਤੇ (ਸਥਾਪਤ ਕਰਨ ਲਈ ਲੰਬਾ, ਚਲਾਉਣ ਲਈ ਤੇਜ਼)

```
sudo apt install build-essential git gcc-mips-linux-gnu autoconf libtool cmake ftp-upload u-boot-tools
mkdir -p ~/dafang/Main/mips-gcc472-glibc216-64bit
ln -s /usr/bin ~/dafang/Main/mips-gcc472-glibc216-64bit
```

# ਲਾਇਬ੍ਰੇਰੀਆਂ ਦਾ ਸੰਗ੍ਰਹਿ ਅਤੇ _v4l2rtspserver-master_

```
git clone --recurse-submodules https://github.com/Dafang-Hacks/Main.git
cd Main
./compile_libraries.sh
cd v4l2rtspserver-master
./compile.sh
```

