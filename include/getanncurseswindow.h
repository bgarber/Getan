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

#ifndef GETANNCURSESWINDOW_H
#define GETANNCURSESWINDOW_H

#include <getanwindow.h>
#include <getanbuffer.h>
#include <getanncurseskeyboard.h>

#include <ncurses.h>


/**
 * @class GetanNcursesWindow
 * @brief Implements the NCurses version of the window system.
 */
class GetanNcursesWindow : public GetanWindow
{
private:
    /**
     * @brief This is the ncurses window.
     */
    WINDOW              *m_pWindow;
    GetanBuffer         *m_pBuffer;
    GetanNcursesKeyboard m_pKeyboard;

public:
    /**
     * @brief  Constructor
     */
    GetanNcursesWindow( );

    /**
     * @brief  Destructor
     */
    ~GetanNcursesWindow( );

    /**
     * @function init()
     * @brief    Implements GetanWindow::init()
     */
    void init();

    /**
     * @function exit()
     * @brief    Implements GetanWindow::exit()
     */
    void exit();

    /**
     * @brief  ...
     */
    GetanError setBuffer( GetanBuffer *pBuffer );

    /**
     * @function getKeyboard()
     * @brief    Implements GetanWindow::getKeyboard()
     */
    const GetanKeyboard * getKeyboard( ) const;
};

#endif // GETANNCURSESWINDOW_H

