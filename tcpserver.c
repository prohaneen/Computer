#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 20

int main() {
    int s, c, n, a[MAX][MAX];
    int u = 1, l = 1, d = 1;
    char result[50];
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    s = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&addr, sizeof(addr));
    listen(s, 3);
    printf("Waiting for client...\n");

    c = accept(s, (struct sockaddr *)&addr, &len);
    read(c, &n, sizeof(n));
    read(c, a, sizeof(a));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j && a[i][j] != 0) u = 0;
            if (i < j && a[i][j] != 0) l = 0;
            if (i != j && a[i][j] != 0) d = 0;
        }
    }

    if (d)
        strcpy(result, "Diagonal Matrix");
    else if (u)
        strcpy(result, "Upper Triangular Matrix");
    else if (l)
        strcpy(result, "Lower Triangular Matrix");
    else
        strcpy(result, "Neither Upper nor Lower nor Diagonal");

    write(c, result, sizeof(result));
    printf("%s\n", result);

    close(c);
    close(s);
    return 0;
}