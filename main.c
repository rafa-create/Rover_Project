#include<stdio.h>
#include<sys/types.h>
#include<pthread.h>
//#include<sys/socket.h>
#include <winsock2.h>
//#include<netdb.h>
//#include<netinet/in.h>
#include<stdlib.h>
#include<strings.h>
#include <unistd.h>
#define LEPORT 2020

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1=PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2=PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3=PTHREAD_COND_INITIALIZER;

int Abs_1 ;
int Ordo_1;
int Abs_2;
int Ordo_2;
char *Dir_1[1];
char *Dir_2[1];
char Com_1[100];
char Com_2[100];
int* carte[100][100];
int large;
int haut;
int T;
int a;

void afficher_carte_th(){
        pthread_mutex_lock(&mutex);
        usleep(100000);

        //AFFICHAGE
        //affichage de la délimitation
        printf("\n");
        int i;
              for (i = 0; i < large; i++)
           {
               printf("=");

           }
        printf("\n");//fin delimitation

                //affichage des elements par ligne
                  for (i = 0; i < haut; i++)
               {
                   // ligne i:
                  int j;
                  for (j = 0; j < large; j++)
               {
                    //printf("%d %d", i,j);
                    //printf("|");
                    if (carte[i][j]==0){
                        printf("%c",' ');
                    }
                     if (carte[i][j]==1){
                        printf("%c",'#');
                    }
                     if (carte[i][j]==7){// rover 1
                        printf("%c",Dir_1[0]);
                        // ou printf("%s",Dir_1);

                    }
                    if (carte[i][j]==2){//rover 2
                    printf("%c",Dir_2[0]);
                }
               }
               printf ("\n");//fin ligne i
               }
           //affichage de la fin du plateau
           srand(large); /* delimitation de la taille de la largeur */

              for (i = 0; i < large; i++)
           {
               printf("=");

           }
        printf("\n");
        //afficher_tableau();
        //FIN AFFICHAGE
        usleep(1000000);

        pthread_mutex_unlock(&mutex);

};


void afficher_carte(){
        //AFFICHAGE
        //affichage de la délimitation
        printf("\n");
        int i;
              for (i = 0; i < large; i++)
           {
               printf("=");

           }
        printf("\n");//fin delimitation

                //affichage des elements par ligne
                  for (i = 0; i < haut; i++)
               {
                   // ligne i:
                  int j;
                  for (j = 0; j < large; j++)
               {
                    //printf("%d %d", i,j);
                    //printf("|");
                    if (carte[i][j]==0){
                        printf("%c",' ');
                    }
                     if (carte[i][j]==1){
                        printf("%c",'#');
                    }
                     if (carte[i][j]==7){// rover 1
                        printf("%c",Dir_1[0]);
                        // ou printf("%s",Dir_1);

                    }
                    if (carte[i][j]==2){//rover 2
                    printf("%c",Dir_2[0]);
                }
               }
               printf ("\n");//fin ligne i
               }
           //affichage de la fin du plateau
           srand(large); /* delimitation de la taille de la largeur */

              for (i = 0; i < large; i++)
           {
               printf("=");

           }
        printf("\n");
        //afficher_tableau();
        //FIN AFFICHAGE
};

void creer_tableau(){
    //création du tableau
        int l,c;

        for (l = 0; l < haut; l++){
            for (c = 0; c < large; c++)
            {
                T =  rand() % (101);

                if (T<a)
               {
                   carte[l][c]=1;//#
               }
               else{
                carte[l][c]=0;//' '

               }

            }
        }
};

void creer_tableau_1(){
    //création du tableau
        int l,c;
        int a;
        printf("\n\n Entrez le pourcentage d'obstacles (conseil : 20 )  \n");
        scanf("%d", &a);// L'utilisateur entre la valeur de a
        for (l = 0; l < haut; l++){
            for (c = 0; c < large; c++)
            {
                T =  rand() % (101);

                if (T<a)
               {
                   carte[l][c]=1;//#
               }
               else{
                carte[l][c]=0;//' '

               }

            }
        }
};
void afficher_tableau(){
            int l,c;
        for (l = 0; l < haut; l++){
            for (c = 0; c < large; c++)
            {
                    printf("%d",carte[l][c]);

            }
                            printf("\n");

        }
};

