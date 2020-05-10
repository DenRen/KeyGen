//
// Created by tester on 10.05.2020.
//

#include "hack_lib.h"
#include <stdexcept>

bool crackSerg(char *data, long size) {
    const unsigned int sym_find = 0x3A1747C6;

    const unsigned int sym_crack[] = {0x381747C6, 0xC01847C6};

    long path = -1;
    for (int i = 0; i < size / 4; i++)
        if (((unsigned int *) data)[i] == sym_find) {
            path = i;
            break;
        }

    if (path == -1) return false;

    ((unsigned int *) data)[path] = sym_crack[0];
    ((unsigned int *) data)[path + 1] = sym_crack[1];

    return true;
}

char *readfile(char *path, long *size) {
    if (path == nullptr)
        return nullptr;

    FILE *file = nullptr;
    if ((file = fopen(path, "rb")) == nullptr)
        return nullptr;

    *size = getSizeFile(file);
    // Checking on empty pointer not needed here,
    // because previous does it

    char *buf = nullptr;
    if ((buf = (char *) calloc(*size, sizeof(char))) == nullptr)
        throw std::runtime_error("Failed to create buffer");

    if (fread(buf, sizeof(char), *size, file) != *size)
        throw std::runtime_error("Failed to read in buffer");

    fclose(file);

    return buf;
}

void writefile(char *path, char *data, long size) {
    FILE *file = fopen(path, "wb");
    if (data == nullptr || size <= 0 || file == nullptr) {
        fclose(file);
        throw std::runtime_error("Empty args in function");
    }

    if (fwrite(data, sizeof(char), size, file) != size) {
        fclose(file);
        throw std::runtime_error("Failed to write data in file");
    }

    fclose(file);
}

long getSizeFile(FILE *file) {
    if (file == nullptr)
        return -1;

    long size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}

long get_hash_sum(char *content, long size) {
    if (content == nullptr)
        return -1;

    long sum = 0;
    for (int i = 0; i < size; i++)
        sum += content[i];

    return sum;
}