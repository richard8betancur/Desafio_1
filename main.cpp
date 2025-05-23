/*
 * Programa demostrativo de manipulaciónprocesamiento de imágenes BMP en C++ usando Qt.
 *
 * Descripción:
 * Este programa realiza las siguientes tareas:
 * 1. Carga una imagen BMP desde un archivo (formato RGB sin usar estructuras ni STL).
 * 2. Modifica los valores RGB de los píxeles asignando un degradado artificial basado en su posición.
 * 3. Exporta la imagen modificada a un nuevo archivo BMP.
 * 4. Carga un archivo de texto que contiene una semilla (offset) y los resultados del enmascaramiento
 *    aplicados a una versión transformada de la imagen, en forma de tripletas RGB.
 * 5. Muestra en consola los valores cargados desde el archivo de enmascaramiento.
 * 6. Gestiona la memoria dinámicamente, liberando los recursos utilizados.
 *
 * Entradas:
 * - Archivo de imagen BMP de entrada ("I_O.bmp").
 * - Archivo de salida para guardar la imagen modificada ("I_D.bmp").
 * - Archivo de texto ("M1.txt") que contiene:
 *     • Una línea con la semilla inicial (offset).
 *     • Varias líneas con tripletas RGB resultantes del enmascaramiento.
 *
 * Salidas:
 * - Imagen BMP modificada ("I_D.bmp").
 * - Datos RGB leídos desde el archivo de enmascaramiento impresos por consola.
 *
 * Requiere:
 * - Librerías Qt para manejo de imágenes (QImage, QString).
 * - No utiliza estructuras ni STL. Solo arreglos dinámicos y memoria básica de C++.
 *
 * Autores: Augusto Salazar Y Aníbal Guerra
 * Fecha: 06/04/2025
 * Asistencia de ChatGPT para mejorar la forma y presentación del código fuente
 */

#include <fstream>
#include <iostream>
#include <QCoreApplication>
#include <QImage>
#include "headers/bitops.h"  // Incluir archivo de cabecera de operaciones bit a bit

using namespace std;

unsigned char* loadPixels(QString input, int &width, int &height);
bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);

int run_principal()
{
    QString archivoEntrada = "I_D.bmp";             // Imagen distorsionada final, usada como entrada
    QString archivoMascara = "I_M.bmp";             // Mascara usada en los XOR
    QString archivoSalidaFinal = "ResultadoF.bmp";  // Resultado de la imagen original recuperada

    int width = 0, height = 0;
    int maskWidth = 0, maskHeight = 0;

    // 1. Cargar la imagen distorsionada I_D.bmp
    unsigned char *imgDistorsionada = loadPixels(archivoEntrada, width, height);

    if (imgDistorsionada == nullptr) {
        cerr << "Error al cargar la imagen distorsionada." << endl;
        return -1; // Salimos si no se carga correctamente la imagen distorsionada
    }

    // 2. Cargar la mascara I_M.bmp
    unsigned char *mascara = loadPixels(archivoMascara, maskWidth, maskHeight);

    if (width != maskWidth || height != maskHeight) {
        cerr << "Error: Las dimensiones de la mascara y la imagen no son iguales." << endl;
        delete[] imgDistorsionada;
        delete[] mascara;
        return -1;
    }

    // 3. Aplicar XOR entre I_D.bmp y I_M.bmp (resultado intermedio (rotado IR3))
    unsigned char* P2 = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height * 3; i++) {
        P2[i] = xor_bits(imgDistorsionada[i], mascara[i]);
    }

    // Guardar P2 para verificacion externa
    if (!exportImage(P2, width, height, "P2.bmp")) {
        cerr << "Error al guardar la imagen P2.bmp" << endl;
    }

    // 4. Aplicar rotacion de 3 bits a la izquierda sobre P2 (recuperamos P1)
    unsigned char* P1 = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height * 3; i++) {
        P1[i] = rotate_left(P2[i], 3);
    }

    // Guardar P1 para verificacion externa
    if (!exportImage(P1, width, height, "P1.bmp")) {
        cerr << "Error al guardar la imagen P1.bmp" << endl;
    }

    // 5. XOR entre P1 y mascara (recuperamos la imagen original)
    unsigned char* originalRecuperada = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height * 3; i++) {
        originalRecuperada[i] = xor_bits(P1[i], mascara[i]);
    }

    if (!exportImage(originalRecuperada, width, height, "originalrecuperada.bmp")) {
        cerr << "Error al guardar la imagen originalrecuperada.bmp" << endl;
    }

    // 6. Exportar la imagen final recuperada
    bool exportOk = exportImage(originalRecuperada, width, height, archivoSalidaFinal);
    cout << "¿Exportación exitosa?: " << (exportOk ? "Sí" : "No") << endl;

    // Liberamos la memoria
    delete[] imgDistorsionada;
    delete[] mascara;
    delete[] P1;
    delete[] P2;
    delete[] originalRecuperada;


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

    return 0;
}

