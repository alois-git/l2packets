# Introduction #

Because L2Packets library uses OpenSLL crypto API, you will need OpenSSL's libs for vc, built using **same C-Runtime** as L2Packets uses.
_(L2Packets uses Multi-Threading CRT in Release build (/MT), and Multi-Threading Debug CRT in Debug build (/MTd))._


# Details #

To compile OpenSSL with Visual Studio, download sources from http://www.openssl.org/source/. Run something like _Start -> All Programs -> MS Visual Studio -> Tools -> Visual Studio Command Promt_. There cd into **folder\_with\_openssl\_sources\ms** and run
```
do_masm.bat
```
After Makefile appears (nt.mak), cancel build. Open nt.mak, edit CFLAGS/CPPFLAGS var: change /MD to /MT :) Then run
```
nmake -f nt.mak clean
nmake -f nt.mak
```

# Warning #
The steps described above are not exact and these instructions may be incomplete or not working :)

# The easy way #
In [downloads\_section](http://code.google.com/p/l2packets/downloads/list) there is a package of openssl libs & headers I used to build applications with (Win32, MS Visual C++)