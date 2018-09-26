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

#include <vector>

/**
 * @class GetanEventDispatcher
 * @brief Simple event dispatcher system for Getan. This class is a Singleton.
 */
class GetanEventDispatcher {
    /**
     * @enum  GetanEventDispatcher::Event
     * @brief Defines event values for the dispatchers.
     */
    enum Event {
        EVENT_CLOSE_APP,
        EVENT_OPEN_FILE,
        EVENT_MAX_VALUE,
    };

    /**
     * @struct GetanEventDispatcher::EventData
     * @brief  Defines a minimal event structure.
     */
    struct EventData {
       Event m_eventId;
    };

    /**
     * @brief Defines the event handler function pointer.
     */
    typedef void (*EventHandlerPtr)(Event, EventData *);

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
    std::vector<EventHandlerPtr> m_eventHandlerTable[EVENT_MAX_VALUE];

public:
    /**
     * @brief Returns an instance of the event dispatcher.
     */
    static GetanEventDispatcher *getInstance();

    /**
     * @brief Registers an event handler.
     */
    void RegisterEventHandler( Event evt, EventHandlerPtr pHandler);

    /**
     * @brief Dispatches an event.
     */
    void Dispatch( Event evt, EventData *pEvtData );
};

#endif // GETANEVENTDISPATCHER_H

