#include <iostream>

#define EJECUTAR_VERIFICADOR // Comentar esta linea para correr el main.cpp principal


#ifdef EJECUTAR_VERIFICADOR
int run_verificador(); // Declaracion de funcion en verificador.cpp


#else
int run_principal();   // Declaración de función en main.cpp
#endif


int main() {
#ifdef EJECUTAR_VERIFICADOR
    return run_verificador();
#else
    return run_principal();
#endif
}
