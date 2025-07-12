#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void find(char *, long, char *);

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

    FILE *buffer = (FILE *)malloc(file_size);

    if (buffer == NULL) {
      fprintf(stderr, "something went wrong when allocating space for the "
                      "buffer on the memory\n");
      continue;
    }

    read_status = fread(buffer, sizeof(char), file_size, file_des);
    char *buffer2 = (char *)malloc(file_size + 1);

    strcpy(buffer2, (char *)buffer);
    find(buffer2, file_size, word);
  }
  return 0;
}

void find(char main_buffer[], long size, char *word_to_be_found) {
  long target_length = strlen(word_to_be_found);
  int word_found = 0;
  char *temp = (char *)malloc(size);
  char *line_buff = (char *)malloc(size);
  for (int i = 0; i < size; i++) {
    if (main_buffer[i] == '\n') {
      if (word_found) {
        printf("%s\n", line_buff);
        word_found = 0;
      }
      strcpy(temp, "");
      strcpy(line_buff, "");
    }
    printf("%s\n", line_buff);
    long temp_len = strlen(temp);
    if (temp_len == target_length) {
      if (strcmp(word_to_be_found, temp) == 0) {
        word_found = 1;
      }
    }
    if (main_buffer[i] == ' ') {
      strcat(line_buff, temp);
      strcat(line_buff, " ");
      strcat(temp, "");
      continue;
    }
    strcat(temp, &main_buffer[i]);
  }
}
