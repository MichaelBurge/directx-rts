// engine.cpp: implementation of the engine class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern input gameinput;
extern draw drawing;
extern music gamemusic;
const int laserballcost=250;
const int shipcost=2000;
engine::engine() {
	unitcount=0;
	pressed=false;
	screenposx=0;
	screenposy=0;
	planetcount=0;
	playercount=0;
	options.GiveMessage(CONTROL_SETPOS,320,240);
	options.GiveMessage(CONTROL_SETSIZE,300,300);
	options.GiveMessage(CONTROL_ACTIVATE,0,0);

}
void engine::AddUnit(unit *theunit) {
	units.push_back(*theunit);
	unitcount++;
}
void engine::MoveUnit(unit *theunit) {
	if (DistanceToPoint(theunit->destx,theunit->desty,theunit->x,theunit->y)>theunit->speed) {
		double cosine = theunit->speed*cos(degtorad(GetDirection(theunit->x,theunit->y,theunit->destx,theunit->desty)));
		double sine = theunit->speed*sin(degtorad(GetDirection(theunit->x,theunit->y,theunit->destx,theunit->desty)));
		if (CanMoveTo(theunit,theunit->x+cosine,theunit->y+sine)) {
			theunit->x += cosine;
			theunit->y -= sine;
		} else FindClosestMovement(theunit,theunit->x,theunit->y);
	} else {theunit->x=theunit->destx;theunit->y=theunit->desty;}
}
void engine::ProcessUnit(unit *theunit) {
	if (theunit->health<=0) {
		KillUnit(theunit);
		return;
	}
	MoveUnit(theunit);
		RECT rect = {0,0,theunit->width,theunit->height};
		//drawing.DrawPicture(theunit->x,theunit->y,theunit->type,&rect);
		//drawing.DrawPictureRotation(units[temp].x,units[temp].y,units[temp].x+units[temp].width
		//	,units[temp].y+units[temp].height,units[temp].type,&rect,units[temp].rotation);
		//drawing.DrawPicture(gameinput.mousex,gameinput.mousey,units[temp].type,&rect);
		
		if (theunit->selected) {
			if (gameinput.rightclicked) {
				//p1 = TranslateCoordinates(gameinput.mousex,gameinput.mousey,screenposx,screenposy);
				theunit->rotation=GetDirection(theunit->x,theunit->y,theunit->destx,theunit->desty)*100;
				theunit->destx=gameinput.mousex+screenposx;
				theunit->desty=gameinput.mousey+screenposy;
			}
			rect.right = 8;
			rect.bottom = 8;
		//	p1 = TranslateCoordinates(theunit->x-8,theunit->y-8,screenposx,screenposy);
			drawing.DrawPicture(theunit->x-8-screenposx,theunit->y-8-screenposy,selectedkey,&rect);
			if (DistanceToPoint(theunit->x+theunit->width/2,theunit->y+theunit->height/2,theunit->destx,theunit->desty)>
				DistanceToPoint(theunit->x,theunit->y,theunit->x+theunit->width,theunit->y+theunit->height))
				drawing.DrawPicture(theunit->destx+4-screenposx,theunit->desty+4-screenposy,redx,&rect);//Draw 'x' if unit is far away and selected
		}
		if (!CanMoveTo(theunit,theunit->x,theunit->y)) FindClosestMovement(theunit,theunit->x,theunit->y);
	rect.right = theunit->width;
	rect.bottom = theunit->height;
	unit *checknearest = ClosestUnitInRange(theunit,theunit->range);
	if (checknearest!=NULL&&checknearest!=theunit->target) {
		if (theunit->target!=NULL)theunit->target->targetted=false;
		theunit->target = checknearest;
	}
	if (theunit->target && (theunit->target==theunit || DistanceToPoint(theunit->x,theunit->y,theunit->target->x,theunit->target->y)>theunit->range))
		theunit->target=NULL;
	theunit->ShootUnit(theunit->target);
	
//	p1 = TranslateCoordinates(theunit->x,theunit->y,screenposx,screenposy);
	drawing.DrawPicture(theunit->x-screenposx,theunit->y-screenposy,theunit->type,&rect);
	double drawlength=theunit->width;
	drawlength/=(theunit->maxhealth/(theunit->health?theunit->health:1));
	
	//POINT p2 = TranslateCoordinates(theunit->x+drawlength,theunit->y+4,screenposx,screenposy);
	//Draw health bar
	drawing.DrawColor(theunit->x-screenposx,theunit->y-screenposy,theunit->x+drawlength-screenposx,theunit->y+4-screenposy,playercolors[theunit->side]);
	if (theunit->target) switch (theunit->type) {//Draw special graphics for different units
		case 1:
			drawing.DrawLine(theunit->x-screenposx+8,theunit->y-screenposy+8,theunit->target->x-screenposx,theunit->target->y-screenposy,RGB(255,0,0));
			break;
	}
}
void engine::ProcessPlanet(planet *theplanet) {
	int player=-1;
	RECT size={0,0,255,255};
	for (int temp=0;temp<unitcount;temp++)
		if (DistanceToPoint(theplanet->positionx+128,theplanet->positiony+128,units[temp].x,units[temp].y)<128.0) player=units[temp].side;
		if (player>=0&&player<playercount) {players[player].productionpoints++;theplanet->player=player;}
	if (theplanet->positionx>=0&&theplanet->positionx<mapwidth&&theplanet->positiony>=0&&theplanet->positiony<mapheight)
		drawing.DrawPicture(theplanet->positionx-screenposx,theplanet->positiony-screenposy,firstplanet+theplanet->type,&size);
}
void engine::ProcessGUI(void) {
	ProcessButtons();
	drawing.DrawText("Current Production Points:",0,0,RGB(255,0,0));
	drawing.DrawNumber(players[0].productionpoints,0,12,RGB(0,255,0));
	drawing.DrawText(helptext.text,72,drawing.height-72,RGB(0,0,255));
}
void engine::Process() {
	if (gameinput.KeyPressed(DIK_F2)) {
		options.GiveMessage(CONTROL_ACTIVATE,1,0);
		resourceinfinite.GiveMessage(CONTROL_ACTIVATE,1,0);
	}
	helptext="";
	bool unitselected=false;
	for (int temp=0;temp<planetcount;temp++)//Process planets
		ProcessPlanet(&planets[temp]);
	for (temp=0;temp<unitcount;temp++)//Process units
		ProcessUnit(&units[temp]);
	for (temp=0;temp<compai.size();temp++)
		compai[temp].process();
	ProcessGUI();
	pressed=gameinput.leftclicked;
	if (pressed) {//Draws mouse rectangle for selecting units
		//POINT p = TranslateCoordinates(x,y,screenposx,screenposy);
		//POINT p2 = TranslateCoordinates(screenposx+gameinput.mousex,screenposy+gameinput.mousey,screenposx,screenposy);
		drawing.DrawLine(x,y,x,gameinput.mousey,RGB(128,128,128));
		drawing.DrawLine(x,gameinput.mousey,gameinput.mousex,gameinput.mousey,RGB(128,128,128));
		drawing.DrawLine(gameinput.mousex,y,gameinput.mousex,gameinput.mousey,RGB(128,128,128));
		drawing.DrawLine(x,y,gameinput.mousex,y,RGB(128,128,128));
		SelectWithinBox(x,y,gameinput.mousex,gameinput.mousey);
		gameinput.Update();
		

	} else {x=gameinput.mousex,y=gameinput.mousey;}
	if (gameinput.mousex < 16 && screenposx>0) screenposx-=4;
	if (gameinput.mousex > drawing.width-16 && screenposx<mapwidth) screenposx+=4;
	if (gameinput.mousey < 16 && screenposy>0) screenposy-=4;
	if (gameinput.mousey > drawing.height-16&& screenposy<mapheight)screenposy+=4;
	bool won = true;
		for (temp=0;temp<unitcount;temp++)
			if (units[temp].side>0 && units[temp].health > 0) won=false;;
	if (won) Win();
}
engine::~engine(){

}
void engine::SelectWithinBox(int x,int y,int x2,int y2) {
	int left = x<x2?x:x2;
	int top = y<y2?y:y2;
	int right = x>x2?x:x2;
	int bottom = y>y2?y:y2;
	for (int temp=0;temp<unitcount;temp++)
		units[temp].selected = (units[temp].x-screenposx > left&& units[temp].x+units[temp].width-screenposx <right
			&& units[temp].y-screenposy > top && units[temp].y+units[temp].height-screenposy < bottom&&units[temp].side==playerside);
}

