#include<stdio.h>
#include<sys/types.h>

//#include<sys/socket.h>

#include <winsock2.h>
//#include<netdb.h>
//#include<netinet/in.h>

#include<stdlib.h>
#include<strings.h>
#include <unistd.h>

#define LEPORT 2020

int main(){

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }
    int s = 0,taille,bd,errno,lg = 40, un_entier;

    struct sockaddr_in  padin; //adresse internet locale
    struct sockaddr_in *p_exp; //pointeur vers adresse internet expediteur (recuperée de l'entete paquet UDP recu)

    int p_lgexp = sizeof(struct sockaddr_in);
    char *name = "localhost";
    char *adr_serv="127.0.0.1";
    char msg[] = "coucou c'est moi, ton client ENSEM";
    char msg1[lg]; // pour recevoir ACK

    int *p_lgexp1;

    struct hostent *host;
    s = socket(AF_INET, SOCK_DGRAM, AF_UNSPEC);
    if(s == -1){
        printf("erreur creation socket %d\n",errno);
        exit(-1);
    }
    printf("le socket est identifie par : %d \n",s);
    taille = sizeof(struct sockaddr_in);
    bzero((char*)&padin,taille);
    // Avec le DNS, on obtient l'adresse ip par gethostbyname()
    if ((host = gethostbyname(name))==NULL){
        perror("Nom de machine");
        exit(2);
    }
    bcopy(host -> h_addr_list[0], &padin.sin_addr,host -> h_length);
    // si on connait l'adresse ip de destination en chiffre, on peut l'affecter directement:
    //un_entier=inet_aton(adr_serv, &padin.sin_addr);
    padin.sin_family = AF_INET;
    padin.sin_port   = htons(LEPORT);

            //POURCENTAGE ET INITIALISATION
        printf("\nQuel est le pourcentage d'obstacle (conseil : 20 ) ?  ");
        //scanf("%d", msg); //pas de ENTREE a la fin, mais coupe si espace
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        p_exp = (struct sockaddr_in *)(malloc(taille));
        p_lgexp1 = (int*)malloc(sizeof(int));
        *p_lgexp1 = sizeof(p_exp);
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);

        printf("\nQuel est la largeur de la carte ?");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);

         printf("\nQuel est la hauteur de la carte ?");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


    //ROBOT 1

        printf("\n\nQuel est l'abscisse initial du robot 1 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


        printf("\nQuel est l'ordonnee initial du robot 1 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


        printf("\nQuel est la direction initial du robot 1 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


        printf("\nQuel sont les commandes du robot 1 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);

    //ROBOT 2

    printf("\n\nQuel est l'abscisse initial du robot 2 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


        printf("\nQuel est l'ordonnee initial du robot 2 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


        printf("\nQuel est la direction initial du robot 2 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);

        printf("\nQuel sont les commandes du robot 2 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        if(bd == -1){
            printf("Erreur send \n");
            exit(-1);
        }
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        printf("%s\n", msg1);

        printf("_____________________________________________________________\n");

        //RECUPARATIONS DIRECTIONS FINALES

        printf("\Direction finale 1 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


        printf("\Direction finale 2 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);

        printf("\Position finale 1 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);

        printf("\Position finale 2 ?  ");
        fgets(msg, 40, stdin); //ENTREE s'ajoute a la fin
        bd = sendto(s,msg,lg,0,&padin,sizeof(padin));
        bd= recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        printf("%s\n", msg1);


        /*printf("\n Direction finale robot 1 :");
        bd=recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        printf("%s\n", msg1);

        printf("Direction finale robot 2 :");
        bd=recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        printf("%s\n", msg1);

    //RECUPARATIONS POSITIONS FINALES



        printf("\n Position finale robot 1 :");
        bd=recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
            printf("Erreur d'attachement : %d \n",bd);
            exit(-1);
                }
        printf("%d\n", msg1);

        printf("\n Position finale robot 2 :");

        bd=recvfrom(s, msg1, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
            printf("Erreur d'attachement : %d \n",bd);
            exit(-1);
                }
        printf("%s\n", msg1);

*/

        printf("\nFIN");


    close(s);
    return 0;
}




