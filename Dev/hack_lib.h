//
// Created by tester on 10.05.2020.
//

#ifndef KEYGEN_HACK_LIB_H
#define KEYGEN_HACK_LIB_H

#include <cstdio>

bool crackSerg(char *data, long size);

long get_hash_sum(char *content, long size);

char *readfile(char *path, long *size);

void writefile(char *path, char *data, long size);

long getSizeFile(FILE *file);


#endif //KEYGEN_HACK_LIB_H
