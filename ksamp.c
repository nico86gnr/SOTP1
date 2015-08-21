/*
 * ksamp.c
 *
 *  Created on: 21 de ago. de 2015
 *      Author: nico
 */

#include <stdio.h>



void cpuInfo(char path[])
{
   FILE *fp;
   char buff[255];

   fp = fopen(path, "r");

   printf("TIPO Y MODELO DE CPU: \n");
   printf("--------------------- \n");

   while(!feof(fp)){
	   //copia hasta 24 caract. y añade uno nulo d fin d cadena
	   //o copia hasta encontrar un cambio de linea
	   fgets(buff, 255, (FILE*)fp);
	   printf("%s", buff ); //imprime buff
   }
	   fclose(fp);

}



int main(){

	char path[]="/proc/cpuinfo";
	cpuInfo(path);

	return 0;
}
