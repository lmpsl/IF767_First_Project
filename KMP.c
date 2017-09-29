#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int *computerPatternSimple(char* pattern, int pattern_size) {
	int lps[pattern_size];
	int i = 1;
	int j = 0;

	for (int i = 0; i < pattern_size; i++) {
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
	for (int i = 0; i < pattern_size; i++) {
		printf("%d, ", lps[i]);
	}
	return lps;
}


int *computerPattern(char* pattern, int pattern_size) {
	int lps[pattern_size+1];
	int i = 1;
	
	for (int i = 0; i < pattern_size+1; i++) {
		lps[i] = -1;
	}
	if (pattern_size == 1 || (pattern>0 && pattern[0] != pattern[1])) {
		lps[i] = 0;
	}

	int j = 0;
	while (i < pattern_size) {
		while (pattern[i+j] == pattern[j] && i+j < pattern_size) {
			j += 1;
			if (i+j == pattern_size || pattern[i+j] != pattern[j]) {
				lps[i+j] = j;
			} else {
				lps[i+j] = lps[j];
			}
		}

		if (j == 0 && (i == pattern_size-1 || pattern[0] != pattern[i+1])) {
			lps[i+1] = 0;
		}
		i = i + j - lps[j];
		printf("%d\n",i);
		j = max(0, lps[j]);
	}
	printf("Preprocessing list:");
	for (int i = 0; i < pattern_size; i++) {
		printf("pos(%d) : %d, ", i, lps[i]);
	}
	return lps;
}

int* insert(int* occ, int item) {
	return NULL;
}

int* kmp(char* text, char* pattern) {
	int text_size = strlen(text);
	int pattern_size = strlen(pattern);
	printf("%d\n", pattern_size);
	printf("%d\n", text_size);
	int* lps;
	lps = computerPatternSimple(pattern, pattern_size);
	int i, j = 0;
	int occ[1];

	while (i <= text_size - pattern_size) {
		while (j < pattern_size && text[i+j] == pattern[j]) {
			j += 1;		
		}
		
		if (j == pattern_size) {
				//insert(occ, i);
			printf("%d", i);
		}

		i += max(1, (j-lps[j]));
		j = max(0, lps[j]);
	}

	return NULL;
}

int main(void) {
	char* text = "FEXLEIEXEXEDADCIDADES EXEXE ANDADES";
	char* pattern = "EXE";
	int* occ = kmp(text, pattern);
	return 0;
}