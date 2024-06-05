#include <Windows.h>
#include "menu.h"
#include "libds/heap_monitor.h"

auto main() -> int
{	
	initHeapMonitor();
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
	Menu menu;
	menu.startMenu();

	return 0;
}
