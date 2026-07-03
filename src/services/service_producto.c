#include "../../include/services/service_producto.h"
#include "../../include/models/model_productos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*define statements*/

// Funcion generado de IDs
void generarIdAleatorio(char *id) {
  char caracteres[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  static int inicializado = 0;

  if (!inicializado) {
    srand((unsigned)time(NULL));
    inicializado = 1;
  }

  for (int i = 0; i < LONGITUD_ID; i++) {
    id[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
  }

  id[LONGITUD_ID] = '\0';
}

int validarIdUnico(Inventario *inv, char *id) {
  for (int i = 0; i < inv->cantidad; i++) {
    if (strcmp(inv->producto[i].id, id) == 0) {
      return 1;
    }
  }
  return 0;
}

// Registra un producto con datos de entrada.
Producto crearProduct(const char *nombre, float precio) {
  Producto p = {0};
  generarIdAleatorio(p.id);
  // Forma segura de copiar una cadena
  strncpy(p.name, nombre, MAX_NAME - 1);
  p.name[MAX_NAME - 1] = '\0'; // Asegura la terminacion

  p.precio = precio;
  p.stock = 0;

  return p;
}

/******************************************
 * Esta funcion leer los datos del usuario
 * para registrar un producto
 * @Param void
 * @Return -> un producto
 * *****************************************/
Producto leerEntradaUsuario(Inventario *inv) {
  Producto p = {0};

  do {
    generarIdAleatorio(p.id);
  } while (validarIdUnico(inv, p.id));

  printf("Introduce el nombre del producto: ");
  if (fgets(p.name, MAX_NAME, stdin) !=
      NULL) {                             // Verifica que se haya leido bien
    p.name[strcspn(p.name, "\n")] = '\0'; // quita el salto de linea.
  }
  printf("Introduce el precio del producto: ");
  while (scanf("%f", &p.precio) != 1) {
    printf("[!] Precio invalido intenta de nuevo: ");
    while (getchar() != '\n')
      ; // Descarta la entrada invalida
  }
  while (getchar() != '\n')
    ; // limpia el buffer

  p.stock = 0;
  return p;
}
