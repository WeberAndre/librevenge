/* libwpd
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2002-2004 Marc Maurer (j.m.maurer@student.utwente.nl)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
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

#ifndef RAWLISTENERIMPL_H
#define RAWLISTENERIMPL_H

#include <stack>
#include <glib.h>
#include "WPXHLListenerImpl.h"

using namespace std;

enum ListenerCallback {
	LC_START_DOCUMENT = 0,
	LC_OPEN_PAGE_SPAN,
	LC_OPEN_HEADER_FOOTER,
	LC_OPEN_PARAGRAPH,
	LC_OPEN_SPAN,
	LC_OPEN_SECTION,
	LC_OPEN_ORDERED_LIST_LEVEL,
	LC_OPEN_UNORDERED_LIST_LEVEL,
	LC_OPEN_LIST_ELEMENT,
	LC_OPEN_FOOTNOTE,
	LC_OPEN_ENDNOTE,
	LC_OPEN_TABLE,
	LC_OPEN_TABLE_ROW,
	LC_OPEN_TABLE_CELL
};

class RawListenerImpl : public WPXHLListenerImpl
{
public:
	RawListenerImpl(bool printCallgraphScore);
	~RawListenerImpl();

 	virtual void setDocumentMetaData(const UCSString &author, const UCSString &subject,
					 const UCSString &publisher, const UCSString &category,
					 const UCSString &keywords, const UCSString &language,
					 const UCSString &abstract, const UCSString &descriptiveName,
					 const UCSString &descriptiveType);

	virtual void startDocument();
	virtual void endDocument();

	virtual void openPageSpan(const int span, const bool isLastPageSpan,
				  const float formLength, const float formWidth, const WPXFormOrientation orientation,
				  const float marginLeft, const float marginRight,
				  const float marginTop, const float marginBottom);
	virtual void closePageSpan();
	virtual void openHeaderFooter(const WPXHeaderFooterType headerFooterType, const WPXHeaderFooterOccurence headerFooterOccurence);
	virtual void closeHeaderFooter(const WPXHeaderFooterType headerFooterType, const WPXHeaderFooterOccurence headerFooterOccurence);

	virtual void openParagraph(const uint8_t paragraphJustification, 
				   const float marginLeftOffset, const float marginRightOffset, const float textIndent,
				   const float lineSpacing, const float spacingAfterParagraph, const vector<WPXTabStop> &tabStops,
				   const bool isColumnBreak, const bool isPageBreak);
	virtual void closeParagraph();
	virtual void openSpan(const uint32_t textAttributeBits, const char *fontName, const float fontSize,
				   const RGBSColor *fontColor, const RGBSColor *highlightColor);
	virtual void closeSpan();
	virtual void openSection(const unsigned int numColumns, const float spaceAfter);
	virtual void closeSection();

	virtual void insertTab();
	virtual void insertText(const UCSString &text);
 	virtual void insertLineBreak();

	virtual void defineOrderedListLevel(const int listID, const int listLevel, const WPXNumberingType listType,
					    const UCSString &textBeforeNumber, const UCSString &textAfterNumber,
					    const int startingNumber);
	virtual void defineUnorderedListLevel(const int listID, const int listLevel, const UCSString &bullet);
	virtual void openOrderedListLevel(const int listID);
	virtual void openUnorderedListLevel(const int listID);
	virtual void closeOrderedListLevel();
	virtual void closeUnorderedListLevel();
	virtual void openListElement(const uint8_t paragraphJustification, 
				     const float marginLeftOffset, const float marginRightOffset, const float textIndent,
				     const float lineSpacing, const float spacingAfterParagraph,
				     const vector<WPXTabStop> &tabStops);
	virtual void closeListElement();

	virtual void openFootnote(int number);
	virtual void closeFootnote();
	virtual void openEndnote(int number);
	virtual void closeEndnote();

 	virtual void openTable(const uint8_t tablePositionBits,
			       const float marginLeftOffset, const float marginRightOffset,
			       const float leftOffset, const vector < WPXColumnDefinition > &columns);
 	virtual void openTableRow(const bool isHeaderRow, const bool isFixedHeightRow, const bool hasMinimumHeight, const float height);
	virtual void closeTableRow();
 	virtual void openTableCell(const uint32_t col, const uint32_t row, const uint32_t colSpan, const uint32_t rowSpan,
				   const uint8_t borderBits, const RGBSColor * cellFgColor, const RGBSColor * cellBgColor,
				   const RGBSColor * cellBorderColor,
				   const WPXVerticalAlignment cellVerticalAlignment);
	virtual void closeTableCell();
	virtual void insertCoveredTableCell(const uint32_t col, const uint32_t row);
 	virtual void closeTable();

private:
	int	m_indent;
	int m_callbackMisses;
	bool m_printCallgraphScore;
	stack<ListenerCallback> m_callStack;

	void __indentUp() { m_indent++; }
	void __indentDown() { if (m_indent > 0) m_indent--; }

	void __iprintf(const char *format, ...);
	void __iuprintf(const char *format, ...);
	void __idprintf(const char *format, ...);

};

#endif /* RAWLISTENERIMPL_H */
