# About L2Packets #
Library was born as support level to write lineage 2 client emulator and radar program. It was a collection of methods for low-level L2 packets manipulation, including easy parsing packet data and encryption/decryption process. It was designed to use from client side, making easier to write logical parts of application and now is working as part of other my closed source projects :) It can be used as server side, too.

Library is not a collection of documentaion about Lineage II protocol, or about packets structure - they may be too different in different protocol versions. Library usage is very specific - it only helps you to receive/send packets, decrypt them and read some data; you must have knowledge about packets structure, packets order in lineage client--sever communication.

More info about packets structure can be found in L2J server source code (thanks them a lot, they are great people :) ); to get info about packets order you can use any sniffer or packet proxifier...

I guess, library is not a good example of design of object-oriented class library; it is not an example of perfect code or something else. There are many things that can be done in a better way than it's done in L2Packets :)