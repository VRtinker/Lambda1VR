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
#include "Bitmap.h"
#include "PicButton.h"
#include "Slider.h"
#include "CheckBox.h"
#include "SpinControl.h"

#define ART_BANNER		"gfx/shell/head_touch"

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
    CMenuPicButton turningwarning;
    CMenuCheckBox   HMDDirection;
    CMenuCheckBox   WeaponRecoil;
    CMenuCheckBox   hand;
    CMenuSpinControl   snapturn;
    CMenuSlider   smoothturn;
} uiTouch;

void CMenuTouch::SaveAndPopMenu( void )
{
    HMDDirection.WriteCvar();
    WeaponRecoil.WriteCvar();
    hand.WriteCvar();
    snapturn.WriteCvar();
    smoothturn.WriteCvar();

    CMenuFramework::SaveAndPopMenu();
}
void CMenuTouch::_Init( void )
{

    banner.SetPicture(ART_BANNER);

    snapturn.SetNameAndStatus( "Snap-Turn Angle", "Choose among 3 different snap-turn angles (15, 30 or 45 degrees)" );
    snapturn.SetCoord(72, 260);
    snapturn.onChanged = CMenuEditable::WriteCvarCb;
    snapturn.LinkCvar( "vr_snapturn_angle", CMenuEditable::CVAR_VALUE );
    snapturn.Setup(15,45,15);
    snapturn.font = QM_SMALLFONT;
    snapturn.SetRect(72, 280, 300, 32 );

    smoothturn.SetNameAndStatus("Smooth-Turn Speed", "Choose among 5 different smooth-turn levels (1 - 5)");
    smoothturn.SetCoord(540, 280);
    smoothturn.Setup(1, 3, 0.5);
    smoothturn.LinkCvar("vr_snapturn_angle");
    smoothturn.onChanged = CMenuEditable::WriteCvarCb;

    turningwarning.SetNameAndStatus( "HOVER HERE TO READ MORE ABOUT THE TURNING OPTIONS", "When you modify the Snap-Turn Angle or the Smooth-Turn Speed\nthe element changed as last will be designated as active/enabled in game\n" );
    turningwarning.SetCoord( 440, 660 );

    HMDDirection.SetNameAndStatus( "Use HMD for walking direction", "The walking direction is based on the forward direction of the HMD when ON\nThe walking direction is based on the forward direction of the Off-Hand Controller when OFF" );
    HMDDirection.SetCoord( 540, 380 );
    HMDDirection.LinkCvar( "vr_walkdirection" );

    WeaponRecoil.SetNameAndStatus( "Weapon Recoil", "Enables weapon recoil in VR, WARNING could make you sick" );
    WeaponRecoil.SetCoord( 540, 460 );
    WeaponRecoil.LinkCvar( " vr_weaponrecoil" );

    hand.SetNameAndStatus( "Left-Handed", "Enable this if you are left-handed" );
    hand.SetCoord( 72, 380 );
    hand.LinkCvar( "hand" );

    done.SetNameAndStatus( "Done", "Go back to the Configuration Menu" );
    done.SetCoord( 670, 520 );
    done.SetPicture( PC_DONE );
    done.onActivated = VoidCb( &CMenuTouch::SaveAndPopMenu );

    AddItem( background );
    AddItem( banner);
    AddItem( turningwarning);
    AddItem( HMDDirection);
    AddItem( hand);
    AddItem( snapturn);
    AddItem( smoothturn);
    AddItem( WeaponRecoil);
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
    EngFuncs::PIC_Load( ART_BANNER );
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

