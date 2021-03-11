// window.cpp: implementation of the window class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern draw drawing;
extern input gameinput;
window::window() {
	x=0;
	y=0;
	width=0;
	height=0;
	bgcolor=0;
	foregroundcolor=RGB(0,255,0);
	textcolor=RGB(255,255,255);
	titlebarcolor=RGB(40,40,40);
	titlebarcolor2=RGB(0,0,0);
	titlebarsize=20;
	selected=false;
	active=true;
	backgroundpicture=-1;
}
window::~window()
{

}
void window::Process() {
	int size = messages.size();
	while (size--) {
		switch (messages[0].message) {
		case CONTROL_SETPOS:
			if	(messages[0].parameter1>0&&messages[0].parameter1<drawing.width&&(!parent||
				(messages[0].parameter1>parent->xpos()&&messages[0].parameter1<parent->xpos()+parent->GetWidth())))
				x = messages[0].parameter1;
			if	(messages[0].parameter2>0&&messages[0].parameter2<drawing.height&&(!parent||
				(messages[0].parameter2>parent->ypos()&&messages[0].parameter2<parent->ypos()+parent->GetHeight())))
				y = messages[0].parameter2;
			break;
		case CONTROL_SETSIZE:
			width=messages[0].parameter1;
			height=messages[0].parameter2;
			break;
		case CWINDOW_SETTITLEBARSIZE:
			titlebarsize=messages[0].parameter1;
			break;
		case CWINDOW_SETTITLEBARCOLOR:
			titlebarcolor=messages[0].parameter1;
			break;
		case CWINDOW_SETBGCOLOR:
			bgcolor=messages[0].parameter1;
			break;
		case CWINDOW_SETFGCOLOR:
			foregroundcolor=messages[0].parameter1;
			break;
		case CWINDOW_SETTEXTCOLOR:
			textcolor=messages[0].parameter1;
			break;
		case CONTROL_ACTIVATE:
			active=messages[0].parameter1;
			break;
		case CWINDOW_SETBACKGROUND:
			backgroundpicture=messages[0].parameter1;
			break;
		case CWINDOW_SETBACKGROUNDSIZE:
			bgpicwidth=messages[0].parameter1;
			bgpicheight=messages[0].parameter2;
			break;
		default:
			break;//Do nothing for default
		}
		messages.pop_front();
	}
	if (active) {
		if (gameinput.leftclicked&&(selected||(gameinput.mousex>xpos()&&gameinput.mousex<xpos()+width&&
			gameinput.mousey>ypos()&&gameinput.mousey<ypos()+titlebarsize))) {
			x+=(x+gameinput.xdiff>0&&x+gameinput.xdiff+width<drawing.width )?gameinput.xdiff:(gameinput.mousex-=gameinput.xdiff,0);
			y+=(y+gameinput.ydiff>0&&y+gameinput.ydiff+height<drawing.height)?gameinput.ydiff:(gameinput.mousey-=gameinput.ydiff,0);
			selected=true;
		} else selected=false;
		if (backgroundpicture<0)drawing.DrawColor(x,y,x+width,y+height,bgcolor);
		else drawing.DrawPictureRepeat(backgroundpicture,bgpicwidth,bgpicheight,xpos(),ypos(),xpos()+width,ypos()+height);
		drawing.DrawColor(x,y,x+width,y+titlebarsize,selected?titlebarcolor:titlebarcolor2);
		drawing.DrawLine(x,y+titlebarsize,x+width,y+titlebarsize,foregroundcolor);
		drawing.DrawLine(x,y,x,y+height,foregroundcolor);
		drawing.DrawLine(x,y+height,x+width,y+height,foregroundcolor);
		drawing.DrawLine(x+width,y+height,x+width,y,foregroundcolor);
	}
}