#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ren 6
#define col 6

char jugador1[20];
char jugador2[20];

int tempSize = ren * col;
int tempDiv = ren * col / 2;

int puntajeJ1 = 0;
int puntajeJ2 = 0;

bool turno = true;

// Crea matriz principal con posiciones aleatorias
void CreaMatriz(int M[ren][col]){
    srand(time(NULL));
    int temp[tempSize];
    int contador = 0;
    int tempRandom = 0;

    for(int i = 0; i < 2; i++){
        for(int j = 1; j <= tempDiv; j++){
            temp[contador] = j;
            contador++;
        }
    }

    // Shuffle
    for (int i = 0; i < tempSize; i++){
        //int j = (rand()%tempSize-1)+1;
        int j = rand()%tempSize;
        tempRandom = temp[i];
        temp[i] = temp[j];
        temp[j] = tempRandom;
    }

    contador = 0;

    for (int i = 0; i < ren; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] = temp[contador];
            contador++;
        }
    }
}

// Imprime la matriz
void ImprimeMatriz(int M[ren][col]) {
    for (int i = 0; i < ren; i++) {
        for (int j = 0; j < col; j++) {
            if(M[i][j] <= 9){
                printf("0%-3d", M[i][j]);
            }
            else {
                printf("%-4d", M[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void CopiarMatriz(int M[ren][col], int C[ren][col]) {
    for(int i = 0; i < ren; i++) {
        for(int j = 0; j < col; j++) {
            C[i][j] = M[i][j];
        }
    }
}

// Enmascarar matriz
void EnmascararMatriz(int M[ren][col]) {
    for(int i = 0; i < ren; i++){
        for(int j = 0; j < col; j++){
            M[i][j] = 0;
        }
    }
}

// Sumar puntaje a los jugadores
void AgregarPuntaje() {
    if (turno) { puntajeJ1++; }
    else { puntajeJ2++; }
}

// Puntaje de los jugadores
void PuntajeGeneral(){
    printf("El puntaje de %s es de %i\n", jugador1, puntajeJ1);
    printf("El puntaje de %s es de %i\n", jugador2, puntajeJ2);
}

// Continuar juego
void Continuar() {
    char op;
    bool temp = true;
    do {
        printf("Seguir jugando: ");
        fflush(stdin);
        scanf("%c", &op);

        switch(op) {
            case 's':
            case 'S':
                temp = false;
                break;
            case 'n':
            case 'N':
                printf("FIN DE LA PARTIDA\n");
                PuntajeGeneral();
                _exit(0);
            default:
                printf("No se entiende el caracter\n");
                printf("S/s para si\nN/n para no\n");
        }
    } while(temp);
}

// Fin del juego
void FinDelJuego() {

}

void ComprobarSizeMatriz() {
    if(tempSize%2 == 0) {  printf("Matriz es par\n"); }
    else { printf("El tamaño de la matriz debe ser par, favor de checarla"); _exit(0); }
}

void Bienvenida(){
    printf("BIENVENIDOS AL JUEGO DEL MEMORAMA\n");
    printf("Introduzca el nombre del primer jugador: ");
    scanf("%s.\n", jugador1);
    printf("Introduzca el nombre del segundo jugador: ");
    scanf("%s.\n", jugador2);
}

int main() {
    ComprobarSizeMatriz();

    int matriz[ren][col];
    int copiaMatriz[ren][col];

    CreaMatriz(matriz); // Creamos la matriz original
    CopiarMatriz(matriz, copiaMatriz); // Copiamos la matriz original
    EnmascararMatriz(matriz); // Enmascaramos la matriz original

    Bienvenida();

    while (true) {
        PuntajeGeneral();
        ImprimeMatriz(matriz);

        if (turno) { printf("El turno es de: %s\n", jugador1); }
        else { printf("El turno es de: %s\n", jugador2); }

        FinDelJuego(); // Comprueba si el juego ya acabó
        Continuar(); // Pregunta al usuario si desea seguir jugando
        system("cls"); // Limpia la consola
    }

    system("PAUSE");
    return 0;
}
