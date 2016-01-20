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
#include <pthread.h>

#include"00pauseSemiminima.h"
#include"00pauseCroma.h"
#include"00pauseSemicroma.h"

#include"16mib3Semiminima.h"
#include"16mib3Croma.h"
#include"16mib3Semicroma.h"

#include"19solb3Semiminima.h"
#include"19solb3Croma.h"
#include"19solb3Semicroma.h"

#include"20sol3Semiminima.h"
#include"20sol3Croma.h"
#include"20sol3Semicroma.h"

#include"21lab3Semiminima.h"
#include"21lab3Croma.h"
#include"21lab3Semicroma.h"

#include"22la3Semiminima.h"
#include"22la3Croma.h"
#include"22la3Semicroma.h"

#include"23sib3Semiminima.h"
#include"23sib3Croma.h"
#include"23sib3Semicroma.h"

#include"24si3Semiminima.h"
#include"24si3Croma.h"
#include"24si3Semicroma.h"

#include"25do4Semiminima.h"
#include"25do4Croma.h"
#include"25do4Semicroma.h"

#include"26reb4Semiminima.h"
#include"26reb4Croma.h"
#include"26reb4Semicroma.h"

#include"27re4Semiminima.h"
#include"27re4Croma.h"
#include"27re4Semicroma.h"

#include"28mib4Semiminima.h"
#include"28mib4Croma.h"
#include"28mib4Semicroma.h"

#include"29mi4Semiminima.h"
#include"29mi4Croma.h"
#include"29mi4Semicroma.h"

#include"30fa4Semiminima.h"
#include"30fa4Croma.h"
#include"30fa4Semicroma.h"

#include"31solb4Semiminima.h"
#include"31solb4Croma.h"
#include"31solb4Semicroma.h"

#include"32sol4Semiminima.h"
#include"32sol4Croma.h"
#include"32sol4Semicroma.h"

ADPCMSound pauseSemiminima_sound(__00pauseSemiminima_bin,__00pauseSemiminima_bin_len);
ADPCMSound pauseCroma_sound(__00pauseCroma_bin,__00pauseCroma_bin_len);
ADPCMSound pauseSemicroma_sound(__00pauseSemicroma_bin,__00pauseSemicroma_bin_len);

ADPCMSound mib3Semiminima_sound(__16mib3Semiminima_bin,__16mib3Semiminima_bin_len);
ADPCMSound mib3Croma_sound(__16mib3Croma_bin,__16mib3Croma_bin_len);
ADPCMSound mib3Semicroma_sound(__16mib3Semicroma_bin,__16mib3Semicroma_bin_len);

ADPCMSound solb3Semiminima_sound(__19solb3Semiminima_bin,__19solb3Semiminima_bin_len);
ADPCMSound solb3Croma_sound(__19solb3Croma_bin,__19solb3Croma_bin_len);
ADPCMSound solb3Semicroma_sound(__19solb3Semicroma_bin,__19solb3Semicroma_bin_len);

ADPCMSound sol3Semiminima_sound(__20sol3Semiminima_bin,__20sol3Semiminima_bin_len);
ADPCMSound sol3Croma_sound(__20sol3Croma_bin,__20sol3Croma_bin_len);
ADPCMSound sol3Semicroma_sound(__20sol3Semicroma_bin,__20sol3Semicroma_bin_len);

ADPCMSound lab3Semiminima_sound(__21lab3Semiminima_bin,__21lab3Semiminima_bin_len);
ADPCMSound lab3Croma_sound(__21lab3Croma_bin,__21lab3Croma_bin_len);
ADPCMSound lab3Semicroma_sound(__21lab3Semicroma_bin,__21lab3Semicroma_bin_len);

ADPCMSound la3Semiminima_sound(__22la3Semiminima_bin,__22la3Semiminima_bin_len);
ADPCMSound la3Croma_sound(__22la3Croma_bin,__22la3Croma_bin_len);
ADPCMSound la3Semicroma_sound(__22la3Semicroma_bin,__22la3Semicroma_bin_len);

ADPCMSound sib3Semiminima_sound(__23sib3Semiminima_bin,__23sib3Semiminima_bin_len);
ADPCMSound sib3Croma_sound(__23sib3Croma_bin,__23sib3Croma_bin_len);
ADPCMSound sib3Semicroma_sound(__23sib3Semicroma_bin,__23sib3Semicroma_bin_len);

