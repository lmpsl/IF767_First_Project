#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b) {
	printf("%s","max() called");

	if (a > b) {
		return a;
	} else {
		return b;
	}

}

void computerPattern(char* pattern, int pattern_size, int* lps) {
	int i = 1;
	int j = 0;
	for (int i = 0; i < pattern_size+1; i++) {
		lps[i] = 0;
	}

	while (i + j < pattern_size) {
		while (i + j < pattern_size && pattern[i+j] == pattern[j]) {
			j += 1;
			lps[i+j] = j;
		}
		i += max(1, (j - lps[j]));
		j = lps[j];
	}
	/*for (int i = 0; i < pattern_size; i++) {
		printf("lps[%d] : %d, ", i, lps[i]);
	}*/

}


int* insert(int* occ, int item) {
	return NULL;
}

int* kmp(char* text, char* pattern) {
	int text_size = strlen(text);
	int pattern_size = strlen(pattern);
	printf("%d\n", pattern_size);
	printf("%d\n", text_size);
	int lps[pattern_size+1];
	computerPattern(pattern, pattern_size, lps);
	int i = 0, j = 0;
	int occ[1];
	printf("%d", lps[0]);

	while (i <= text_size - pattern_size) {
		while (j < pattern_size && text[i+j] == pattern[j]) {
			j += 1;
		}
		printf("%s %d\n","j: ", j);
		printf("%s %d\n","i: ", i);
		if (j == pattern_size) {
				//insert(occ, i);
			printf("found pattern at: %d \n\n", i);
		}
		i += max(1, (j-lps[j]));
		j = max(0, lps[j]);
	}

	return NULL;
}

int main(void) {
	char* text = "FEXLEIEXEXEDADCIDADES EXEXE ANDADES";
	char* pattern = "EXE";
	kmp(text, pattern);
	return 0;
}
