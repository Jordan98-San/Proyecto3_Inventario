// src/menu/menuPrincipal.c

#include "../../include/menu/menuPrincipal.h"
#include "../../include/services/service_inventario.h"
#include "../../include/services/service_producto.h"
#include "../../include/storage/productos_s.h"
#include <stdio.h>

void iniciarMenu(void) {
  printf("====Gensokyo SoftInv=====\n");

  Inventario inv;
  inicializarInventario(&inv);
  readProductoFromText(&inv);

  int opcion = 0;
  do {
    printf("1. Registar Producto\n");
    printf("2. Cargar Inventraio\n");
    printf("3. Salir\n");
    printf("Selccione una opcion: ");

    scanf("%d", &opcion);
    while (getchar() != '\n')
      ;

    switch (opcion) {
    case 1: {
      // Producto p = crearProduct("Pilsener", 16.50); Funcion de prueba
      Producto p = leerEntradaUsuario(&inv);
      agregarProducto(&inv, p);
      break;
    }
    case 2: {
      for (int i = 0; i < inv.cantidad; i++) {
        printf("[%s] %s $%2.f (Stock: %u)\n", inv.producto[i].id,
               inv.producto[i].name, inv.producto[i].precio,
               inv.producto[i].stock);
      }
      break;
    }
    case 3: {
      saveProductInText(&inv);
      printf("Hasta luego...");
      break;
    }
    default: {
      printf("Opcion invalidad.");
      break;
    }
    }

  } while (opcion != 3);
}
