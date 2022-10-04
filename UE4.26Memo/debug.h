#pragma once

#ifdef _DEBUG
#define PRINTF( f, ... ) { printf( "[*] " f "\n", __VA_ARGS__ ); }
#define PUTS( s ) { printf( "[*] %s \n", s ); }
#else
#define PRINTF( f, ... ) { ; }
#define PUTS( s ) { ; }
#endif
