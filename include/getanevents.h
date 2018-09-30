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

#ifndef GETANEVENTS_H
#define GETANEVENTS_H

#include <string>

/**
 * @enum  GetanEventDispatcher::Event
 * @brief Defines event values for the dispatchers.
 */
enum GetanEvent {
    GETAN_EVENT_CLOSE_APP,
    GETAN_EVENT_OPEN_FILE,
    GETAN_EVENT_MAX
};

/**
 * @struct GetanEventData
 * @brief  Defines a minimal event structure.
 */
struct GetanEventData {
    GetanEvent m_eventId;

    GetanEventData( GetanEvent eventId ) : m_eventId(eventId)
    {
        // empty
    };

    virtual ~GetanEventData()
    {
        // empty
    }
};

/**
 * @struct GetanOpenFileEventData
 * @brief  Defines the expected structure for an open file event.
 */
struct GetanOpenFileEventData : public GetanEventData {
    std::string m_filename;

    GetanOpenFileEventData( const std::string& filename ) :
        GetanEventData( GETAN_EVENT_OPEN_FILE ),
        m_filename    ( filename )
    {
        // empty
    };

    ~GetanOpenFileEventData()
    {
        // empty
    }
};



#endif //  GETANEVENTS_H