ADPCMSound si3Semiminima_sound(__24si3Semiminima_bin,__24si3Semiminima_bin_len);
ADPCMSound si3Croma_sound(__24si3Croma_bin,__24si3Croma_bin_len);
ADPCMSound si3Semicroma_sound(__24si3Semicroma_bin,__24si3Semicroma_bin_len);

ADPCMSound do4Semiminima_sound(__25do4Semiminima_bin,__25do4Semiminima_bin_len);
ADPCMSound do4Croma_sound(__25do4Croma_bin,__25do4Croma_bin_len);
ADPCMSound do4Semicroma_sound(__25do4Semicroma_bin,__25do4Semicroma_bin_len);

ADPCMSound reb4Semiminima_sound(__26reb4Semiminima_bin,__26reb4Semiminima_bin_len);
ADPCMSound reb4Croma_sound(__26reb4Croma_bin,__26reb4Croma_bin_len);
ADPCMSound reb4Semicroma_sound(__26reb4Semicroma_bin,__26reb4Semicroma_bin_len);

ADPCMSound re4Semiminima_sound(__27re4Semiminima_bin,__27re4Semiminima_bin_len);
ADPCMSound re4Croma_sound(__27re4Croma_bin,__27re4Croma_bin_len);
ADPCMSound re4Semicroma_sound(__27re4Semicroma_bin,__27re4Semicroma_bin_len);

ADPCMSound mib4Semiminima_sound(__28mib4Semiminima_bin,__28mib4Semiminima_bin_len);
ADPCMSound mib4Croma_sound(__28mib4Croma_bin,__28mib4Croma_bin_len);
ADPCMSound mib4Semicroma_sound(__28mib4Semicroma_bin,__28mib4Semicroma_bin_len);

ADPCMSound mi4Semiminima_sound(__29mi4Semiminima_bin,__29mi4Semiminima_bin_len);
ADPCMSound mi4Croma_sound(__29mi4Croma_bin,__29mi4Croma_bin_len);
ADPCMSound mi4Semicroma_sound(__29mi4Semicroma_bin,__29mi4Semicroma_bin_len);

ADPCMSound fa4Semiminima_sound(__30fa4Semiminima_bin,__30fa4Semiminima_bin_len);
ADPCMSound fa4Croma_sound(__30fa4Croma_bin,__30fa4Croma_bin_len);
ADPCMSound fa4Semicroma_sound(__30fa4Semicroma_bin,__30fa4Semicroma_bin_len);

ADPCMSound solb4Semiminima_sound(__31solb4Semiminima_bin,__31solb4Semiminima_bin_len);
ADPCMSound solb4Croma_sound(__31solb4Croma_bin,__31solb4Croma_bin_len);
ADPCMSound solb4Semicroma_sound(__31solb4Semicroma_bin,__31solb4Semicroma_bin_len);

