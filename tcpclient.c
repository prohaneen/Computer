#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 20

int main() {
    int s, n, a[MAX][MAX];
    char result[50];
    struct sockaddr_in addr;

    s = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(s, (struct sockaddr *)&addr, sizeof(addr));

    printf("Enter order: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        close(s);
        return 1;
    }

    srand(time(0));

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            a[i][j] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 50 + 1;
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }

    write(s, &n, sizeof(n));
    write(s, a, sizeof(a));
    read(s, result, sizeof(result));

    printf("Matrix Type: %s\n", result);

    close(s);
    return 0;
}