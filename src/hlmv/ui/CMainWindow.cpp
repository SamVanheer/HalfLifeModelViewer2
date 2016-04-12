#include <wx/filename.h>

#include "hlmv/ui/CModelViewerApp.h"

#include "graphics/OpenGL.h"

#include "hlmv/CHLMVSettings.h"

#include "filesystem/CFileSystem.h"

#include "utility/CString.h"

#include "CMainPanel.h"

#include "CMainWindow.h"

wxBEGIN_EVENT_TABLE( CMainWindow, wxFrame )
	EVT_MENU( wxID_MAINWND_LOADMODEL, CMainWindow::LoadModel )
	EVT_MENU( wxID_MAINWND_LOADBACKGROUND, CMainWindow::LoadBackgroundTexture )
	EVT_MENU( wxID_MAINWND_LOADGROUND, CMainWindow::LoadGroundTexture )
	EVT_MENU( wxID_MAINWND_UNLOADGROUND, CMainWindow::UnloadGroundTexture )
	EVT_MENU( wxID_MAINWND_SAVEMODEL, CMainWindow::SaveModel )
	EVT_MENU( wxID_EXIT, CMainWindow::OnExit )
	EVT_MENU( wxID_ABOUT, CMainWindow::OnAbout )
wxEND_EVENT_TABLE()

CMainWindow::CMainWindow()
	: wxFrame( nullptr, wxID_ANY, HLMV_TITLE, wxDefaultPosition, wxSize( 600, 400 ) )
	, m_pSettings( new CHLMVSettings() )
{
	//TODO: move this
	if( !m_pSettings->LoadFromFile( "settings.txt" ) )
		m_pSettings->SaveToFile( "settings.txt" );
	else
	{
		if( auto activeConfig = m_pSettings->configManager->GetActiveConfig() )
		{
			fileSystem().SetBasePath( activeConfig->GetBasePath() );

			fileSystem().RemoveAllSearchPaths();

			CString szPath;

			const char* pszDirs[] = 
			{
				"",
				"_downloads",
				"_addon",
				"_hd"
			};

			//Note: do not use a reference here. Varargs doesn't convert it, so it'll end up being const char**.

			//Add mod dirs first, since they override game dirs.
			if( strcmp( activeConfig->GetGameDir(), activeConfig->GetModDir() ) )
			{
				for( const auto pszDir : pszDirs )
				{
					szPath.Format( "%s%s", activeConfig->GetModDir(), pszDir );

					fileSystem().AddSearchPath( szPath.CStr() );
				}
			}

			for( const auto pszDir : pszDirs )
			{
				szPath.Format( "%s%s", activeConfig->GetGameDir(), pszDir );

				fileSystem().AddSearchPath( szPath.CStr() );
			}
		}
	}

	wxMenu* menuFile = new wxMenu;

	menuFile->Append( wxID_MAINWND_LOADMODEL, "&Load Model...",
					  "Load a model" );

	menuFile->AppendSeparator();

	menuFile->Append( wxID_MAINWND_LOADBACKGROUND, "Load Background Texture..." );

	menuFile->Append( wxID_MAINWND_LOADGROUND, "Load Ground Texture..." );

	menuFile->AppendSeparator();

	menuFile->Append( wxID_MAINWND_UNLOADGROUND, "Unload Ground Texture" );

	menuFile->AppendSeparator();

	menuFile->Append( wxID_MAINWND_SAVEMODEL, "Save Model As...", "Save model to disk" );

	menuFile->AppendSeparator();

	//TODO: add recent files list
	//menuFile->AppendSubMenu( ... );

	menuFile->AppendSeparator();

	menuFile->Append( wxID_EXIT );

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append( wxID_ABOUT );

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuHelp, "&Help" );
	SetMenuBar( menuBar );

	CreateStatusBar();
	SetStatusText( "" );

	m_pMainPanel = new CMainPanel( this, m_pSettings );

	Maximize( true );

	//LoadModel( "barney.mdl" );
}

