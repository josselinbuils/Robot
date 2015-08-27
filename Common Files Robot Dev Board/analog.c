/*
 * Fichier :        analog.c
 * Description :    Fonctions liées aux périphériques analogiques
 * Projet :         Robot Development Board 2013 (version 3.4)
 * Auteur :         Christopher BUREL
 * Version :        1 février 2013
 */

#include "analog.h"

/* Conversion analogique/numérique */

unsigned int readADC(unsigned int channel) {
	ADC_CHANNEL = channel;	// select the input channel to be converted
	START_SAMPLING();	// start sampling
	WAIT_SAMPLING();        // wait the required acquisition time
	CLEAR_ADC_INT_FLAG();	// clear ADC interrupt flag
	STOP_SAMPLING();	// stop sampling, start conversion
	WAIT_CONVERSION();	// wait for ADC conversion complete
	return(ADC_BUFFER);	// read A/D result buffer
}
