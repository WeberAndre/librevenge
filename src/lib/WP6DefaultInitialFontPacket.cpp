/* libwpd2
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#include "WP6LLListener.h"
#include "WP6DefaultInitialFontPacket.h"
#include "libwpd_internal.h"

WP6DefaultInitialFontPacket::WP6DefaultInitialFontPacket(GsfInput *input, int id, guint32 dataOffset, guint32 dataSize)
	: WP6PrefixDataPacket(input)
{
	_read(input, dataOffset, dataSize);
}

void WP6DefaultInitialFontPacket::parse(WP6LLListener *llListener)
{
	llListener->fontChange(getPointSize(), getInitialFontDescriptorPID());
}

void WP6DefaultInitialFontPacket::_readContents(GsfInput *input)
{
   m_numPrefixIDs = *(const guint16 *)gsf_input_read(input, sizeof(guint16), NULL);
   m_initialFontDescriptorPID = *(const guint16 *)gsf_input_read(input, sizeof(guint16), NULL);
   m_pointSize = *(const guint16 *)gsf_input_read( input, sizeof(guint16), NULL);
   WPD_DEBUG_MSG(("WordPerfect: Read default initial font packet (initial font descriptor pid: %i, point size: %i)\n", 
		  (int) m_initialFontDescriptorPID, (int) m_pointSize));

}