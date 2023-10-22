typedef struct {
    struct in_addr address;
    unsigned short port;
    unsigned short start_cmd;
} settings;

void check_pass(){
    char password[60];
    printf("Enter password: ");
    scanf("%59[^\n]s", password);
	// TODO: Check password
}

settings* get_settings(){
    settings *serv_settings = (settings*)malloc(sizeof(settings));
    serv_settings->start_cmd = 0;
    
    printf("Enter Command Number: ");
    scanf("%hu", &(serv_settings->start_cmd));
    if(serv_settings->start_cmd != 0){
        printf("Invalid command number.\n");
        exit(0);
    }
	
    printf("Enter Listening Address: ");
    char addr[16];
    scanf("%15s", addr);
    inet_pton(AF_INET, addr, &(serv_settings->address));
    
    printf("Enter Listening Port: ");
    scanf("%lu", &(serv_settings->port));
    return serv_settings;
}

int setup_socket(settings *serv_settings){
	int listenfd = 0;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_settings->port);
    serv_addr.sin_addr = serv_settings->address;
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    return fd;
}


void print_flag(){
    // TODO: Print out flag.
}

void record_message(char *message){
	FILE *fp = fopen("./log.txt", "a");
	fprintf(fp, message);
	fclose(fp);
}

void print_error(){
    printf("The server received a message from the client but is unable to display it.\n");
}

void handle_message(unsigned short start_cmd, char *message){
	switch(start_cmd){
		case 0:
			record_message(message);
			break;
		case 1:
            print_flag();
            break;
        default:
            print_error();
    }
}

void accept_conns(int socket, settings *serv_settings){
    bind(socket, (struct sockaddr *)&serv_settings, sizeof(serv_settings));
    listen(socket,5);
    
	char address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(serv_settings->address), address, INET_ADDRSTRLEN);
    printf("Listening for connections on %s:%hu\n", address, serv_settings->port);

	int conn;
    char message[100] = "";
    while(conn = accept(socket, (struct sockaddr *)NULL, NULL)) {
        int pid;
        if((pid = fork()) == 0) {
            while (recv(conn, message, 100, 0)>0) {
                handle_message(serv_settings->start_cmd, &message);
                *message = "";
            }
            exit(0);
        }
    }
}

int main() {
    check_pass();
    settings *serv_settings = get_settings();
    int socket = setup_socket(serv_settings);
    accept_conns(socket, serv_settings);
    
    free(serv_settings);
    printf("Complete\n");
    return 0;
}
