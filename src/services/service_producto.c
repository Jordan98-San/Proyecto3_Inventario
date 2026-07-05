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
    printf("[!] Precio de venta debe ser mayor al precio de compra. Intenta de "
           "nuevo: ");

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

void actualizarProduct(Producto *p) {
  int opcion = 0;

  if (p == NULL) {
    printf("\n[!] Producto no encontrado.\n");
    return;
  }

  do {
    printf("\n========== ACTUALIZAR PRODUCTO ==========\n");
    printf("Producto actual: %s - %s\n", p->codigo, p->nombre);
    printf("1. Actualizar nombre\n");
    printf("2. Actualizar categoria\n");
    printf("3. Actualizar precio de compra\n");
    printf("4. Actualizar precio de venta\n");
    printf("5. Actualizar cantidad\n");
    printf("6. Actualizar todos los campos excepto codigo\n");
    printf("0. Terminar actualizacion\n");
    printf("Seleccione una opcion: ");

    scanf("%d", &opcion);
    while (getchar() != '\n')
      ;

    switch (opcion) {
    case 1:
      printf("Nuevo nombre: ");
      if (fgets(p->nombre, MAX_NAME, stdin) != NULL) {
        p->nombre[strcspn(p->nombre, "\n")] = '\0';
      }
      printf("[+] Nombre actualizado.\n");
      break;

    case 2:
      printf("Nueva categoria: ");
      if (fgets(p->categoria, MAX_CATEGORIA, stdin) != NULL) {
        p->categoria[strcspn(p->categoria, "\n")] = '\0';
      }
      printf("[+] Categoria actualizada.\n");
      break;

    case 3: {
      float nuevoPrecioCompra;

      printf("Nuevo precio de compra: ");
      while (scanf("%f", &nuevoPrecioCompra) != 1 || nuevoPrecioCompra <= 0 ||
             nuevoPrecioCompra >= p->precioVenta) {
        printf("[!] El precio de compra debe ser mayor a 0 y menor al precio de venta actual. Intenta de nuevo: ");
        while (getchar() != '\n')
          ;
      }

      while (getchar() != '\n')
        ;

      p->precioCompra = nuevoPrecioCompra;
      p->utilidad = utilidadCalc(p);

      printf("[+] Precio de compra actualizado.\n");
      break;
    }

    case 4: {
      float nuevoPrecioVenta;

      printf("Nuevo precio de venta: ");
      while (scanf("%f", &nuevoPrecioVenta) != 1 ||
             nuevoPrecioVenta <= p->precioCompra) {
        printf("[!] El precio de venta debe ser mayor al precio de compra. Intenta de nuevo: ");
        while (getchar() != '\n')
          ;
      }

      while (getchar() != '\n')
        ;

      p->precioVenta = nuevoPrecioVenta;
      p->utilidad = utilidadCalc(p);

      printf("[+] Precio de venta actualizado.\n");
      break;
    }

    case 5: {
      unsigned int nuevaCantidad;

      printf("Nueva cantidad: ");
      while (scanf("%u", &nuevaCantidad) != 1) {
        printf("[!] Cantidad invalida. Intenta de nuevo: ");
        while (getchar() != '\n')
          ;
      }

      while (getchar() != '\n')
        ;

      p->cantidad = nuevaCantidad;
      p->utilidad = utilidadCalc(p);

      printf("[+] Cantidad actualizada.\n");
      break;
    }

    case 6: {
      float nuevoPrecioCompra;
      float nuevoPrecioVenta;
      unsigned int nuevaCantidad;

      printf("Nuevo nombre: ");
      if (fgets(p->nombre, MAX_NAME, stdin) != NULL) {
        p->nombre[strcspn(p->nombre, "\n")] = '\0';
      }

      printf("Nueva categoria: ");
      if (fgets(p->categoria, MAX_CATEGORIA, stdin) != NULL) {
        p->categoria[strcspn(p->categoria, "\n")] = '\0';
      }

      printf("Nuevo precio de compra: ");
      while (scanf("%f", &nuevoPrecioCompra) != 1 || nuevoPrecioCompra <= 0) {
        printf("[!] Precio de compra invalido. Intenta de nuevo: ");
        while (getchar() != '\n')
          ;
      }

      while (getchar() != '\n')
        ;

      printf("Nuevo precio de venta: ");
      while (scanf("%f", &nuevoPrecioVenta) != 1 ||
             nuevoPrecioVenta <= nuevoPrecioCompra) {
        printf("[!] El precio de venta debe ser mayor al precio de compra. Intenta de nuevo: ");
        while (getchar() != '\n')
          ;
      }

      while (getchar() != '\n')
        ;

      printf("Nueva cantidad: ");
      while (scanf("%u", &nuevaCantidad) != 1) {
        printf("[!] Cantidad invalida. Intenta de nuevo: ");
        while (getchar() != '\n')
          ;
      }

      while (getchar() != '\n')
        ;

      p->precioCompra = nuevoPrecioCompra;
      p->precioVenta = nuevoPrecioVenta;
      p->cantidad = nuevaCantidad;
      p->utilidad = utilidadCalc(p);

      printf("[+] Producto actualizado correctamente.\n");
      break;
    }

    case 0:
      printf("[i] Actualizacion terminada.\n");
      break;

    default:
      printf("[!] Opcion invalida.\n");
      break;
    }

  } while (opcion != 0);
}

int eliminarProducto(Inventario *inv, char *id) {
  if (inv == NULL || id == NULL) {
    return 0;
  }

  for (int i = 0; i < inv->cantidad; i++) {
    if (strcmp(inv->producto[i].codigo, id) == 0) {

      for (int j = i; j < inv->cantidad - 1; j++) {
        inv->producto[j] = inv->producto[j + 1];
      }

      inv->cantidad--;

      return 1;
    }
  }

  return 0;
}

// Funcion para calcular la utilidad por producto, no de todo el inventario.
float utilidadTotalInventario(Inventario *inv) {
  float total = 0;

  if (inv == NULL) {
    return 0;
  }

  for (int i = 0; i < inv->cantidad; i++) {
    inv->producto[i].utilidad = utilidadCalc(&inv->producto[i]);
    total += inv->producto[i].utilidad;
  }

  return total;
}

// Funcion para calcular la utilidad por producto, no de todo el inventario.
float utilidadCalc(Producto *p) {
  if (p == NULL) {
    return 0;
  }

  return (p->precioVenta - p->precioCompra) * p->cantidad;
}