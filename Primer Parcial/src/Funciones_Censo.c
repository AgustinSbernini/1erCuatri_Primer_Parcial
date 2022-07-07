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

	if (list != NULL && censista != NULL && tipo != NULL)
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

int mostrarViviendasConCensistas(eViviendas* list, int len, eCensista* censista, int lenCensista, eTipoDeVivienda* tipo, int lenTipo)
{
	int retorno = -1;
	int contador = 0;

	if (list != NULL && censista != NULL && tipo != NULL)
	{
		if (len >= 0)
		{
			for (int i = 0; i < lenCensista; i++)
			{
				for (int l = 0; l < len; l++)
				{
					if((list[l].legajoCensista == censista[i].legajoCensista) && (list[l].idViviendas >= 20000))
					{
						contador++;
						break;
					}
				}
				if(censista[i].legajoCensista >= 100 && contador == 1)
				{
					printf("\n%d-%s %d años tel: %s", censista[i].legajoCensista, censista[i].nombre, censista[i].edad, censista[i].telefono);
					printf("\n  idVivienda\t Calle\t\t\t Habitantes  Habitaciones  Tipo de Vivienda\n");
					for(int j = 0; j < len; j++)
					{
						if(list[j].idViviendas >= 20000)
						{
							if(list[j].legajoCensista == censista[i].legajoCensista)
							{
								for(int k = 0; k < lenTipo; k++)
								{
									if(list[j].tipoVivienda == tipo[k].tipoVivienda)
									{
										printf("  %-14d %-23s %-11d %-13d %s\n", list[j].idViviendas, list[j].calle, list[j].cantidadPersonas,
												list[j].cantidadHabitaciones, tipo[k].descripcion);
									}
								}
							}
						}
					}
					retorno = 0;
				}
				contador = 0;
			}
		}
	}

	return retorno;
}

int buscarCantidadCensosRealizados(eViviendas* list, int len, eCensista* censista, int lenCensista, eCensosRealizados* cantCensos)
{
	int retorno = -1;
	int contador = 0;
	eCensosRealizados auxiliar;

	if (list != NULL && censista != NULL && cantCensos != NULL)
	{
		if (len >= 0)
		{
			for(int i = 0; i < lenCensista; i++)
			{
				if(censista[i].legajoCensista >= 100)
				{
					for(int k = 0; k < len; k++)
					{
						if((censista[i].legajoCensista == list[k].legajoCensista) && (list[k].idViviendas >= 20000))
						{
							contador++;
						}
					}
					cantCensos[i].legajoCensista = censista[i].legajoCensista;
					cantCensos[i].cantidadCensos = contador;
					strcpy(cantCensos[i].nombre, censista[i].nombre);
				}
				contador = 0;
			}

			for(int i = 0; i < lenCensista; i++)
			{
				for(int j = i; j < lenCensista; j++)
				{
					if(cantCensos[i].cantidadCensos < cantCensos[j].cantidadCensos)
					{
						auxiliar = cantCensos[j];
						cantCensos[j] = cantCensos[i];
						cantCensos[i] = auxiliar;
					}
				}
			}
			retorno = 0;
		}
	}

	return retorno;
}

int mostrarMayorCensista(eCensista* censista, int lenCensista, eCensosRealizados* cantCensos)
{
	int retorno = -1;

	if(censista != NULL && cantCensos != NULL)
	{
		if(lenCensista > 0)
		{
			printf("\nEl/La/Los censista/s que más censos realizaron fueron: \n");
			for(int i = 0; i < lenCensista; i++)
			{
				printf("  %d-%s\n", cantCensos[i].legajoCensista, cantCensos[i].nombre);

				if(cantCensos[i].cantidadCensos > cantCensos[i + 1].cantidadCensos)
				{
					return 0;
				}
			}
			retorno = 0;
		}
	}

	return retorno;
}
