// input.h: interface for the input class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUT_H__BB702B0F_54F6_4078_8278_DC73269548A5__INCLUDED_)
#define AFX_INPUT_H__BB702B0F_54F6_4078_8278_DC73269548A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"

class input  
{
	IDirectInput *directinput;
	IDirectInputDevice *keyboard;
	IDirectInputDevice *mouse;
	char keyboardbuffer[256];
	HWND hwnd;
	int x,y;
	int screenwidth,screenheight;
	void (*callback)(char);//Callback function for when keys are pressed
public:
	int mousex,mousey,xdiff,ydiff;
	bool leftclicked,rightclicked;
	void initialize(HWND hWnd,int x,int y,int screenwidth,int screenheight);
	int KeyPressed(int key);
	bool Update(void);
	void SetCallback(void (*target)(char));
	input();
	virtual ~input();

};

#endif // !defined(AFX_INPUT_H__BB702B0F_54F6_4078_8278_DC73269548A5__INCLUDED_)
