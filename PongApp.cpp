/**
    Name :          wxPong
    Purpose :
                    wxPong is a port of the classic video game, Pong, on the C++ platform wxWidgets. Created as a project template for the Glenforest Secondary School Grade 12 Computer Science course.

    Author :        Copyright 2010 Daniel Li (http://x711Li.com/)
    Created :       04/28/10
    Tools :         n/a
    License :
                    This file is part of wxPong.
                    wxPong is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
                    wxPong is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
                    You should have received a copy of the GNU General Public License along with wxPong. If not, see http://www.gnu.org/licenses/.
**/

#include "PongApp.h"

//(*AppHeaders
#include "PongMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PongApp);

bool PongApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PongFrame* Frame = new PongFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