void mettre_rovers(){
    carte[Abs_1][Ordo_1]=7;
    carte[Abs_2][Ordo_2]=2;
};

void clean_rovers(){
     int l,c;
        for (l = 0; l < haut; l++){
            for (c = 0; c < large; c++)
            {
                if (carte[l][c]==7 || carte[l][c]==2){
                    carte[l][c]=0;
            }

        }
}
};

void recup_donnee(){
{
    FILE* fichier = NULL;
    char dims[10] = "";
    char rover_1[100] = "";
    char rover_2[100] = "";

    fichier = fopen("mouvements.txt", "r");

    if (fichier != NULL)
    {
        //on récupère chaque ligne dans une variable
        fgets(dims, 100, fichier);
        fgets(rover_1, 100, fichier);
        fgets(rover_2, 100, fichier);
        fclose(fichier);

        const char *separator = " ";

        int len_dims = strlen(dims);
        char *hauteur = strtok(dims, separator);
        char *largeur = strtok(NULL, separator);
        printf("Hauteur carte : %s",hauteur," %s\n");
        printf("\nLargeur carte : %s", largeur," %s\n");

        int len_rover_1=strlen(rover_1);
        char *abs_1 = strtok(rover_1, separator);
        char *ordo_1 = strtok(NULL, separator);
        char *dir_1 = strtok(NULL, separator);
        char *com_1 = strtok(NULL, separator);
        strcpy(Dir_1,dir_1);//char*, com_1 to char[] in c

        printf("\nPosition robot 1: %s %s %s",abs_1,ordo_1,Dir_1," %s\n");
        printf("\nCommande 1 : %s",com_1,"%s\n");

        char *abs_2 = strtok(rover_2, separator);
        char *ordo_2 = strtok(NULL, separator);
        char *dir_2 = strtok(NULL, separator);
        char *com_2 = strtok(NULL, separator);
        strcpy(Dir_2,dir_2);//char*, com_2 to char[] in c


        printf("\nPosition robot 2: %s %s %s",abs_2,ordo_2,Dir_2," %s\n");
        printf("\nCommande 2 : %s",com_2,"%s\n");


        if (Dir_1[0]=='N'){
        strcpy(Dir_1,"^");//char*, com_2 to char[] in c
        }
        if (Dir_1[0]=='O'){
        strcpy(Dir_1,"<");//char*, com_2 to char[] in c
        }
        if (Dir_1[0]=='S'){
        strcpy(Dir_1,"v");//char*, com_2 to char[] in c
        }
        if (Dir_1[0]=='E'){
        strcpy(Dir_1,">");//char*, com_2 to char[] in c
        }


        if (Dir_2[0]=='N'){
        strcpy(Dir_2,"^");//char*, com_2 to char[] in c
        }
        if (Dir_2[0]=='O'){
        strcpy(Dir_2,"<");//char*, com_2 to char[] in c
        }
        if (Dir_2[0]=='S'){
        strcpy(Dir_2,"v");//char*, com_2 to char[] in c
        }
        if (Dir_2[0]=='E'){
        strcpy(Dir_2,">");//char*, com_2 to char[] in c
        }

        strcpy(Com_1,com_1);//char*, com_1 to char[] in c
        strcpy(Com_2,com_2);//char*, com_2 to char[] in c


        haut = atoi(hauteur);// char to int
        large = atoi(largeur);

        //on inverse pour le tableau
         Abs_1= atoi(abs_1);
         Ordo_1= atoi(ordo_1);

        Abs_2 = atoi(abs_2);
        Ordo_2 = atoi(ordo_2);
        };
};
};

