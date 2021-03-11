// window.h: interface for the window class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOW_H__6D536665_2BD7_4154_8B70_F0680D3E52BC__INCLUDED_)
#define AFX_WINDOW_H__6D536665_2BD7_4154_8B70_F0680D3E52BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"
class control;

const int CWINDOW_SETBGCOLOR			=0;
const int CWINDOW_SETFGCOLOR			=1;
const int CWINDOW_SETTEXTCOLOR			=2;
const int CWINDOW_SETTITLEBARSIZE		=3;
const int CWINDOW_SETTITLEBARCOLOR		=4;
const int CWINDOW_SETBACKGROUND			=5;
const int CWINDOW_SETBACKGROUNDSIZE		=6;
const int CWINDOW_USESIDEPICTURE		=7;
const int CWINDOW_TOPCORNERPICTURE		=8;
const int CWINDOW_BOTTOMCORNERPICTURE	=9;
const int CWINDOW_SIDESPICTURE			=10;
const int CWINDOW_TOPBOTTOMPICTURE		=11;

class window:public control {
	COLORREF	bgcolor;
	COLORREF	textcolor;
	COLORREF	foregroundcolor;
	COLORREF	titlebarcolor,titlebarcolor2;
	int			titlebarsize;
	bool		selected;
	int			backgroundpicture,bgpicwidth,bgpicheight;
public:
	unsigned char IsStandard(void) {return STANDARDID_WINDOW;}
	void Process();
	window();
	virtual ~window();

};

#endif // !defined(AFX_WINDOW_H__6D536665_2BD7_4154_8B70_F0680D3E52BC__INCLUDED_)
