#include <cstdlib>
#include <iostream>
#include <ctime>

#include "bounce.h"


int main( int argc, char ** argv )
{	
	srand( time(NULL) );
	bounce Bouncy( 50 );
	return Bouncy.loop();
}