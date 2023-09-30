#include <stdio.h>
#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

// Estructura para representar un lugar de interés turístico
typedef struct PuntoInteres {
    char nombre[101];
    char tipo[101];
    char direccion[101];
    char horario[101];
    char descripcion[101];
} PuntoInteres;

// Estructura para representar un turista
typedef struct  {
    char pasaporte[100];
    char nombre[100];
    char pais[100];
    struct LugarFavorito* lugaresFavoritos;
} Turista;

// Estructura para representar un lugar favorito
typedef struct LugarFavorito {
    char nombre[100];
    struct LugarFavorito* siguiente;
} LugarFavorito;



void registrarPuntoInteres(HashMap * mapaInteres) // Función 1
{
  PuntoInteres* puntoInteres = (PuntoInteres *) malloc(sizeof(PuntoInteres)); // Se crea la variable para el punto de interés
  if (puntoInteres == NULL) // Si no se pudo asignar memoria
  { // Entonces
    printf("\nError al reservar memoria"); // Se indica en la consola
    exit(EXIT_FAILURE); // Finaliza el programa.
  }

  // Se solicitan los datos del punto
  printf("\nIngrese el nombre del punto: \n");
  scanf(" %100[^\n]", puntoInteres->nombre);

  printf("Ingrese el tipo del punto: \n");
  scanf(" %100[^\n]", puntoInteres->tipo);

  printf("Ingrese la dirección del punto: \n");
  scanf(" %100[^\n]", puntoInteres->direccion);

  printf("Ingrese el horario del punto: \n");
  scanf(" %100[^\n]", puntoInteres->horario);

  printf("Ingrese la descripción del punto: \n");
  scanf(" %100[^\n]", puntoInteres->descripcion);
  printf("\n");

  insertMap(mapaInteres, puntoInteres->nombre, puntoInteres); // Una vez con toda la información, se guarda en el mapa de puntos de interés.
}

void mostrarPuntoInteres(HashMap * mapaInteres) // Función 2
{
  char puntoBuscar[101];
  
  printf("Ingrese el nombre del punto a mostrar: \n"); // Se solicita el nombre del lugar.
  scanf(" %100[^\n]", puntoBuscar);

  Pair* resultado = searchMap(mapaInteres, puntoBuscar); // Se busca en el mapa.

  if (resultado != NULL) // Si existe
  {
    PuntoInteres* puntoEncontrado = (PuntoInteres *) resultado->value; // Se transforma el par en la estructura de un punto de interés
    printf("\nDatos del punto de interes \n"); // Se imprimen los datos del punto.
    printf("Nombre: %s \n", puntoEncontrado->nombre);
    printf("Tipo: %s \n", puntoEncontrado->tipo);
    printf("Dirección: %s \n", puntoEncontrado->direccion);
    printf("Horario: %s \n", puntoEncontrado->horario);
    printf("Descripción: %s \n\n", puntoEncontrado->descripcion);
  }
  else // Si no existe
  {
    printf("\nNo existe el punto de interés.\n\n");
  }
}

void eliminarPuntoInteres(HashMap * mapaInteres) // Función 3
{
  char puntoEliminar[101];

  printf("Ingrese el nombre del punto a eliminar: \n"); // Se solicita el nombre del punto a eliminar.
  scanf(" %100[^\n]", puntoEliminar);

  Pair* resultado = searchMap(mapaInteres, puntoEliminar); // Se busca en el mapa.

  if (resultado != NULL) // Si existe
  {
    eraseMap(mapaInteres, puntoEliminar); // Se borra del mapa.
    printf("\nPunto de interés eliminado exitosamente.\n\n");
  }
  else // Si no existe
  {
    printf("\nNo existe el punto de interés.\n\n");
  }
}

