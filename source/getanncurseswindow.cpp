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

#include <getanncurseswindow.h>


GetanNcursesWindow::GetanNcursesWindow( )
    : m_pWindow   ( nullptr )
    , m_pKeyboard ( )
{
}

GetanNcursesWindow::~GetanNcursesWindow( )
{
}

void
GetanNcursesWindow::init( )
{
    // Start up ncurses.
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    m_pWindow = newwin(LINES, COLS, 0, 0);
    //box(m_pWindow, 0, 0);
    wrefresh(m_pWindow);
}

void
GetanNcursesWindow::exit( )
{
    // Clean up ncurses.
    wborder(m_pWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(m_pWindow);
    delwin(m_pWindow);
    endwin();
}

GetanError
GetanNcursesWindow::setBuffer( GetanBuffer *pBuffer )
{
    m_pBuffer = pBuffer;
    return GETAN_SUCCESS;
}

const GetanKeyboard *
GetanNcursesWindow::getKeyboard( ) const
{
    return &m_pKeyboard;
}