ADPCMSound sol4Semiminima_sound(__32sol4Semiminima_bin,__32sol4Semiminima_bin_len);
ADPCMSound sol4Croma_sound(__32sol4Croma_bin,__32sol4Croma_bin_len);
ADPCMSound sol4Semicroma_sound(__32sol4Semicroma_bin,__32sol4Semicroma_bin_len);

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ack=PTHREAD_COND_INITIALIZER;

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
		//printf("consumer:note:%c,timestamp:%c",note,timestamp);
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
		case 63:
			switch(ts) {
				case 1:
					Player::instance().play(mib3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(mib3Croma_sound);
					break;
				case 3:
					Player::instance().play(mib3Semicroma_sound);
					break;
			}
			break;
		case 66:
			switch(ts) {
				case 1:
					Player::instance().play(mi3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(mi3Croma_sound);
					break;
				case 3:
					Player::instance().play(mi3Semicroma_sound);
					break;
			}
			break;
		case 67:
			switch(ts) {
				case 1:
					Player::instance().play(sol3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(sol3Croma_sound);
					break;
				case 3:
					Player::instance().play(sol3Semicroma_sound);
					break;
			}
			break;
		case 68:
			switch(ts) {
				case 1:
					Player::instance().play(lab3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(lab3Croma_sound);
					break;
				case 3:
					Player::instance().play(lab3Semicroma_sound);
					break;
			}
			break;
		case 69:
			switch(ts) {
				case 1:
					Player::instance().play(la3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(la3Croma_sound);
					break;
				case 3:
					Player::instance().play(la3Semicroma_sound);
					break;
			}
			break;
		case 70:
			switch(ts) {
				case 1:
					Player::instance().play(sib3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(sib3Croma_sound);
					break;
				case 3:
					Player::instance().play(sib3Semicroma_sound);
					break;
			}
			break;
		case 71:
			switch(ts) {
				case 1:
					Player::instance().play(si3Semiminima_sound);
					break;
				case 2:
					Player::instance().play(si3Croma_sound);
					break;
				case 3:
					Player::instance().play(si3Semicroma_sound);
					break;
			}
			break;
		case 72:
			switch(ts) {
				case 1:
					Player::instance().play(do4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(do4Croma_sound);
					break;
				case 3:
					Player::instance().play(do4Semicroma_sound);
					break;
			}
			break;
		case 73:
			switch(ts) {
				case 1:
					Player::instance().play(reb4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(reb4Croma_sound);
					break;
				case 3:
					Player::instance().play(reb4Semicroma_sound);
					break;
			}
			break;
		case 74:
			switch(ts) {
				case 1:
					Player::instance().play(re4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(re4Croma_sound);
					break;
				case 3:
					Player::instance().play(re4Semicroma_sound);
					break;
			}
			break;
		case 75:
			switch(ts) {
				case 1:
					Player::instance().play(mib4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(mib4Croma_sound);
					break;
				case 3:
					Player::instance().play(mib4Semicroma_sound);
					break;
			}
			break;
		case 76:
			switch(ts) {
				case 1:
					Player::instance().play(mi4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(mi4Croma_sound);
					break;
				case 3:
					Player::instance().play(mi4Semicroma_sound);
					break;
			}
			break;
		case 77:
			switch(ts) {
				case 1:
					Player::instance().play(fa4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(fa4Croma_sound);
					break;
				case 3:
					Player::instance().play(fa4Semicroma_sound);
					break;
			}
			break;
		case 78:
			switch(ts) {
				case 1:
					Player::instance().play(solb4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(solb4Croma_sound);
					break;
				case 3:
					Player::instance().play(solb4Semicroma_sound);
					break;
			}
			break;
		case 79:
			switch(ts) {
				case 1:
					Player::instance().play(sol4Semiminima_sound);
					break;
				case 2:
					Player::instance().play(sol4Croma_sound);
					break;
				case 3:
					Player::instance().play(sol4Semicroma_sound);
					break;
			}
			break;
		}
		producer=true;
		//signals the producer
		pthread_cond_signal(&ack);
		pthread_mutex_unlock(&mutex);
	}
}

void parse_byte(char c);

int main()
{
	struct termios t;
	tcgetattr(STDIN_FILENO,&t);
	t.c_lflag &= ~(ISIG | ICANON | ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&t);
	Player::instance().init();
	for(;;) {
	Player::instance().play(sol4Semiminima_sound);
	Player::instance().play(pauseSemiminima_sound);
	Player::instance().play(sol4Croma_sound);
	Player::instance().play(pauseCroma_sound);
	Player::instance().play(sol4Semicroma_sound);
	Player::instance().play(pauseSemicroma_sound);
	}

	//player thread
	pthread_t player;
	pthread_create(&player,NULL,play_sound,NULL);
	//endless loop to get the bytes
	
	//for(;;)	parse_byte(getchar());
	pthread_join(player,NULL);
}

void parse_byte(char c) {
	char note,velocity;
	//don't care about the channel
	if((c & 0b10010000)==0x90) {
		/*when I set the note I'm already in the 0 case=>no reproduction*/
		pthread_mutex_lock(&mutex);
		//waits the consumer to play the note
		while(!producer) pthread_cond_wait(&ack,&mutex);
		note=getchar();
		velocity=getchar();
		//set the note to be played
			if(velocity==0) {
				current_note=0;	
			}
			else
				current_note=note;	
			//gets the timestamp
			if(getchar()>=0x80) {
				if(getchar()>=0x5C)	
					timestamp=1;
				else
					timestamp=2;
			} else
				timestamp=3;
			producer=false;
			//printf("producer:note:%c,timestamp:%c",note,timestamp);
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
