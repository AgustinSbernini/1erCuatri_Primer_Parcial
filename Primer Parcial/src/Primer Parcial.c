/*****************************************************************************************************
*	Programa: Primer Parcial
*
*	Objetivo:
*		Se necesita gestionar el Censo Nacional 2022 y para eso se deberá desarrollar lo siguiente:
*			MENU DE OPCIONES:
*				A. ALTA VIVENDA
*				B. MODIFICAR VIVIENDA: Se ingresará el idVivienda, permitiendo en un submenú modificar:
* 					* la calle
* 					* la cantidad de las personas
* 					* la cantidad de habitaciones
* 					* el tipo de vivienda
*				C. BAJA VIVIENDA: Se ingresará el idVivienda y se realizará una baja lógica.
*				D. LISTAR VIVENDAS: Hacer un único listado de todas las viviendas ordenados por calle
*				y ante igualdad de calle por cantidad de personas.
*				E. LISTAR CENSISTAS
*
*	Version: 1.0 del 25 de Mayo de 2022
*	Autor: Agustin Sbernini
*
******************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Funciones_Censo.h"
#include "Funciones_Extras.h"

#define TAM_VIVIENDAS 2000
#define TAM_CENSISTAS 3
#define TAM_CALLE 26
#define TAM_TIPOVIVIENDA 4
#define INICIOID 20000

int main(void) {

	char menuPrincipal;
	char calle[TAM_CALLE];
	int id = INICIOID;
	int cantPersonas;
	int cantHabitaciones;
	int tipoVivienda;
	int legajoCensista;
	int menuModificacion;
	int IDAModificar;
	int indiceAModificar;
	int verificadorDeViviendasCargadas = 0;

	setbuf(stdout, NULL);

	eViviendas viviendas[TAM_VIVIENDAS];
	eCensista censista[TAM_CENSISTAS] = {{100, "Ana", 34, "1203-2345"},
										{101, "Juan", 24, "4301-54678"},
										{102, "Sol", 47, "5902-37487"}};
	eTipoDeVivienda TipoDeViviendaCensada[TAM_TIPOVIVIENDA] =   {{1, "Casa"},
																{2, "Departamento"},
																{3, "Casilla"},
																{4, "Rancho"}};
	eCensosRealizados cantCensos[TAM_CENSISTAS];
	if(inicializarViviendas(viviendas, TAM_VIVIENDAS) != 0)
	{
		printf("\nError al intentar inicializar la estructura viviendas.\n");
	}

	do{

		printf("\nMenu principal:\n"
				"  A. ALTA VIVENDA.\n"
				"  B. MODIFICAR VIVIENDA.\n"
				"  C. BAJA VIVIENDA.\n"
				"  D. LISTAR VIVENDAS.\n"
				"  E. LISTAR CENSISTAS.\n"
				"  F. Listado de todos los datos de cada Censista con todos los datos de las viviendas censadas.\n"
				"  G. El o los censistas con más censos realizados.\n"
				"  H. Cerrar sistema.\n"
				"Elija una opción del menú: ");
		fflush(stdin);
		scanf("%c", &menuPrincipal);
		menuPrincipal = toupper(menuPrincipal);

		switch(menuPrincipal)
		{
			case 'A':
				if(verificadorDeViviendasCargadas == TAM_VIVIENDAS)
				{
					printf("\nLa lista de viviendas esta llena.\n");
				}
				else
				{
					utn_getName(calle, "\nIngrese la calle donde vive: ", "Error. Ingrese correctamente la calle.\n", TAM_CALLE);
					utn_getInt(&cantPersonas, "Ingrese la cantidad de personas que viven en la vivienda: ", "Error, Ingrese correctamente la cantidad de personas que viven en la vivienda.\n", 1, 100);
					utn_getInt(&cantHabitaciones, "Ingrese la cantidad de habitaciones de la vivienda: ", "Error, Ingrese correctamente la cantidad de habitaciones de la vivienda.\n", 0,100);
					utn_getInt(&tipoVivienda, "Ingrese el tipo de vivienda (Ingrese 1 para casa, 2 para departamento, 3 para casilla, 4 para rancho): ", "Error, Ingrese correctamente el tipo de vivienda.\n",1,4);
					utn_getInt(&legajoCensista, "Ingrese el legajo del censista(Ingrese 100 para Ana, 101 para Juan, 102 para Sol): ", "Error, ingrese un legajo valido.\n", 100, 102);
					if(altaVivienda(viviendas, TAM_VIVIENDAS, id, calle, cantPersonas,  cantHabitaciones, tipoVivienda,  legajoCensista) == 0)
					{
						printf("\nSe ha dado de alta a la vivienda con exito.\n");
						id++;
						verificadorDeViviendasCargadas++;
					}
					else
					{
						printf("\nHubo un error al intentar cargar la vivienda\n");
					}
				}
				break;
			case 'B':
				if(verificadorDeViviendasCargadas > 0)
				{
					printf("\nIndique el ID de la vivienda que desea modificar: ");
					fflush(stdin);
					scanf("%d", &IDAModificar);
					indiceAModificar = buscarViviendaPorId(viviendas, TAM_VIVIENDAS, IDAModificar);
					fflush(stdin);
					if(indiceAModificar < 0)
					{
						printf("\nError. El id ingresado no coincide con ninguna vivienda, por favor revise el listado para verificar el id\n");
					}
					else
					{
						do{
							utn_getInt(&menuModificacion,"\nMenu de Modificación:\n"
								"  1- Modificar la calle.\n"
								"  2- Modificar la cantidad de personas.\n"
								"  3- Modificar la cantidad de habitaciones.\n"
								"  4- Modificar el tipo de vivienda.\n"
								"  5- Volver al menú principal.\n"
								"Elija una opción: ", "\nError. Elija una opción valida.\n",1,5);

							switch(menuModificacion)
							{
								case 1:
									utn_getName(calle, "\nIngrese la modificacion de la calle donde vive: ", "Error. Ingrese correctamente la calle.\n", TAM_CALLE);
									strcpy(viviendas[indiceAModificar].calle, calle);
									printf("\nCalle modificada con exito.\n");
									break;
								case 2:
									utn_getInt(&cantPersonas, "\nIngrese la modificacion de la cantidad de personas que viven en la vivienda: ", "Error, Ingrese correctamente la cantidad de personas que viven en la vivienda.\n", 1, 100);
									viviendas[indiceAModificar].cantidadPersonas = cantPersonas;
									printf("\nCantidad de personas modificada con exito.\n");
									break;
								case 3:
									utn_getInt(&cantHabitaciones, "\nIngrese la modificacion de la cantidad de habitaciones de la vivienda: ", "Error, Ingrese correctamente la cantidad de habitaciones de la vivienda.\n", 0,100);
									viviendas[indiceAModificar].cantidadHabitaciones = cantHabitaciones;
									printf("\nCantidad de habitaciones modificadas con exito.\n");
									break;
								case 4:
									utn_getInt(&tipoVivienda, "\nIngrese la modificacion del tipo de vivienda (Ingrese 1 para casa, 2 para departamento, 3 para casilla, 4 para rancho): ", "Error, Ingrese correctamente el tipo de vivienda.\n",1,4);
									viviendas[indiceAModificar].tipoVivienda = tipoVivienda;
									printf("\nTipo de vivienda modificada con exito.\n");
									break;
							}
						}while(menuModificacion != 5);
					}
				}
				else
				{
					printf("\nLa lista de viviendas se encuentra vacía. Por favor cargue una vivienda.\n");
				}
				printf("\nVolviendo al Menú Principal.\n");
				break;
			case 'C':
				if(verificadorDeViviendasCargadas > 0)
				{
					printf("Indique el ID de la vivienda que desea dar de baja: ");
					fflush(stdin);
					scanf("%d", &IDAModificar);
					indiceAModificar = buscarViviendaPorId(viviendas, TAM_VIVIENDAS, IDAModificar);
					if (indiceAModificar > -1)
					{
						if(darDeBajaVivienda(viviendas, TAM_VIVIENDAS, indiceAModificar) == 0)
						{
							printf("\nSe ha dado de baja con exito la vivienda ubicada en %s.\n", viviendas[indiceAModificar].calle);
							verificadorDeViviendasCargadas--;
						}
						else
						{
							printf("\nHubo un error al intentar dar de baja a la vivienda.\n");
						}
					}
					else
					{
						printf("\nEl ID ingresado no coincide con ninguna vivienda, por favor revise el listado para verificar el id.\n\n");
					}
				}
				else
				{
					printf("\nLa lista de viviendas se encuentra vacía. Por favor cargue una vivienda.\n");
				}
				printf("\nVolviendo al Menú Principal.\n");
				break;
			case 'D':
				if(verificadorDeViviendasCargadas > 0)
				{
					if(ordenarViviendasPorCalle(viviendas, TAM_VIVIENDAS) == 0)
					{
						if(mostrarViviendas(viviendas, TAM_VIVIENDAS, censista, TAM_CENSISTAS, TipoDeViviendaCensada, TAM_TIPOVIVIENDA) != 0)
						{
							printf("\nHubo un error al intentar mostrar el listado de viviendas.\n");
						}
					}
					else
					{
						printf("\nHubo un error al intentar ordenar las viviendas.\n");
					}
				}
				else
				{
					printf("\nLa lista de viviendas se encuentra vacía. Por favor cargue una vivienda.\n");
				}
				printf("\nVolviendo al Menú Principal.\n");
				break;
			case 'E':
				mostrarCensistas(censista, TAM_CENSISTAS);
				break;
			case 'F':
				if(verificadorDeViviendasCargadas > 0)
				{
					if(ordenarViviendasPorCalle(viviendas, TAM_VIVIENDAS) == 0)
					{
						if(mostrarViviendasConCensistas(viviendas, TAM_VIVIENDAS, censista, TAM_CENSISTAS, TipoDeViviendaCensada, TAM_TIPOVIVIENDA) != 0)
						{
							printf("\nHubo un error al intentar mostrar el listado de viviendas.\n");
						}
					}
					else
					{
						printf("\nHubo un error al intentar ordenar las viviendas.\n");
					}
				}
				else
				{
					printf("\nLa lista de viviendas se encuentra vacía. Por favor cargue una vivienda.\n");
				}
				printf("\nVolviendo al Menú Principal.\n");
				break;
			case 'G':
				if(verificadorDeViviendasCargadas > 0)
				{
					if(buscarCantidadCensosRealizados(viviendas, TAM_VIVIENDAS,censista, TAM_CENSISTAS, cantCensos) == 0)
					{
						printf("\nEl censista con mas censos realizados fue %d-%s.\n",cantCensos[0].legajoCensista, cantCensos[0].nombre);
					}
					else
					{
						printf("\nHubo un error al intentar mostrar los censistas.\n");
					}
				}
				else
				{
					printf("\nLa lista de viviendas se encuentra vacía. Por favor cargue una vivienda.\n");
				}
				printf("\nVolviendo al Menú Principal.\n");
				break;
			case 'H':
				printf("\nCerrando sistema.\n");
				break;
			default:
				printf("\nError, ingrese una opción valida.\n");
		}

	}while(menuPrincipal != 'H');

	return 0;
}
