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

#ifndef GETANAPPLICATION_H
#define GETANAPPLICATION_H

#include <getanwindow.h>

/**
 * @class GetanApplication
 * @brief This is the main class, implements the main loop and behaviors.
 */
class GetanApplication
{
private:
    /**
     * @brief  Pointer to the window system.
     */
    GetanWindow *m_pWindow;

public:
    /**
     * @brief Constructor
     */
    GetanApplication( GetanWindow *pWindow );

    /**
     * @brief Destructor
     */
    ~GetanApplication( );

    /**
     * @function start()
     * @brief    Starts the main loop.
     */
    int start();
};

#endif // GETANAPPLICATION_H