bool engine::CanMoveTo(unit *theunit,double x,double y) {
	for (int temp=0;temp<unitcount;temp++)
		if (theunit!=&units[temp] && DistanceToPoint(units[temp].x,units[temp].y,x,y)<
			DistanceToPoint(units[temp].x-units[temp].width/2,units[temp].y-units[temp].height/2,units[temp].x,units[temp].y)) 
			return false;
	return true;
}
bool engine::CanMoveTo(double x,double y) {
	if (x < 0 || x > mapwidth || y < 0 || y > mapheight) return false;
	for (int temp=0;temp<unitcount;temp++)
		if (DistanceToPoint(units[temp].x,units[temp].y,x,y)<25) return false;
	return true;
}
unit *engine::ConflictingUnit(unit *theunit,double x,double y) {
	for (int temp=0;temp<unitcount;temp++)
		if (theunit!=&units[temp] && DistanceToPoint(units[temp].x,units[temp].y,x,y)<25) return &units[temp];
	return NULL;
}

void engine::FindClosestMovement(unit *theunit,double x,double y) {
	int direction=GetDirection(theunit->x,theunit->y,x,y);
	double tempx,tempy;
	bool found=false;
	for (int temp=direction-90?direction-90:270+direction-90;temp<direction+90&&!found;temp+=10) {
		tempx = theunit->x+theunit->speed*cos(degtorad(temp%360));
		tempy = theunit->y+theunit->speed*sin(degtorad(temp%360));
		if (CanMoveTo(theunit,tempx,tempy)) {
			theunit->x = tempx;
			theunit->y = tempy;
			found=true;
		}
	}
}
void engine::ProcessAI(void) {

}
unit *engine::ClosestUnitInRange(unit *theunit,double range) {
	int currentrange=range;
	unit *ret=NULL;
	double temp2;
	for (int temp=0;temp<unitcount;temp++) 
		if (theunit!=&units[temp]&&units[temp].side!=theunit->side&&(temp2=DistanceToPoint(theunit->x,theunit->y,units[temp].x,units[temp].y))<currentrange) 
			 {ret=&units[temp];currentrange=temp2;}
	return ret;
}
void engine::KillUnit(unit *theunit) {//Function erases a unit from memory
	if (theunit) {
		unit *temp=&units[0];
		int temp2=0;
		while (temp<theunit&&temp2++<unitcount) temp++;
		if (temp2<=unitcount) units.erase(units.begin()+temp2);
		unitcount--;
	}
}
void engine::AddPlayer(player *theplayer) {
	players.push_back(*theplayer);
	playercount++;
}
void engine::AddPlanet(planet *theplanet) {
	planets.push_back(*theplanet);
	planetcount++;
}
void engine::Clear(void) {
	players.clear();
	planets.clear();
	units.clear();
	planetcount=0;
	unitcount=0;
	playercount=0;
	buttoncount=0;
	screenposx=0;
	screenposy=0;
	mapwidth=0;
	mapheight=0;
	x=0;y=0;pressed=0;
}
void engine::Win(void) {
	RECT rect = {0,0,798,598};
	drawing.Clear();
	drawing.DrawPicture(0,0,win,&rect);
	drawing.Flip();
	while (gameinput.leftclicked) gameinput.Update();
	while (!gameinput.leftclicked) gameinput.Update();
	while (gameinput.leftclicked) gameinput.Update();
	state=2;
	Clear();
}
void engine::Lose(void) {
}
void engine::StartGame(void) {
	buttoncount=0;
	playercount=0;
	planetcount=0;
	unitcount=0;
	unit test;
	test.x = 320;
	test.y = 240;
	test.type = 0;
	test.selected = false;
	test.width = 32;
	test.height = 32;
	test.speed = 2.0f;
	test.destx=test.x;
	test.desty=test.y;
	test.side=0;
	test.range=128.0;
	test.health = 5000;
	test.maxhealth=5000;
	test.targetted=false;
	test.attack=5;
	AddUnit(&test);
	test.y = 320;
	test.x = 240;
	test.destx=test.x;
	test.desty=test.y;
	AddUnit(&test);
	test.x = 32;
	test.y = 24;
	test.side = 1;
	AddUnit(&test);
	test.x = 700;
	test.y = 700;
	test.destx=700;
	test.desty=700;
	test.side = 1;
	AddUnit(&test);
	test.x = 800;
	test.y = 700;
	test.destx=800;
	test.desty=700;
	test.side = 1;
	AddUnit(&test);
	planet test2;
	test2.positionx=0;
	test2.positiony=0;
	test2.type=0;
	AddPlanet(&test2);
	test2.positionx=600;
	test2.positiony=700;
	test2.type=1;
	AddPlanet(&test2);
	player test3;
	test3.productionpoints=0;
	AddPlayer(&test3);
	AddPlayer(&test3);
	mapwidth=1000;
	mapheight=1000;
	ai test4;
	test4.player=1;
	compai.push_back(test4);
	LoadButtons();
}

