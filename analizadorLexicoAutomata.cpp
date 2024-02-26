//Gustavo Flores Mejia

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class AnalizadorLexico {
private:
    string cadena_entrada;
    int posicion;

public:
    AnalizadorLexico(string cadena_entrada) : cadena_entrada(cadena_entrada), posicion(0) {}

    char siguiente_caracter() {
        if (posicion < cadena_entrada.length()) {
            return cadena_entrada[posicion++];
        } else {
            return '\0';
        }
    }
    
    void devolver_caracter() {
        if (posicion > 0) {
            posicion--;
        }
    }

    void analizar() {
        int estado = 0;
        string token = "";
        
        while (true) {
            char caracter = siguiente_caracter();
            
            switch (estado) {
                case 0:
                    if (isdigit(caracter)) {
                        token += caracter;
                        estado = 1;
                    } else if (caracter == '+') {
                        token += caracter;
                        estado = 8;
                    } else if (isspace(caracter)) {
                        estado = 0;
                    } else if (caracter == '\0') {
                        return;
                    } else {
                        token += caracter;
                        cout << "<error," << token << ">" << endl;
                        token = "";
                        estado = 0;
                    }
                    break;
                case 1:
                    if (isdigit(caracter)) {
                        token += caracter;
                    } else if (caracter == '.') {
                        token += caracter;
                        estado = 2;
                    } else {
                        cout << "<entero," << token << ">" << endl;
                        token = "";
                        estado = 0;
                        if (caracter != '\0') {
                            devolver_caracter();
                        }
                    }
                    break;
                case 2:
                    if (isdigit(caracter)) {
                        token += caracter;
                        estado = 3;
                    } else {
                        cout << "<error," << token << ">" << endl;
                        token = "";
                        estado = 0;
                    }
                    break;
                case 3:
                    if (isdigit(caracter)) {
                        token += caracter;
                        estado = 3;
                    } else if (caracter == 'E' || caracter == 'e') {
                        token += caracter;
                        estado = 4;
                    }else {
                        cout << "<flotante," << token << ">" << endl;
                        token = "";
                        estado = 0;
                        if (caracter != '\0') {
                            devolver_caracter();
                        }
                    }
                    break;
                case 4:
                    if (caracter == '+' || caracter == '-') {
                        token += caracter;
                        estado = 7;
                    } else {
                        cout << "<error," << token << ">" << endl;
                        token = "";
                        estado = 0;
                    }
                    break;
                case 7:
                    if (isdigit(caracter)) {
                        token += caracter;
                        estado = 9;
                    } else {
                        cout << "<error," << token << ">" << endl;
                        token = "";
                        estado = 0;
                    }
                    break;
                case 8:
                    if (caracter == '+') {
                        token += caracter;
                        estado = 10;
                    }else {
                        cout << "<suma," << token << ">" << endl;
                        token = "";
                        estado = 0;
                        if (caracter != '\0') {
                            devolver_caracter();
                        }
                    }
                    break;
                case 9:
                        cout << "<Exponente," << token << ">" << endl;
                        token = "";
                        estado = 0;
                        if (caracter != '\0') {
                            devolver_caracter();
                        }

                    break;
                case 10:
                    cout << "<incremento," << token << ">" << endl;
                    token = "";
                    estado = 0;
                    if (caracter != '\0') {
                            devolver_caracter();
                        }
                    break;
                default:
                    cout << "<error," << token << ">" << endl;
                    token = "";
                    estado = 0;
                    break;
            }
        }
    }
};

int main() {


    AnalizadorLexico analizador("5.25+23*325Ee12.5");
    analizador.analizar();
    return 0;
}

