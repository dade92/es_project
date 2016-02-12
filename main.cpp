#include "player.h"
#include <termios.h>
#include <cstdio>
#include <miosix.h>
#include <pthread.h>
//note header files
#include"00pauseSemicroma.h"
#include"13do3Semicroma.h"
#include"16mib3Semicroma.h"
#include"17mi3Semicroma.h"
#include"19solb3Semicroma.h"
#include"20sol3Semicroma.h"
#include"21lab3Semicroma.h"
#include"22la3Semicroma.h"
#include"23sib3Semicroma.h"
#include"24si3Semicroma.h"
#include"25do4Semicroma.h"
#include"26reb4Semicroma.h"
#include"27re4Semicroma.h"
#include"28mib4Semicroma.h"
#include"29mi4Semicroma.h"
#include"30fa4Semicroma.h"
#include"31solb4Semicroma.h"
#include"32sol4Semicroma.h"
#include"34la4Semicroma.h"
#include"37do5Semicroma.h"
//notes
ADPCMSound pauseSemicroma_sound(__00pauseSemicroma_bin,__00pauseSemicroma_bin_len);
ADPCMSound do3Semicroma_sound(__13do3Semicroma_bin,__13do3Semicroma_bin_len);
ADPCMSound mib3Semicroma_sound(__16mib3Semicroma_bin,__16mib3Semicroma_bin_len);
ADPCMSound mi3Semicroma_sound(__17mi3Semicroma_bin,__17mi3Semicroma_bin_len);
ADPCMSound solb3Semicroma_sound(__19solb3Semicroma_bin,__19solb3Semicroma_bin_len);
ADPCMSound sol3Semicroma_sound(__20sol3Semicroma_bin,__20sol3Semicroma_bin_len);
ADPCMSound lab3Semicroma_sound(__21lab3Semicroma_bin,__21lab3Semicroma_bin_len);
ADPCMSound la3Semicroma_sound(__22la3Semicroma_bin,__22la3Semicroma_bin_len);
ADPCMSound sib3Semicroma_sound(__23sib3Semicroma_bin,__23sib3Semicroma_bin_len);
ADPCMSound si3Semicroma_sound(__24si3Semicroma_bin,__24si3Semicroma_bin_len);
ADPCMSound do4Semicroma_sound(__25do4Semicroma_bin,__25do4Semicroma_bin_len);
ADPCMSound reb4Semicroma_sound(__26reb4Semicroma_bin,__26reb4Semicroma_bin_len);
ADPCMSound re4Semicroma_sound(__27re4Semicroma_bin,__27re4Semicroma_bin_len);
ADPCMSound mib4Semicroma_sound(__28mib4Semicroma_bin,__28mib4Semicroma_bin_len);
ADPCMSound mi4Semicroma_sound(__29mi4Semicroma_bin,__29mi4Semicroma_bin_len);
ADPCMSound fa4Semicroma_sound(__30fa4Semicroma_bin,__30fa4Semicroma_bin_len);
ADPCMSound solb4Semicroma_sound(__31solb4Semicroma_bin,__31solb4Semicroma_bin_len);
ADPCMSound sol4Semicroma_sound(__32sol4Semicroma_bin,__32sol4Semicroma_bin_len);
ADPCMSound la4Semicroma_sound(__34la4Semicroma_bin,__34la4Semicroma_bin_len);
ADPCMSound do5Semicroma_sound(__37do5Semicroma_bin,__37do5Semicroma_bin_len);
//concurrency controlled by mutex
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
//shared variables between threads
char current_note=0;
//function prototypes
void parse_byte(char c);
void* play_sound(void *argv);

int main()
{
	struct termios t;
	tcgetattr(STDIN_FILENO,&t);
	t.c_lflag &= ~(ISIG | ICANON | ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&t);
	
	Player::instance().init();
	//player thread
	pthread_t player;
	pthread_create(&player,NULL,play_sound,NULL);
	//endless loop to get the bytes
	for(;;) parse_byte(getchar());	
	pthread_join(player,NULL);
}
void parse_byte(char c) {
	char note,velocity;
	//note reproduction
	if((c & 0b10010000)==0x90) {
		note=getchar();
		velocity=getchar();
		//atomic access to the shared variable
		pthread_mutex_lock(&mutex);
		if(velocity==0) current_note=0;
		else current_note=note;
		pthread_mutex_unlock(&mutex);
	}
	//note pause
	 else if((c & 0b10000000)==0x80) current_note=0;
}
void* play_sound(void* argv) {
	char note;
	char previous_note=0;
	for(;;) {
		pthread_mutex_lock(&mutex);
		//simple state machine
		if(current_note==previous_note) note=0;
		else note=current_note;
		previous_note=current_note;
		pthread_mutex_unlock(&mutex);
		switch(note) {
			case 0:
				Player::instance().play(pauseSemicroma_sound);
				break;
			case 63:
				Player::instance().play(mib3Semicroma_sound);
				break;
			case 66:
				Player::instance().play(solb3Semicroma_sound);
				break;
			case 67:
				Player::instance().play(sol3Semicroma_sound);
				break;
			case 68:
				Player::instance().play(lab3Semicroma_sound);
				break;
			case 69:
				Player::instance().play(la3Semicroma_sound);
				break;
			case 70:
				Player::instance().play(sib3Semicroma_sound);
				break;
			case 71:
				Player::instance().play(si3Semicroma_sound);
				break;
			case 72:
				Player::instance().play(do4Semicroma_sound);
				break;
			case 73:
				Player::instance().play(reb4Semicroma_sound);
				break;
			case 74:
				Player::instance().play(re4Semicroma_sound);
				break;
			case 75:
				Player::instance().play(mib4Semicroma_sound);
				break;
			case 76:
				Player::instance().play(mi4Semicroma_sound);
				break;
			case 77:
				Player::instance().play(fa4Semicroma_sound);
				break;
			case 78:
				Player::instance().play(solb4Semicroma_sound);
				break;
			case 79:
				Player::instance().play(sol4Semicroma_sound);
				break;
		}
	}
}
