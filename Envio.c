#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);

    struct sockaddr_in saddr;
    saddr.sin_family      = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Endereço do servidor
    saddr.sin_port        = htons(5000);             // Porta do servidor

    int client = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(client, (struct sockaddr *)&saddr, sizeof saddr) == -1) {
        perror("Falha na conexão");
        return 1;
    }

    char message[128];
    printf("Digite a mensagem a ser enviada: ");
    fgets(message, sizeof message, stdin);

    // Adicione o nome da máquina (ID) ao início da mensagem
    char id[64];
    if (gethostname(id, sizeof id) == 0) {
        snprintf(id, sizeof id, "%s: ", id);
    } else {
        strcpy(id, "[Nome da máquina desconhecido]: ");
    }

    char fullMessage[192];  // Tamanho total da mensagem (ID + mensagem)
    snprintf(fullMessage, sizeof fullMessage, "%s%s", id, message);

    send(client, fullMessage, strlen(fullMessage), 0);

    closesocket(client);

    return 0;
}
