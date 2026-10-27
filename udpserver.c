#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main() {
    int s;
    char msg[MAX], result[MAX] = "";
    char *words[] = {
        "tbh", "idc", "ig", "tbf", "atm", "irl",
        "lol", "asap", "omg", "ttyl", "idk", "nvm"
    };
    char *full[] = {
        "to be honest", "I don't care", "I guess",
        "to be fair", "at the moment", "in real life",
        "laughing out loud", "as soon as possible",
        "oh my God", "talk to you later",
        "I don't know", "never mind"
    };

    struct sockaddr_in addr, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&addr, sizeof(addr));
    printf("UDP Server Running...\n");

    int n = recvfrom(s, msg, MAX - 1, 0,
                     (struct sockaddr *)&client, &len);
    msg[n] = '\0';

    char *token = strtok(msg, " \n");
    while (token != NULL) {
        char word[100];
        strcpy(word, token);

        for (int i = 0; word[i]; i++)
            word[i] = tolower((unsigned char)word[i]);

        int found = 0;
        for (int i = 0; i < 12; i++) {
            if (strcmp(word, words[i]) == 0) {
                strcat(result, full[i]);
                found = 1;
                break;
            }
        }

        if (!found)
            strcat(result, token);

        strcat(result, " ");
        token = strtok(NULL, " \n");
    }

    sendto(s, result, strlen(result) + 1, 0,
           (struct sockaddr *)&client, len);

    close(s);
    return 0;
}