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

#ifndef PONGMAIN_H
#define PONGMAIN_H

#include <wx/wx.h>

//(*Headers(PongFrame)
#include <wx/frame.h>
#include <wx/timer.h>
//*)

class PongFrame: public wxFrame
{
    wxBitmap bg_img;
    wxBitmap ball_img;
    wxBitmap paddle_img;

    struct projectile
    {
        double x, y, vx, vy;
    } ball, paddle[2];

    char turn;

    public:

        PongFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~PongFrame();

    private:

        //(*Handlers(PongFrame)
        void OnEraseBackground(wxEraseEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnTick(wxTimerEvent& event);
        //*)

        //(*Identifiers(PongFrame)
        static const long ID_TIMER1;
        //*)

        //(*Declarations(PongFrame)
        wxTimer GameTimer;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PONGMAIN_H
