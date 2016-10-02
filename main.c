#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "grep.h"
int max = 1000;
typedef struct counter {
	int options;
	int files;
	int other;
}counter;
counter *c;
int main(int argc, char *argv[]) {
	char *str;
	int i, j, k, flag = 0;
	c = (counter *)malloc(sizeof(counter));
	set = (set_option *)malloc(sizeof(set_option));
	set -> print_line_number = OFF;
	set -> print_file_name = OFF; 
	set -> case_insensitive = OFF;
	set -> print_max_lines = OFF;	
	count_function(argc, argv);
	str = (char *)malloc(max);
	for(i = 1; i <= (c -> options); i++) {
		if(strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-y") != 0 && strcmp(argv[i], "-v") != 0 &&
		   strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-x") != 0 && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-m") != 0 &&
	           strcmp(argv[i], "-o") != 0 && strcmp(argv[i], "-n") != 0 && strcmp(argv[i], "-G") != 0) {
			printf("Invalid option.\n");
			return EINVAL;
		}
		if(strcmp(argv[i], "-m") == 0) {
			i++;
		}
	}
	for(k = 1; k <= (c -> options + c -> other); k++) {	
		for(j = ((c -> options) + (c -> other) + 2); j < ((c -> options) + (c -> other) + 2 + (c -> files)); j++) {
			if((c -> files) != 1) {
					(set -> file_name) = (char *)malloc(strlen(argv[j]) + 1);
					strcpy((set -> file_name), argv[j]);
					(set -> print_file_name) = ON;
			}
			line_count = 0;
			/*while((i = readline(argv[j], str)) != 1)*/do {
				i = readline(argv[j], str);
				if(i == -1) {
					perror("Error");
					return errno;
				}
				line_count++;
				/*if(strlen(str) == 0) {
					continue;
				}*/
				if((c -> options) == 0) {
					normal_grep(str, argv[(c -> options) + 1]);
				}
				else if((c -> options) == 1) {
					if(strcmp(argv[k], "-G") == 0) {
						normal_grep(str, argv[(c -> options) + 1]);
					}
					else if(strcmp(argv[k], "-c") == 0) {
						count_line(str, argv[(c -> options) + 1], 0, i);
					}
					else if(strcmp(argv[k], "-v") == 0) {
						inverse_grep(str, argv[(c -> options) + 1]);
					}	
					else if(strcmp(argv[k], "-o") == 0) {
						only_matching_grep(str, argv[(c -> options) + 1]);
					}
					else if(strcmp(argv[k], "-n") == 0) {
						(set -> print_line_number) = ON;
						normal_grep(str, argv[(c -> options) + 1]);
					}
					else if(strcmp(argv[k], "-x") == 0) {
						matching_lines(str, argv[(c -> options) + 1]);
					}
					else if(strcmp(argv[k], "-i") == 0 || strcmp(argv[k], "-y") == 0) {
						set -> case_insensitive = ON;
						normal_grep(str, argv[(c -> options) + 1]);
					}
					else if(strcmp(argv[k], "-w") == 0) {
						print_word_grep(str, argv[(c -> options) + 1]);
					}
					else if(strcmp(argv[k], "-m") == 0) {
						k++;
						if(flag == 0) {
							set -> print_max_lines = ON;
							flag = 1;
							(set -> max_lines) = atoi(argv[k]);
							k--;
						}					
						if((set -> max_lines) != 0) {
							normal_grep(str, argv[(c -> options) + (c -> other) + 1]);
						}
						else {
							set -> print_max_lines = OFF;
							break;
						}
					}							
				}	 
			}while(i != 1);
		}
	} 
	free(c);
	free(set);
	free(str);
	return 0;
}
void count_function(int n, char **argv) {
	int i, flag = 0;
	(c -> options) = 0;
	(c -> files) = 0;
	(c -> other) = 0;
	for(i = 1; i < n; i++) {
		if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-y") == 0 || strcmp(argv[i], "-v") == 0 ||
		   strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-m") == 0 ||
		   strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-G") == 0) {
		   	(c -> options)++;
		   	if(strcmp(argv[i], "-m") == 0) {
		   		i++; 
		   		(c -> other)++;
		   	}
		}
		else {
			if(flag == 0) {
				flag = 1;
			}
			else {
				(c -> files)++;
			}
		}
	}
}	
int readline(char *file, char *str) {
	FILE *fp;
	char ch;
	int i = 0, flag = 0, error, j;
	static int count = 0;
	fp = fopen(file, "r");
	if(fp == NULL) {
		return -1;
	}
	error = fseek(fp, count, SEEK_SET);
	if(error == -1) {
		return -1;
	}
	while(1) {
		j = fread(&ch, 1, 1, fp);
		if(j == 0) {
			flag = 1;
			break;
		}
		else if(ch == '\n') {
			str[i++] = '\n';
			count++;
			break;		
		}
		else {
			str[i++] = ch;
			count++;
		}
	}
	if(flag !=1) {
		str[i] = '\0';
	}
	fclose(fp);
	if(flag == 1) {
		count = 0;
	}
	return flag;
}
