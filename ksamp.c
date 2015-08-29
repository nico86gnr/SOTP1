/*
 * ksamp.c
 *
 *  Created on: 21 de ago. de 2015
 *      Author: nico
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//funcion que muestra el tipo y modelo de CPU
void cpuInfo()
{
   FILE *fp;
   char buffer_tipo[255];
   char buffer_modelo[255];
   char *tipo=NULL;
   char *modelo=NULL;

   //se abre el fichero que contiene la informacion
   fp = fopen("/proc/cpuinfo", "r");

   while(tipo==NULL){
	   //copia hasta 254 caract. y añade uno nulo d fin d cadena
	   //o copia hasta encontrar un cambio de linea
	   fgets(buffer_tipo, 255, (FILE*)fp);

	   //funcion que busca en el buffer el string "vendor_id"
	   //en caso de encontralo posiciona al puntero alli
	   tipo = strstr(buffer_tipo,"vendor_id");

   }   fseek(fp, SEEK_SET, 0);//posiciona el cursor al incio del fichero

   while(modelo==NULL){
   	   //copia hasta 24 caract. y añade uno nulo d fin d cadena
   	   //o copia hasta encontrar un cambio de linea
   	   fgets(buffer_modelo, 255, (FILE*)fp);

   	   //funcion que busca en el buffer el string "model name"
   	   //en caso de encontralo posiciona al puntero alli
   	   modelo = strstr(buffer_modelo,"model name");

      }

   fclose(fp);

   while(*modelo!=':')modelo++;
   while(*tipo!=':')tipo++;


   //se imprime la informacion requerida
   printf("tipo de CPU %s", tipo);
   printf("modelo de CPU %s", modelo);

}

//funcion que muestra la version del kernel
void versionKernel(){

	FILE *fp;
	char buffer_kernel[255];
	int i=0;

	fp = fopen("/proc/version", "r");
	fgets(buffer_kernel, 255, (FILE*)fp);

	fclose(fp);

	while(buffer_kernel[i]!='(')i++;
	buffer_kernel[i]='\0';
	printf("Kernel: %s\n", buffer_kernel);

}

//funcion que muestra el tiempo que lleva el sistema funcionando
void tiempoSistema(){

	FILE *fp;
	float tiempo;
	int dias;
	int horas;
	int minutos;
	int segundos;

	fp = fopen("/proc/uptime", "r");

	//se lee el primer valor que representa el tiempo en segundos
	//y se lo almacena como un float en la variable tiempo
	fscanf(fp, "%f", &tiempo);

	//printf("uptime: %f\n", tiempo);

	//aca se hacen las conversiones para pasar el valor a dias horas
	//miunutos y segundos
	tiempo=(tiempo/86400);
	dias=(int)tiempo;

	tiempo=tiempo-dias;
	tiempo=tiempo*24;
	horas=(int)tiempo;

	tiempo=tiempo-horas;
	tiempo=tiempo*60;
	minutos=(int)tiempo;

	tiempo=tiempo-minutos;
	tiempo=tiempo*60;
	segundos=(int)tiempo;

	//se imprime la informacion requerida
	printf("tiempo transcurrido del sistema: %d %s" "\n\t\t\t\t "
			"",dias,"dias");
	printf("%d %s\n\t\t\t\t ",horas,"horas");
	printf("%d %s\n\t\t\t\t ",minutos,"minutos");
	printf("%d %s\n\n",segundos,"segundos");

	fclose(fp);

}

//funcion que muestra la cantidad de sistemas de archivos que soporta el kernel
void sistemasArchivos(){

	FILE *fp;
	char sistema_de_archivos[255];
	int cantidad=0;

	fp = fopen("/proc/filesystems", "r");

	//se recorre el fichero y se va incrementando la variable
	//cantidad a medida que cambia de linea
	while(!feof(fp)){
		fgets(sistema_de_archivos, 255, (FILE*)fp);
		cantidad++;
	}

	fclose(fp);

	//se imprime la info pedida
	printf("Cantidad de sistemas de archivos"
			" soportados por el kernel: %d\n", cantidad);

}

//funcion que muestra el tiempo de uso del usuario, sistema y proceso idle
void tiempoCPU(){

	FILE *fp;
	char cpu[10];
	//char cpub[255];
	int tiempo_usuario1;
	int tiempo_usuario2;
	int tiempo_sistema;
	int tiempo_idle;

	fp = fopen("/proc/stat", "r");
	/*fgets(cpub, 255, (FILE*)fp);
	fseek(fp, SEEK_SET, 0);*/

	//se guardan los valores leidos como enteros
	fscanf(fp,"%s""%d""%d""%d""%d",cpu,&tiempo_usuario1,&tiempo_usuario2,
				&tiempo_sistema,&tiempo_idle);
	//printf("%s\n",cpub);
	//printf(" %s",cpu);
	printf("tiempo de uso de usuario: %d\n",tiempo_usuario1);
	printf("tiempo de uso de usuario con baja prioridad: %d\n",tiempo_usuario2);
	printf("tiempo de uso de sistema: %d\n",tiempo_sistema);
	printf("tiempo de uso de proceso idle: %d\n",tiempo_idle);

}