CMainWindow::~CMainWindow()
{
	//Call this first so nothing tries to access the settings object.
	DestroyChildren();

	m_pSettings->ClearStudioModel();

	delete m_pSettings;

	wxGetApp().ExitApp( true );
}

void CMainWindow::OnTimer( CTimer& timer )
{
	m_pMainPanel->OnTimer( timer );
}

bool CMainWindow::LoadModel( const wxString& szFilename )
{
	wxFileName file( szFilename );

	file.MakeAbsolute();

	const wxString szAbsFilename = file.GetFullPath();

	const bool bSuccess = m_pMainPanel->LoadModel( szAbsFilename );

	if( bSuccess )
	{
		this->SetTitle( wxString::Format( "%s - %s", HLMV_TITLE, szAbsFilename.c_str() ) );
	}
	else
		this->SetTitle( HLMV_TITLE );

	return bSuccess;
}

bool CMainWindow::PromptLoadModel()
{
	wxFileDialog dlg( this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, "Half-Life Models (*.mdl)|*.mdl" );

	if( dlg.ShowModal() == wxID_CANCEL )
		return false;

	return LoadModel( dlg.GetPath() );
}

bool CMainWindow::SaveModel( const wxString& szFilename )
{
	const bool bSuccess = m_pSettings->GetStudioModel()->SaveModel( szFilename.char_str( wxMBConvUTF8() ) );

	if( !bSuccess )
	{
		wxMessageBox( wxString::Format( "An error occurred while saving the model \"%s\"", szFilename.c_str() ) );
	}

	return bSuccess;
}

bool CMainWindow::PromptSaveModel()
{
	if( m_pSettings->GetStudioModel() == nullptr )
	{
		wxMessageBox( "No model to save!" );
		return false;
	}

	wxFileDialog dlg( this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, "Half-Life Models (*.mdl)|*.mdl", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

	if( dlg.ShowModal() == wxID_CANCEL )
		return false;

	return SaveModel( dlg.GetPath() );
}

bool CMainWindow::LoadBackgroundTexture( const wxString& szFilename )
{
	return m_pMainPanel->LoadBackgroundTexture( szFilename );
}

bool CMainWindow::PromptLoadBackgroundTexture()
{
	wxFileDialog dlg( this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, "*.*" );

	if( dlg.ShowModal() == wxID_CANCEL )
		return false;

	return LoadBackgroundTexture( dlg.GetPath() );
}

void CMainWindow::UnloadBackgroundTexture()
{
	m_pMainPanel->UnloadBackgroundTexture();
}

bool CMainWindow::LoadGroundTexture( const wxString& szFilename )
{
	return m_pMainPanel->LoadGroundTexture( szFilename );
}

bool CMainWindow::PromptLoadGroundTexture()
{
	wxFileDialog dlg( this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, "*.*" );

	if( dlg.ShowModal() == wxID_CANCEL )
		return false;

	return LoadGroundTexture( dlg.GetPath() );
}

void CMainWindow::UnloadGroundTexture()
{
	m_pMainPanel->UnloadGroundTexture();
}

void CMainWindow::LoadModel( wxCommandEvent& event )
{
	PromptLoadModel();
}

void CMainWindow::LoadBackgroundTexture( wxCommandEvent& event )
{
	PromptLoadBackgroundTexture();
}

void CMainWindow::LoadGroundTexture( wxCommandEvent& event )
{
	PromptLoadGroundTexture();
}

void CMainWindow::UnloadGroundTexture( wxCommandEvent& event )
{
	UnloadGroundTexture();
}

void CMainWindow::SaveModel( wxCommandEvent& event )
{
	PromptSaveModel();
}

void CMainWindow::OnExit( wxCommandEvent& event )
{
	Close( true );
}

void CMainWindow::OnAbout( wxCommandEvent& event )
{
	wxMessageBox( "Half-Life Model Viewer 1.40 By Sam \"Solokiller\" Vanheer",
				  "About Half-Life Model Viewer", wxOK | wxICON_INFORMATION );
}