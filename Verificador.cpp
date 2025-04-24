#include <iostream>
#include <fstream>
#include <QImage>
#include <QString>
#include "headers/bitops.h"  // XOR y rotaciones

using namespace std;

// Declaraciones de funciones externas
unsigned char* loadPixels(QString input, int &width, int &height);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);

int run_verificador() {

    QString archivoImagen = "I_D.bmp";     // Imagen distorsionada
    QString archivoMascara = "M.bmp";       // Máscara de color
    const char* archivoRastreo = "M1.txt";  // Archivo de rastreo

    int width = 0, height = 0;
    int maskWidth = 0, maskHeight = 0;

    // 1. Cargar imagen distorsionada y máscara de color
    unsigned char* imagen = loadPixels(archivoImagen, width, height);
    unsigned char* mascaraColor = loadPixels(archivoMascara, maskWidth, maskHeight);

    if (!imagen || !mascaraColor) {
        cerr << "Error al cargar la imagen o la máscara." << endl;
        return -1;
    }

    if (width != maskWidth || height != maskHeight) {
        cerr << "Dimensiones no coinciden entre la imagen y la máscara." << endl;
        delete[] imagen;
        delete[] mascaraColor;
        return -1;
    }

    // 2. Cargar archivo de rastreo
    int seed = 0, n_pixels = 0;
    unsigned int* datosRastreo = loadSeedMasking(archivoRastreo, seed, n_pixels);

    if (!datosRastreo) {
        cerr << "No se pudo cargar el archivo de rastreo." << endl;
        delete[] imagen;
        delete[] mascaraColor;
        return -1;
    }

    // 3. Aplicar transformación XOR como candidata
    bool coincide = true;
    for (int i = 0; i < n_pixels * 3; i++) {
        int idx = seed * 3 + i;
        if (idx >= width * height * 3) {
            coincide = false;
            break;
        }

        unsigned char pixelTransformado = xor_bits(imagen[idx], mascaraColor[i]);
        unsigned int suma = static_cast<unsigned int>(pixelTransformado) + static_cast<unsigned int>(mascaraColor[i]);

        if (suma != datosRastreo[i]) {
            coincide = false;
            break;
        }
    }

    if (coincide) {
        cout << "Transformaci\xC3\xB3n XOR coincide con el archivo de rastreo." << endl;
    } else {
        cout << "Transformaci\xC3\xB3n XOR no coincide." << endl;
    }

    // Limpiar memoria
    delete[] imagen;
    delete[] mascaraColor;
    delete[] datosRastreo;

    return 0;
}


