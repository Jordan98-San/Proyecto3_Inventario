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
    if (strcmp(inv->producto[i].codigo, id) == 0) {
      return 1;
    }
  }
  return 0;
}

// Registra un producto con datos de entrada.
Producto crearProduct(const char *nombre, float precio) {
  Producto p = {0};
  generarIdAleatorio(p.codigo);
  // Forma segura de copiar una cadena
  strncpy(p.nombre, nombre, MAX_NAME - 1);
  p.nombre[MAX_NAME - 1] = '\0'; // Asegura la terminacion

  p.precioVenta = precio;
  p.cantidad = 0;

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
    generarIdAleatorio(p.codigo);
  } while (validarIdUnico(inv, p.codigo));

  printf("Introduce el nombre del producto: ");
  if (fgets(p.nombre, MAX_NAME, stdin) !=
      NULL) {                                 // Verifica que se haya leido bien
    p.nombre[strcspn(p.nombre, "\n")] = '\0'; // quita el salto de linea.
  }

  printf("Ingresa la categoria del producto: ");
  if (fgets(p.categoria, MAX_CATEGORIA, stdin) != NULL) {
    p.categoria[strcspn(p.categoria, "\n")] = '\0';
  }
  printf("Introduce el precio de Compra del producto: ");
  while (scanf("%f", &p.precioCompra) != 1) {
    printf("[!] Precio invalido intenta de nuevo: ");
    while (getchar() != '\n')
      ; // Descarta la entrada invalida
  }
  while (getchar() != '\n')
    ; // limpia el buffer

  printf("Introduce el precio venta del producto: ");
  while (scanf("%f", &p.precioVenta) != 1 || p.precioVenta <= p.precioCompra) {
    printf("[!]Precio venta debe ser mayor al precio compra");
    while (getchar() != '\n')
      ;
  }
  while (getchar() != '\n')
    ;

  printf("Introduce la cantidad: ");
  while (scanf("%d", &p.cantidad) != 1) {
    printf("[!] Cantidad invalida: ");
    while (getchar() != '\n')
      ;
  }
  while (getchar() != '\n')
    ;
  p.utilidad = utilidadCalc(&p);
  return p;
}
float utilidadCalc(Producto *p) {
  return (p->precioVenta - p->precioCompra) * p->cantidad;
}
