/* libwpd
 * Copyright (C) 2004 Marc Maurer (j.m.maurer@student.utwente.nl)
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

#ifndef WP3FILESTRUCTURE_H
#define WP3FILESTRUCTURE_H

// size of the fixed length functiongroups 0xC0 to 0xCF
extern int WP3_FIXED_LENGTH_FUNCTION_GROUP_SIZE[16]; 

/* Main function group list  */

#define WP3_INDENT_GROUP 0xC2
#define WP3_ATTRIBUTE_GROUP 0xC3

#define WP3_WINDOW_GROUP 0xDA
#define WP3_STYLE_GROUP 0xDB
#define WP3_END_OF_LINE_PAGE_GROUP 0xDC

#endif /* WP3FILESTRUCTURE_H */