void registrarTurista(HashMap * mapaTurista){ // Función 4
  
  Turista * nuevo=(Turista*)malloc(sizeof(Turista)); // Se crea la variable para el turista.
  if (nuevo==NULL){ // Si no se pudo asignar memoria
    printf("error asignacion de memoria\n"); // Se indica en la consola
    exit(EXIT_FAILURE); // Finaliza el programa
  }
  // Se solicita la información del turista
  printf("\nIngrese pasaporte del turista.\n");
  scanf(" %101[^\n]", nuevo->pasaporte);
  printf("Ingrese nombre del turista.\n");
  scanf(" %101[^\n]", nuevo->nombre);
  printf("ingrese pais del turista.\n");
  scanf(" %101[^\n]", nuevo->pais);
  printf("\n");
  
  insertMap(mapaTurista, nuevo->pasaporte, nuevo); // Una vez con toda la información, se guarda en el mapa de turistas.
}


void agregarLugar(HashMap *mapaTurista, LugarFavorito * luagarfav){ // Función 5
  LugarFavorito*nuevo=(LugarFavorito*)malloc(sizeof(LugarFavorito)); // Se crea la variable del lugar favorito.
  if (nuevo==NULL){ // Si no se pudo asignar memoria
    printf("error asignacion de memoria.\n"); // Se indica en consola
    exit(EXIT_FAILURE); // Finaliza el programa
  }
  char buscar[101];
  printf("ingrese pasaporte del turista.\n"); // Se solicita el pasaporte del turista a buscar
  scanf("%100[^\n]", buscar);

  Pair * turista=searchMap(mapaTurista, buscar); // Se busca al turista en el mapa.
  if (turista==NULL){ // Si no se encuentra
    printf("Turista no encontrado.\n");
    return;
  }
  // Si se encuentra, se le asigna el lugar favorito.
  printf("ingrese lugar favorito del turista.\n");
  scanf(" %101[^\n]", nuevo->nombre);
  nuevo->siguiente=NULL;
}

void mostrarTuristas(HashMap * mapaTurista){ // Función 6
  char paisbuscar[101];
  int i=0; // Contador de turistas por país
  Turista * actual;
  printf("ingrese pais a buscar.\n"); // Se solicita el país a buscar
  scanf("%s", paisbuscar);
  
  Pair *current=firstMap(mapaTurista); // Puntero a la primera casilla con datos en el mapa.
  printf("Lista turistas por país: %s.\n", paisbuscar);
  while(current!=NULL){ // Mientras hayan casillas ocupadas
    actual=current->value; // Se pasan los datos del bucket, a una variable de tipo Turista
    if(strcmp(actual->pais, paisbuscar)==0){ // Si el país coincide con el que se busca
      printf("- %s.\n", actual->nombre); // Se imprime el nombre del turista

      LugarFavorito*lugar=actual->lugaresFavoritos;
      while(lugar!=NULL){ // Mientras tenga lugares favoritos
        printf("- %s.\n", lugar->nombre); // Se imprime el lugar
        lugar=lugar->siguiente;
      }
      i++;
    }
    current =nextMap(mapaTurista); // Se va la siguiente posición ocupada
  }
  if (i==0){ // Si no hubieron turistas de ese país
    printf("No hay turistas de este país.\n");
  }
}

void mostrarPuntoInteresxTipo(HashMap * mapaInteres) // Función 7
{
  char tipoBuscar[101];
  PuntoInteres * puntoActual;
  int contador = 0; // Contador para la cantidad de puntos x tipo

  printf("Ingrese el tipo a mostrar\n"); // Se solicita el tipo a buscar
  scanf(" %100[^\n]", tipoBuscar);

  Pair * current = firstMap(mapaInteres); // Puntero a la primera casilla con datos en el mapa.

  printf("Lista de tipo %s:\n", tipoBuscar);
  while (current != NULL) // Mientras el hayan casillas ocupadas
    {
      puntoActual = current->value; // Se pasan los datos de la casilla a una variable de tipo PuntoInteres
      if (strcmp(puntoActual->tipo, tipoBuscar) == 0) // Si el tipo en la casilla coincide con el tipo que se quiere mostrar
      {
        printf("%s \n", puntoActual->nombre); // Se imprime el nombre del lugar
        contador++; // Se aumenta el contador de lugares con ese tipo
      }
      current = nextMap(mapaInteres); // Se avanza a la siguiente casilla ocupada.
    }
  printf("\n");

  
  if (contador == 0) // Si el contador no subió, entonces no habían lugares de ese tipo.
  {
    printf("No hay lugares de este tipo. \n\n");
  }
}

