/*****************************************************************************
 * Copyright (C) Kuvalekar Abhishek Vijay kuvalekarav15.it@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "grep.h"

/*"readline" reads a line of maximum length 1000 and returns 0 if a line is read, 1 if EOF is reached and -1 on error.*/
int readline(char *file, char *str) {
	FILE *fp;
	char ch;
	char *err;
	int i = 0, flag = 0, error, j;
	static int count = 0;
	fp = fopen(file, "r");
	if(fp == NULL) {
		err = strerror(errno);
		printf("Error:%s:%s.\n", file, err);
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
