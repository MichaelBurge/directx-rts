#include "main.h"
bool running=true;
HWND hwnd;
int selectedkey,target,targetted;
TCHAR szWindowClass[] = "Window";
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
long _stdcall WndProc(HWND hwnd, unsigned int message, WPARAM wparam, LPARAM lparam);

draw drawing;
input gameinput;
engine gameengine;
music gamemusic;
button tehbutton;
window tehwindow;
text tehtext;
checkbox tehcheck;
d3d direct3d;
debug debugger;
int screenx=0,screeny=0;
int x=0,y=0;
int targetrotation=0;
int playerside=0;
int state=0;
int stars=0;
int firstplanet=0;
int win,lose;
int redx;
int bottomgui;
int playercolors[] = {
	RGB(0,255,0),
	RGB(255,0,0)
};
bool initialized=false;
void inputprocess(char key) {
	static bool window=true;
	switch(key) {
	case DIK_F2:
		window=!window;
		//tehwindow.GiveMessage(CONTROL_ACTIVATE,window,0);
	}
}
void Process(void) {
	//if (!initialized) {direct3d.initialize(hwnd);initialized=true;}
	RECT rect = {0,0,32,32};
	gameinput.Update();

	if (gameinput.KeyPressed(DIK_ESCAPE)) {running=false;return;}

/*	x = gameinput.mousex;
	y = gameinput.mousey;
	if (x < 16) x=16;
	if (x >= drawing.width-16) x=drawing.width-17;
	if (y < 16) y=16;
	if (y >= drawing.height-16) y=drawing.height-17;
	if (targetrotation==360) targetrotation=0;
	targetrotation++;
//	SetCursorPos(x,y);
	if (SUCCEEDED(drawing.Clear())) {
		drawing.DrawPictureRepeat(stars,256,256,-(gameengine.screenposx%255),-(gameengine.screenposy%255),drawing.width,drawing.height);
		//drawing.DrawColor(0,0,540,540,RGB(25,25,25));
		switch(state) {
		case 0:tehwindow.Process();tehbutton.Process();tehtext.Process();tehcheck.Process();break;
		case 1:gameengine.Process();break;
		case 2:state=0;return;
		}
		gameengine.ProcessButtons();
		drawing.DrawPicture(x-16,y-16,target,&rect);
		drawing.Flip();
	}*/
	

	direct3d.Clear();
	direct3d.Start();
	
	vertex vertexes[] =
    {
        {  50.0f,  50.0f, 0.0f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.0f, 1.0f, 0xff00ff00, },
        {  50.0f, 250.0f, 0.0f, 1.0f, 0xff00ffff, },
    };
	triangle atriangle(D3DFVF_VERTEX,sizeof(vertex),vertexes,direct3d.device);
	direct3d.End();
	direct3d.Flip();
	
}
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}


void blah(bool pressed) {
	if (pressed) {
		gameengine.StartGame();
		state=1;
	}
}
int _stdcall WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int nshowcmd) {
	MSG msg;
	MyRegisterClass(hinstance);
	hwnd=CreateWindowEx(WS_EX_APPWINDOW|WS_EX_TOPMOST	,
		szWindowClass, "DirectX RTS", WS_POPUP,
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		NULL, NULL, hinstance, NULL);
	ShowWindow(hwnd,1);
	if (hwnd) {
		drawing.SetBackground(CLR_INVALID);
		gamemusic.LoadMusic(L"music.mid",DMUS_SEG_REPEAT_INFINITE,GUID_StandardMIDIFile);
		gamemusic.PlayMusic(0);
	/*	drawing.initialize(hwnd);
		drawing.LoadSurface("ship.bmp");
		drawing.LoadSurface("laserball.bmp");
		selectedkey=drawing.LoadSurface("selected.bmp");
		target = drawing.LoadSurface("target.bmp");
		targetted=drawing.LoadSurface("targetted.bmp");
		stars=drawing.LoadSurface("stars.bmp");
		firstplanet=drawing.LoadSurface("planet1.bmp");
		drawing.LoadSurface("volcano.bmp");
		win=drawing.LoadSurface("win.bmp");
		redx=drawing.LoadSurface("x.bmp");*/
		gameinput.initialize(hwnd,0,0,800,600);
		gameinput.SetCallback(inputprocess);
		/*tehbutton.GiveMessage(CBUTTON_SETUP,drawing.LoadSurface("uppicture.bmp"),0);
		tehbutton.GiveMessage(CBUTTON_SETDOWN,drawing.LoadSurface("downpicture.bmp"),0);
		tehbutton.GiveMessage(CBUTTON_SETCALLBACK,(int)blah,0);
		tehbutton.GiveMessage(CONTROL_SETPOS,40,120);
		tehbutton.GiveMessage(CONTROL_SETSIZE,320,160);
		tehwindow.GiveMessage(CONTROL_SETPOS,0,0);
		tehwindow.GiveMessage(CONTROL_SETSIZE,100,100);
		tehcheck.GiveMessage(CONTROL_SETPOS,10,10);
		tehcheck.GiveMessage(CONTROL_SETSIZE,16,16);
		tehcheck.GiveMessage(CCHECKBOX_SETPICTURE,drawing.LoadSurface("radiooff.bmp"),drawing.LoadSurface("radioon.bmp"));*/
		ShowCursor(NULL);
		debugger.SetFile("log.txt");
		direct3d.initialize(hwnd);
		while (running) {
			
			if (PeekMessage(&msg,0,0,0,PM_NOREMOVE)) {
				if (!GetMessage(&msg,0,0,0)) running = false;
				else DispatchMessage(&msg);
			} else Process();
		}
	} else MessageBox(NULL,NULL,NULL,NULL);
	return 0;
}

long _stdcall WndProc(HWND hwnd, unsigned int message, WPARAM wparam, LPARAM lparam) {
	switch (message) {
	case WM_DESTROY:
		DestroyWindow(hwnd);
		running=false;
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		running=false;
		break;
	default:
		return DefWindowProc(hwnd,message,wparam,lparam);
	
	}
	return TRUE;
}


