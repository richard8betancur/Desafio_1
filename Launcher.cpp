// launcher.cpp
#include <iostream>

#define EJECUTAR_VERIFICADOR // Comentá esta línea para correr main.cpp

#ifdef EJECUTAR_VERIFICADOR
int run_verificador(); // Declaración de función en verificador.cpp
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
