/**
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

#ifndef GETANWINDOW_H
#define GETANWINDOW_H

/**
 * @class GetanWindow
 * @brief Defines a pure virtual class to abstract a window.
 */
class GetanWindow
{
public:
    /**
     * @function init()
     * @brief    Initializes the window system.
     */
    virtual void init() = 0;

    /**
     * @function exit()
     * @brief    Exits the window system.
     */
    virtual void exit() = 0;
};

#endif // GETANWINDOW_H

