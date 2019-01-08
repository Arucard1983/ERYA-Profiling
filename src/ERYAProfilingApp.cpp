/***************************************************************
 * Name:      ERYAProfilingApp.cpp
 * Purpose:   ERYA Profiling Application Class
 * Author:    Vasco Manteigas (vm.manteigas@campus.fct.utl.pt)
 * Created:   2017-03-01
 * Copyright: Grupo de Reacoes Nucleares - LIBPHYS
 * License:
 **************************************************************/


#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ERYAProfilingApp.h"
#include "ERYAProfilingERYAProfilingMain.h"

IMPLEMENT_APP(ERYAProfilingApp);

bool ERYAProfilingApp::OnInit()
{

    ERYAProfilingERYAProfilingMain* frame = new ERYAProfilingERYAProfilingMain(0L);

    frame->Show();

    frame->Maximize(true);

    wxFileSystem::AddHandler(new wxZipFSHandler);

    ::wxInitAllImageHandlers();

    return true;
}