void afficher_fin(){
        if (Dir_1[0]=='^'){
        strcpy(Dir_1,"N");//char*, com_2 to char[] in c
        }
        if (Dir_1[0]=='<'){
        strcpy(Dir_1,"O");//char*, com_2 to char[] in c
        }
        if (Dir_1[0]=='v'){
        strcpy(Dir_1,"S");//char*, com_2 to char[] in c
        }
        if (Dir_1[0]=='>'){
        strcpy(Dir_1,"E");//char*, com_2 to char[] in c
        }

        if (Dir_2[0]=='^'){
        strcpy(Dir_2,"N");//char*, com_2 to char[] in c
        }
        if (Dir_2[0]=='<'){
        strcpy(Dir_2,"O");//char*, com_2 to char[] in c
        }
        if (Dir_2[0]=='v'){
        strcpy(Dir_2,"S");//char*, com_2 to char[] in c
        }
        if (Dir_2[0]=='>'){
        strcpy(Dir_2,"E");//char*, com_2 to char[] in c
        }
        printf("\nPosition final robot 1: %d %d %s",Abs_1,Ordo_1,Dir_1," %s\n");
        printf("\nPosition final robot 2: %d %d %s",Abs_2,Ordo_2,Dir_2," %s\n");
        printf("\n");


};

void func_1(){
            int i=0;
            while (Com_1[i] != '\0'){
            //usleep(100000);

            usleep(10000);
            pthread_mutex_lock(&mutex);
            pthread_cond_signal(&cond1);


            printf("Rover 1 : Apres commande %c avec direction %s :",Com_1[i],Dir_1);

            if (Com_1[i]=='L'){

                    if (Dir_1[0]=='^'){
                        strcpy(Dir_1,"<");//to copy into the array.
                    }
                    else if (Dir_1[0]=='<'){
                        strcpy(Dir_1,"v");//to copy into the array.
                            }
                    else if (Dir_1[0]=='v'){
                                strcpy(Dir_1,">");//to copy into the array.
                            }
                    else if (Dir_1[0]=='>'){
                                strcpy(Dir_1,"^");//to copy into the array.
                            }

            }
            else if (Com_1[i]=='R'){
                    if (Dir_1[0]=='^'){
                        strcpy(Dir_1,">");//to copy into the array.
                    }
                    else if (Dir_1[0]=='<'){
                                strcpy(Dir_1,"^");//to copy into the array.
                            }
                    else if (Dir_1[0]=='v'){
                                strcpy(Dir_1,"<");//to copy into the array.
                            }
                    else if (Dir_1[0]=='>'){
                                strcpy(Dir_1,"v");//to copy into the array.
                            }
            }
            else if (Com_1[i]=='M'){
                    if (Dir_1[0]=='^'){
                            --Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='<'){
                            --Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Ordo_1;
                            }
                            }
                    else if (Dir_1[0]=='v'){
                            ++Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1>haut-1 || carte[Abs_1][Ordo_1]==2){
                                --Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='>'){
                            ++Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1>large-1 || carte[Abs_1][Ordo_1]==2){
                                --Ordo_1;
                            }
                            }
            }
            else if (Com_1[i]=='B'){
                    if (Dir_1[0]=='^'){
                            ++Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1>haut-1 || carte[Abs_1][Ordo_1]==2){
                                --Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='<'){
                            ++Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1>large-1 || carte[Abs_1][Ordo_1]==2){
                                --Ordo_1;
                            }
                            }
                    else if (Dir_1[0]=='v'){
                            --Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='>'){
                            --Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Ordo_1;
                            }
                            }}
            i++;
            //afficher_tableau();
            clean_rovers();
            mettre_rovers();

            pthread_cond_signal(&cond1);
            pthread_mutex_unlock(&mutex);

            afficher_carte_th();

        }
            pthread_exit(NULL);

};


