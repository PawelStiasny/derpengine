#include "MechLauncher.h"
#include "Tile.h"

MechLauncher::MechLauncher()
{
	// horizontal plates
	float vpos = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		/*
		Tile *t1 = new Tile;
		t1->setScale(0.3f, 0.3f, 1.0f);
		t1->setPosition(0.0f, vpos, 0.0f);
		t1->setRotation(90.0f, 0.0f, 0.0f);
		addMember(t1);

		Tile *t2 = new Tile;
		t2->setScale(0.3f, 0.3f, 1.0f);
		t2->setPosition(0.0f, vpos, 0.0f);
		t2->setRotation(270.0f, 0.0f, 0.0f);
		addMember(t2);*/

		vpos += 0.1f;
	}

	// vertical plates
	for (int i = 1; i < 8; i++)
	{
		/*Tile *t1 = new Tile;
		t1->setScale(0.3f, 0.15f, 1.0f);
		t1->setPosition(0.1f * (float)i - 0.4f, 0.15f, 0.0f);
		t1->setRotation(0.0f, 90.0f, 0.0f);
		addMember(t1);

		Tile *t2 = new Tile;
		t2->setScale(0.3f, 0.15f, 1.0f);
		t2->setPosition(0.1f * (float)i - 0.4f, 0.15f, 0.0f);
		t2->setRotation(0.0f, 270.0f, 0.0f);
		addMember(t2);*/
	}
}

void MechLauncher::doRender(RenderingContext *rc)
{

}
