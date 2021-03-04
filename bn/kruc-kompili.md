---
lang: bn
lang-niv: auto
lang-ref: 005-kruc-compili
layout: page
title: 'ক্রস সংকলন'
---



উত্স:
 * <https://znanev.github.io/Cross-compile-tools-for-Ingenic-T20/>  
 * <https://github.com/Dafang-Hacks/Main>




# সংকলক ইনস্টলেশন:
## বিকল্প 1: ইনস্টল করতে ডকারের সাথে (° 1 faster) দ্রুত, শুরু করতে ধীর)

```
sudo apt install docker.io
sudo usermod -aG docker mia_uzanto
 se déconnecter puis se reconnecter
mkdir ~/dafang
cd ~/dafang
docker run --rm -ti -v $(pwd):/root/ daviey/dafang-cross-compile:latest
```

## বিকল্প 2: স্থানীয়ভাবে (ইনস্টল করতে দীর্ঘতর, কার্যকর করার জন্য দ্রুত)

```
sudo apt install build-essential git gcc-mips-linux-gnu autoconf libtool cmake ftp-upload u-boot-tools
mkdir -p ~/dafang/Main/mips-gcc472-glibc216-64bit
ln -s /usr/bin ~/dafang/Main/mips-gcc472-glibc216-64bit
```

# গ্রন্থাগার সংকলন এবং _v4l2rtspserver-master_

```
git clone --recurse-submodules https://github.com/Dafang-Hacks/Main.git
cd Main
./compile_libraries.sh
cd v4l2rtspserver-master
./compile.sh
```

