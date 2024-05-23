#include <stdio.h>
#include <string.h>
#define max_string_size 100
#define max_pattern_size 100
int nfind(char* string, char* pat);
int pmatch(char* string, char* pat);
void fail(char* pat);
int failure[max_pattern_size];
char string[max_string_size];
char pat[max_pattern_size];
static int nfindcount = 0, kmpcount = 0;

int main(void)
{
	int nfind_ret, kmp_ret;
	
	// input string, pattern
	scanf("%s", string);
	scanf("%s", pat);

	nfind_ret = nfind(string, pat);	
	if (nfind_ret == -1)
		printf("nfind:  NO\n");
	else
		printf("nfind:  YES %d\n", nfindcount);

	fail(pat); // fill fail array
	kmp_ret = pmatch(string, pat);
	if (kmp_ret == -1)
		printf("kmp:    NO\n");
	else
		printf("kmp:    YES %d\n", kmpcount);

	return 0;
}

int nfind(char* string, char* pat)
{
	int i, j = -1, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++, nfindcount++)
				;
		nfindcount++; // return ÀÌÀü¿¡ count
		if (j == lastp) return start; 
	}
	return -1;
}

int pmatch(char* string, char* pat)
{
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;
		kmpcount++;
	}
	return ((j == lenp) ? (i - lenp) : -1);
}

void fail(char* pat)
{
	int i, j, n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++,kmpcount++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else failure[j] = -1;
	}
}

