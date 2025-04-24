#include <fstream>
#include <iostream>
#include <QCoreApplication>
#include <QImage>
#include "headers/bitops.h"  // Incluir archivo de cabecera de operaciones bit a bit

using namespace std;

unsigned char* loadPixels(QString input, int &width, int &height);
bool exportImage(unsigned char* pixelData, int width, int height, QString archivoSalida);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);

int run_verificador() {

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


    return 0;
}






