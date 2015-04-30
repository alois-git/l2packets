## Linking ##
### Win32-mingw, Linux ###
Link application with libL2Packets.a.
Also, because library uses OpenSSL crypto API, you will need openSSL's libs for mingw.
OpenSSL may require linking to winsock, so add also ws2\_32.
You will have something like that:
`g++ .... -lL2Packets -lssl32 -leay32 -lws2_32 ...` or
`g++ .... -lL2Packets -lssl -lcrypto -lws2_32 ...`.

Under Linux, command line will look the same, except that you don't need -lws2\_32; and openssl headers/libs usually already exist in your system.

### Win32-VC ###
Link application with L2Packets.lib.
Also, because library uses OpenSSL crypto API, you will need openSSL's libs for vc, built using the **same C-Runtime** as L2Packets uses. (L2Packets uses statically linked Multi-Threading CRT in Release build (/MT), and static Multi-Threading Debug CRT in Debug build (/MTd)). See [Compile OpenSSL in VC](http://code.google.com/p/l2packets/wiki/CompileOpenSSLinVC). Later I will add my compiled and working openssl static-MT libs for vc2008...
Also, OpenSSL may require linking to winsock, so add also ws2\_32.lib.