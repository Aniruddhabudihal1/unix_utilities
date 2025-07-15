#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void find(char *, long, char[]);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "please provide the text to be found in the respective "
                    "file with the format:\n<word><file>\n");
    exit(EXIT_FAILURE);
  }

  char word[sizeof(argv[1])];
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
    free(buffer);
    free(buffer2);
  }
  return 0;
}

void find(char main_buffer[], long size, char word_to_be_found[]) {
  char *line_buff = (char *)malloc(1000);
  char* temp;
  for (int i = 0; i < size; i++) {
    strncat(line_buff,&main_buffer[i],1);
    if (strncmp(&main_buffer[i], "\n", 1) == 0) {
      temp = strstr(line_buff,word_to_be_found);
      if(temp != NULL){
        printf("%s", line_buff);
      }
      strcpy(line_buff, "");
    }
  }

  free(line_buff);
}
