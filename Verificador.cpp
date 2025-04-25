#include <fstream>
#include <iostream>
#include <QCoreApplication>
#include <QImage>
#include "headers/bitops.h"

using namespace std;

unsigned char* loadPixels(QString input, int &width, int &height);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);

int run_verificador() {

    QString imagen1 = "originalRecuperada.bmp";
    QString imagen2 = "P1.bmp";
    QString imagen3 = "P2.bmp";
    QString mascara = "M.bmp";

    int width = 0, height = 0;
    int mascaraWidth = 0, mascaraHeight = 0;


    // Cargamos las imagenes de cada paso de recuperacion de I_0
    unsigned char *primerXOR = loadPixels(imagen3, width, height);

    if (primerXOR == nullptr) {
        cerr << "Error al cargar la imagen distorsionada." << endl;
        return -1; // Salimos si no se carga correctamente la imagen distorsionada.
    }

    unsigned char *rotacion3bits = loadPixels(imagen2, width, height);

    if (rotacion3bits == nullptr) {
        cerr << "Error al cargar la imagen distorsionada." << endl;
        return -1; // Salimos si no se carga correctamente la imagen distorsionada.
    }

    unsigned char *segundoXOR = loadPixels(imagen1, width, height);

    if (segundoXOR == nullptr) {
        cerr << "Error al cargar la imagen distorsionada." << endl;
        return -1; // Salimos si no se carga correctamente la imagen distorsionada.
    }

    // Cargamos mascara de color
    unsigned char *mascaraColor = loadPixels(mascara, mascaraWidth, mascaraHeight);

    if (mascaraColor == nullptr) {
        cerr << "Error al cargar la mascara." << endl;
        return -1; // Salimos si no se carga correctamente la mascara de color.
    }




    int n_pixels = 0;
    int totalBytes = n_pixels * 3;
    bool coincidencia = true;




    // Cargar datos de M0.txt y comparar con el el ultimo paso (segundoXOR)
    int semilla0 = 58077;

    unsigned int* valoresM0 = loadSeedMasking("M0.txt", semilla0, n_pixels);
    if (valoresM0 == nullptr) {
        cerr << "Error al cargar M0.txt" << endl;
        return -1;
    }

    for (int i = 0; i < totalBytes; i++) {
        int suma = int(segundoXOR[semilla0 + i]) + int(mascaraColor[i]);
        if (suma != int(valoresM0[i])) {
            coincidencia = false;
            break;
        }
    }

    if (coincidencia) {
        cout << "CORRECTO: originalrecuperada + M.bmp coincide con M0.txt" << endl;
    } else {
        cout << "INCORRECTO: originalrecuperada + M.bmp no coincide con M0.txt" << endl;
    }

    delete[] valoresM0;




    // Cargar datos de M1.txt y comparar con el segundo paso (rotacion3bits)
    int semilla1 = 100;

    unsigned int* valoresM1 = loadSeedMasking("M1.txt", semilla1, n_pixels);
    if (valoresM1 == nullptr) {
        cerr << "Error al cargar M1.txt" << endl;
        return -1;
    }

    for (int i = 0; i < totalBytes; i++) {
        int suma = int(rotacion3bits[semilla1 + i]) + int(mascaraColor[i]);
        if (suma != int(valoresM1[i])) {
            coincidencia = false;
            break;
        }
    }

    if (coincidencia) {
        cout << "CORRECTO: P1 + M.bmp coincide con M1.txt" << endl;
    } else {
        cout << "INCORRECTO: P1 + M.bmp no coincide con M1.txt" << endl;
    }

    delete[] valoresM1;




    // Cargar datos de M2.txt y comparar con el primer paso (primerXOR)
    int semilla2 = 15;

    unsigned int* valoresM2 = loadSeedMasking("M2.txt", semilla2, n_pixels);
    if (valoresM2 == nullptr) {
        cerr << "Error al cargar M2.txt" << endl;
        return -1;
    }

    for (int i = 0; i < totalBytes; i++) {
        int suma = int(primerXOR[semilla2 + i]) + int(mascaraColor[i]);

        if (suma != int(valoresM2[i])) {
            coincidencia = false;
            break;
        }
    }

    if (coincidencia) {
        cout << "CORRECTO: P2 + M.bmp coincide con M2.txt" << endl;
    } else {
        cout << "CORRECTO: P2 + M.bmp no coincide con M2.txt" << endl;
    }

    delete[] valoresM2;

    return 0;
}














