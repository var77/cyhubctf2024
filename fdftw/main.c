#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int open_in_custom_fd(char *filename, int desired_fd) {
  int original_fd = open(filename, O_RDONLY);
  if (original_fd == -1) {
    perror("open");
    return -1;
  }

  if (dup2(original_fd, desired_fd) == -1) {
    perror("dup2");
    close(original_fd);
    return -1;
  }
  close(original_fd);

  return desired_fd;
}

int open_note(uint16_t *fd) {
  *fd += 1;

  if (*fd >= 31336) {
    *fd = 1337;
  }

  if (open_in_custom_fd("./note.txt", *fd) < 0) {
    return -1;
  }

  return 0;
}

void close_note(uint16_t *fd) {
  if (*fd > 1) {
    close(*fd);
  }
  *fd -= 1;
}

void print_note(uint16_t fd) {
  char content[256] = {0};

  read(fd, &content, 255);
  content[255] = '\0';

  printf("\nNote -> %s\n", content);
}

int main() {
  setbuf(stdout, NULL);
  uint16_t fd = 10;
  unsigned int choice = 0;
  open_in_custom_fd("./flag.txt", 65530);

  while (1) {
    printf("\n1 - Open note\n2 - Print note\n3 - Close note\n4 - Exit\n>> ");
    scanf("%u", &choice);

    switch (choice) {
    case 1:
      open_note(&fd);
      break;
    case 2:
      print_note(fd);
      break;
    case 3:
      close_note(&fd);
      break;
    case 4:
      return 0;
    default:
      continue;
    }
  }

  return 0;
}
