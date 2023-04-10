#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * reads text file - a function that reads and prints to POSIX
 *
 * @fd: filename
 *
 * Return: return 0 or num_written
 */

ssize_t read_textfile(const char *filename, size_t letters) {
    if (filename == NULL) {
        return 0;
    }

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return 0;
    }

    char *buffer = (char *) malloc(letters * sizeof(char));
    if (buffer == NULL) {
        close(fd);
        return 0;
    }

    ssize_t num_read = read(fd, buffer, letters);
    if (num_read == -1) {
        close(fd);
        free(buffer);
        return 0;
    }

    ssize_t num_written = write(STDOUT_FILENO, buffer, num_read);
    if (num_written == -1 || num_written != num_read) {
        close(fd);
        free(buffer);
        return 0;
    }

    close(fd);
    free(buffer);
    return num_written;
}
