#ifndef __MY_WX_APP_H__
#define __MY_WX_APP_H__

#include "wx/wx.h"

class c_wx_app : public wxApp
{
public:
	c_wx_app() {}  

	virtual bool OnInit(); 
	virtual int OnExit(); 
	
};

#endif