void importarLugares(HashMap * mapaInteres, const char* archivo){
  FILE* archivocsv = fopen(archivo, "r");
  if (archivocsv==NULL){
    printf("no se encontró archivo CSV.\n");
    return;
  }
  char linea[500];
  while(fgets(linea, sizeof(linea), archivocsv)!=NULL){
    char nombre[101],tipo[101], direccion[101], horario[16], descripcion[101];
    sscanf(linea,"%100[^,],%100[^,],%100[^,],%15[^,],%100[^\n]", nombre, tipo, direccion,horario,descripcion);

    //agregar
    
    PuntoInteres*puntointeres=(PuntoInteres*)malloc(sizeof(puntointeres));
    if (puntointeres==NULL){
      exit(EXIT_FAILURE);
    }
    strcpy(puntointeres->nombre, nombre);
    strcpy(puntointeres->tipo, tipo);
    strcpy(puntointeres->direccion, direccion);
    strcpy(puntointeres->horario,horario);
    strcpy(puntointeres->descripcion, descripcion);

  insertMap(mapaInteres, puntointeres->nombre, puntointeres);
    
  }
  fclose(archivocsv);
  printf("Archivos importados con Exito.\n");
}


void importarTuristas(HashMap *mapaTurista, const char*archivo){
  FILE*archivocsv=fopen(archivo, "r");
  if(archivocsv==NULL){
    printf("no se encontró archivo CSV.\n");
    return;
  }
  char linea[500];
  while (fgets(linea,sizeof(linea), archivocsv)!=NULL){
    char pasaporte[101],nombre[101], pais[101], lugaresFavoritos[101];
    sscanf(linea,"%100[^,],%100[^,],%100[^,],%100[^\n]", pasaporte, nombre, pais,lugaresFavoritos);
    
    Turista*turista=(Turista*)malloc(sizeof(Turista));
    if (turista==NULL){
      exit(EXIT_FAILURE);
    }
    strcpy(turista->pasaporte, pasaporte);
    strcpy(turista->nombre, nombre);
    strcpy(turista->pais, pais);
    strcpy(turista->lugaresFavoritos,lugaresFavoritos);

  insertMap(mapaTurista, turista->nombre, turista);
    
  }
  fclose(archivocsv);
  printf("Archivos importados con Exito.\n");
  
}

void exportarLugares(HashMap* mapaInteres) // Función 9.1
{
  char nombreArchivo[101];
  printf("\nIngrese el nombre del archivo. Con la extensión .csv"); // Se solicita el nombre del archivo, este tiene que incluir la extensión de este.
  scanf(" %53[^\n]", nombreArchivo);
  
  FILE* archivoCSV = fopen(nombreArchivo, "w"); // Se abre el archivo
  if (archivoCSV==NULL){ // Si no se puede abrir el archivo
    printf("No se pudo abrir el archivo.\n");
    return; // Se regresa sin hacer nada.
  }
  fprintf(archivoCSV, "Nombre,Tipo,Dirección,Horario,Descripción\n"); // La primera linea de categorias del archivo

  Pair* current = firstMap(mapaInteres); // Puntero a la primera casilla ocupada en el mapa
  PuntoInteres* puntoActual;

  while (current != NULL) // Mientras hayan casillas ocupadas
    {
      puntoActual = current->value; // Se pasan los datos de la casilla a una variable de tipo PuntoInteres
      fprintf(archivoCSV, "%s,%s,%s,%s,%s\n", puntoActual->nombre, puntoActual->tipo, puntoActual->direccion, puntoActual->horario, puntoActual->descripcion); // Se añade el contenido de la variable al archivo
      current = nextMap(mapaInteres); // Se avanza a la siguiente casilla ocupada
    }
  fclose(archivoCSV); // Se cierra el archivo
}

