#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones_Censo.h"
#include "Funciones_Extras.h"

int inicializarViviendas(eViviendas* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL)
	{
		if (len >= 0)
		{
			for (i = 0; i < len; i++)
			{
				list[i].idViviendas = -1;
			}
			retorno = 0;
		}
	}

	return retorno;
}

int buscarSlotLibre(eViviendas* list, int len)
{
	int retorno = -1;

	if (list != NULL)
	{
		if (len >= 0)
		{
			for (int indice = 0; indice < len; indice++)
			{
				if(list[indice].idViviendas == -1)
				{
					retorno = indice;
					break;
				}
			}
		}
	}

	return retorno;
}

int altaVivienda(eViviendas* list, int len, int id, char calle[],int cantidadPersonas, int cantidadHabitaciones,int tipoVivienda, int legajoCensista)
{
	int retorno = -1;
	int slotLibre;
	eViviendas auxiliar;

	if (list != NULL)
	{
		if (len >= 0)
		{
			slotLibre = buscarSlotLibre(list, len);
			if (slotLibre >= 0)
			{
				auxiliar.idViviendas = id;
				strcpy(auxiliar.calle, calle);
				auxiliar.cantidadPersonas = cantidadPersonas;
				auxiliar.cantidadHabitaciones = cantidadHabitaciones;
				auxiliar.tipoVivienda = tipoVivienda;
				auxiliar.legajoCensista = legajoCensista;

				list[slotLibre] = auxiliar;
				retorno = 0;
			}
		}
	}

	return retorno;
}

int buscarViviendaPorId(eViviendas* list, int len,int id)
{
	int retorno = -1;

	if(list != NULL)
	{
		if(len >= 0 && id >= 20000)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].idViviendas == id)
				{
					retorno = i;
					break;
				}
			}
		}
	}

	return retorno;
}

int darDeBajaVivienda(eViviendas* list, int len, int indice)
{
	int retorno = -1;
	if(list != NULL)
	{
		if(len >= 0)
		{
			list[indice].idViviendas = -1;
			retorno = 0;
		}
	}
	return retorno;
}

int ordenarViviendasPorCalle(eViviendas* list, int len)
{
	eViviendas auxiliar;
	int retorno = -1;

	if (list != NULL)
		{
			if (len >= 0)
			{

				for (int i = 0; i < len; i++)
				{
					for(int j = i + 1; j < len - 1; j++)
					{
						if (strcmp(list[i].calle, list[j].calle) > 0)
						{
							auxiliar = list[j];
							list[j] = list[i];
							list[i] = auxiliar;
						}
						if(strcmp(list[i].calle, list[j].calle) == 0)
						{
							if(list[i].cantidadPersonas > list[j].cantidadPersonas)
							{
								auxiliar = list[j];
								list[j] = list[i];
								list[i] = auxiliar;
							}
						}
					}
				}
				retorno = 0;
			}
		}
	return retorno;
}

int mostrarViviendas(eViviendas* list, int len, eCensista* censista, int lenCensista, eTipoDeVivienda* tipo, int lenTipo)
{
	int retorno = -1;

	if (list != NULL)
	{
		if (len >= 0)
		{
			printf("\nCalle\t\t\t ID\t Cantidad de Personas  Cantidad de Habitaciones  Tipo de Vivienda  Censista\n");
			for (int i = 0; i < len; i++)
			{
				if(list[i].idViviendas >= 20000)
				{
					for(int j = 0; j < lenCensista; j++)
					{
						if(list[i].legajoCensista == censista[j].legajoCensista)
						{
							for(int k = 0; k < lenTipo; k++)
							{
								if(list[i].tipoVivienda == tipo[k].tipoVivienda)
								{
									printf("%-24s %-7d %-21d %-25d %-17s %d-%s\n", list[i].calle, list[i].idViviendas, list[i].cantidadPersonas,
											list[i].cantidadHabitaciones, tipo[k].descripcion, censista[j].legajoCensista, censista[j].nombre);
									break;
								}
							}
							break;
						}
					}
					retorno = 0;
				}
			}
		}
	}

	return retorno;
}

int mostrarCensistas (eCensista* censistas, int len)
{
	int retorno = -1;

	if(censistas != NULL && len > 0)
	{
		printf("\nLegajo\t Nombre\t  Edad\t Numero de telefono\n");
		for(int i = 0; i < len; i++)
		{
			printf("%-8d %-8s %-6d %s\n", censistas[i].legajoCensista, censistas[i].nombre, censistas[i].edad, censistas[i].telefono);
		}
		retorno = 0;
	}

	return retorno;
}
