// text.h: interface for the text class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__BF4C6C2A_2BFE_4960_BBC5_80BCDF197BAF__INCLUDED_)
#define AFX_TEXT_H__BF4C6C2A_2BFE_4960_BBC5_80BCDF197BAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"
const int CTEXT_SETTEXT =0;
const int CTEXT_SETCOLOR=1;
class text:public control
{
	char *string;
	COLORREF textcolor;
public:
	unsigned char IsStandard(void) {return STANDARDID_TEXT;}
	text();
	void Process(void);
	virtual ~text();

};

#endif // !defined(AFX_TEXT_H__BF4C6C2A_2BFE_4960_BBC5_80BCDF197BAF__INCLUDED_)
