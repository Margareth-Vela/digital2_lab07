/*Autor: Margareth Vela
 *Dispositivo: Launchpad Tiva C  
 *
 *Programa: Manejo de Memoria SD
 *Hardware: Pantalla TFT LCD
 *
 *Creado: Agosto 28, 2021
 *Ultima modificacion: Agosto 28, 2021
 */

//Librerias necesarias
#include <SPI.h>
#include <SD.h>

//Variables del programa
File myFile;
int opcion = 0;
char eleccion[20];
void setup() {

//Inicializacion comunicacion serial
  Serial.begin(9600);  
  SPI.setModule(0);  //Inicializacion comunicacion SPI en el modulo 0
  Serial.print("Initializing SD card...");
  
  pinMode(PA_3, OUTPUT);  //Se coloca el CS en el pin 12
  
//Se verifica que se haya iniciado correctamente la SD
  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  //Se imprime el mensaje inicial
  Serial.println("Seleccione el numero correspondiente a la imagen que desea abrir de la memoria");
  
  //Se imprimen los archivos existentes dentro de la SD card
  myFile = SD.open("/");
  printDirectory(myFile, 0);
  while(Serial.available()<1); //Se espera el numero seleccionado por el usuario
  Serial.readBytes(eleccion,sizeof eleccion); //Se imprime la imagen completa
  
  //Menu para identificar la imagen seleccionada por el usuario
  if (eleccion[0] == '1'){
      ReadFile("FANTASMA.txt"); //Se despliega el archivo del Fantasma de Pacman
  } else if (eleccion[0] == '2'){
      ReadFile("FLOR.txt"); //Se despliega el archivo de la Flor de Mario Bros
    }else if (eleccion[0] == '3'){
      ReadFile("HONGO.txt"); //Se despliega el archivo del Hongo de Mario Bros
    }
    else{ // Si el usuario no coloca alguna de las opciones disponibles, se despliega el siguiente mensaje
      Serial.println("No escribiste un comando valido, escribe unicamente un numero entre 1 y 3");
    } 
}

//Despliegue de los archivos dentro de la SD
void printDirectory(File dir, int numTabs) {
   opcion = 0;
  
   dir.rewindDirectory(); //Se coloca el puntero para leer los archivos de la SD al principio
   while(true) {
     
     File entry =  dir.openNextFile();  //Se abre el siguiente archivo del puntero
     if (! entry) {
       // Si ya no hay mas archivos
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     if (entry.isDirectory()) {  //Si no esta leyendo solamente un archivo
       
     } else {
       opcion ++;
       Serial.print(opcion);
       Serial.print(". ");
       Serial.println(entry.name());  //Se imprime el nombre del archivo
     }
     }
}

//Para leer el archivo
void ReadFile(char name[]){
  myFile = SD.open(name); //Se abre el arhivo dependiendo del argumento
  if (myFile) { //Si se logro abrir de manera correcta
    Serial.println(name); //se imprime el archivo

    while (myFile.available()) { //Se va leyendo cada caracter del archivo hasta completarlo
      Serial.write(myFile.read());
    }

    myFile.close(); //Se cierra el archivo
  } else {
    // Si el archivo no se abre correctamente
    Serial.println("Error al abrir el txt");
  }
  }
