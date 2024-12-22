#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static void set_read_timeout(int client_fd, int seconds) {
  struct timeval timeout;

  timeout.tv_sec = seconds;
  timeout.tv_usec = 0;

  if (setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) <
      0) {
    perror("setsockopt");
    exit(1);
  }
}

static void set_write_timeout(int client_fd, int seconds) {
  struct timeval timeout;

  timeout.tv_sec = seconds;
  timeout.tv_usec = 0;

  if (setsockopt(client_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof timeout) <
      0) {
    perror("setsockopt");
    exit(1);
  }
}

int parseMessage(char *msg) {
  char *izvini = "ИЗВИНИ";
  int izvini_len = strlen(izvini);
  if (strncmp(msg, izvini, izvini_len) == 0) {
    return -4;
  }

  char *method = "ստանալ⠀  ";
  int method_len = strlen(method);
  if (strncmp(msg, method, method_len) != 0) {
    return -1;
  }

  char *path = "/flag\n";
  int path_len = strlen(path);
  if (strncmp(msg + method_len, path, path_len) != 0) {
    return -2;
  }

  char *body = "խնդրում եմ⠀\n";
  int body_len = strlen(body);
  if (strncmp(msg + method_len + path_len, body, body_len) != 0) {
    return -3;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int listenfd = 0, connfd = 0;
  struct sockaddr_in serv_addr;

  char sendBuff[1025];
  char recvBuff[1025];
  const char *flag = getenv("FLAG");
  time_t ticks;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) <
      0)
    perror("setsockopt(SO_REUSEADDR) failed");

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(1337);

  set_read_timeout(listenfd, 5);
  set_write_timeout(listenfd, 5);

  if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
    perror("bind");
    exit(1);
  };

  listen(listenfd, 10);

  puts("Server started");
  while (1) {
    connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

    read(connfd, &recvBuff, 1024);

    int ret = parseMessage(recvBuff);
    if (ret == -1) {
      snprintf(sendBuff, 1024, "ԱՍԱ ИЗВИНИ\n");
      write(connfd, sendBuff, strlen(sendBuff));
    } else if (ret == -4) {
      snprintf(sendBuff, 1024, "ԻԶՎԻՆԻ ԷՆ ԱՇԽԱՐՀՈՒՄ Michael Jackson ԻՆ ԿԱՍԵՍ\n");
      write(connfd, sendBuff, strlen(sendBuff));
    } else if (ret != 0) {
      snprintf(sendBuff, 1024, "ИЗВИНИТЕ ДУК ОВ ЕК?\n");
      write(connfd, sendBuff, strlen(sendBuff));
    } else {
      snprintf(sendBuff, 1024, "%s", flag);
      write(connfd, sendBuff, strlen(sendBuff));
    }
    memset(sendBuff, 0, 1025);
    memset(recvBuff, 0, 1025);
    close(connfd);
  }
}
