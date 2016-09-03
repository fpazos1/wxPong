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

#include "PongMain.h"

#include <time.h>

#include <wx/msgdlg.h>
#include <wx/utils.h>
#include <wx/dcbuffer.h>
#include <wx/defs.h>

//( *InternalHeaders( PongFrame )
#include <wx/intl.h>
#include <wx/string.h>
//* )

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo( wxbuildinfoformat format )
{
    wxString wxbuild( wxVERSION_STRING );

    if ( format == long_f  )
    {
#if defined( __WXMSW__ )
        wxbuild << _T( "-Windows" );
#elif defined( __UNIX__ )
        wxbuild << _T( "-Linux" );
#endif

#if wxUSE_UNICODE
        wxbuild << _T( "-Unicode build" );
#else
        wxbuild << _T( "-ANSI build" );
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//( *IdInit( PongFrame )
const long PongFrame::ID_TIMER1 = wxNewId(  );
//* )

BEGIN_EVENT_TABLE( PongFrame,wxFrame )
    //( *EventTable( PongFrame )
    //* )
END_EVENT_TABLE(  )

PongFrame::PongFrame( wxWindow* parent,wxWindowID id )
{
    srand( time( NULL ) );

    bg_img.LoadFile( wxT( "bg.png" ), wxBITMAP_TYPE_PNG );
    ball_img.LoadFile( wxT( "ball.png" ), wxBITMAP_TYPE_PNG );
    paddle_img.LoadFile( wxT( "paddle.png" ), wxBITMAP_TYPE_PNG );

    turn = -1;
    ball.x = 232; // Ball’s x component
    ball.y = 232; // Ball’s y component
    ball.vx = rand(  ) % 10 - 5; // Generate ball’s velocity y component from -20 to 20
    ball.vy = rand(  ) % 10 - 5; // Generate ball’s velocity x component from -20 to 20
    paddle[0].x = 0; // Paddle’s x component
    paddle[0].y = 208; // Paddle’s x component
    paddle[1].x = 456; // Paddle’s y component
    paddle[1].y = 208; // Paddle’s y component

    //( *Initialize( PongFrame )
    Create( parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxNO_FULL_REPAINT_ON_RESIZE|wxCLIP_CHILDREN, _T( "id" ) );
    SetClientSize( wxSize( 480,480 ) );
    GameTimer.SetOwner( this, ID_TIMER1 );
    GameTimer.Start( 17, false );

    Connect( ID_TIMER1,wxEVT_TIMER,( wxObjectEventFunction )&PongFrame::OnTick );
    Connect( wxID_ANY,wxEVT_PAINT,( wxObjectEventFunction )&PongFrame::OnPaint );
    Connect( wxID_ANY,wxEVT_ERASE_BACKGROUND,( wxObjectEventFunction )&PongFrame::OnEraseBackground );
    //* )
}

PongFrame::~PongFrame(  )
{
    //( *Destroy( PongFrame )
    //* )
}

void PongFrame::OnEraseBackground( wxEraseEvent& event )
{
}

void PongFrame::OnPaint( wxPaintEvent& event )
{
    wxBufferedPaintDC dc( this );

    dc.BeginDrawing(  );

    dc.DrawBitmap( bg_img, 0, 0, true );
    dc.DrawBitmap( paddle_img, int( paddle[0].x ), int( paddle[0].y ), true );
    dc.DrawBitmap( paddle_img, int( paddle[1].x ), int( paddle[1].y ), true );
    dc.DrawBitmap( ball_img, int( ball.x ), int( ball.y ), true );

    dc.EndDrawing(  );
}

void PongFrame::OnTick( wxTimerEvent& event )
{
    if( wxGetKeyState( WXK_SHIFT ) )
        paddle[0].y -= 8;
    else if( wxGetKeyState( WXK_CONTROL ) )
        paddle[0].y += 8;
    if( wxGetKeyState( WXK_UP ) )
        paddle[1].y -= 8;
    else if( wxGetKeyState( WXK_DOWN ) )
        paddle[1].y += 8;

	ball.x += ball.vx;
	ball.y += ball.vy;

    if( ball.x < 0 || ball.x > 464 )
    {
        ball.x = 232;                               // Ball’s x component
        ball.y = 232;                               // Ball’s y component
        ball.vx = ( rand(  ) % 10 + 1 ) * turn;         // Generate ball’s velocity y component
        ball.vy = rand(  ) % 10 + 1;                  // Generate ball’s velocity x component
        paddle[0].x = 0;                            // Paddle’s x component
        paddle[0].y = 208;                          // Paddle’s x component
        paddle[1].x = 456;                          // Paddle’s y component
        paddle[1].y = 208;                          // Paddle’s y component
        turn = ( turn < 0 ) ? 1 : -1;
    }
    else if( ball.y < 0 || ball.y > 464 )
        ball.vy *= -1;
	else if( ( ball.x < 24 && ball.y > paddle[0].y && ball.y + 16 < paddle[0].y + 64 )
        || ( ball.x > 456 && ball.y > paddle[1].y && ball.y + 16 < paddle[1].y + 64 ) )
        ball.vx *= -1;


    this->Refresh(  );
}
