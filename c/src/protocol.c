#include "protocol.h"

#include "common.h"
#include "network.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <pthread.h>

////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

typedef struct entity {
    char            id[9]; // 8th char max, 9th is 0
    unsigned short  udp;
    unsigned short  tcp;
    char            ip_next[16];
    unsigned short  port_next;
    char            mdiff_ip[16];
    unsigned short  mdiff_port;
} entity;


typedef struct welc_msg {
    char ip[16];
    int  port;
    char ip_diff[16];
    int  port_diff;
} welc_msg;

typedef struct newc_msg {
    char ip[16];
    int port;
} newc_msg;
 

entity ent = { .id = "Bryan", .udp = 4242, .tcp = 4343,
    .ip_next = "127.000.000.100", .port_next = 4243,
    .mdiff_ip = "255.255.255.255", .mdiff_port = 8888
};

////////////////////////////////////////////////////////////////////////////////
// LOCAL
////////////////////////////////////////////////////////////////////////////////

static char *entitytostr() {
    char *str = (char *)malloc(350);
    char *id = malloc(50), *udp = malloc(50), *tcp = malloc(50),
         *ip = malloc(50), *np = malloc(50), *mdip = malloc(50), 
         *mdp = malloc(50);
    sprintf(id, "%30s - %s", "\x1b[4mid\x1b[0m", ent.id);
    sprintf(udp, "%30s - %d", "\x1b[4mudp listening port\x1b[0m", ent.udp);
    sprintf(tcp, "%30s - %d", "\x1b[4mtcp listening port\x1b[0m", ent.tcp);
    sprintf(ip, "%30s - %s", "\x1b[4mip of next entity\x1b[0m", ent.ip_next);
    sprintf(np, "%30s - %d", "\x1b[4mport of next entity\x1b[0m", ent.port_next);
    sprintf(mdip, "%30s - %s", "\x1b[4mmultidiff ip\x1b[0m", ent.mdiff_ip);
    sprintf(mdp, "%30s - %d", "\x1b[4mmultidiff port\x1b[0m", ent.mdiff_port);
    sprintf(str, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", id, udp, tcp, ip, np, mdip, mdp);
    free(id);free(udp);free(tcp);free(ip);free(np);free(mdip);free(mdp);
    return str;
}

static welc_msg *parse_welc(const char *w_msg) {
    char *msg = strdup(w_msg);
#ifdef DEBUG
#define parse_test(test, format, ...) \
    if (test) { \
        debug("parse_welc(\"%s\")", #test " -> " format, msg, ##__VA_ARGS__); \
        free(welc); \
        free(msg); \
        return NULL; \
    }
#else
#define parse_test(test, format, ...) \
    if (test) { \
        free(welc); \
        free(msg); \
        return NULL; \
    }
#endif
    welc_msg *welc = (welc_msg *)malloc(sizeof(welc_msg));
    // token 1: WELC
    char *token = strtok(msg, " ");
    parse_test(token == NULL, 
            "first call to strtok returned NULL, \"WELC\" required.\n");
    parse_test(strcmp(token, "WELC") != 0, 
            "token = \"%s\", \"WELC\" required.\n",
            token);
    // token 2: ip
    token = strtok(NULL, " ");
    parse_test(token == NULL, 
            "second call to strtok returned NULL, ip required.\n");
    parse_test(strlen(token) != 15,
            "ip length must be of 15.\n");
    strncpy(welc->ip, token, 16);
    // token 3: port
    token = strtok(NULL, " ");
    parse_test(token == NULL, 
            "third call to strtok returned NULL, port required.\n");
    parse_test(!isnumeric(token),
            "non int found, port required.\n");
    welc->port = atoi(token);
    // token 4: multidiff ip
    token = strtok(NULL, " ");
    parse_test(token == NULL, 
            "fourth call to strtok returned NULL, multi-diff ip required.\n");
    parse_test(strlen(token) != 15,
            "multi diff ip length must be of 15.\n");
    strncpy(welc->ip_diff, token, 16);
    // token 5: multidiff port
    token = strtok(NULL, " ");
    parse_test(token == NULL, 
            "fifth call to strtok returned NULL, port required.\n");
    parse_test(!isnumeric(token),
            "non int found, multi-diff port required.\n");
    welc->port_diff = atoi(token);
    // test for non valid extra things
    parse_test(strtok(NULL, " ") != NULL,
            "unvalid extra informations found : %s", token);
#undef parse_test
    free(msg);
    return welc;
}

static newc_msg *parse_newc(const char *n_msg) {
    char *msg = strdup(n_msg);
#ifdef DEBUG
#define parse_test(test, format, ...) \
    if (test) { \
        debug("parse_newc(\"%s\")", #test " -> " format, msg, ##__VA_ARGS__); \
        free(newc); \
        free(msg); \
        return NULL; \
    }
#else
#define parse_test(test, format, ...) \
    if (test) { \
        free(newc); \
        free(msg); \
        return NULL; \
    }
#endif
    newc_msg *newc = (newc_msg *)malloc(sizeof(newc_msg));
    // token 1: WELC
    char *token = strtok(msg, " ");
    parse_test(token == NULL, 
            "first call to strtok returned NULL, \"NEWC\" required.\n");
    parse_test(strcmp(token, "NEWC") != 0, 
            "token = \"%s\", \"NEWC\" required.\n",
            token);
    // token 2: ip
    token = strtok(NULL, " ");
    parse_test(token == NULL, 
            "second call to strtok returned NULL, ip required.\n");
    parse_test(strlen(token) != 15,
            "ip length must be of 15.\n");
    strncpy(newc->ip, token, 16);
    // token 3: port
    token = strtok(NULL, " ");
    parse_test(token == NULL, 
            "third call to strtok returned NULL, port required.\n");
    parse_test(!isnumeric(token),
            "non int found, port required.\n");
    newc->port = atoi(token);
    // test for non valid extra things
    parse_test(strtok(NULL, " ") != NULL,
            "unvalid extra informations found : %s", token);
#undef parse_test
    free(msg);
    return newc;
}




static char *prepare_welc() {
    char *msg = (char *)malloc(50);
    sprintf(msg, "WELC %s %s %s %s\n",
            ent.ip_next, itoa4(ent.port_next), 
            ent.mdiff_ip, itoa4(ent.mdiff_port));
    return msg;
}



static char *prepare_newc() {
    char *msg = (char *)malloc(30);
    sprintf(msg, "NEWC %s %s\n", getLocalIp(), itoa4(ent.udp));
    return msg;
}



////////////////////////////////////////////////////////////////////////////////
// GLOBAL
////////////////////////////////////////////////////////////////////////////////

int insert(const char *host, const char *tcpport) {
    // preparing the structure
    struct sockaddr_in *addr;
    struct addrinfo *first_info;
    struct addrinfo hints;
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, tcpport, &hints, &first_info) != 0 ||
            first_info == NULL) {
        fprintf(stderr, 
                "Can't get address of %s at port %s.\n", host, tcpport);
        return 0;
    }
    addr = (struct sockaddr_in *) first_info->ai_addr;
    // socket creation
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(sock, (struct sockaddr *)addr,
                (socklen_t)sizeof(struct sockaddr_in)) != 0)
    {
        close(sock);
        fprintf(stderr,
                "Can't establish connection with %s on port %s.\n", host, tcpport);
        return 0;
    }
    verbose("Connection established with %s on port %s.\n", host, tcpport);
    // WELC message reception
    verbose("waitig for WELC message...\n");
    char *msg = receptLine(sock);
    verbose("Message received : \"%s\".\n", msg);
    verbose("Parsing message...\n");
    welc_msg *welc = parse_welc(msg);
    free(msg);
    if (welc == NULL) {
        fprintf(stderr, "Protocol error: bad response.\nInsertion failed.\n");
        free(welc);
        return 0;
    }
    verbose("Parsing successfull.\n");
    // NEWC message sending
    verbose("Preparing NEWC message...\n");
    char *newc_str = prepare_newc();
    verbose("Sending: \"%s\".\n", newc_str);
    send(sock, newc_str, strlen(newc_str), 0);
    verbose("Message sent.\n");
    fflush(stdout);
    // ACKC message reception
    verbose("Waiting for ACKC confirmation message...\n");
    msg = receptLine(sock);
    verbose("Message received: \"%s\".\n", msg);
    if (strcmp(msg, "ACKC") != 0) {
        fprintf(stderr, "Protocol error: bad response.\nInsertion failed.\n");
        free(welc);
        free(msg);
        return 0;
    }
    verbose("Modifying current entity...");
    verbose("Current entity:\n%s\n", entitytostr());
    ent.port_next = welc->port;
    ent.mdiff_port = welc->port_diff;
    strcpy(ent.ip_next, welc->ip);
    strcpy(ent.mdiff_ip, welc->ip_diff);
    verbose("Modified entity:\n%s\n", entitytostr());

    return 1;
}


