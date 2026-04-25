#include <stdio.h>
using namespace std;

#include <version.h>

extern int cmd();

int main() {
	
	printf("PISHELL %d.%d\n(c) ADITYA KUMAR 2024\n\n", VERSION_MAJOR, VERSION_MINOR);

	while (cmd());

	return 0;

}