/*
	actually I don't know which of these
	I need in order to use scanf.
	For the serial: 
	red->VDD
	black->GND
	yellow->PB10
	orange->PB11-
*/
#include "player.h"
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
#include"13do3Croma.h"
#include"13do3Semicroma.h"
#include"13do3Semiminima.h"
#include"00pauseCroma.h"
#include"00pauseSemicroma.h"
#include"00pauseSemiminima.h"
#include <pthread.h>


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
ADPCMSound do3Croma_sound(__13do3Croma_bin,__13do3Croma_bin_len);
ADPCMSound do3Semicroma_sound(__13do3Semicroma_bin,__13do3Semicroma_bin_len);
ADPCMSound do3Semiminima_sound(__13do3Semiminima_bin,__13do3Semiminima_bin_len);
ADPCMSound pauseCroma_sound(__00pauseCroma_bin,__00pauseCroma_bin_len);
ADPCMSound pauseSemicroma_sound(__00pauseSemicroma_bin,__00pauseSemicroma_bin_len);
ADPCMSound pauseSemiminima_sound(__00pauseSemiminima_bin,__00pauseSemiminima_bin_len);
ADPCMSound do3d_sound(__14do3__bin,__14do3__bin_len);
ADPCMSound re3_sound(__15re3_bin,__15re3_bin_len);
ADPCMSound re3d_sound(__16re3__bin,__16re3__bin_len);

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ack=PTHREAD_COND_INITIALIZER;
/*
	simple function that reproduce some notes based
	on their name (C=DO,D=RE,A=la,F=fa ecc..)
	this function at the end should be something
	like play_sound(int[] byte_stream) and I should
	pass to it a piece of the MIDI file. Then I parse
	it.
*/
//current note to play:initialized with 0 (=empty_sound)
char current_note=0;
bool producer=true;
char timestamp=-1;
//length of the note
 
void* play_sound(void* argv) {
	char note,ts;
	for(;;) {
		pthread_mutex_lock(&mutex);
		while(producer) pthread_cond_wait(&ack,&mutex);
		note=current_note;
		ts=timestamp;
		printf("consumer:note:%c,timestamp:%c",note,timestamp);
		switch(note) {
		case 0:
			//empty sound
			//choose the correct time
			switch(ts) {
				case 1:
					Player::instance().play(pauseSemiminima_sound);
					break;
				case 2:
					Player::instance().play(pauseCroma_sound);
					break;
				case 3:
					Player::instance().play(pauseSemicroma_sound);
					break;
			}
			break;
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
			//choose the correct time
			switch(ts) {
				case 1:
					Player::instance().play(do3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(do3Croma_sound);
					break;
				case 3:
					Player::instance().play(do3Semicroma_sound);
					break;
			}
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
		producer=true;
		//signals the producer
		pthread_cond_signal(&ack);
		pthread_mutex_unlock(&mutex);
	}
}
void parse_byte(char c);
/*another thread to play the sound*/

/*integer for the note and a mutex and a thread*/
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

	Player::instance().init();
	//player thread
	pthread_t player;
	pthread_create(&player,NULL,play_sound,NULL);
	//endless loop to get the bytes
	
	for(;;)	parse_byte(getchar());
	pthread_join(player,NULL);

}

void parse_byte(char c) {
	char note,velocity;
	//don't care about the channel
	if((c & 0b10010000)==0x90) {
		/*when I set the note I'm already in the 0 case=>no reproduction*/
		pthread_mutex_lock(&mutex);
		while(!producer) pthread_cond_wait(&ack,&mutex);
		note=getchar();
		velocity=getchar();
		//set the note to be played
			if(velocity==0)
				current_note=0;
			else
				current_note=note;	
			//gets the timestamp
			if(getchar()>=0x81) {
				if(getchar()>0x71)	
					timestamp=1;
				else
					timestamp=2;
			} else
				timestamp=3;
			producer=false;
			printf("producer:note:%c,timestamp:%c",note,timestamp);
			pthread_cond_signal(&ack);
			pthread_mutex_unlock(&mutex);	
		/*in order to stop the note I set a boolean variable*/
		//lock the mutex and set a variable
	} else if((c & 0b10000000)==0x80) {
		pthread_mutex_lock(&mutex);
		current_note=0;
		pthread_mutex_unlock(&mutex);
		getchar();getchar();
	}
}
