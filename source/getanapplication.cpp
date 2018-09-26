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
#include <getankeyboard.h>
#include <getanbuffer.h>
#include <getaneventdispatcher.h>

#include <fstream>

GetanApplication::GetanApplication( GetanWindow *pWindow )
    : m_pWindow ( pWindow )
{
    GetanEventDispatcher *evtDispatcher = GetanEventDispatcher::getInstance();

    evtDispatcher->RegisterEvent( GetanEventDispatcher::EVENT_CLOSE_APP,
          &GetanApplication::EventHandler );
    evtDispatcher->RegisterEvent( GetanEventDispatcher::EVENT_OPEN_FILE,
          &GetanApplication::EventHandler );
}

GetanApplication::~GetanApplication( )
{

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

    std::fstream fileStream;
    fileStream.open("/home/bgarber/Projects/Getan/compile.sh");
    GetanBuffer fileBuffer;
    fileBuffer.read(&fileStream);
    m_pWindow->setBuffer(&fileBuffer);
    //m_pWindow->Refresh();

    /*
     * MAIN LOOP
     */
    while ( pKeyboard->getChr() != 'q' )
    {
        //empty.
    }

    // End window.
    m_pWindow->exit();

    return 0;
}

GetanEventDispatcher::EventHandlerPtr
GetanApplication::EventHandler( GetanEventDispatcher::Event eventId,
      GetanEventDispatcher::EventData *pData )
{
    switch ( eventId ) {
    case GetanEventDispatcher::EVENT_CLOSE_APP:
       break;
    case GetanEventDispatcher::EVENT_OPEN_FILE:
       break;
    default:
       // empty.
    }
}

