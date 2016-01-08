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
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <list>
#include <stdexcept>
#include <miosix.h>
#include"02do2#.h"
#include"01do2.h"
#include"08sol2.h"
#include"03re2.h"
#include"04re2#.h"
#include"05mi2.h"
#include"06fa2.h"
#include"07fa2#.h"
#include"09sol2#.h"
#include"10la2.h"
#include"11la2#.h"
#include"12si2.h"
#include"13do3.h"
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
ADPCMSound do2_sound(__01do2_bin,__01do2_bin_len);
ADPCMSound do2d_sound(__02do2__bin,__02do2__bin_len);
ADPCMSound re2_sound(__03re2_bin,__03re2_bin_len);
ADPCMSound re2d_sound(__04re2__bin,__04re2__bin_len);
ADPCMSound mi2_sound(__05mi2_bin,__05mi2_bin_len);
ADPCMSound fa2_sound(__06fa2_bin,__06fa2_bin_len);
ADPCMSound fa2d_sound(__07fa2__bin,__07fa2__bin_len);
ADPCMSound sol2_sound(__08sol2_bin,__08sol2_bin_len);
ADPCMSound sol2d_sound(__09sol2__bin,__09sol2__bin_len);
ADPCMSound la2_sound(__10la2_bin,__10la2_bin_len);
ADPCMSound la2d_sound(__11la2__bin,__11la2__bin_len);
ADPCMSound si2_sound(__12si2_bin,__12si2_bin_len);
ADPCMSound do3_sound(__13do3_bin,__13do3_bin_len);

void play_sound(char c);
void play_something();
int main()
{
	//taskes as input directly without pressing enter
	struct termios t;
	tcgetattr(STDIN_FILENO,&t);
	t.c_lflag &= ~(ISIG | ICANON | ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&t);
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
	Player::instance().init();
	/*
	for(;;) {
		Player::instance().play(do2_sound);
		Player::instance().play(re2_sound);
		Player::instance().play(mi2_sound);
		Player::instance().play(fa2_sound);
		Player::instance().play(sol2_sound);
		Player::instance().play(la2_sound);
		Player::instance().play(si2_sound);
		Player::instance().play(do3_sound);
	}*/
	for(;;) {
		getchar();
		play_something();
	}
	Player::instance().stop();

}

void play_something() {
	Player::instance().play(do2_sound);
}
/*
	simple function that reproduce some notes based
	on their name (C=DO,D=RE,A=la,F=fa ecc..)
	this function at the end should be something
	like play_sound(int[] byte_stream) and I should
	pass to it a piece of the MIDI file. Then I parse
	it.
*/
/*usage=use the second line of the qwerty:a=do(C). s=re(D). d=mi(E). etc..*/
void play_sound(char c) {
	switch(c) {
		case 'a':
			Player::instance().play(do2_sound);
			break;
		case 's':
			Player::instance().play(re2_sound);
			break;
		case 'd':
			Player::instance().play(mi2_sound);
			break;
		case 'f':
			Player::instance().play(fa2_sound);
			break;
		case 'g':
			Player::instance().play(sol2_sound);
			break;
		case 'h':
			Player::instance().play(la2_sound);
			break;
		case 'j':
			Player::instance().play(si2_sound);
			break;
		case 'k':
			Player::instance().play(do3_sound);
			break;
	}
}
