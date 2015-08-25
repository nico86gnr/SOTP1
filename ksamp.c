/*
 * ksamp.c
 *
 *  Created on: 21 de ago. de 2015
 *      Author: nico
 */

#include <stdio.h>


void cpuInfo()
{
   FILE *fp;
   char buffer_tipo[255];
   char buffer_modelo[255];
   char *tipo=NULL;
   char *modelo=NULL;

   fp = fopen("/proc/cpuinfo", "r");

   while(tipo==NULL){
	   //copia hasta 254 caract. y añade uno nulo d fin d cadena
	   //o copia hasta encontrar un cambio de linea
	   fgets(buffer_tipo, 255, (FILE*)fp);

	   tipo = strstr(buffer_tipo,"vendor_id");

   }   fseek(fp, SEEK_SET, 0);

   while(modelo==NULL){
   	   //copia hasta 24 caract. y añade uno nulo d fin d cadena
   	   //o copia hasta encontrar un cambio de linea
   	   fgets(buffer_modelo, 255, (FILE*)fp);

   	   modelo = strstr(buffer_modelo,"model name");

      }

   fclose(fp);

   printf("%s\n", tipo);
   printf("%s\n", modelo);

}


void versionKernel(){

	FILE *fp;
	char buffer_kernel[255];

	fp = fopen("/proc/version", "r");
	fgets(buffer_kernel, 255, (FILE*)fp);

	fclose(fp);
	printf("Version del Kernel: %s\n", buffer_kernel);

}


void tiempoSistema(){

	FILE *fp;
	float tiempo;
	int dias;
	int horas;
	int minutos;
	int segundos;

	fp = fopen("/proc/uptime", "r");
	fscanf(fp, "%f", &tiempo);

	//printf("uptime: %f\n", tiempo);

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

	printf("tiempo: %d %s",dias,"dias   ");
	printf("%d %s",horas,"horas   ");
	printf("%d %s",minutos,"minutos   ");
	printf("%d %s\n",segundos,"segundos   ");

	fclose(fp);

}


void tiempoCPU(){

	FILE *fp;
	char cpu[10];
	int tiempo_usuario1;
	int tiempo_usuario2;
	int tiempo_sistema;
	long tiempo_idle;

	fp = fopen("/proc/stat", "r");
	fscanf(fp,"%s""%d""%d""%d",cpu,&tiempo_usuario1,&tiempo_usuario2,
				&tiempo_sistema,&tiempo_idle);
	printf(" %s",cpu);
	printf("tiempo de uso de usuario: %d",tiempo_usuario1);
	printf("tiempo de uso de usuario: %d",tiempo_usuario2);
	printf("tiempo de uso de sistema: %d",tiempo_sistema);
	printf("tiempo de proceso idle %d ", tiempo_idle);

}
void cambioContexto(){

}
void inicioSistema(){

}
void nroProcesos(){

}



int main(int argc, char *argv[]){

	if(argc==1){
			cpuInfo();
			versionKernel();
			tiempoSistema();
			tiempoCPU();
		}
	if(argv[1]=="-s"){
			tiempoCPU();
			cambioContexto();
			inicioSistema();
			nroProcesos();
		}

	return 0;
}
