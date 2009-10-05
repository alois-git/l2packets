#!/bin/bash
# Create directory with only header files

dn=L2Packets_inc
src=../src

if [ -d $dn ] ; then
  echo "Dir exists" ;
  rm -r $dn ;
  echo "Deleted existing dir tree" ;
fi

mkdir $dn
mkdir $dn/base
mkdir $dn/game
mkdir $dn/game/client
mkdir $dn/game/server
mkdir $dn/l2data
mkdir $dn/l2world
mkdir $dn/login
mkdir $dn/login/client
mkdir $dn/login/server
mkdir $dn/net_io
mkdir $dn/packetNames
mkdir $dn/pcode_obfuscator
mkdir $dn/xcpt
echo "Created dir tree"

# main header
cp $src/L2Packets.h $dn/L2Packets.h
cp $src/L2_versions.h $dn/L2_versions.h
# base
cp $src/base/ByteArray.h    $dn/base/ByteArray.h
cp $src/base/L2BasePacket.h $dn/base/L2BasePacket.h
# game
cp $src/game/L2GamePacket.h $dn/game/L2GamePacket.h
cp $src/game/client/*.h     $dn/game/client
cp $src/game/server/*.h     $dn/game/server
# l2data
cp $src/l2data/L2Data.h         $dn/l2data/L2Data.h
cp $src/l2data/L2Data_Recipes.h $dn/l2data/L2Data_Recipes.h
# l2world
cp $src/l2world/*.h $dn/l2world
# login
cp $src/login/L2LoginPacket.h $dn/login/L2LoginPacket.h
cp $src/login/client/*.h      $dn/login/client
cp $src/login/server/*.h      $dn/login/server
# net_io
cp $src/net_io/*.h $dn/net_io
# packetNames
cp $src/packetNames/L2PacketNames.h $dn/packetNames/L2PacketNames.h
# pcode_obfuscator
cp $src/pcode_obfuscator/L2PCodeObfuscator.h $dn/pcode_obfuscator/L2PCodeObfuscator.h
#xcpt
cp $src/xcpt/L2Packets_xcpt.h $dn/xcpt/L2Packets_xcpt.h

echo "Copy headers complete to $dn"