void insertionsrv() {
    // socket preparation
    int sock = socket(PF_INET,SOCK_STREAM, 0);
    struct sockaddr_in addr_sock;
    // server socket filling
    addr_sock.sin_family      = AF_INET;
    addr_sock.sin_port        = htons(ent.tcp);
    addr_sock.sin_addr.s_addr = htonl(INADDR_ANY);
    // port binding
    int res;
    res = bind(sock, (struct sockaddr *)&addr_sock, 
            sizeof(struct sockaddr_in));
    if ( res == -1 ) {
        close(sock);
        perror("Binding error.");
        exit(1);
    }
    // listening sock
    res = listen(sock, 0);
    if ( res == -1 ) {
        close(sock);
        perror("Listen error.");
        exit(1);
    }
    while (1) {
        // wait for connection
        verbose("Waiting for client...\n");
        struct sockaddr_in caller;
        socklen_t size = sizeof(caller);
        int sock2;
        sock2 = accept(sock, (struct sockaddr *)&caller, &size);
        // error from accept
        if ( sock2 == -1 ) {
            perror("Error accept.");
            continue;
        }
        verbose("Connection established.\n");
        // insertion protocol
        // WELC message sending
        verbose("Prepaing WELC message...\n");
        char *msg = prepare_welc();
        verbose("Sending \"%s\"...\n", msg);
        send(sock2, msg, strlen(msg), 0);
        verbose("Message sent.\n");
        free(msg);
        // NEWC message reception
        verbose("Waiting for NEWC message...\n");
        msg = receptLine(sock2);
        verbose("Received : \"%s\".\n", msg);
        verbose("Parsing message...\n");
        newc_msg *newc = parse_newc(msg);
        if (newc == NULL) {
            fprintf(stderr, "Protocol error: bad response from client.\nInsertion failed.\n");
            free(newc);
            close(sock2);
            continue;
        }
        verbose("Parsing successful.\n");
        // modifying entity
        verbose("Modifying current entity...\n");
        verbose("Current entity :\n%s\n", entitytostr());
        ent.port_next = newc->port;
        strcpy(ent.ip_next, newc->ip);
        verbose("Modified entity :\n%s\n", entitytostr());
        free(newc);
        // ACKC message sending
        verbose("Sending ACKC confirmation message...\n");
        send(sock2, "ACKC\n", 5, 0);
        verbose("Message sent.\n");
        // closing connection
        verbose("Closing connection.");
        close(sock2);
    }
}



void *insertion_thread(void *arg) {
    insertionsrv();
}

void launch_insserv() {
    pthread_t th;
    pthread_create(&th, NULL, insertion_thread, NULL);
    //pthread_join(th, NULL);


}