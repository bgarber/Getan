/*
 * Copyright 2018 Bryan Garber
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <getanapplication.h>

#include <getaneventdispatcher.h>
#include <getankeyboard.h>
#include <getanbuffer.h>
#include <getanevents.h>

#include <fstream>

GetanApplication::GetanApplication( GetanWindow *pWindow ) :
    m_pWindow     ( pWindow )
{
    m_pDispatcher = GetanEventDispatcher::getInstance();

    m_pDispatcher->RegisterEventHandler( GETAN_EVENT_CLOSE_APP, this );
    m_pDispatcher->RegisterEventHandler( GETAN_EVENT_OPEN_FILE, this );
}

GetanApplication::~GetanApplication( )
{
    //m_pDispatcher->UnregisterFromAllEvents(this);
}

int
GetanApplication::start( )
{
    const GetanKeyboard *pKeyboard = m_pWindow->getKeyboard();

    // Load basic editor configuration.
    //m_pConfiguration->SetDefaults();
    //m_pConfiguration->ReadUserDefined();
    //keyManager->SetupKeyShortcuts(m_pConfiguration->getConfiguredShortCuts());

    // Start window.
    m_pWindow->init();

    GetanOpenFileEventData eventData("/home/bgarber/Projects/Getan/compile.sh");
    m_pDispatcher->Dispatch(&eventData);

    /*
     * MAIN LOOP
     */
    while ( pKeyboard->getChr() != 'q' )
    {
        // TODO
    }

    // End window.
    m_pWindow->exit();

    return 0;
}

void
GetanApplication::HandleEvent( GetanEventData *pData )
{
    GetanOpenFileEventData *pOpenFile;

    switch ( pData->m_eventId ) {
    case GETAN_EVENT_OPEN_FILE:
        pOpenFile = dynamic_cast<GetanOpenFileEventData *>(pData);
        OpenFile(pOpenFile->m_filename);
        break;
    default:
        // Unknown event.
        break;
    }
}

void
GetanApplication::OpenFile( std::string& filename )
{
    std::fstream fileStream;
    fileStream.open(filename);
    GetanBuffer fileBuffer;
    fileBuffer.read(&fileStream);
    m_pWindow->setBuffer(&fileBuffer);
    //m_pWindow->Refresh();
}

