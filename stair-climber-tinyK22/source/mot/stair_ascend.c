/*
 * stair_ascend.c
 *
 *  Created on: 07.05.2021
 *      Author: manue
 */

#include "stair_ascend.h"
#include "mot/liftmot.h"
#include "mot/dcmot.h"
#include "sensors/groundsensor.h"

static void wait(int cycles) {
	for (int i = 0; i < cycles; i++) {
		__asm volatile ("nop");
	}
}

void stair_ascend_ascend() {
// auskommentiert am 27.5
//	//Äussere Segmente auf den Boden
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//
//	//Fahr an die Treppe
//	DCMOT_sync_vorward(false, 200);
//	wait(5000000);
//	DCMOT_sync_vorward(false, 150);
//	wait(5000000);
//	DCMOT_sync_vorward(false, 0);
//
//	//Alle Segmente auf den Boden
//	wait(4000000);

// alles ausschalten und kurz warten
//	LIFTMOT_sync_down(0);
//	wait(10000000);
	LIFTMOT_DRIVE_POS_MIDDLEDOWN();

//	wait(10000000);

//Frontsegment nach oben stellen
	LIFTMOT_GOTO_TOP(true);

	//Mittleres Segment an die Treppe fahren
	DCMOT_sync_vorward(true, 254);
	wait(10000000);
	DCMOT_sync_vorward(true, 200);
	wait(10000000);
	DCMOT_sync_vorward(true, 0);
//	wait(10000000);

	LIFTMOT_MIDSEGM_TOP();
	wait(1000000);

	//Mitleres Segment über die Treppe fahren
	DCMOT_sync_vorward(true, 254);
	wait(10000000);
	DCMOT_sync_vorward(true, 150);
	wait(40000000);
	DCMOT_sync_vorward(true, 0);
	LIFTMOT_down(1, 0);
	LIFTMOT_down(2, 0);
	wait(10000000);

	//Mittleres Segment herunterlassen
	LIFTMOT_LETDOWN();

	// vorderes segment war in der luft
//	LIFTMOT_FRONT_GROUND();

// hinteres segment heben
	LIFTMOT_GOTO_TOP(0);

	wait(10000000);

	//Fahren
	DCMOT_sync_vorward(true, 254);
	wait(15000000);
	DCMOT_sync_vorward(true, 200);
	wait(15000000);
	DCMOT_sync_vorward(true, 0);
	wait(10000000);

	LIFTMOT_DRIVE_POS_OUTERGROUND();

}

