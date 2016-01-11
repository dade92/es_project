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
#include"14do3#.h"
#include"15re3.h"
#include"16re3#.h"
#include"no_sound.h"
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
ADPCMSound do3d_sound(__14do3__bin,__14do3__bin_len);
ADPCMSound re3_sound(__15re3_bin,__15re3_bin_len);
ADPCMSound re3d_sound(__16re3__bin,__16re3__bin_len);
ADPCMSound no_sound(no_sound_bin,no_sound_bin_len);

void play_sound(char c);
void play_something();
void parse_byte(char c);
void stop_sound();
char timestamp;
char current_note=0;
char previous_note=0;
char velocity=1;
char stopped_note;
int main()
{
	
	/*I think that I need another thread: one
	to play the notes and the other to gets the characters
	from the serial port,otherwise I cannot stop the notes.*/
	
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
	//endless loop to get the bytes
	for(;;) {
		parse_byte(getchar());
	}
	Player::instance().stop();

}

void parse_byte(char c) {
	//don't care about the channel
	if(c==0x90) {
		current_note=getchar();
		velocity=getchar();
		if(velocity==0 && previous_note==current_note)
			stop_sound();	
		else 
			play_sound(current_note);
		//don't actually know where this statement should be placed
		previous_note=current_note;
	} else if(c==0x80) {
		//stop sound ???
		stopped_note=getchar();
		getchar();
		if(stopped_note==current_note)
			stop_sound();
	}
	//THIS DOES NOT WORK AND DON'T KNOW WHY
	//handles the timestamp:one or two bytes
	//TODO:add the case in which the timestamp exceeds FF 7F
	//timestamp=getchar();
	//if(timestamp>=0x81)
	//	getchar();
	//maybe here 
}
void stop_sound() {
	//TODO:reproduce an empty sound
	Player::instance().play(no_sound);
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
		case 48:
			Player::instance().play(do2_sound);
			break;
		case 49:
			Player::instance().play(do2d_sound);
			break;
		case 50:
			Player::instance().play(re2_sound);
			break;
		case 51:
			Player::instance().play(re2d_sound);
			break;
		case 52:
			Player::instance().play(mi2_sound);
			break;
		case 53:
			Player::instance().play(fa2_sound);
			break;
		case 54:
			Player::instance().play(fa2d_sound);
			break;
		case 55:
			Player::instance().play(sol2_sound);
			break;
		case 56:
			Player::instance().play(sol2d_sound);
			break;
		case 57:
			Player::instance().play(la2_sound);
			break;
		case 58:
			Player::instance().play(la2d_sound);
			break;
		case 59:
			Player::instance().play(si2_sound);
			break;
		case 60:
			Player::instance().play(do3_sound);
			break;
		case 61:
			Player::instance().play(do3d_sound);
			break;
		case 62:
			Player::instance().play(re3_sound);
			break;
		case 63:
			Player::instance().play(re3d_sound);
			break;
	}
}
