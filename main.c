#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ren 6
#define col 6

char jugador1[20], jugador2[20];

int tempSize = ren * col;
int tempDiv = ren * col / 2;
int puntajeJ1, puntajeJ2 = 0;
int X1, Y1, X2, Y2 = 0;

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
            if(M[i][j] <= 9){ printf("0%-3d", M[i][j]); }
            else { printf("%-4d", M[i][j]); }
        }
        printf("\n");
    }
    printf("\n");
}

// Clonar matriz
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

// Desmascarar la matriz
void DesenmascararMatriz(int A[ren][col], int Amascara[ren][col]){
    if (X1 <= 0 || X1 > ren || Y1 <= 0 || Y1 > col || X2 <= 0 || X2 > ren || Y2 <= 0 || Y2 > col){
        printf("Tiene un numero fuera del rango\n");
        printf("Perdiste tu turno por no prestar atencion\n");
        turno = !turno;
    }
    else if (X1 == X2 && Y1 == Y2){
        printf("No se pueden repetir las casillas durante la misma jugada\n");
        printf("Perdiste tu turno por no prestar atencion\n");
        turno = !turno;
    }
    else if(Amascara[X1-1][Y1-1] != 0 || Amascara[X2-1][Y2-1] != 0){
        printf("No se pueden obtener las casillas que ya han sido desbloqueadas\n");
        printf("Perdiste tu turno por no prestar atencion\n");
        turno = !turno;
    }
    else if(A[X1-1][Y1-1] == A[X2-1][Y2-1]){
        Amascara[X1-1][Y1-1] = A[X1-1][Y1-1];
        Amascara[X2-1][Y2-1] = A[X2-1][Y2-1];
        printf("Primer numero elegido: %i\n", A[X1-1][Y1-1]);
        printf("Segundo numero elegido: %i\n", A[X2-1][Y2-1]);
        AgregarPuntaje();
    }
    else{
        printf("Fallaste\n");
        turno = !turno;
    }
}

// X1, Y1, X2, Y2
void Coordenadas(){
    printf("Introduzca el primer numero de la fila: ");
    scanf("%i", &X1);

    printf("Introduzca el primer numero de la columna: ");
    scanf("%i", &Y1);

    printf("Introduzca el segundo numero de la fila: ");
    scanf("%i", &X2);

    printf("Introduzca el segundo numero de la columna: ");
    scanf("%i", &Y2);
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
void FinDelJuego(int Amascara[ren][col]) {
    int contador = 0;
    for (int i = 0; i < ren; i++){
        for (int j = 0; j < col; j++) {
            if(Amascara[i][j] != 0){
                contador++;
            }
        }
    }

    if(contador == tempSize) {
        printf("FIN DEL JUEGO\n");
        if(puntajeJ1 == puntajeJ2){ printf("EMPATE\n"); }
        else if(puntajeJ1 > puntajeJ2){ printf("%s es el ganador con %i\n", jugador1, puntajeJ1); }
        else{ printf("%s es el ganador con %i\n", jugador2, puntajeJ2); }
        system("PAUSE");
        _exit(0);
    }
}

// Comprobar tamaño de la matriz para saber si es par
void ComprobarSizeMatriz() {
    if(tempSize%2 == 0) {  printf("Matriz es par\n"); }
    else { printf("El tamaño de la matriz debe ser par, favor de checarla"); _exit(0); }
}

// Bienvenida del juego, pregunta nombres de los jugadores
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
        ImprimeMatriz(copiaMatriz);
        ImprimeMatriz(matriz);

        if (turno) { printf("El turno es de: %s\n", jugador1); }
        else { printf("El turno es de: %s\n", jugador2); }

        Coordenadas();
        DesenmascararMatriz(copiaMatriz, matriz);

        FinDelJuego(matriz); // Comprueba si el juego ya acabó
        Continuar(); // Pregunta al usuario si desea seguir jugando
        system("cls"); // Limpia la consola
    }

    system("PAUSE");
    return 0;
}
