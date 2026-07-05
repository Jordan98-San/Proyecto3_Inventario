// src/menu/menuPrincipal.c

#include "../../include/menu/menuPrincipal.h"
#include "../../include/services/service_inventario.h"
#include "../../include/services/service_producto.h"
#include "../../include/storage/productos_s.h"
#include <stdio.h>

void iniciarMenu(void) {
  printf("==== Inventario Softnv =====\n");

  Inventario inv;
  inicializarInventario(&inv);
  readProductoFromText(&inv);

  int opcion = 0;

  do {
    printf("\n========== MENU ==========\n");
    printf("1. Registrar Producto\n");
    printf("2. Listar Inventario \n");
    printf("3. Buscar por Codigo\n");
    printf("4. Actualizar\n");
    printf("5. Eliminar\n");
    printf("6. Guardar cambios\n");
    printf("7. Salir y Guardar\n");
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
                 inv.producto[i].codigo, inv.producto[i].nombre,
                 inv.producto[i].categoria, inv.producto[i].precioCompra,
                 inv.producto[i].precioVenta, inv.producto[i].cantidad,
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
      char codigo[LONGITUD_ID + 1];
      Producto *productoEncontrado;

      printf("\nIngrese el codigo del producto a actualizar: ");
      scanf("%8s", codigo);

      while (getchar() != '\n')
        ;

      productoEncontrado = buscarPorID(&inv, codigo);

      if (productoEncontrado == NULL) {
        printf("\n[!] No existe un producto con ese codigo.\n");
      } else {
        actualizarProduct(productoEncontrado);
      }

      break;
    }

    case 5: {
      char codigo[LONGITUD_ID + 1];
      char confirmacion;
      Producto *productoEncontrado;

      printf("\nIngrese el codigo del producto a eliminar: ");
      scanf("%8s", codigo);

      while (getchar() != '\n')
        ;

      productoEncontrado = buscarPorID(&inv, codigo);

      if (productoEncontrado == NULL) {
        printf("\n[!] No existe un producto con ese codigo.\n");
      } else {
        printf("\nProducto encontrado:\n");
        printf("Codigo: %s\n", productoEncontrado->codigo);
        printf("Nombre: %s\n", productoEncontrado->nombre);
        printf("Categoria: %s\n", productoEncontrado->categoria);

        printf("\nSeguro que deseas eliminar este producto? (s/n): ");
        scanf("%c", &confirmacion);

        while (getchar() != '\n')
          ;

        if (confirmacion == 's' || confirmacion == 'S') {
          if (eliminarProducto(&inv, codigo)) {
            printf("\n[+] Producto eliminado correctamente.\n");
          } else {
            printf("\n[!] No se pudo eliminar el producto.\n");
          }
        } else {
          printf("\n[i] Eliminacion cancelada.\n");
        }
      }

      break;
    }

    case 6: {
      saveProductInText(&inv);
      printf("\n[+] Cambios guardados correctamente.\n");
      break;
    }

    case 7: {
      saveProductInText(&inv);
      printf("\nHasta luego...\n");
      break;
    }

    default: {
      printf("\n[!] Opcion invalida.\n");
      break;
    }
    }

  } while (opcion != 7);
}
