---
lang: zh
lang-niv: auto
lang-ref: 005-kruc-compili
layout: page
title: 交叉编译
---



来源：
 * <https://znanev.github.io/Cross-compile-tools-for-Ingenic-T20/>  
 * <https://github.com/Dafang-Hacks/Main>




# 安装编译器：
## 选项1：使用docker (，安装速度更快，启动速度更慢)

```
sudo apt install docker.io
sudo usermod -aG docker mia_uzanto
 se déconnecter puis se reconnecter
mkdir ~/dafang
cd ~/dafang
docker run --rm -ti -v $(pwd):/root/ daviey/dafang-cross-compile:latest
```

## 选项2：本地安装 (的时间更长，执行速度更快)

```
sudo apt install build-essential git gcc-mips-linux-gnu autoconf libtool cmake ftp-upload u-boot-tools
mkdir -p ~/dafang/Main/mips-gcc472-glibc216-64bit
ln -s /usr/bin ~/dafang/Main/mips-gcc472-glibc216-64bit
```

# 库和 _v4l2rtspserver-master_的汇编

```
git clone --recurse-submodules https://github.com/Dafang-Hacks/Main.git
cd Main
./compile_libraries.sh
cd v4l2rtspserver-master
./compile.sh
```

