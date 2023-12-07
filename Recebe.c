#include <stdio.h>
#include <winsock2.h>

int main() {
    char buff[192];  // Tamanho total da mensagem (ID + mensagem)
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);

    struct sockaddr_in caddr;
    struct sockaddr_in saddr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port        = htons(5000)
    };

    int server = socket(AF_INET, SOCK_STREAM, 0);
    int client, x;
    int csize  = sizeof caddr;

    bind(server, (struct sockaddr *) &saddr, sizeof saddr);
    listen(server, 5);

    while (1) {
        client = accept(server, (struct sockaddr *) &caddr, &csize);
        x = recv(client, buff, sizeof buff, 0);

        buff[x] = '\0';  // Adiciona terminador nulo para imprimir a mensagem corretamente

        printf("Mensagem recebida: %s (de %s:%d)\n", buff, inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

        closesocket(client);
    }

    return 0;
}
