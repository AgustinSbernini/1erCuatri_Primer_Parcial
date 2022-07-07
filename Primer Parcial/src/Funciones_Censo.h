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

typedef struct
{
	int legajoCensista;
	char nombre[51];
	int cantidadCensos;
}eCensosRealizados;

/// @brief inicializo el ID de todas las viviendas en -1 para utilizarlo de bandera para verificar
///  cuales estan censadas.
/// @param list eViviendas* puntero al array de viviendas
/// @param len int tamaño del array
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido) o (0) si funciono bien
int inicializarViviendas(eViviendas* list, int len);

/// @brief recorre el array buscando un id en -1 (lo que significa que esta disponible para usar) y
/// devuelve el indice donde esta ubicado dicho slot.
/// @param list eViviendas* puntero al array de viviendas
/// @param len int tamaño del array
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido) o (indice) del slot disponible
int buscarSlotLibre(eViviendas* list, int len);

/// @brief utiliza buscarSlotLibre para conseguir el indice disponible y utiliza una estructura auxiliar
/// para cargar todos los datos recibidos en la estructura de eViviendas.
/// @param list eViviendas* puntero al array de viviendas
/// @param len int tamaño del array
/// @param id int id que se le va a asignar a la vivienda
/// @param calle char que se le va a asignar a la vivienda
/// @param cantidadPersonas int que se le va a asignar a la vivienda
/// @param cantidadHabitaciones int que se le va a asignar a la vivienda
/// @param tipoVivienda int que se le va a asignar a la vivienda
/// @param legajoCensista int que se le va a asignar a la vivienda
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido o no hay slot libre) o (0) si funciono bien
int altaVivienda(eViviendas* list, int len, int id, char calle[],int cantidadPersonas, int cantidadHabitaciones,int tipoVivienda, int legajoCensista);

/// @brief recorre el array buscando la coincidencia entre el id ingresado y el id de alguna de las
/// viviendas censadas y devuelve el indice donde esta cargada dicha vivienda.
/// @param list eViviendas* puntero al array de viviendas
/// @param len int tamaño del array
/// @param id int id ingresado por el usuario de la vivienda que esta buscando
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido) o (indice) de la vivienda buscada
int buscarViviendaPorId(eViviendas* list, int len,int id);

/// @brief cambia el id de la vivienda ingresada por indice a -1 para que pueda verificarse que
/// se dio de baja la vivienda y el slot esta disponible.
/// @param list eViviendas* puntero al array de viviendas
/// @param len int tamaño del array
/// @param indice int indice donde esta cargada la vivienda que se desea dar de baja
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido) o (0) si funciono bien
int darDeBajaVivienda(eViviendas* list, int len, int indice);

/// @brief recorre el array y utiliza una estructura auxiliar para poder ordenar mediante burbujeo
/// las viviendas por orden alfabetico de las calles. En caso de igualdad se utiliza la cantidad
/// de personas como segundo criterio.
/// @param list eViviendas* puntero al array de viviendas
/// @param len int tamaño del array
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido) o (0) si funciono bien
int ordenarViviendasPorCalle(eViviendas* list, int len);

/// @brief recorre el array de viviendas buscando viviendas censadas, al encontrarla recorre el array
/// de censistas y tipo de viviendas para encontrar los match. Una vez conseguido todos los datos
/// muestra en forma encolumnada las viviendas censadas con todos sus datos.
/// @param list eViviendas* puntero al array de viviendas
/// @param len int tamaño del array viviendas
/// @param censista eCensista* puntero al array de censista
/// @param lenCensista int tamaño del array censista
/// @param tipo puntero al array de tipo de vivienda
/// @param lenTipo int tamaño del array tipo de vivienda
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido) o (0) si funciono bien
int mostrarViviendas(eViviendas* list, int len, eCensista* censista, int lenCensista, eTipoDeVivienda* tipo, int lenTipo);

/// @brief recorre el array de censista y muestra en forma encolumnada los censistas registrados.
/// @param censistas eCensista* puntero al array de censistas
/// @param len int tamaño del array
/// @return int retorna (-1) si hubo algún error (puntero en NULL o tamaño invalido) o (0) si funciono bien
int mostrarCensistas (eCensista* censistas, int len);

int mostrarViviendasConCensistas(eViviendas* list, int len, eCensista* censista, int lenCensista, eTipoDeVivienda* tipo, int lenTipo);

int buscarCantidadCensosRealizados(eViviendas* list, int len, eCensista* censista, int lenCensista, eCensosRealizados* cantCensos);

int mostrarMayorCensista(eCensista* censista, int lenCensista, eCensosRealizados* cantCensos);
#endif
