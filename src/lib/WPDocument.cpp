/* libwpd2
 * Copyright (C) 2003 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2003 Marc Maurer (j.m.maurer@student.utwente.nl)
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

#include <gsf/gsf-input.h>
#include <stdlib.h>
#include <string.h>
#include "WPDocument.h"
#include "WPXParser.h"
#include "WP42Parser.h"
#include "WP42Heuristics.h"
#include "WP5Parser.h"
#include "WP6Parser.h"
#include "libwpd_internal.h"

WPDConfidence WPDocument::isFileFormatSupported(GsfInput *input, bool partialContent)
{
	WPXHeader *header = NULL;	
	
	try
	{
		// NOTE: even when passed partial content, we for now just assume that
		// we can extract the header from it. We could also read the major version
		// and the preceding -1 WPC stuff manually.
		header = new WPXHeader(input);
		int majorVersion = header->getMajorVersion();
		DELETEP(header);
		
		switch (majorVersion)
		{
			case 0x00: // WP5 
				return WPD_CONFIDENCE_POOR;
				break;
			case 0x01: // ???
				return WPD_CONFIDENCE_NONE;
				break;
			case 0x02: // WP6
				return WPD_CONFIDENCE_EXCELLENT;
				break;
			default:
				// unhandled file format
				return WPD_CONFIDENCE_NONE;
				break;
		}
	}	
	catch (NoFileHeaderException)
	{
		return WP42Heuristics::isWP42FileFormat(input, partialContent);
	}
		
	return WPD_CONFIDENCE_NONE;
}

void WPDocument::parse(GsfInput *input, WPXHLListenerImpl *listenerImpl)
{
	WPXParser *parser = NULL;
	WPXHeader *header = NULL;
	
	try
	{
		header = new WPXHeader(input);
		
		switch (header->getMajorVersion())
		{
			case 0x00: // WP5 
				WPD_DEBUG_MSG(("WordPerfect: Using the WP5 parser.\n"));
				parser = new WP5Parser(input, header);
				parser->parse(listenerImpl);
				DELETEP(parser);
				break;
			case 0x01: // ???
				WPD_DEBUG_MSG(("WordPerfect: Unsupported file format.\n"));
				// NOTE: WHEN WE KNOW WHICH PARSER TO INSTANIATE, UPDATE ::isFileFormatSupported AS WELL!
				break;
			case 0x02: // WP6
				WPD_DEBUG_MSG(("WordPerfect: Using the WP6 parser.\n"));
				parser = new WP6Parser(input, header);
				parser->parse(listenerImpl);
				DELETEP(parser);
				break;
			default:
				// unhandled file format
				WPD_DEBUG_MSG(("WordPerfect: Unsupported file format.\n"));
				break;
		}

		DELETEP(header);	
	}
	catch (NoFileHeaderException)
	{
		// WP file formats prior to version 5.x do not contain a generic 
		// header which can be used to determine which parser to instanciate. 
		// Use heuristics to determine with some certainty if we are dealing with
		// a file in the WP4.2 format.		
		int confidence = WP42Heuristics::isWP42FileFormat(input, false /* FIXME: allow for partial content */);

		if (confidence == WPD_CONFIDENCE_GOOD || confidence == WPD_CONFIDENCE_EXCELLENT)
		{
			WPD_DEBUG_MSG(("WordPerfect: Mostly likely the file format is WP4.2.\n\n"));
			WPD_DEBUG_MSG(("WordPerfect: Using the WP4.2 parser.\n\n"));
			WP42Parser *parser = new WP42Parser(input);
			parser->parse(listenerImpl);
			DELETEP(parser);
		}
	}
	catch (FileException)
	{
		DELETEP(parser);
		DELETEP(header);
		throw FileException(); 
	}
}

void WPDocument::parse(GsfInput *input, WPXHLListenerImpl *listenerImpl, WPXFileType fileType)
{
	WPXParser *parser = NULL;
	WPXHeader *header = NULL;
	
	try
	{
		switch (fileType)
		{
			case WP42_DOCUMENT:
				WPD_DEBUG_MSG(("WordPerfect: Using the WP42 parser.\n"));
				parser = new WP42Parser(input);
				parser->parse(listenerImpl);
				DELETEP(parser);
				break;
			case WP5_DOCUMENT:
				WPD_DEBUG_MSG(("WordPerfect: Using the WP5 parser.\n"));
				header = new WPXHeader(input);
				parser = new WP5Parser(input, header);
				parser->parse(listenerImpl);
				DELETEP(parser);
				DELETEP(header);
				break;
			case WP6_DOCUMENT:
				WPD_DEBUG_MSG(("WordPerfect: Using the WP6 parser.\n"));
				header = new WPXHeader(input);
				parser = new WP6Parser(input, header);
				parser->parse(listenerImpl);
				DELETEP(parser);			
				DELETEP(header);
				break;
			default:
				// unhandled file format
				WPD_DEBUG_MSG(("WordPerfect: Unsupported file format.\n"));
				break;
		}
	}
	catch (NoFileHeaderException)
	{
		// should not happen
		DELETEP(parser);
		DELETEP(header);		
		throw NoFileHeaderException();
	}
	catch (FileException)
	{
		DELETEP(parser);
		DELETEP(header);
		throw FileException(); 
	}
}

/*void WPDocument::parse(GsfInput *input, WPXLLListener *llistener)
{
	// TODO: implement me
}*/
