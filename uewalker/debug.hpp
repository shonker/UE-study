#pragma once

#ifdef _DEBUG
#define ALLOCCONSOLE()\
{\
    AllocConsole();\
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);\
}
#define FREECONSOLE()\
{\
    fclose(stdout);\
    FreeConsole();\
}
#define PRINTF( f, ... ) { printf( "[+] " f "\n", __VA_ARGS__ ); }
#define PUTS( s ) { printf( "[+] %s \n", s ); }
#else
#define ALLOCCONSOLE()
#define FREECONSOLE()
#define PRINTF( f, ... ) { ; }
#define PUTS( s ) { ; }
#endif

#define PRINT_HEADER() {\
	wprintf(\
 L"\n"\
L" ██▓███    ██████ ▓█████  █    ██ ▒██   ██▒ ██▓▓█████▄ ▓█████ \n"\
L"▓██░  ██▒▒██    ▒ ▓█   ▀  ██  ▓██▒▒▒ █ █ ▒░▓██▒▒██▀ ██▌▓█   ▀ \n"\
L"▓██░ ██▓▒░ ▓██▄   ▒███   ▓██  ▒██░░░  █   ░▒██▒░██   █▌▒███   \n"\
L"▒██▄█▓▒ ▒  ▒   ██▒▒▓█  ▄ ▓▓█  ░██░ ░ █ █ ▒ ░██░░▓█▄   ▌▒▓█  ▄ \n"\
L"▒██▒ ░  ░▒██████▒▒░▒████▒▒▒█████▓ ▒██▒ ▒██▒░██░░▒████▓ ░▒████▒\n"\
L"▒▓▒░ ░  ░▒ ▒▓▒ ▒ ░░░ ▒░ ░░▒▓▒ ▒ ▒ ▒▒ ░ ░▓ ░░▓   ▒▒▓  ▒ ░░ ▒░ ░\n"\
L"░▒ ░     ░ ░▒  ░ ░ ░ ░  ░░░▒░ ░ ░ ░░   ░▒ ░ ▒ ░ ░ ▒  ▒  ░ ░  ░\n"\
L"░░       ░  ░  ░     ░    ░░░ ░ ░  ░    ░   ▒ ░ ░ ░  ░    ░   \n"\
L"               ░     ░  ░   ░      ░    ░   ░     ░       ░  ░\n"\
L"                                                ░             \n"\
); \
}
