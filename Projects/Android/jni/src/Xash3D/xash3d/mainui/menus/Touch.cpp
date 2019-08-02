/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include <filesystem>
#include "Framework.h"
#include "PicButton.h"
#include "Slider.h"
#include "CheckBox.h"


class CMenuTouch : public CMenuFramework
{
private:
    void _Init() override;
    void _VidInit() override;

public:
    CMenuTouch() : CMenuFramework( "CMenuTouch" ) { }
    void SaveAndPopMenu() override;

    int		outlineWidth;

    CMenuPicButton	done;
    CMenuPicButton VROptions;
    CMenuPicButton turningwarning;
    CMenuSlider	smoothturning;
    CMenuSlider	snapturning;
    CMenuCheckBox   HMDDirection;
    CMenuCheckBox   hand;
} uiTouch;

void CMenuTouch::SaveAndPopMenu( void )
{
    snapturning.WriteCvar();
    smoothturning.WriteCvar();
    HMDDirection.WriteCvar();
    hand.WriteCvar();

    CMenuFramework::SaveAndPopMenu();
}
void CMenuTouch::_Init( void )
{

    snapturning.SetNameAndStatus("Snap Turning", "Choose among 3 different snap-rotation angles (15, 30 or 45 degrees)");
    snapturning.SetCoord(72, 220);
    snapturning.Setup(15, 45, 15);
    snapturning.LinkCvar("vr_snapturn_angle");
    snapturning.onChanged = CMenuEditable::WriteCvarCb;

    smoothturning.SetNameAndStatus("Smooth Turning", "Choose among 5 different smooth-acceleration levels (1 - 5)");
    smoothturning.SetCoord(72, 280);
    smoothturning.Setup(1, 3, 0.5);
    smoothturning.LinkCvar("vr_snapturn_angle");
    smoothturning.onChanged = CMenuEditable::WriteCvarCb;

    VROptions.SetNameAndStatus( "VR OPTIONS", "" );
    VROptions.SetCoord( 640, 120 );

    turningwarning.SetNameAndStatus( "HOVER HERE TO READ ABOUT THE TURNING SLIDERS", "The last used slider (Snap or Smooth) will be designated as active/enabled" );
    turningwarning.SetCoord( 440, 220 );

    HMDDirection.SetNameAndStatus( "Use HMD for walking direction", "The walking direction is based on the forward direction of the HMD when ON, or the forward direction of the Off-Hand Controller when OFF" );
    HMDDirection.SetCoord( 72, 340 );
    HMDDirection.LinkCvar( "vr_walkdirection" );

    hand.SetNameAndStatus( "Left-Handed", "Enable this if you are left-handed" );
    hand.SetCoord( 72, 400 );
    hand.LinkCvar( "hand" );

    done.SetNameAndStatus( "Done", "Go back to the Configuration Menu" );
    done.SetCoord( 670, 400 );
    done.SetPicture( PC_DONE );
    done.onActivated = VoidCb( &CMenuTouch::SaveAndPopMenu );


    AddItem( background );
    AddItem( smoothturning);
    AddItem( snapturning);
    AddItem( VROptions);
    AddItem( turningwarning);
    AddItem( HMDDirection);
    AddItem( hand);
    AddItem( done );
}

void CMenuTouch::_VidInit()
{
    outlineWidth = 2;
    UI_ScaleCoords( NULL, NULL, &outlineWidth, NULL );
}

/*
=================
UI_Touch_Precache
=================
*/
void UI_Touch_Precache( void )
{
}

/*
=================
UI_Touch_Menu
=================
*/
void UI_Touch_Menu( void )
{
    uiTouch.Show();
}
ADD_MENU( menu_touch, UI_Touch_Precache, UI_Touch_Menu );

