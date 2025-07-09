#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// code to implement a clone of cat

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("No file provided\nexiting\n");
    exit(EXIT_SUCCESS);
  }

  FILE *sock_des;
  size_t rread_status;
  long file_size;
  // char buffer[BUF];

  for (int i = 1; i < argc; i++) {
    char *filepath = argv[i];

    sock_des = fopen(filepath, "r");

    if (sock_des < 0) {
      fprintf(stderr,
              "something went wrong while opening the file %s\nplease check if "
              "it exists\n",
              argv[i]);
      continue;
    }

    fseek(sock_des, 0L, SEEK_END);
    file_size = ftell(sock_des);
    fseek(sock_des, 0L, SEEK_SET);

    FILE *file_ptr = malloc(file_size);
    if (file_ptr == NULL) {
      fprintf(stderr,
              "something went wrong while allocating memory for the buffer\n");
      continue;
    }
    rread_status = fread(file_ptr, sizeof(char), file_size, sock_des);
    printf("Content of file %s :\n%s\n", filepath, (char *)file_ptr);
    free(file_ptr);
  }
  return 0;
}
