#ifndef FUNCIONES_CENSO_H_
#define FUNCIONES_CENSO_H_

typedef struct
{
	int idViviendas;
	char calle [25];
	int cantidadPersonas;
	int cantidadHabitaciones;
	int tipoVivienda;
	int legajoCensista;
}eViviendas;

typedef struct
{
	int legajoCensista;
	char nombre[64];
	int edad;
	char telefono[11];
}eCensista;

typedef struct
{
	int tipoVivienda;
	char descripcion[15];
}eTipoDeVivienda;

int inicializarViviendas(eViviendas* list, int len);
int buscarSlotLibre(eViviendas* list, int len);
int altaVivienda(eViviendas* list, int len, int id, char calle[],int cantidadPersonas, int cantidadHabitaciones,int tipoVivienda, int legajoCensista);
int buscarViviendaPorId(eViviendas* list, int len,int id);
int darDeBajaVivienda(eViviendas* list, int len, int indice);
int ordenarViviendasPorCalle(eViviendas* list, int len);
int mostrarViviendas(eViviendas* list, int len, eCensista* censista, int lenCensista, eTipoDeVivienda* tipo, int lenTipo);
int mostrarCensistas (eCensista* censistas, int len);









#endif
