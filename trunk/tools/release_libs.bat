@echo off
@rem Create directory with only static library files
set dn=L2Packets_lib
set dist=..\dist

if not exist %dn% goto createtree
:deletetree
del /s /q %dn%
rmdir /s /q %dn%
echo Deleted existing dir

:createtree
mkdir %dn%
echo Created dir

copy %dist%\Debug\mingw32\*.a %dn%
copy %dist%\Release\mingw32\*.a %dn%
copy %dist%\Debug\vc\*.lib %dn%
copy %dist%\Release\vc\*.lib %dn%
echo Copy done to %dn%

pause
