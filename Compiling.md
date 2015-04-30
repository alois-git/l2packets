# Supported OS, compilers #
At this moment L2Packets is tested only under Win32, but it can be compiled under Linux.
Win32: There are 2 ways of compiling: [Mingw32](http://www.mingw.org/) and [Visual C++](http://www.microsoft.com/express/vc/).
Linux: tested to compile OK with gcc4.


# Mingw32 #
Download source archive, in console cd into subdir **project\_mingw32**, execute:
> `make_release.bat`
or
> `mingw32-make -s -f Makefile_release.mingw32`
Result static library will be in folder **dist/Release/mingw32**.
Building as DLL is not supported now (no real need, imho).

# Visual C++ #
In folder **project\_vc** open file L2Packets.sln with Visual Studio, choose build configuration **Release|Win32**, and build solution. Project is provided for vc2008 express. Result static library will be in folder **dist/Release/vc**.
Debug build by default uses /MTd (Multi-threaded debug) C runtime, release - /MT.
Building as DLL is not supported now (no real need, imho).

# Linux #
cd into folder **project\_linux** and execute
> `make -f Makefile_release.`
Result library will be in folder **dist/Release/linux**.


# sqlite3 compile warnings #
Yes, during build you will see lots of warnings in file sqlite3.c. sqlite devs think it is normal, see [(17) I get hundreds of compiler warnings when I compile SQLite. Isn't this a problem? Doesn't it indicate poor code quality?](http://www.sqlite.org/faq.html#q17)