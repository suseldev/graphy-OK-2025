#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

#include "cli.h"
#include "config.h"

CliConfig cliParse(int argc, char **argv) {
	CliConfig cfg = {
		.n = -1,
		.k = -1,
		.seed = 0,
		.quiet = false,
		.integralityCheck = true,
		.outFile = NULL,
		.populationSize = 500,
		.generations = 1000
	};
	int opt;
	while((opt = getopt(argc, argv, "qIs:w:p:g:")) != -1) {
		switch(opt) {
			case 'q':
				cfg.quiet = true;
				break;
			case 'I':
				cfg.integralityCheck = false;
				break;
			case 's':
				cfg.seed = (unsigned int)atoi(optarg);
				break;
			case 'p':
				cfg.populationSize = atoi(optarg);
				break;
			case 'g':
				cfg.generations = atoi(optarg);
				break;
			case 'w':
				cfg.outFile = optarg;
				break;
			default:
				fprintf(stderr, "Usage: %s [-qI] [-s rng_seed] [-w output_file] [-p population_size] [-g generations] n k\n", argv[0]);
				exit(1);
			}
	}
	if(argc-optind<2) {
		fprintf(stderr, "Usage: %s [-qI] [-s rng_seed] [-w output_file] [-p population_size] [-g generations] n k\n", argv[0]);
		exit(1);
	}
	cfg.n = atoi(argv[optind]);
	cfg.k = atoi(argv[optind+1]);

	QUIET = cfg.quiet;
	INTEGRALITY_CHECK_ENABLED = cfg.integralityCheck;
	if(cfg.seed != 0) {
		srand(cfg.seed);
	} else {
		if(!QUIET) printf("[CLI] Using random seed\n");
		srand((unsigned int)time(NULL));
	}
	if(!QUIET) printf("[CLI] Config: n=%d, k=%d, seed=%d, quiet=%d, integralityCheck=%d outFile=%s \n", cfg.n, cfg.k, cfg.seed, cfg.quiet, cfg.integralityCheck, cfg.outFile);
	return cfg;
}

