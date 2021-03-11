// control.h: interface for the control class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROL_H__E6FA119D_60D0_40B1_B372_FF81B103B66B__INCLUDED_)
#define AFX_CONTROL_H__E6FA119D_60D0_40B1_B372_FF81B103B66B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
struct Message {
	int message,parameter1,parameter2;
};
const int STANDARDID_BUTTON		=1;
const int STANDARDID_CHECKBOX	=2;
const int STANDARDID_RADIO		=3;
const int STANDARDID_TEXT		=4;
const int STANDARDID_WINDOW		=5;

const int CONTROL_SETPOS		=-1;
const int CONTROL_SETSIZE		=-2;
const int CONTROL_ACTIVATE		=-3;
class control {
protected:
	int x,y;
	int width,height;
	deque<Message> messages;
	deque<control*> children;
	control *parent;
	bool active;
	void virtual Process()=0;
public:
	////void virtual Save(void);
	//void virtual Load(void);
	unsigned char virtual IsStandard(void)=0;
	void GiveMessage(int message,int parameter1,int parameter2);
	int xpos(void) {return x+(parent?parent->xpos():0);}
	int ypos(void) {return y+(parent?parent->ypos():0);}
	void SetParent(control *target) {parent=target;}
	int AddChild(control *target);
	void SetChild(int child, control *target);
	void RemoveChild(int child);
	int GetWidth() {return width;}
	int GetHeight(){return height;}
	virtual ProcessAll(void) {
		Process();
		for (int temp=0;temp<children.size();temp++)
			children[temp]->ProcessAll();
	}
};

#endif // !defined(AFX_CONTROL_H__E6FA119D_60D0_40B1_B372_FF81B103B66B__INCLUDED_)
