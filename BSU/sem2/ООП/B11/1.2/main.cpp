#include "header.h"

int main() {
	srand(time(0));

	int mode = select();

	if (mode == MODE_GENERATE)
		generate();
	else if(mode == MODE_READ)
		read_files();
	else if(mode == MODE_SOLVE)
		solve();

	return 0;
}