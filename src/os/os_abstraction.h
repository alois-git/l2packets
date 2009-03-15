#ifndef H_OS_ABSTRCTION
#define H_OS_ABSTRCTION

// uses #defines to determine under which OS it is compiled:
// #ifdef WIN32 - Windows
// #ifndef WIN32 - Linux :)

// returns number of milliseconds of current time
// in windows - since Windows Start (uptime)
// in Lunux - in current day
unsigned int OS_GetTickCount();

#endif