//funcion que muestra los cambios de contexto
void cambioContexto(){

	FILE *fp;
	char buffer[50];
	char *cambio_contexto=NULL;

	fp = fopen("/proc/stat", "r");

	//se busca la linea con la informacion de contexto y una vez
	//encontrada se posiciona el puntero alli
	while(cambio_contexto==NULL){
		fgets(buffer, 25, (FILE*)fp);
		cambio_contexto=strstr(buffer,"ctxt");
	}

	while(*cambio_contexto!=' ')cambio_contexto++;

	//se imprime la informacion pedida
	printf("cantidad de cambios de contexto:%s",cambio_contexto);

}

//funcion que muestra la fecha y hora del inicio del sistema
void inicioSistema(){

	 FILE *in;
	    extern FILE *popen();
	    char buff[255];

	    in = popen("date -d \"`cut -f1 -d. /proc/uptime` seconds ago\"", "r");
	    printf("fecha y hora de inicio del sistema: ");
	    while(fgets(buff, sizeof(buff), in)!=NULL){
	        printf("%s", buff);
	    }
	pclose(in);
}

//funcion que muestra la cantidad de procesos desde que inicio el sistema
void nroProcesos(){

	FILE *fp;
	char buffer[50];
	char *procesos=NULL;

	fp = fopen("/proc/stat", "r");

	//se recorre el fichero y cuando se encuentra la linea de la informacion
	//pedida se posiciona el puntero alli
	while(procesos==NULL){
		fgets(buffer, 25, (FILE*)fp);
		procesos=strstr(buffer,"processes");
	}

	while(*procesos!=' ')procesos++;

	//se muestra la informacion pedida
	printf("cantidad de procesos:%s\n",procesos);

}

//funcion que mustra el total de memoria y la cantidad de memoria libre
void informacionMemoria(){
    FILE *fd;
	char meminfo1[255];
	char meminfo2[255];
	char str1 [20];

	fd = fopen("/proc/meminfo","r");
	fgets(meminfo1, 255, fd);
	fgets(meminfo2, 255, fd);
	fclose(fd);
	fflush(fd);

	//Filtra memoria total y la imprime
    sscanf(meminfo1,"%*s %s ", str1);
    printf("TotalMem: %s Kb\n",str1);

    //Filtra memoria libre y la imprime
    sscanf(meminfo2,"%*s %s ", str1);
    printf("FreeMem: %s Kb\n",str1);
}


void match(char* filename, char* matched, char* matchStr){
	FILE* fd;
	char* match = NULL;
	char buffer[500];
	fd = fopen(filename,"r");

	while(feof(fd)==0){
		fgets(buffer, 500, fd);
		match = strstr(buffer, matchStr);
		if(match!=NULL)
			break;
	}

	fclose(fd);
	strcpy(matched,match);
	return;
}

//funcion que muestra las peticiones a disco
void pedidosDisco(){
	char matched[256];
	unsigned int lecturas, escrituras, pedidos;

	match("/proc/diskstats", matched, "sda");
	sscanf(matched, "sda %u", &lecturas);
	sscanf(matched, "sda %*u %*u %*u %*u %u", &escrituras);
	pedidos = escrituras + lecturas;
	printf("Cantidad de peticiones a disco: %u\n", pedidos);
	return;
}

//funcion que muestra el promedio de carga
void informacionDisco(){
	FILE *archivo;
	char aux[255];
	float promedio;

		archivo=fopen("/proc/loadavg","r");

		fscanf(archivo, "%s", aux);
		promedio = atof(aux);
		printf("Promedio de carga en el ultimo minuto: %.2f\n",promedio);
		fclose(archivo);

}


int main(int argc, char *argv[]){

	printf("\n\n\t\t\t KSAMP\n");
	printf("\t\t\t -----\n\n");

	//si el main solo tiene un argumento
	if(argc==1){
		printf("PARTE B \n\n");
		cpuInfo();
		versionKernel();
		tiempoSistema();
		sistemasArchivos();
		printf("\n\n");
		}
	//si el main tiene dos argumentos y el segundo es "-s"
	else if(argc==2 && strcmp(argv[1],"-s")==0){
			printf("PARTE C \n\n");
			cpuInfo();
			versionKernel();
			tiempoSistema();
			sistemasArchivos();
			tiempoCPU();
			cambioContexto();
			inicioSistema();
			nroProcesos();
			printf("\n\n");
		}
	//si el main tiene cuatro argumentos, siendo el segundo "-l"
	//y el tercero y cuarto un entero
	else if(argc==4 && strcmp(argv[1],"-l")==0 && atoi(argv[2])!=0
		&& atoi(argv[3])!=0){
			printf("PARTE D \n\n");
			int intervalo=atoi(argv[2]);
			int duracion=atoi(argv[3]);
			int repeticiones=duracion/intervalo;

			cpuInfo();
			versionKernel();
			tiempoSistema();
			tiempoCPU();
			cambioContexto();
			inicioSistema();
			nroProcesos();

		while(1){
			//printf("dormir %d %s\n",intervalo," segundos");
			pedidosDisco();
			informacionMemoria();
			informacionDisco();
			if(repeticiones!=0){
				printf("esperar %d %s\n",intervalo," segundos");
				sleep(intervalo);
			}
			else break;
			repeticiones--;
		}
		printf("\n\n");
	}

	else{
		printf("error en el pasaje de parametros\n\n");
	}

	return 0;
}
