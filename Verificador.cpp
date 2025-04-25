#include <fstream>
#include <iostream>
#include <QCoreApplication>
#include <QImage>
#include "headers/bitops.h"

using namespace std;

// Declaraciones de funciones auxiliares
unsigned char* loadPixels(QString input, int &width, int &height);

// Función principal de verificación
int verificarConImagentxt(QString imagenPath, const char* archivoTxt, int semilla, QString mascaraPath) {

    int width = 0, height = 0;
    int maskWidth = 0, maskHeight = 0;

    // 1. Cargar la imagen a verificar
    unsigned char* imagen = loadPixels(imagenPath, width, height);
    if (!imagen) {
        cerr << "Error al cargar la imagen: " << imagenPath.toStdString() << endl;
        return -1;
    }

    // 2. Cargar la máscara M.bmp
    unsigned char* mascara = loadPixels(mascaraPath, maskWidth, maskHeight);
    if (!mascara) {
        cerr << "Error al cargar la máscara: " << mascaraPath.toStdString() << endl;
        delete[] imagen;
        return -1;
    }

    int total_mascara = maskWidth * maskHeight * 3;

    // 4. Leer archivo mX.txt
    ifstream archivo(archivoTxt);

    // 5. Comparar pixel a pixel con la formula S(k) = I_D(k + s) + M(k)
    int coincidencias = 0;
    int tolerancia    = 5;  // Diferencia permitida en cada suma

    for (int k = 0; k < total_mascara; ++k) {
        int esperado;
        archivo >> esperado;

        // Suma directa con desplazamiento, máscara y comparación con tolerancia
        if (abs(((imagen[k + semilla] + mascara[k]) & 0xFF) - esperado) <= tolerancia) {
            coincidencias++;
        }
    }
    archivo.close();

    // 6. Mostrar resultados
    double porcentaje = 100.0 * coincidencias / total_mascara;

    cout << "Comparando: " << imagenPath.toStdString() << " con " << archivoTxt
         << " | Semilla: " << semilla << endl;
    cout << "   Coincidencias: " << coincidencias << " / " << total_mascara
         << " (" << porcentaje << "%)" << endl;

    if (porcentaje >= 80.0) {
        cout << "Coincidencia aceptable! Esta imagen podría ser " << archivoTxt << endl;
    } else {
        cout << "No parece coincidir con " << archivoTxt << endl;
    }

    // 7. Liberar memoria
    delete[] imagen;
    delete[] mascara;

    return 0;
}

// Función para ejecutar varias comparaciones
int run_verificador() {

    QString imagen1 = "originalRecuperada.bmp";
    QString imagen2 = "P1.bmp";
    QString imagen3 = "IR3.bmp";
    QString mascara = "M.bmp";

    // 1. Comparar M0 con imagen recuperada
    verificarConImagentxt(imagen1, "m0.txt", 58077, mascara);

    // 2. Comparar M1 con P1
    verificarConImagentxt(imagen2, "m1.txt", 100, mascara);

    // 3. Comparar M2 con IR3
    verificarConImagentxt(imagen3, "m2.txt", 15, mascara);

    return 0;
}






// Mostrar la semilla y los pixeles de cada archivo txt (M0, M1, M2)




/*
    int seed = 0;
    int n_pixels = 0;

    // Usamos la misma variable para cargar los datos de los tres archivos
    unsigned int* maskingData = nullptr;


    // Cargar y mostrar los datos de M0.txt
    maskingData = loadSeedMasking("M0.txt", seed, n_pixels);
    if (maskingData != nullptr) {
        for (int i = 0; i < n_pixels * 3; i += 3) {
            cout << "Pixel " << i / 3 << ": ("
                 << maskingData[i] << ", "
                 << maskingData[i + 1] << ", "
                 << maskingData[i + 2] << ")" << endl;
        }
        delete[] maskingData;  // Liberar memoria
        maskingData = nullptr;
    } else {
        cout << "Error al cargar M0.txt" << endl;
    }





    // Cargar y mostrar los datos de M1.txt
    maskingData = loadSeedMasking("M1.txt", seed, n_pixels);
    if (maskingData != nullptr) {
        for (int i = 0; i < n_pixels * 3; i += 3) {
            cout << "Pixel " << i / 3 << ": ("
                 << maskingData[i] << ", "
                 << maskingData[i + 1] << ", "
                 << maskingData[i + 2] << ")" << endl;
        }
        delete[] maskingData;  // Liberar memoria
        maskingData = nullptr;
    } else {
        cout << "Error al cargar M1.txt" << endl;
    }


    // Cargar y mostrar los datos de M2.txt
    maskingData = loadSeedMasking("M2.txt", seed, n_pixels);
    if (maskingData != nullptr) {
        for (int i = 0; i < n_pixels * 3; i += 3) {
            cout << "Pixel " << i / 3 << ": ("
                 << maskingData[i] << ", "
                 << maskingData[i + 1] << ", "
                 << maskingData[i + 2] << ")" << endl;
        }
        delete[] maskingData;  // Liberar memoria
        maskingData = nullptr;
    } else {
        cout << "Error al cargar M2.txt" << endl;
    }
*/







