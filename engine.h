// engine.h: interface for the engine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGINE_H__41D04E05_498F_41E0_843A_63640A3B5513__INCLUDED_)
#define AFX_ENGINE_H__41D04E05_498F_41E0_843A_63640A3B5513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"
class engine;
class button;
class ai;
extern engine gameengine;
	struct unit {
	int type;
	short rotation;
	double x,y;
	int destx,desty;
	bool selected;
	int width,height;
	int side;
	int chargetime;
	double speed;
	int range;
	int attack;
	int defense;
	unit *target;
	int health,maxhealth;
	bool targetted;
	void ShootUnit(unit *target);
	unit(void) {
		type=0;
		rotation=0;
		destx=0;
		desty=0;
		selected=false;
		width=0;
		height=0;
		side=0;
		chargetime=0;
		speed=0;
		range=0;
		attack=40;
		defense=0;
		target=NULL;
		health=1;
		maxhealth=1;
		targetted=false;
	}
};
struct planet {
	int type;
	int positionx,positiony; 
	int player;
};
struct player {
	int productionpoints;
};
class engine  
{
	

	int x,y;
	bool pressed;
	int mapwidth,mapheight;
	window options;
	checkbox resourceinfinite;
public:
	int screenposx,screenposy;
	deque<unit> units;
	vector<player> players;
	deque<button> buttons;
	vector<planet> planets;
	vector<ai> compai;
	strings helptext;
	int buttoncount;
	int unitcount;
	int playercount;
	int planetcount;
	void AddUnit(unit *theunit);
	void AddPlanet(planet *theplanet);
	void AddPlayer(player *theplayer);
	void MoveUnit(unit *theunit);
	void Process(void);
	void ProcessUnit(unit *theunit);
	void ProcessPlanet(planet *theplanet);
	void ProcessGUI(void);
	void ProcessButtons(void);
	void ProcessAI(void);
	void SelectWithinBox(int x,int y,int x2,int y2);
	void FindClosestMovement(unit *theunit,double x,double y);
	void KillUnit(unit *theunit);
	void StartGame(void);
	void Clear(void);
	void Lose(void);
	void Win(void);
	void LoadButtons(void);
	void LoadButton(int uppicture,int downpicture,int callback,int x,int y,int width,int height);
	unit *ClosestUnitInRange(unit *theunit,double range);
	bool CanMoveTo(unit *theunit,double x,double y);
	bool CanMoveTo(double x,double y);
	unit *ConflictingUnit(unit *theunit,double x,double y);
	engine();
	virtual ~engine();
	friend unit;
	friend ai;
};

#endif // !defined(AFX_ENGINE_H__41D04E05_498F_41E0_843A_63640A3B5513__INCLUDED_)
