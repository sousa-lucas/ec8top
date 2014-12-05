#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bateria.h"


#define TAMBUFF 500
 

int bateria(char *b, size_t s){
    //buffer that contains text
    char buffer[TAMBUFF];
    buffer[0] = '\x0';
    
    //file reader
    FILE *arquivo;
    
    char *linha;
    char buff[TAMBUFF];
    buff[0] = '\x0';
    
    //battery percentage value
    float valor;
    
    //by setting the total battery leveli
    arquivo = fopen("/sys/class/power_supply/BAT0/charge_full", "r");
    if (arquivo == 0)
      arquivo = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
    if (arquivo == 0)
    {
      strncat(b, "<br><p>Dispositivo Desktop</p>", s); 
      return -1;
    }
      //The battery level could not be read
      
    //assigning the total battery to a float
    while (!feof(arquivo)){
	linha = fgets(buff, TAMBUFF, arquivo);
	if (linha != 0){
	    valor = atoi(linha);
	}
    }
    fclose(arquivo);

    //by setting the current battery level
    arquivo = fopen("/sys/class/power_supply/BAT0/charge_now", "r");
    if (arquivo == 0)
      arquivo = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
    if (arquivo == 0)
    {
      strncat(b, "O arquivo _now nao pode ser lido", s); 
      return -1;
    }
      //The battery level could not be read    
      
    //assigning the total charge to float
    while (!feof(arquivo)){
	linha = fgets(buff, TAMBUFF, arquivo);
	if (linha != 0){
	    //calculating the percentage
	    valor = atoi(linha)/valor*100;
	}
    }
    fclose(arquivo);
    
    //put the details in the buffer function
    snprintf(buffer,TAMBUFF, "<p><b>Battery:</b> %.0f%%</p>", valor);
    
    //put the details in the project buffer
    strncat(b, buffer, s);

    //returns success
    return 1;
}
