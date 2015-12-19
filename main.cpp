
#include "player.h"
#include "sad_trombone.h"
#include "la.h"

/*
	scaricare audacity. 
	convertire in un header il wav.istruzioni nel convert.cpp (terraneo l'ha testato con noi).
	includere l'header creato
	instanziare una nuova classe ADPCM
	modificare il metodo play
*/
/*
	note sono forme d'onda. se registro ho l'elenco per punti
	della forma d'onda.
	nel buffer ci sono livelli di tensione,e  li costruisce piano piano
	
*/
int main()
{
	//codifica molto semplice, lossy, codifica un 4 bit ogni nota
	//passa le note
	ADPCMSound sound(sad_trombone_bin,sad_trombone_bin_len);
	ADPCMSound la_sound(la_bin,la_bin_len);

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
	for(i=0;i<10;++i) Player::instance().play(la_sound);
	Player::instance().stop();

}
