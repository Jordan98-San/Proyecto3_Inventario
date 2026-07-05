#include "../../include/services/service_producto.h"
#include "../../include/models/model_productos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* define statements */

// Funcion generadora de IDs
void generarIdAleatorio(char *id) {
  char caracteres[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  for (int i = 0; i < LONGITUD_ID; i++) {
    id[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
  }

  id[LONGITUD_ID] = '\0';
}

int validarIdUnico(Inventario *inv, char *id) {
  if (inv == NULL || id == NULL) {
    return 0;
  }

  for (int i = 0; i < inv->cantidad; i++) {
    if (strcmp(inv->producto[i].codigo, id) == 0) {
      return 1;
    }
  }

  return 0;
}

Producto *buscarPorID(Inventario *inv, char *id) {
  if (inv == NULL || id == NULL) {
    return NULL;
  }

  for (int i = 0; i < inv->cantidad; i++) {
    if (strcmp(inv->producto[i].codigo, id) == 0) {
      return &inv->producto[i];
    }
  }

  return NULL; // Retorna NULL si el producto no existe
}

void mostrarProductoPorID(Inventario *inv, char *id) {
  Producto *productoEncontrado = buscarPorID(inv, id);

  if (productoEncontrado == NULL) {
    printf("\n[!] No existe un producto con ese codigo.\n");
    return;
  }

  productoEncontrado->utilidad = utilidadCalc(productoEncontrado);

  printf("\n========== PRODUCTO ENCONTRADO ==========\n");
  printf("Codigo: %s\n", productoEncontrado->codigo);
  printf("Nombre: %s\n", productoEncontrado->nombre);
  printf("Categoria: %s\n", productoEncontrado->categoria);
  printf("Precio de compra: %.2f\n", productoEncontrado->precioCompra);
  printf("Precio de venta: %.2f\n", productoEncontrado->precioVenta);
  printf("Cantidad: %u\n", productoEncontrado->cantidad);
  printf("Utilidad calculada: %.2f\n", productoEncontrado->utilidad);
  printf("=========================================\n");
}

// Registra un producto con datos de entrada
// Esta funcion podria borrarse no hace nada
Producto crearProduct(const char *nombre, float precio) {
  Producto p = {0};

  generarIdAleatorio(p.codigo);

  if (nombre != NULL) {
    strncpy(p.nombre, nombre, MAX_NAME - 1);
    p.nombre[MAX_NAME - 1] = '\0'; // Asegura la terminacion
  }

  strcpy(p.categoria, "Sin categoria");

  p.precioCompra = 0;
  p.precioVenta = precio;
  p.cantidad = 0;
  p.utilidad = utilidadCalc(&p);

  return p;
}

/******************************************
 * Esta funcion lee los datos del usuario
 * para registrar un producto
 * @Param -> Todo el inventario
 * @Return -> un producto
 * *****************************************/
Producto leerEntradaUsuario(Inventario *inv) {
  Producto p = {0};

  do {
    generarIdAleatorio(p.codigo);
  } while (validarIdUnico(inv, p.codigo));

  printf("Codigo generado: %s\n", p.codigo);

  printf("Introduce el nombre del producto: ");
  if (fgets(p.nombre, MAX_NAME, stdin) != NULL) {
    p.nombre[strcspn(p.nombre, "\n")] = '\0';
  }

  printf("Ingresa la categoria del producto: ");
  if (fgets(p.categoria, MAX_CATEGORIA, stdin) != NULL) {
    p.categoria[strcspn(p.categoria, "\n")] = '\0';
  }

  printf("Introduce el precio de compra del producto: ");
  while (scanf("%f", &p.precioCompra) != 1 || p.precioCompra <= 0) {
    printf("[!] Precio de compra invalido. Intenta de nuevo: ");

    while (getchar() != '\n')
      ;
  }

  while (getchar() != '\n')
    ;

  printf("Introduce el precio de venta del producto: ");
  while (scanf("%f", &p.precioVenta) != 1 || p.precioVenta <= p.precioCompra) {
    printf("[!] Precio de venta debe ser mayor al precio de compra. Intenta de nuevo: ");

    while (getchar() != '\n')
      ;
  }

  while (getchar() != '\n')
    ;

  printf("Introduce la cantidad: ");
  while (scanf("%u", &p.cantidad) != 1) {
    printf("[!] Cantidad invalida. Intenta de nuevo: ");

    while (getchar() != '\n')
      ;
  }

  while (getchar() != '\n')
    ;

  p.utilidad = utilidadCalc(&p);

  return p;
}

// Funcion para calcular la utilidad por producto, no de todo el inventario.
float utilidadCalc(Producto *p) {
  if (p == NULL) {
    return 0;
  }

  return (p->precioVenta - p->precioCompra) * p->cantidad;
}