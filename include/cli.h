#ifndef CLI_H
#define CLI_H

#include <stdbool.h>
#include <getopt.h>

typedef struct {
	int n;
	int k;
	unsigned int seed;
	bool quiet;
	bool integralityCheck;
	const char *outFile;
} CliConfig;

CliConfig cliParse(int argc, char **argv);

#endif
