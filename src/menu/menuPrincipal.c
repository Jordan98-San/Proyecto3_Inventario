// src/menu/menuPrincipal.c

#include "../../include/menu/menuPrincipal.h"
#include "../../include/services/service_inventario.h"
#include "../../include/services/service_producto.h"
#include "../../include/storage/productos_s.h"
#include <stdio.h>

void iniciarMenu(void) {
  printf("==== Gensokyo SoftInv =====\n");

  Inventario inv;
  inicializarInventario(&inv);
  readProductoFromText(&inv);

  int opcion = 0;

  do {
    printf("\n========== MENU ==========\n");
    printf("1. Registrar Producto\n");
    printf("2. Listar Inventario en Memoria\n");
    printf("3. Buscar por Codigo\n");
    printf("4. Guardar cambios\n");
    printf("5. Salir y Guardar\n");
    printf("==========================\n");
    printf("Seleccione una opcion: ");

    scanf("%d", &opcion);
    while (getchar() != '\n')
      ;

    switch (opcion) {
    case 1: {
      Producto p = leerEntradaUsuario(&inv);
      agregarProducto(&inv, p);
      printf("\n[+] Producto agregado correctamente.\n");
      break;
    }

    case 2: {
      if (inv.cantidad == 0) {
        printf("\n[!] No hay productos registrados.\n");
      } else {
        printf("\n========== INVENTARIO ==========\n");

        for (int i = 0; i < inv.cantidad; i++) {
          inv.producto[i].utilidad = utilidadCalc(&inv.producto[i]);

          printf("[%s] %s | %s | P.Compra: $%.2f | P.Venta: $%.2f | "
                 "Cantidad: %u | Utilidad: $%.2f\n",
                 inv.producto[i].codigo,
                 inv.producto[i].nombre,
                 inv.producto[i].categoria,
                 inv.producto[i].precioCompra,
                 inv.producto[i].precioVenta,
                 inv.producto[i].cantidad,
                 inv.producto[i].utilidad);
        }
      }

      break;
    }

    case 3: {
      char codigo[LONGITUD_ID + 1];

      printf("\nIngrese el codigo del producto: ");
      scanf("%8s", codigo);

      while (getchar() != '\n')
        ;

      mostrarProductoPorID(&inv, codigo);

      break;
    }

    case 4: {
      saveProductInText(&inv);
      printf("\n[+] Cambios guardados correctamente.\n");
      break;
    }

    case 5: {
      saveProductInText(&inv);
      printf("\nHasta luego...\n");
      break;
    }

    default: {
      printf("\n[!] Opcion invalida.\n");
      break;
    }
    }

  } while (opcion != 5);
}