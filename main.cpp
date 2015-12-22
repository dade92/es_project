/*
	actually I don't know which of these
	I need in order to use scanf.
	For the serial: 
	red->VDD
	black->GND
	yellow->PB10
	orange->PB11
*/
#include "player.h"
#include "sad_trombone.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <list>
#include <stdexcept>
#include <miosix.h>
#include "la.h"
#include"fa1.h"
#include"do2.h"
/*
	scaricare audacity. 
	convertire in un header il wav.istruzioni nel convert.cpp (terraneo l'ha testato con noi).
	includere l'header creato
	instanziare una nuova classe ADPCM
	modificare il metodo play
	File vanno convertiti da audacity,non so il perchè
*/
/*
	note sono forme d'onda. se registro ho l'elenco per punti
	della forma d'onda.
	nel buffer ci sono livelli di tensione,e  li costruisce piano piano
	
*/
ADPCMSound sound(sad_trombone_bin,sad_trombone_bin_len);
ADPCMSound la_sound(la_bin,la_bin_len);
ADPCMSound do_sound(do2_bin,do2_bin_len);
ADPCMSound fa_sound(fa1_bin,fa1_bin_len);
void play_sound(char c);
int main()
{
	//codifica molto semplice, lossy, codifica un 4 bit ogni nota
	//passa le note

	/*
		instanziare diversi oggetti ognuno con una nota diversa
		e riprodurli 
	*/
	/*
		generare .h di un suono.
		modificare 	
	*/
	int i;
	Player::instance().init();
	for(;;) 
		play_sound(getchar());
	Player::instance().stop();

}
/*
	simple function that reproduce some notes based
	on their name (C=DO,D=RE,A=la,F=fa ecc..)
	this function at the end should be something
	like play_sound(int[] byte_stream) and I should
	pass to it a piece of the MIDI file. Then I parse
	it.
*/
void play_sound(char c) {
	switch(c) {
		case 'a':
			Player::instance().play(la_sound);
			break;
		case 'c':
			Player::instance().play(fa_sound);
			break;
		case 'f':
			Player::instance().play(do_sound);
			break;
	}
}
