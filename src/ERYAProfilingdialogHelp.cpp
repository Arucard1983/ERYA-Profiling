/***************************************************************
 * Name:      ERYAProfilingdialogHelp.cpp
 * Purpose:   ERYA Help Viewer implementation
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2017-03-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/

#include "ERYAProfilingdialogHelp.h"
#include "ERYAProfilingERYAProfilingMain.h"
#include "ERYAProfilingdialogAddDatabase.h"
#include "ERYAProfilingdialogDatabaseManager.h"
#include "ERYAProfilingdialogDetectorSetup.h"
#include "ERYAProfilingdialogZieglerParameters.h"
#include "ERYAProfilingdialogERYACalculator.h"

ERYAProfilingdialogHelp::ERYAProfilingdialogHelp( wxWindow* parent )
:
dialogHelp( parent )
{

}

ERYAProfilingdialogHelp::ERYAProfilingdialogHelp( wxWindow* parent, wxString HelpFile)
:
dialogHelp( parent )
{
  wxString rootpath = ::wxStandardPaths::Get().GetExecutablePath();
  wxFileName rootfile(rootpath);
  rootpath = rootfile.GetPath();
  pageHelpViewer->LoadPage(rootpath + wxFileName::GetPathSeparator() + HelpFile);
  helpMainPage = HelpFile;
}

void ERYAProfilingdialogHelp::OnHelpMain( wxCommandEvent& event )
{
 wxString rootpath = ::wxStandardPaths::Get().GetExecutablePath();
 wxFileName rootfile(rootpath);
 rootpath = rootfile.GetPath();
 pageHelpViewer->LoadPage(rootpath + wxFileName::GetPathSeparator() + helpMainPage);
}

void ERYAProfilingdialogHelp::OnHelpIndex( wxCommandEvent& event )
{
 wxString rootpath = ::wxStandardPaths::Get().GetExecutablePath();
 wxFileName rootfile(rootpath);
 rootpath = rootfile.GetPath();
 pageHelpViewer->LoadPage(rootpath + wxFileName::GetPathSeparator() + wxT("Index.html"));
}

void ERYAProfilingdialogHelp::OnHelpReadme( wxCommandEvent& event )
{
 wxString rootpath = ::wxStandardPaths::Get().GetExecutablePath();
 wxFileName rootfile(rootpath);
 rootpath = rootfile.GetPath();
 pageHelpViewer->LoadPage(rootpath + wxFileName::GetPathSeparator() + wxT("readme.txt"));
}

void ERYAProfilingdialogHelp::OnHelpBack( wxCommandEvent& event )
{
  pageHelpViewer->HistoryBack();
}

void ERYAProfilingdialogHelp::OnHelpForward( wxCommandEvent& event )
{
  pageHelpViewer->HistoryForward();
}

void ERYAProfilingdialogHelp::OnHelpClose( wxCommandEvent& event )
{
 Destroy();
}
