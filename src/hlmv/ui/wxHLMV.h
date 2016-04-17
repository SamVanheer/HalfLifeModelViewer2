#ifndef HLMV_UI_WXHLMV_H
#define HLMV_UI_WXHLMV_H

#include "ui/wxInclude.h"

enum wxIdentifier
{
	wxID_CUSTOM_LOWEST = wxID_SHARED_HIGHEST + 1,

	//Main window
	//File menu
	wxID_MAINWND_LOADMODEL,
	wxID_MAINWND_LOADBACKGROUND,
	wxID_MAINWND_LOADGROUND,
	wxID_MAINWND_UNLOADGROUND,
	wxID_MAINWND_SAVEMODEL,
	wxID_MAINWND_RECENTFILE1,
	wxID_MAINWND_RECENTFILE2,
	wxID_MAINWND_RECENTFILE3,
	wxID_MAINWND_RECENTFILE4,

	//View menu
	wxID_MAINWND_CENTERVIEW,
	wxID_MAINWND_SAVEVIEW,
	wxID_MAINWND_RESTOREVIEW,
	wxID_MAINWND_TAKESCREENSHOT,
	wxID_MAINWND_DUMPMODELINFO,

	//Tools menu
	wxID_MAINWND_TOGGLEMESSAGES,
	wxID_MAINWND_OPTIONS,

	//Main panel
	wxID_MAIN_PAGECHANGED,
	wxID_MAIN_VIEWORIGINCHANGED,

	//Model Display panel
	wxID_MDLDISP_RENDERMODE,
	wxID_MDLDISP_OPACITY,
	wxID_MDLDISP_CHECKBOX,
	wxID_MDLDISP_SCALEMESH,
	wxID_MDLDISP_SCALEBONES,

	//Body Parts panel
	wxID_BODY_BODYPARTS,
	wxID_BODY_SUBMODELS,
	wxID_BODY_SKIN,
	wxID_BODY_CONTROLLER,
	wxID_BODY_CONTROLLER_SLIDER,

	//Base sequences panel
	wxID_BASESEQUENCE_SEQCHANGED,
	wxID_BASESEQUENCE_TOGGLEPLAY,
	wxID_BASESEQUENCE_PREVFRAME,
	wxID_BASESEQUENCE_NEXTFRAME,
	wxID_BASESEQUENCE_FRAME,
	WXID_BASESEQUENCE_ANIMSPEED,

	//Sequences panel
	wxID_SEQUENCE_EVENT,
	wxID_SEQUENCE_PLAYSOUND,

	//Weapon Origin panel
	wxID_WPN_TESTORIGINS,

	//Textures panel
	wxID_TEX_CHANGED,
	wxID_TEX_SCALE,
	wxID_TEX_CHECKBOX,
	wxID_TEX_MESH,
	wxID_TEX_IMPORTTEXTURE,
	wxID_TEX_EXPORTTEXTURE,
	wxID_TEX_EXPORTUVMAP,

	//Fullscreen panel
	wxID_FULLSCREEN_GO,

	//Options
	//General panel
	wxID_OPTIONS_GENERAL_DEFAULT_GROUND_COLOR,
	wxID_OPTIONS_GENERAL_DEFAULT_BACKGROUND_COLOR,
	wxID_OPTIONS_GENERAL_DEFAULT_CROSSHAIR_COLOR,
	wxID_OPTIONS_GENERAL_DEFAULT_LIGHT_COLOR,
	wxID_OPTIONS_GENERAL_DEFAULT_WIREFRAME_COLOR,
	wxID_OPTIONS_GENERAL_DEFAULT_FPS,

	wxID_CUSTOM_HIGHEST
};

#define HLMV_TITLE "Half-Life Model Viewer"
#define HLMV_SETTINGS_FILE "HLMVSettings.txt"
#define HLMV_DUMP_MODEL_INFO_FILE "midump.txt"

#endif //HLMV_UI_WXHLMV_H