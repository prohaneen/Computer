#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main() {
    int s;
    char msg[MAX], result[MAX];
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    s = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    printf("Enter sentence: ");
    fgets(msg, MAX, stdin);

    sendto(s, msg, strlen(msg) + 1, 0,
           (struct sockaddr *)&addr, len);

    recvfrom(s, result, MAX, 0,
             (struct sockaddr *)&addr, &len);

    printf("Translated sentence: %s\n", result);

    close(s);
    return 0;
}