void unit::ShootUnit(unit *target) {
	if (target!=NULL&&DistanceToPoint(x,y,target->x,target->y)<range) {
		target->health-=attack-defense?attack-defense:1;
	}
}
void engine::ProcessButtons(void) {
	for (int temp=0;temp<buttoncount;temp++)
		buttons[temp].Process();
}
void level1(bool pressed) {
	if (pressed&&(gameengine.players[0].productionpoints>=laserballcost)) {
		unit theunit;
		theunit.attack=1;
		theunit.maxhealth=16;
		theunit.health=16;
		theunit.range=200;
		theunit.speed=1;
		theunit.side=0;
		theunit.type=1;
		theunit.width=16;
		theunit.height=16;
		//theunit.
		theunit.x=/*gameengine.planets[temp].positionx+*/128;
		theunit.y=/*gameengine.planets[temp].positiony+*/128;
		theunit.destx=theunit.x;
		theunit.desty=theunit.y;
		for (int temp=0;temp<gameengine.planetcount;temp++)
			if (gameengine.planets[temp].player==0) {
				theunit.x=gameengine.planets[temp].positionx+128;
				theunit.y=gameengine.planets[temp].positiony+128;
				theunit.destx=theunit.x;
				theunit.desty=theunit.y;
			}
			gameengine.AddUnit(&theunit);
			gameengine.players[0].productionpoints-=laserballcost;
	} else gameengine.helptext="Laser-Orb:Costs 250PD;Shoots laser;Good in groups";
}
void level2(bool pressed) {
	if (pressed&&(gameengine.players[0].productionpoints>=shipcost)) {
		unit theunit;
		theunit.attack=5;
		theunit.maxhealth=320;
		theunit.health=320;
		theunit.range=100;
		theunit.defense=1;
		theunit.speed=2;
		theunit.side=0;
		theunit.type=0;
		theunit.width=32;
		theunit.height=32;
		//theunit.
		theunit.x=/*gameengine.planets[temp].positionx+*/128;
		theunit.y=/*gameengine.planets[temp].positiony+*/128;
		theunit.destx=theunit.x;
		theunit.desty=theunit.y;
		for (int temp=0;temp<gameengine.planetcount;temp++)
			if (gameengine.planets[temp].player==0) {
				theunit.x=gameengine.planets[temp].positionx+128;
				theunit.y=gameengine.planets[temp].positiony+128;
				theunit.destx=theunit.x;
				theunit.desty=theunit.y;
			}
			gameengine.AddUnit(&theunit);
			gameengine.players[0].productionpoints-=shipcost;
	}else gameengine.helptext="Small Fighter:Costs 2000PD;Takes out small groups of weak units easily";
}
void engine::LoadButton(int uppicture,int downpicture,int callback,int x,int y,int width,int height) {
	button temp;
	temp.GiveMessage(CBUTTON_SETUP,uppicture,0);
	temp.GiveMessage(CBUTTON_SETDOWN,downpicture,0);
	temp.GiveMessage(CONTROL_ACTIVATE,1,0);
	temp.GiveMessage(CONTROL_SETPOS,x,y);
	temp.GiveMessage(CONTROL_SETSIZE,width,height);
	temp.GiveMessage(CBUTTON_SETCALLBACK,callback,0);
	buttons.push_back(temp);
	buttoncount++;
}
void engine::LoadButtons(void) {
	LoadButton(drawing.LoadSurface("laserbuttonup.bmp"),drawing.LoadSurface("laserbuttondown.bmp"),(int)level1,0,32,32,32);
	LoadButton(drawing.LoadSurface("shipbutton.bmp"),drawing.LoadSurface("shipbuttondown.bmp"),(int)level2,0,64,32,32);
}