unsigned char* loadPixels(QString input, int &width, int &height){

    /*
 * @brief Carga una imagen BMP desde un archivo y extrae los datos de píxeles en formato RGB.
 *
 * Esta función utiliza la clase QImage de Qt para abrir una imagen en formato BMP, convertirla al
 * formato RGB888 (24 bits: 8 bits por canal), y copiar sus datos de píxeles a un arreglo dinámico
 * de tipo unsigned char. El arreglo contendrá los valores de los canales Rojo, Verde y Azul (R, G, B)
 * de cada píxel de la imagen, sin rellenos (padding).
 *
 * @param input Ruta del archivo de imagen BMP a cargar (tipo QString).
 * @param width Parámetro de salida que contendrá el ancho de la imagen cargada (en píxeles).
 * @param height Parámetro de salida que contendrá la altura de la imagen cargada (en píxeles).
 * @return Puntero a un arreglo dinámico que contiene los datos de los píxeles en formato RGB.
 *         Devuelve nullptr si la imagen no pudo cargarse.
 *
 * @note Es responsabilidad del usuario liberar la memoria asignada al arreglo devuelto usando `delete[]`.
 */

    // Cargar la imagen BMP desde el archivo especificado (usando Qt)
    QImage imagen(input);

    // Verifica si la imagen fue cargada correctamente
    if (imagen.isNull()) {
        cout << "Error: No se pudo cargar la imagen BMP." << endl;
        return nullptr; // Retorna un puntero nulo si la carga falló
    }

    // Convierte la imagen al formato RGB888 (3 canales de 8 bits sin transparencia)
    imagen = imagen.convertToFormat(QImage::Format_RGB888);

    // Obtiene el ancho y el alto de la imagen cargada
    width = imagen.width();
    height = imagen.height();

    // Calcula el tamaño total de datos (3 bytes por píxel: R, G, B)
    int dataSize = width * height * 3;

    // Reserva memoria dinámica para almacenar los valores RGB de cada píxel
    unsigned char* pixelData = new unsigned char[dataSize];

    // Copia cada línea de píxeles de la imagen Qt a nuestro arreglo lineal
    for (int y = 0; y < height; ++y) {
        const uchar* srcLine = imagen.scanLine(y);              // Línea original de la imagen con posible padding
        unsigned char* dstLine = pixelData + y * width * 3;     // Línea destino en el arreglo lineal sin padding
        memcpy(dstLine, srcLine, width * 3);                    // Copia los píxeles RGB de esa línea (sin padding)
    }

    // Retorna el puntero al arreglo de datos de píxeles cargado en memoria
    return pixelData;
}

bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida){
    /*
 * @brief Exporta una imagen en formato BMP a partir de un arreglo de píxeles en formato RGB.
 *
 * Esta función crea una imagen de tipo QImage utilizando los datos contenidos en el arreglo dinámico
 * `pixelData`, que debe representar una imagen en formato RGB888 (3 bytes por píxel, sin padding).
 * A continuación, copia los datos línea por línea a la imagen de salida y guarda el archivo resultante
 * en formato BMP en la ruta especificada.
 *
 * @param pixelData Puntero a un arreglo de bytes que contiene los datos RGB de la imagen a exportar.
 *                  El tamaño debe ser igual a width * height * 3 bytes.
 * @param width Ancho de la imagen en píxeles.
 * @param height Alto de la imagen en píxeles.
 * @param archivoSalida Ruta y nombre del archivo de salida en el que se guardará la imagen BMP (QString).
 *
 * @return true si la imagen se guardó exitosamente; false si ocurrió un error durante el proceso.
 *
 * @note La función no libera la memoria del arreglo pixelData; esta responsabilidad recae en el usuario.
 */

    // Crear una nueva imagen de salida con el mismo tamaño que la original
    // usando el formato RGB888 (3 bytes por píxel, sin canal alfa)
    QImage outputImage(width, height, QImage::Format_RGB888);

    // Copiar los datos de píxeles desde el buffer al objeto QImage
    for (int y = 0; y < height; ++y) {
        // outputImage.scanLine(y) devuelve un puntero a la línea y-ésima de píxeles en la imagen
        // pixelData + y * width * 3 apunta al inicio de la línea y-ésima en el buffer (sin padding)
        // width * 3 son los bytes a copiar (3 por píxel)
        memcpy(outputImage.scanLine(y), pixelData + y * width * 3, width * 3);
    }

    // Guardar la imagen en disco como archivo BMP
    if (!outputImage.save(archivoSalida, "BMP")) {
        // Si hubo un error al guardar, mostrar mensaje de error
        cout << "Error: No se pudo guardar la imagen BMP modificada.";
        return false; // Indica que la operación falló
    } else {
        // Si la imagen fue guardada correctamente, mostrar mensaje de éxito
        cout << "Imagen BMP modificada guardada como " << archivoSalida.toStdString() << endl;
        return true; // Indica éxito
    }

}

unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels){
    /*
 * @brief Carga la semilla y los resultados del enmascaramiento desde un archivo de texto.
 *
 * Esta función abre un archivo de texto que contiene una semilla en la primera línea y,
 * a continuación, una lista de valores RGB resultantes del proceso de enmascaramiento.
 * Primero cuenta cuántos tripletes de píxeles hay, luego reserva memoria dinámica
 * y finalmente carga los valores en un arreglo de enteros.
 *
 * @param nombreArchivo Ruta del archivo de texto que contiene la semilla y los valores RGB.
 * @param seed Variable de referencia donde se almacenará el valor entero de la semilla.
 * @param n_pixels Variable de referencia donde se almacenará la cantidad de píxeles leídos
 *                 (equivalente al número de líneas después de la semilla).
 *
 * @return Puntero a un arreglo dinámico de enteros que contiene los valores RGB
 *         en orden secuencial (R, G, B, R, G, B, ...). Devuelve nullptr si ocurre un error al abrir el archivo.
 *
 * @note Es responsabilidad del usuario liberar la memoria reservada con delete[].
 */

    // Abrir el archivo que contiene la semilla y los valores RGB
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        // Verificar si el archivo pudo abrirse correctamente
        cout << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }

    // Leer la semilla desde la primera línea del archivo
    archivo >> seed;

    int r, g, b;

    // Contar cuántos grupos de valores RGB hay en el archivo
    // Se asume que cada línea después de la semilla tiene tres valores (r, g, b)
    while (archivo >> r >> g >> b) {
        n_pixels++;  // Contamos la cantidad de píxeles
    }

    // Cerrar el archivo para volver a abrirlo desde el inicio
    archivo.close();
    archivo.open(nombreArchivo);

    // Verificar que se pudo reabrir el archivo correctamente
    if (!archivo.is_open()) {
        cout << "Error al reabrir el archivo." << endl;
        return nullptr;
    }

    // Reservar memoria dinámica para guardar todos los valores RGB
    // Cada píxel tiene 3 componentes: R, G y B
    unsigned int* RGB = new unsigned int[n_pixels * 3];

    // Leer nuevamente la semilla desde el archivo (se descarta su valor porque ya se cargó antes)
    archivo >> seed;

    // Leer y almacenar los valores RGB uno por uno en el arreglo dinámico
    for (int i = 0; i < n_pixels * 3; i += 3) {
        archivo >> r >> g >> b;
        RGB[i] = r;
        RGB[i + 1] = g;
        RGB[i + 2] = b;
    }

    // Cerrar el archivo después de terminar la lectura
    archivo.close();

    // Mostrar información de control en consola
    cout << "Semilla: " << seed << endl;
    cout << "Cantidad de píxeles leídos: " << n_pixels << endl;

    // Retornar el puntero al arreglo con los datos RGB
    return RGB;
}






















