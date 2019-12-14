//Tarea 2
//Paolo Pietrantoni
//Joaquín De La Peña

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include <ctype.h>


//definicion de funciones

typedef struct cancion cancion;
const char *get_csv_field (char * tmp, int i);
cancion *crear_cancion (char * nombre, char *artista, char*duracion, char*album);

long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

//struct cancion
struct cancion{                 
    char*nombre;
    char *artista;
    char *duracion;
    char *album;
};

int main () {

    int op;

    Map * canciones = createMap(stringHash, stringEqual);     //crea mapas a trabajar
    Map * album = createMap(stringHash, stringEqual);
    Map * artist = createMap(stringHash, stringEqual);


    do{
        printf("ELIJA UNA OPCION: \n");
        printf("       1.- Importar musica desde un archivo\n");
        printf("       2.- Exportar musica CSV\n");
        printf("       3.- Agregar album \n");
        printf("       4.- Agregar cancion \n");
        printf("       5.- Eliminar artista \n");
        printf("       6.- Buscar cancion\n");
        printf("       7.- Buscar canciones de un artista\n");
        printf("       8.- Buscar album\n");
        printf("       9.- Salir\n");
        printf("Indique la opcion: ");
        scanf("%d", &op);
        fflush( stdin );
        printf("\n");

        if(op==1){
            FILE*fp;
            fp=fopen("canciones.csv","r");
            if(fp==NULL){
                printf("No se pudo cargar el archivo. \n");
                exit(1);
            }
            else{
                printf("Las canciones se cargaron correctamente!! \n");

                char linea[1024];

                //llena los mapas con las canciones
                while (fgets (linea, 1023, fp) != NULL){
                    char *nombre = get_csv_field(linea, 1);
                    char *artista = get_csv_field(linea, 2);
                    char *duracion = get_csv_field(linea, 3);
                    char *album = get_csv_field(linea, 4);
                    cancion *c = crear_cancion (nombre, artista, duracion, album);
                    insertMap(canciones, c->nombre, c);
                    insertMap(album,c->album,c);
                    insertMap(artist,c->artista,c);
                }
                
                fclose(fp);
            }
        }

        if (op==2){

            FILE*fp;
            fp=fopen("canciones.csv","r");

            FILE*f;
            f=fopen("cancion.csv", "w");

            int data=0;

            if(f==NULL){

                printf("No se pudo cargar el archivo. \n");
                exit(1);
            }
            else{
                
                //copia el archivo original en data, y lo pega en el nuevo archivo
                while ( (data = fgetc ( fp )) != EOF ) {
                    fputc ( data, f );
                }
                fclose ( fp );
                fclose ( f );
            }
        }

        if (op==3){

            char albuw[20];
            char fecha[30];
            int n;
            cancion * x = firstMap(album);
            cancion * s = firstMap(canciones);

            printf("Escriba el album que desea agregar:\n");
            scanf("%s",albuw);
            printf("Escriba su fecha de lanzamiento:\n");
            scanf("%s",fecha);

            x = searchMap(album,albuw);                       //busca en el mapa album, el album deseado
            char canciow[20];
            char awtista[20];
            char duwacion[20];

            if (x == NULL){                                //en caso de no existir el album pregunta los demas datos a agregar
                
                printf("Escriba el nombre de la cancion que desea agregar a este album\n");
                scanf("%s",canciow);
                s=searchMap(canciones,canciow);
                    
                
                //verifica que la cancion no exista ya
                if(s==NULL){                         
                    printf("Escriba el nombre del artista de la cancion que desea agregar a este album\n");
                    scanf("%s",awtista);
                    printf("Escriba la duracion de la cancion que desea agregar a este album\n");
                    scanf("%s",duwacion);
                    cancion *u = crear_cancion (canciow,awtista,duwacion, albuw);
                    insertMap(canciones, u->nombre, u);

                }
                else printf("esta cancion ya existe \n");

            }
            else{
                printf("Ya existe este album. \n");
                printf("desea seguir agregando canciones de todas formas?:    (seleccione numero)\n");
                printf("1-SI\n");
                printf("2-NO\n");
                scanf("%d", &n);

                if (n == 1){
                    printf("Escriba el nombre de la cancion que desea agregar a este album\n");
                    scanf("%s",canciow);
                    s=searchMap(canciones,canciow);

                    if(s==NULL){
                        printf("Escriba el nombre del artista de la cancion que desea agregar a este album\n");
                        scanf("%s",awtista);
                        printf("Escriba la duracion de la cancion que desea agregar a este album\n");
                        scanf("%s",duwacion);
                        cancion *u = crear_cancion (canciow,awtista,duwacion, albuw);
                        insertMap(canciones, u->nombre, u);
                    }
                    else {
                        printf("esta cancion ya existe \n");
                    }
                }
            }
        }

        if(op==4){
            char song[20];
            int n;
            cancion * x = firstMap(canciones);

            printf("Escriba la cancion que desea agregar:\n");
            scanf("%s",song);

            x = searchMap(canciones,song);
            char awtista[20];
            char duwacion[20];
            char albuw [20];

            if (x == NULL){

                printf("Escriba el nombre del artista de la cancion que desea agregar a este album\n");
                scanf("%s",awtista);
                printf("Escriba el album al que pertenece la cancion\n");
                scanf("%s",albuw);
                printf("Escriba la duracion de la cancion que desea agregar a este album\n");
                scanf("%s",duwacion);
                cancion *u = crear_cancion (song,awtista,duwacion, albuw);

                insertMap(canciones, u->nombre, u);

            }
            else {
                printf("esta cancion ya existe \n");
            }

        }

        if(op==5){
            char awtista[20];

            printf("Escriba el artista que desea eliminar:\n");
            scanf("%s",awtista);

            cancion * s = firstMap(canciones);

            while (s != NULL) {
                    if (strcmp(s->artista,awtista)==0) {
                        eraseKeyMap(canciones,s->nombre);
                    }
                    s = nextMap(canciones);
            }
        }

        if (op == 6){
            cancion * s = firstMap(canciones);
            char sonk [20];

            printf("Escriba el nombre de la cancion que desea buscar: \n");
            scanf("%s",sonk);

            s= searchMap(canciones,sonk);

            if(s==NULL)printf("No existe esta cancion  \n");
            else printf(" Cancion: %s , Artista: %s \n ", s->nombre, s->artista);

        }

        if (op == 7){
            cancion * s = firstMap(canciones);

            removeAllMap(artist);

            while (s != NULL) {
                insertMap(artist,s->artista,s);
                s = nextMap(canciones);
            }

            char art [20];
            int cont;
            printf("Escriba el nombre del artista que desea buscar: \n");
            scanf("%s",art);

            cancion * u = firstMap(artist);

            while(u != NULL){
                if (strcmp(art,u->artista)==0) {
                    printf("Cancion: %s  , Artista: %s ,  Album: %s  \n", u->nombre, u->artista, u->album);
                    cont++;
                }
                u = nextMap(artist);

            }
            if (cont<1) printf("no existe este artista \n");
        }

        if (op == 8){
           cancion * s = firstMap(canciones);

            removeAllMap(album);

            while (s != NULL) {
                insertMap(album,s->album,s);
                s = nextMap(canciones);
            }

            char albumm [20];
            int cont;
            printf("Escriba el nombre del album que desea buscar: \n");
            scanf("%s",albumm);

            cancion * u = firstMap(album);

            while(u != NULL){
                if (strcmp(albumm,u->album)==0) {
                    printf("Cancion: %s  , Artista: %s , Album: %s\n", u->nombre, u->artista, u->album);
                    cont++;
                }
                u = nextMap(album);

            }
            if (cont<1) printf("no existe este album \n");

        }

        if(op==9) break;
        printf("\n");

    }while(op!=9);

    return 0;
}


cancion *crear_cancion (char * nombre, char *artista, char*duracion, char*album){
    cancion *c = malloc(sizeof(cancion));
    c->nombre = nombre;
    c->artista = artista;
    c->duracion = duracion;
    c->album = album;
    return c;
}

const char *get_csv_field (char * tmp, int i){
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) if (!--i) return tok;
    return NULL;
}

