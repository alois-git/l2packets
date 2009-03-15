#include "stdafx.h"
#include "os_abstraction.h"

// in Lunux must include <sys/time.h>

// returns number of milliseconds of current time
// in windows - since Windows Start (uptime)
// in Lunux - in current day
unsigned int OS_GetTickCount()
{
#ifdef _WIN32
	return (unsigned int)GetTickCount();
#else
	timeval tv;
	if( gettimeofday( &tv, NULL ) == 0 )
	{
		return (unsigned int)( (tv.tv_sec*1000 + tv.tv_usec) / 1000 );
	}
	else return 0; // error
#endif
}

/** http://www.linuxmanpages.com/man2/gettimeofday.2.php
uses Libc, .....
{$IFDEF LINUX}
function GetTickCount: Cardinal;
var
tv: timeval;
begin
gettimeofday(tv, nil);
{$RANGECHECKS OFF}
Result := int64(tv.tv_sec) * 1000 + tv.tv_usec div 1000;
end;
{$ENDIF}
**/

/** Another idea:
Implement GetTickCount in Linux
To implement the GetTickCount API when porting code from Windows to Linux, use the following code:

long getTickCount()
{
    tms tm;
    return times(&tm);
}

**/
