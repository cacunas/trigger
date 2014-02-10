trigger
=======

Cálculo de la probabilidad de detección de un sensor dada la activación del "trigger", para un material dado.

*Compilación y Ejecución*

Este proyecto usa la versión 9.6.4 de Geant4.

Para compilar, se debe crear una carpeta en la cual se escriban los archivos necesarios. También es necesario 
tener instalado cmake. En dicha carpeta (en este caso 'build') se ejecuta la siguiente línea:

$ cmake /path_to_CMakeList.txt

Luego de esto, si se cumple con las dependencias, se generará un Makefile. Con esto, se procede a compilar:

$ make

Lo que genera el ejecutable 'trigger'. Para correr se debe ejecutar como sigue:

$ ./trigger

Opcionalmente, se puede ejecutar usando el script de ejecución:

$ ./trigger run.mac

Al tertminar la ejecución, si todo funcionó bien, el programam genera un archivo llamado
'output.txt' el cual contiene los resultados de los eventos guardados.

Finalmente, para limpiar se puede ejecutar 

$ make clean
