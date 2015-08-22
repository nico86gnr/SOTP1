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


int main(){

	cpuInfo();
	versionKernel();
	tiempoSistema();

	return 0;
}
