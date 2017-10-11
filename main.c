#include <stdio.h>
#include <string.h>

int valid(argc) {
	if (argc < 1) {
		return 0;
	} else {
		return 1;
	}
}



int main (int argc, char *args[]) {
	printf("%d", argc);
	if (!valid(argc)) {
		printf("There are missing arguments");
	}

	char* algorithm_choice = "";
	char* pattern_file = "";
	char* pattern;
	char* file_name;
	char* max;
	int count_option;
	if (argc > 2) {
		for (int i = 0; i < argc; i++) {
			if (strncmp(args[i], "--", 2)) { //it is an options
				switch (args[i]) {
					case "--algorithm":
						algorithm_choice = args[i+1];
						i += 1; //because we already got the name of the algorithm
					break;
					case "--edit":
						max = args[i+1];
						i += 1; //because we already got the parameter
					break;
					case "--pattern":
						i += 1; //because we already got the file_name
					break;
					case "--count":
					break;
					default:
						printf("error");
					break;
				}
			} else {
				if (i == argc) { //filename
					file_name = args[i];
				} else { //pattern
					pattern = args[i];
				}
			}
		}
	} else {
		//it is just one pattern and one file pattern
	}
}