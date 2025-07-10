#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void find(const char *buffer, long buf_size, char *word);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr,
            "please provide the text to be found in the respective file\n");
    exit(EXIT_FAILURE);
  }

  long size_word = sizeof(argv[1]);
  char word[size_word];
  strcpy(word, argv[1]);

  FILE *file_des;
  size_t read_status;

  for (int i = 2; i < argc; i++) {

    char *filename = argv[i];
    file_des = fopen(filename, "r");

    if (file_des == NULL) {
      fprintf(stderr,
              "something went wrong while opening the file : %s\nplease make "
              "sure the file exists\n",
              filename);
      continue;
    }
    fseek(file_des, 0L, SEEK_END);
    long file_size = ftell(file_des);
    rewind(file_des);

    FILE *buffer = malloc(file_size);

    if (buffer == NULL) {
      fprintf(stderr, "something went wrong when allocating space for the "
                      "buffer on the memory\n");
      continue;
    }

    char buffer2[file_size];
    read_status = fread(buffer, sizeof(char), file_size, file_des);
    strcpy(buffer2, (char *)buffer);

    find(buffer2, file_size, word);
  }
  return 0;
}

void find(const char *buffer, long buf_size, char *word) {
  char *line_buf = malloc(buf_size);
  int len = sizeof word;
  int return_flag = 0;

  char *bait[100];
  for (int i = 0; i < buf_size; i++) {
    if (buffer[i] == '\n') {
      if (return_flag) {
        printf("%s\n", line_buf);
      }
      return_flag = 0;
      strcpy(line_buf, "");
    }

    if (buffer[i] != '\0') {
      printf("%c\n", buffer[i]);
      strcat(*bait, &buffer[i]);
      // sprintf(*bait, "%c", buffer[i]);
    }
    if (strcmp(*bait, word)) {
      return_flag = 1;
    }
  }
  free(line_buf);
}
