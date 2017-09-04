/*
 * Copyright 2016 Bryan Garber
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

#ifndef __GETAN_CONTENT_MANAGER__
#define __GETAN_CONTENT_MANAGER__

namespace Getan {
    class ContentManager {
        public:
            ContentManager();
            ~ContentManager();

            void OpenBuffer()

        private:
            static std::list<Buffer> m_bufferList;
    }
}

#endif // __GETAN_CONTENT_MANAGER__