void exportarTuristas(HashMap* mapaTurista) // Función 9.2
{
  char nombreArchivo[101];
  printf("\nIngrese el nombre del archivo. Con la extensión .csv"); // Se solicita el nombre del archivo, este tiene que incluir la extensión de este.
  scanf(" %53[^\n]", nombreArchivo);

  FILE* archivoCSV = fopen(nombreArchivo, "w"); // Se abre el archivo
  if (archivoCSV == NULL) // Si no se pudo abrir el archivo
  {
    printf("No se pudo abrir el archivo.\n");
    return; // Se regresa sin hacer nada
  }
  fprintf(archivoCSV, "Pasaporte,Nombre,Pais,LugaresFavoritos\n"); // La primera linea de categorias del archivo

  Pair* current = firstMap(mapaTurista); // Puntero a la primera casilla ocupada en el mapa
  Turista* turistaActual;
  LugarFavorito* lugarActual;

  while (current != NULL) // Mientras hayan casillas ocupadas
    {
      turistaActual = current->value; // Se pasan los datos de la casilla a una variable de tipo Turista
      fprintf(archivoCSV, "%s,%s,%s,", turistaActual->pasaporte, turistaActual->nombre, turistaActual->pais); // Se añade el contenido de la variable al archivo
      lugarActual = turistaActual->lugaresFavoritos;
      while (lugarActual != NULL) // Si el turista tiene lugares favoritos.
        {
          fprintf(archivoCSV, "%s;", lugarActual->nombre); // Se añaden al archivo
          lugarActual = lugarActual->siguiente; // Se avanza al siguiente
        }
      fprintf(archivoCSV, "\n");
      current = nextMap(mapaTurista); // Se avanza a la siguiente casilla ocupada
    }
  fclose(archivoCSV); // Se cierra el archivo
}

int main() {
  long capacidadInicial = 100;
  HashMap * mapaInteres = createMap(capacidadInicial); // Creación del mapa de puntos de interés
  HashMap *mapaTurista = createMap(capacidadInicial); // Creación del mapa de turistas
  LugarFavorito *luagarfav;//lista para lugares favoritos del turista
  //menu
  int opcion;
  
  do{
    printf("\nMenu:\n");
    printf("1.-Registrar punto de interés.\n");
    printf("2.-Mostrar datos de punto de interés.\n");
    printf("3.-Eliminar punto de interés.\n");
    printf("4.-Registrar turista.\n");
    printf("5.-Agregar lugar favorito a turista.\n");
    printf("6.-Mostrar turistas por país.\n");
    printf("7.-Mostrar todos los puntos de interés de un tipo.\n");
    printf("8.-Importar puntos de interés y turistas desde archivos CSV.\n");
    printf("9.-Exportar puntos de interés y turistas a archivos CSV.\n");
    printf("10.-Salir.\n");
    printf("\nSeleccione una opcion.\n");
    scanf("%d", &opcion);
    getchar();


    switch(opcion){
      case 1: // Función 1: Registrar punto de interés
        {
          registrarPuntoInteres(mapaInteres);
          break;
        }
      case 2: // Función 2: Mostrar los datos de un punto de interés
        {
          mostrarPuntoInteres(mapaInteres);
          break;
        }
      case 3: // Función 3: Eliminar un punto de interés
        {
          eliminarPuntoInteres(mapaInteres);
          break;
        }
      case 4:{ // Función 4: Registrar a un turista
        registrarTurista(mapaTurista);
        break;
      }
      case 5:{ // Función 5: Agregar un lugar favorito a un turista
        agregarLugar(mapaTurista,luagarfav);
        break;
      }
      case 6:{ // Función 6: Mostrar a los turistas de un país
        mostrarTuristas(mapaTurista);
        break;
      }
      case 7: // Función 7: Mostrar los puntos de interés, basados en un tipo/categoría 
        {
          mostrarPuntoInteresxTipo(mapaInteres);
          break;
        }
      case 8:{ // Función 8: Importar desde archivos CSV
        importarLugares(mapaInteres, "puntos_interes.csv");
        importarTuristas(mapaTurista, "turistas.csv");
        break;
      }
      case 9: // Función 9: Exportar hacia archivos CSV
        {
        exportarLugares(mapaInteres);
        exportarTuristas(mapaTurista);
        break;
        }
      case 10:{ // Opción 10: Salir del menú, para finalizar el programa.
        //salir
        printf("Saliendo.");
        break;
      }
      default:{
        printf("Seleccione una opcion valida.\n");  
      }
    
    }
  }
  while (opcion!=10);
  //liberarmemoria()
  return 0;
}