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

#ifndef GETANEVENTDISPATCHER_H
#define GETANEVENTDISPATCHER_H

#include <getanevents.h>
#include <getaneventhandler.h>

#include <vector>

/**
 * @class GetanEventDispatcher
 * @brief Simple event dispatcher system for Getan. This class is a Singleton.
 */
class GetanEventDispatcher {
private:
    /**
     * @brief Private constructor.
     */
    GetanEventDispatcher();

    /**
     * @brief Private destructor.
     */
    ~GetanEventDispatcher();

    /**
     * @brief Event handler table.
     */
    std::vector<GetanEventHandler *> m_eventHandlerTable[GETAN_EVENT_MAX];

public:
    /**
     * @brief Get the event dispatcher instance.
     */
    static GetanEventDispatcher *getInstance();

    /**
     * @brief Registers an event handler.
     */
    void RegisterEventHandler( GetanEvent evt, GetanEventHandler *pHandler );

    /**
     * @brief Dispatches an event.
     */
    void Dispatch( GetanEventData *pEvtData );
};

#endif // GETANEVENTDISPATCHER_H