void func_2(){
        int i=0;
        while (Com_2[i] != '\0'){
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond1,&mutex);


            //afficher_tableau();

            printf("Rover 2 : Apres commande %c avec direction %s :",Com_2[i],Dir_2);

            if (Com_2[i]=='L'){

                    if (Dir_2[0]=='^'){
                        strcpy(Dir_2,"<");//to copy into the array.
                    }
                    else if (Dir_2[0]=='<'){
                        strcpy(Dir_2,"v");//to copy into the array.
                            }
                    else if (Dir_2[0]=='v'){
                                strcpy(Dir_2,">");//to copy into the array.
                            }
                    else if (Dir_2[0]=='>'){
                                strcpy(Dir_2,"^");//to copy into the array.
                            }

            }
            else if (Com_2[i]=='R'){
                    if (Dir_2[0]=='^'){
                        strcpy(Dir_2,">");//to copy into the array.
                    }
                    else if (Dir_2[0]=='<'){
                                strcpy(Dir_2,"^");//to copy into the array.
                            }
                    else if (Dir_2[0]=='v'){
                                strcpy(Dir_2,"<");//to copy into the array.
                            }
                    else if (Dir_2[0]=='>'){
                                strcpy(Dir_2,"v");//to copy into the array.
                            }
            }
            else if (Com_2[i]=='M'){
                    if (Dir_2[0]=='^'){
                            --Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='<'){
                            --Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Ordo_2;
                            }
                            }
                    else if (Dir_2[0]=='v'){
                            ++Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2>haut-1 || carte[Abs_2][Ordo_2]==7){
                                --Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='E'){
                            ++Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2>large-1 || carte[Abs_2][Ordo_2]==7){
                                --Ordo_2;
                            }
                            }
            }
            else if (Com_2[i]=='B'){
                    if (Dir_2[0]=='^'){
                            ++Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2>haut-1 || carte[Abs_2][Ordo_2]==7){
                                --Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='<'){
                            ++Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2>large-1 || carte[Abs_2][Ordo_2]==7){
                                --Ordo_2;
                            }
                            }
                    else if (Dir_2[0]=='v'){
                            --Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='>'){
                            --Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Ordo_2;
                            }
                            }}
            i++;
            clean_rovers();
            mettre_rovers();

            pthread_cond_signal(&cond2);
            pthread_mutex_unlock(&mutex);


            afficher_carte_th();

        }
    pthread_exit(NULL);

    };


