/* Para la persistencia de archivos modifiqué el código para que ejecute las opciones que el usuario desee en el menú 
y, si no existiese el archivo, para que lo cree el programa.*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct FileData 
{
    string name;// Nombre del archivo
    int size;// El tamaño en bytes
};
FileData files[1000];

int numberOfFiles;// Número de archivos que ya tenemos
int i;// Para bucles
int option;// La option del menu que elija el usuario

string tempText;// Para pedir datos al usuario
int tempNumber;

int main()
{

    do
    {
        numberOfFiles = 0; //inicializamos siempre nuestra numberofiles en 0 para actualizar los datos

        ifstream file; //cargamos los datos del archivo...
        file.open("FileData.txt", ios::in);
        if(file.is_open())
        {
            while(!file.eof())
            {
                file >> files[numberOfFiles].size;

                file.get();

                getline(file, files[numberOfFiles].name);

                if((!files[numberOfFiles].name.empty())&&(files[numberOfFiles].size != 0)) //si el renglon no esta vacio...
                {
                    numberOfFiles++;
                }
            }
        }
        file.close();

        // Menu principal
        cout << endl;
        cout << "Escoja una opcion:" << endl;
        cout << "1.- Aniadir datos de un nuevo archivo" << endl;
        cout << "2.- Mostrar los nombres de todos los archivos" << endl;
        cout << "3.- Mostrar archivos que sean de mas de un cierto tamanio" << endl;
        cout << "4.- Ver datos de un archivo" << endl;
        cout << "5.- Salir" << endl;

        cin >> option;
        cin.ignore();

        // Hacemos una cosa u otra según la opción escogida.
        switch(option)
        {
            case 1: // Añadir un dato nuevo

            if (numberOfFiles < 1000)   // Si queda hueco
            {
                cout << "Introduce el nombre del archivo: ";
                getline(cin, files[numberOfFiles].name);
                cout << "Introduce el tamanio en KB: ";
                cin >> files[numberOfFiles].size;

                ofstream oup_file; //guardamos los nuevos datos en el archivo y creamos uno si el archivo no existe...
                oup_file.open("FileData.txt", ios::app);
                if(oup_file.is_open())
                {
                    oup_file << files[numberOfFiles].size << " " << files[numberOfFiles].name << endl;
                }
                oup_file.close();

                numberOfFiles++;  // Y tenemos una ficha más
            }
            else   // Si no hay hueco para más archivos, avisamos.
            {
                cout << "¡Maximo de archivos alcanzado (1000)!" << endl;
            }
            break;
            case 2: // Mostrar todos

            for (i = 0; i < numberOfFiles; i++)
            {
                cout << "Nombre: " << files[i].name << "; Tamanio: " << files[i].size << "Kb" << endl;
            }

            break;
            case 3: // Mostrar según el tamaño.

            cout << "A partir de que tamanio quieres que te muestre? ";
            cin >> tempNumber;
            for (i=0; i<numberOfFiles; i++)
            {
                if (files[i].size >= tempNumber)
                {
                    cout << "Nombre: " << files[i].name << "; Tamanio: " << files[i].size << " Kb" << endl;
                }
            }
            break;
            case 4: // Ver todos los datos (pocos) de un archivo.

            cout << "De que archivo quieres ver todos los datos?";
            cin >> tempText;
            for (i=0; i<numberOfFiles; i++)
            {
                if (files[i].name == tempText)
                {
                    cout << "Nombre: " << files[i].name << "; Tamanio: " << files[i].size << " Kb" << endl;
                }
            }
            break;
            case 5: // Salir: avisamos de que salimos del programa.

            cout << "Fin del programa" << endl;

            break;
            default: // Otra opción: no válida

            cout << "¡Opcion desconocida!" << endl;

            break;
        }
    } while(option != 5);// Si la opción es 5, terminamos el programa.

    return 0;
}
