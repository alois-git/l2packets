@echo off
@rem Create directory with only header files
set dn=L2Packets_inc
set src=..\src

if not exist %dn% goto createtree
:deletetree
del /s /q %dn%
rmdir /s /q %dn%
echo Deleted existing dir tree

:createtree
mkdir %dn%
mkdir %dn%\base
mkdir %dn%\game
mkdir %dn%\game\client
mkdir %dn%\game\server
mkdir %dn%\l2data
mkdir %dn%\l2world
mkdir %dn%\login
mkdir %dn%\login\client
mkdir %dn%\login\server
mkdir %dn%\net_io
mkdir %dn%\packetNames
mkdir %dn%\pcode_obfuscator
echo Created dir tree

:copy
copy %src%\L2Packets.h %dn%\L2Packets.h > NUL
rem base
copy %src%\base\ByteArray.h %dn%\base\ByteArray.h > NUL
copy %src%\base\L2BasePacket.h %dn%\base\L2BasePacket.h > NUL
rem game
copy %src%\game\L2GamePacket.h %dn%\game\L2GamePacket.h > NUL
copy %src%\game\client\*.h %dn%\game\client > NUL
copy %src%\game\server\*.h %dn%\game\server > NUL
rem l2data
copy %src%\l2data\L2Data.h %dn%\l2data\L2Data.h > NUL
copy %src%\l2data\L2Data_Recipes.h %dn%\l2data\L2Data_Recipes.h > NUL
rem l2world
copy %src%\l2world\*.h %dn%\l2world > NUL
rem login
copy %src%\login\L2LoginPacket.h %dn%\login\L2LoginPacket.h > NUL
copy %src%\login\client\*.h %dn%\login\client > NUL
copy %src%\login\server\*.h %dn%\login\server > NUL
rem net_io
copy %src%\net_io\*.h %dn%\net_io > NUL
rem packetNames
copy %src%\packetNames\L2PacketNames.h %dn%\packetNames\L2PacketNames.h > NUL
rem pcode_obfuscator
copy %src%\pcode_obfuscator\L2PCodeObfuscator.h %dn%\pcode_obfuscator\L2PCodeObfuscator.h > NUL

echo Copy headers complete to %dn%

pause