int main(int argc, char *argv[])
{
    int version;
    do {
    printf("Quelle version ?\n1 pour la version basique\n2 pour la version thread\n3 pour la version socket\n");
    scanf("%d",&version);
    }

    while (version != 1 && version != 2 && version!=3);

    if (version==1){
        recup_donnee();
        creer_tableau_1();
        printf("\n\nPosition initial :");
        mettre_rovers();
        afficher_carte();
        int i=0;
        //dep rover 1
            i=0;
            while (Com_1[i] != '\0'){
            printf("Rover 1 : Apres commande %c avec direction %s :",Com_1[i],Dir_1);

            if (Com_1[i]=='L'){

                    if (Dir_1[0]=='^'){
                        strcpy(Dir_1,"<");//to copy into the array.
                    }
                    else if (Dir_1[0]=='<'){
                        strcpy(Dir_1,"v");//to copy into the array.
                            }
                    else if (Dir_1[0]=='v'){
                                strcpy(Dir_1,">");//to copy into the array.
                            }
                    else if (Dir_1[0]=='>'){
                                strcpy(Dir_1,"^");//to copy into the array.
                            }

            }
            else if (Com_1[i]=='R'){
                    if (Dir_1[0]=='^'){
                        strcpy(Dir_1,">");//to copy into the array.
                    }
                    else if (Dir_1[0]=='<'){
                                strcpy(Dir_1,"^");//to copy into the array.
                            }
                    else if (Dir_1[0]=='v'){
                                strcpy(Dir_1,"<");//to copy into the array.
                            }
                    else if (Dir_1[0]=='>'){
                                strcpy(Dir_1,"v");//to copy into the array.
                            }
            }
            else if (Com_1[i]=='M'){
                    if (Dir_1[0]=='^'){
                            --Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='<'){
                            --Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Ordo_1;
                            }
                            }
                    else if (Dir_1[0]=='v'){
                            ++Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1>haut-1 || carte[Abs_1][Ordo_1]==2){
                                --Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='>'){
                            ++Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1>large-1 || carte[Abs_1][Ordo_1]==2){
                                --Ordo_1;
                            }
                            }
            }
            else if (Com_1[i]=='B'){
                    if (Dir_1[0]=='^'){
                            ++Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1>haut-1 || carte[Abs_1][Ordo_1]==2){
                                --Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='<'){
                            ++Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1>large-1 || carte[Abs_1][Ordo_1]==2){
                                --Ordo_1;
                            }
                            }
                    else if (Dir_1[0]=='v'){
                            --Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='>'){
                            --Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Ordo_1;
                            }
                            }}
            i++;
            //afficher_tableau();
            clean_rovers();
            mettre_rovers();
            afficher_carte();
        }
        printf("Fin deplacements rover 1 :");

        afficher_carte();

        i=0;
        while (Com_2[i] != '\0'){

            //afficher_tableau();

            printf("Rover 2 : Apres commande %c avec direction %s :",Com_2[i],Dir_2);

            if (Com_2[i]=='L'){

                    if (Dir_2[0]=='^'){
                        strcpy(Dir_2,"<");//to copy into the array.
                    }
                    else if (Dir_2[0]=='<'){
                        strcpy(Dir_2,"v");//to copy into the array.
                            }
                    else if (Dir_2[0]=='v'){
                                strcpy(Dir_2,">");//to copy into the array.
                            }
                    else if (Dir_2[0]=='>'){
                                strcpy(Dir_2,"^");//to copy into the array.
                            }

            }
            else if (Com_2[i]=='R'){
                    if (Dir_2[0]=='^'){
                        strcpy(Dir_2,">");//to copy into the array.
                    }
                    else if (Dir_2[0]=='<'){
                                strcpy(Dir_2,"^");//to copy into the array.
                            }
                    else if (Dir_2[0]=='v'){
                                strcpy(Dir_2,"<");//to copy into the array.
                            }
                    else if (Dir_2[0]=='>'){
                                strcpy(Dir_2,"v");//to copy into the array.
                            }
            }
            else if (Com_2[i]=='M'){
                    if (Dir_2[0]=='^'){
                            --Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='<'){
                            --Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Ordo_2;
                            }
                            }
                    else if (Dir_2[0]=='v'){
                            ++Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2>haut-1 || carte[Abs_2][Ordo_2]==7){
                                --Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='E'){
                            ++Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2>large-1 || carte[Abs_2][Ordo_2]==7){
                                --Ordo_2;
                            }
                            }
            }
            else if (Com_2[i]=='B'){
                    if (Dir_2[0]=='^'){
                            ++Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2>haut-1 || carte[Abs_2][Ordo_2]==7){
                                --Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='<'){
                            ++Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2>large-1 || carte[Abs_2][Ordo_2]==7){
                                --Ordo_2;
                            }
                            }
                    else if (Dir_2[0]=='v'){
                            --Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='>'){
                            --Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Ordo_2;
                            }
                            }}
            i++;
            clean_rovers();
            mettre_rovers();

            afficher_carte();

        }
        printf("Fin deplacements des deux rovers:"),

        afficher_carte();
        afficher_fin();

        return 0;
    }
    else if (version==2){
        recup_donnee();
        creer_tableau_1();
        printf("\n\nPosition initial :");
        mettre_rovers();
        //afficher_carte();

        pthread_t th_robot1;
        pthread_t th_robot2;
        pthread_t th_affichage;

        pthread_create(&th_affichage,NULL,afficher_carte_th,NULL); //Thread affichage
        pthread_create(&th_robot1,NULL,func_1,NULL); //Thread robot 1
        pthread_create(&th_robot2,NULL,func_2,NULL); //Thread robot 2

        pthread_join(th_affichage,NULL);
        pthread_join(th_robot1,NULL);
        pthread_join(th_robot2,NULL);

        printf("\n\nFin deplacements des deux rovers, position finale :\n");
        afficher_carte_th();
        afficher_fin();

    return 0;
    }

    else if (version==3){

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

    int s = 0,taille,bd,errno,lg = 40;
    char msg[lg];
    char msg1[] = "message bien recu ";

    struct sockaddr_in *padin; //pointeur adresse internet locale
    struct sockaddr_in *p_exp; //pointeur adresse internet expediteur (recuperée de l'entete paquet UDP recu)

    /* RAPPEL de cette structure
    struct sockaddr_in
    {
        short      sin_family;
        unsigned short   sin_port;
        struct   in_addr   sin_addr;
        char   sin_zero[8];
    };
    */
    s = socket(AF_INET, SOCK_DGRAM, AF_UNSPEC);
    if(s == -1){
        printf("erreur creation socket %d\n",errno);
        exit(-1);
    }
    printf("le socket est identifie par : %d \n",s);
    taille = sizeof(struct sockaddr_in);
    padin  = (struct sockaddr_in *) (malloc(taille));
    bzero((char*)padin,taille);
    padin -> sin_family = AF_INET;
    padin -> sin_port   = htons(LEPORT);
    bd = bind(s, (struct sockaddr *)padin, taille);

    if(bd == -1){
        printf("Erreur d'attachement : %d \n",errno);
        exit(-1);
    }
    p_exp = (struct sockaddr_in *) (malloc(sizeof(struct sockaddr_in)));
    int p_lgexp = sizeof(struct sockaddr_in);

   //recup_donnee();
        //POURCENTAGE ET INITIALISATION
        printf("\n\n Attente du pourcentage d'obstacles");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        a=atoi(msg);
        printf("\n Pourcentage : %d ",a);
        bd = sendto(s, "Pourcentage bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n\n Attente de la largeur de la carte ");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        large=atoi(msg);
        printf("\n Largeur : %d ",large);
        bd = sendto(s, "Largeur bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n\n Attente de la hauteur de la carte");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        haut=atoi(msg);
        printf("\n Hauteur : %d ",haut);
        bd = sendto(s, "Hauteur bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        creer_tableau();

        //ROBOT 1

        printf("\n\n Attente abscisse robot 1 ");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        Abs_1=atoi(msg);
        printf("\n Abs_1 = %d",Abs_1);
        bd = sendto(s, "Abs_1 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n\n Attente ordonnee robot 1 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        Ordo_1=atoi(msg);
        printf(" Ordo_1 = %d",Ordo_1);
        bd = sendto(s, "Ordo_1 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n\n Attente direction robot 1 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        strcpy(Dir_1,msg);//char*, com_2 to char[] in c
        printf(" Dir_1 = %s",Dir_1);
        bd = sendto(s, "Dir_1 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n Attente commandes robot 1");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        strcpy(Com_1,msg);//char*, com_2 to char[] in c
        printf("\n Com_1 = %s",Com_1);
        bd = sendto(s, "Com_1 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\nRecap robot 1: %d %d %s %s",Abs_1,Ordo_1,Dir_1,Com_1," %s");



                //ROBOT 2
        printf("\n\n Attente abscisse robot 2 ");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        Abs_2=atoi(msg);
        printf("\n Abs_2 = %d",Abs_2);
        bd = sendto(s, "Abs_2 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n\n Attente ordonnee robot 2 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        Ordo_2=atoi(msg);
        printf(" Ordo_2 = %d",Ordo_2);
        bd = sendto(s, "Ordo_2 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n\n Attente direction robot 2 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        strcpy(Dir_2,msg);//char*, com_2 to char[] in c
        printf(" Dir_2 = %s",Dir_2);
        bd = sendto(s, "Dir_2 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\n Attente commandes robot 1 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        if(bd == -1){
        printf("Erreur d'attachement : %d \n",bd);
        exit(-1);
            }
        strcpy(Com_2,msg);//char*, com_2 to char[] in c
        printf(" Com_2 = %s",Com_2);
        bd = sendto(s, "Com_2 bien recu ", lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\nRecap robot 2: %d %d %s %s",Abs_2,Ordo_2,Dir_2,Com_2);

        //CONV DONNES

        if (Dir_1[0]=="N"){
          printf("\n dans iffff\n");

        strcpy(Dir_1,"^");//char*, com_2 to char[] in c
        }
        else if (Dir_1[0]=='O'){
          printf("\n dans iffff\n");

        strcpy(Dir_1,"<");//char*, com_2 to char[] in c
        }
        else if (Dir_1[0]=='S'){
          printf("\n dans iffff\n");
        strcpy(Dir_1,"v");//char*, com_2 to char[] in c
        }
        else {
        strcpy(Dir_1,">");//char*, com_2 to char[] in c
        }


        if (Dir_2[0]=='N'){
          printf("\n dans iffff\n");
        strcpy(Dir_2,"^");//char*, com_2 to char[] in c
        }
        else if (Dir_2[0]=='O'){
          printf("\n dans iffff\n");

        strcpy(Dir_2,"<");//char*, com_2 to char[] in c
        }
        else if (Dir_2[0]=="S"){
        printf("\n dans iffff\n");

        strcpy(Dir_2,"v");//char*, com_2 to char[] in c
        }
        else {
        strcpy(Dir_2,">");//char*, com_2 to char[] in c
        }
    //MOUVEMENTS
        printf("\n\nPosition initial :");
        mettre_rovers();
        afficher_carte();
        int i=0;
        i=0;
        if(bd == -1){
            printf("Erreur receive %d\n",bd);
            exit(-1);
        }
        while (Com_1[i] != '\0'){
            //printf("Rover 1 : Apres commande %c avec direction %s :",Com_1[i],Dir_1);

            if (Com_1[i]=='L'){

                    if (Dir_1[0]=='^'){
                        strcpy(Dir_1,"<");//to copy into the array.
                    }
                    else if (Dir_1[0]=='<'){
                        strcpy(Dir_1,"v");//to copy into the array.
                            }
                    else if (Dir_1[0]=='v'){
                                strcpy(Dir_1,">");//to copy into the array.
                            }
                    else if (Dir_1[0]=='>'){
                                strcpy(Dir_1,"^");//to copy into the array.
                            }

            }
            else if (Com_1[i]=='R'){
                    if (Dir_1[0]=='^'){
                        strcpy(Dir_1,">");//to copy into the array.
                    }
                    else if (Dir_1[0]=='<'){
                                strcpy(Dir_1,"^");//to copy into the array.
                            }
                    else if (Dir_1[0]=='v'){
                                strcpy(Dir_1,"<");//to copy into the array.
                            }
                    else if (Dir_1[0]=='>'){
                                strcpy(Dir_1,"v");//to copy into the array.
                            }
            }
            else if (Com_1[i]=='M'){
                    if (Dir_1[0]=='^'){
                            --Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='<'){
                            --Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Ordo_1;
                            }
                            }
                    else if (Dir_1[0]=='v'){
                            ++Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1>haut-1 || carte[Abs_1][Ordo_1]==2){
                                --Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='>'){
                            ++Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1>large-1 || carte[Abs_1][Ordo_1]==2){
                                --Ordo_1;
                            }
                            }
            }
            else if (Com_1[i]=='B'){
                    if (Dir_1[0]=='^'){
                            ++Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1>haut-1 || carte[Abs_1][Ordo_1]==2){
                                --Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='<'){
                            ++Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1>large-1 || carte[Abs_1][Ordo_1]==2){
                                --Ordo_1;
                            }
                            }
                    else if (Dir_1[0]=='v'){
                            --Abs_1;
                            if (carte[Abs_1][Ordo_1]==1 || Abs_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Abs_1;
                            }
                            }
                    else if (Dir_1[0]=='>'){
                            --Ordo_1;
                            if (carte[Abs_1][Ordo_1]==1 || Ordo_1<0 || carte[Abs_1][Ordo_1]==2){
                                ++Ordo_1;
                            }
                            }}
            i++;
            //afficher_tableau();
            clean_rovers();
            mettre_rovers();
            //afficher_carte();
        }
        printf("Fin deplacements rover 1 :");

        afficher_carte();

        i=0;
        while (Com_2[i] != '\0'){

            //afficher_tableau();

            //printf("Rover 2 : Apres commande %c avec direction %s :",Com_2[i],Dir_2);

            if (Com_2[i]=='L'){

                    if (Dir_2[0]=='^'){
                        strcpy(Dir_2,"<");//to copy into the array.
                    }
                    else if (Dir_2[0]=='<'){
                        strcpy(Dir_2,"v");//to copy into the array.
                            }
                    else if (Dir_2[0]=='v'){
                                strcpy(Dir_2,">");//to copy into the array.
                            }
                    else if (Dir_2[0]=='>'){
                                strcpy(Dir_2,"^");//to copy into the array.
                            }

            }
            else if (Com_2[i]=='R'){
                    if (Dir_2[0]=='^'){
                        strcpy(Dir_2,">");//to copy into the array.
                    }
                    else if (Dir_2[0]=='<'){
                                strcpy(Dir_2,"^");//to copy into the array.
                            }
                    else if (Dir_2[0]=='v'){
                                strcpy(Dir_2,"<");//to copy into the array.
                            }
                    else if (Dir_2[0]=='>'){
                                strcpy(Dir_2,"v");//to copy into the array.
                            }
            }
            else if (Com_2[i]=='M'){
                    if (Dir_2[0]=='^'){
                            --Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='<'){
                            --Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Ordo_2;
                            }
                            }
                    else if (Dir_2[0]=='v'){
                            ++Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2>haut-1 || carte[Abs_2][Ordo_2]==7){
                                --Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='>'){
                            ++Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2>large-1 || carte[Abs_2][Ordo_2]==7){
                                --Ordo_2;
                            }
                            }
            }
            else if (Com_2[i]=='B'){
                    if (Dir_2[0]=='^'){
                            ++Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2>haut-1 || carte[Abs_2][Ordo_2]==7){
                                --Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='<'){
                            ++Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2>large-1 || carte[Abs_2][Ordo_2]==7){
                                --Ordo_2;
                            }
                            }
                    else if (Dir_2[0]=='v'){
                            --Abs_2;
                            if (carte[Abs_2][Ordo_2]==1 || Abs_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Abs_2;
                            }
                            }
                    else if (Dir_2[0]=='>'){
                            --Ordo_2;
                            if (carte[Abs_2][Ordo_2]==1 || Ordo_2<0 || carte[Abs_2][Ordo_2]==7){
                                ++Ordo_2;
                            }
                            }}
            i++;
            clean_rovers();
            mettre_rovers();
            //afficher_carte();

        }
        printf("\nFin deplacements des deux rovers:\n");
        //afficher_tableau();
        afficher_carte();
        if (Dir_1[0]=='^'){
        strcpy(Dir_1,"N");//char*, com_2 to char[] in c
        }
        else if(Dir_1[0]=='<'){
        strcpy(Dir_1,"O");//char*, com_2 to char[] in c
        }
        else if (Dir_1[0]=='>'){
        strcpy(Dir_1,"E");//char*, com_2 to char[] in c
        }
        else {
        strcpy(Dir_1,"S");//char*, com_2 to char[] in c
        }

        if (Dir_2[0]=='^'){
        strcpy(Dir_2,"N");//char*, com_2 to char[] in c
        }
        else if (Dir_2[0]=='<'){
        strcpy(Dir_2,"O");//char*, com_2 to char[] in c
        }
        else if (Dir_2[0]=='v'){
        strcpy(Dir_2,"S");//char*, com_2 to char[] in c
        }
        else {
        strcpy(Dir_2,"E");//char*, com_2 to char[] in c
        }


        printf("\nPosition final robot 1: %d %d %s",Abs_1,Ordo_1,Dir_1," %s\n");
        printf("\nPosition final robot 2: %d %d %s",Abs_2,Ordo_2,Dir_2," %s\n");


        printf("\n Attente reponse DF1 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        char* dir=Dir_1;
        bd = sendto(s,dir,lg,0,(struct sockaddr *)p_exp, taille);

        printf("\n Attente reponse DF2 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        char* dirEC=Dir_2;
        bd = sendto(s,dirEC,lg,0,(struct sockaddr *)p_exp, taille);

        printf("\n Attente reponse P1 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        char* pos_f_1=Dir_1+' '+atoi(Abs_1)+' '+ atoi(Ordo_1)+'\0';
        bd = sendto(s,pos_f_1, lg, 0, (struct sockaddr *)p_exp, taille);

        char* pos_f_2=Dir_2+' '+atoi(Abs_2)+' '+ atoi(Ordo_2)+'\0';
        printf("\n Attente reponse P2 \n");
        bd = recvfrom(s,msg,lg,0,(struct sockaddr *)p_exp, &p_lgexp);
        bd = sendto(s, pos_f_2, lg, 0, (struct sockaddr *)p_exp, taille);

        printf("\nFIN");

    close(s);
    return 0;

    }

}





