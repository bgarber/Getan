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

#include <getaneventdispatcher.h>

GetanEventDispatcher::GetanEventDispatcher()
    : m_eventHandlerTable()
{

}


GetanEventDispatcher::~GetanEventDispatcher()
{

}

GetanEventDispatcher *
GetanEventDispatcher::getInstance()
{
    static GetanEventDispatcher *instance = nullptr;
    if ( nullptr == instance ) {
        instance = new GetanEventDispatcher();
    }

    return instance;
}

void
GetanEventDispatcher::RegisterEventHandler( GetanEvent evt,
        GetanEventHandler *pHandler )
{
    m_eventHandlerTable[evt].push_back(pHandler);
}

void
GetanEventDispatcher::Dispatch( GetanEventData *pEvtData )
{

}
