// radio.h: interface for the radio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADIO_H__366DCE4C_91AC_4EF6_A5DB_F681DF179730__INCLUDED_)
#define AFX_RADIO_H__366DCE4C_91AC_4EF6_A5DB_F681DF179730__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"
const int CRADIO_ADDBUTTON	=0;
const int CRADIO_KILLBUTTON	=1;
const int CRADIO_CLEAR		=2;
const int CRADIO_SETPICTURES=3;
const int CRADIO_GETSELECTED=4;
class radio:public control {
	deque<POINT> buttons;
	int selected;
	int selectedpic;
	int unselectedpic;
public:
	unsigned char IsStandard(void) {return STANDARDID_RADIO;}
	radio();
	void Process(void);
	virtual ~radio();

};

#endif // !defined(AFX_RADIO_H__366DCE4C_91AC_4EF6_A5DB_F681DF179730__INCLUDED_)
