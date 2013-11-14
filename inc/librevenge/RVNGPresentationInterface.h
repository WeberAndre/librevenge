/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGPRESENTATIONINTERFACE_H
#define RVNGPRESENTATIONINTERFACE_H

#include "RVNGPropertyList.h"
#include "RVNGPropertyListVector.h"

namespace librevenge
{

/** Interface for import of presentations.
  */
class RVNGPresentationInterface
{
public:
	virtual ~RVNGPresentationInterface() {}

	// none of the other callback functions will be called before this function is called
	virtual void startDocument(const RVNGPropertyList &propList) = 0;

	// none of the other callback functions will be called after this function is called
	virtual void endDocument() = 0;

	/**
	Called when all document metadata should be set. This is always the first callback made.
	\param propList Property list for the metadata. May contain:
	\li \c dc:creator
	\li \c dc:language The document's keywords
	\li \c dc:publisher The document's publisher
	\li \c dc:source
	\li \c dc:subject The document's subject
	\li \c dc:type The document's type
	\li \c dcterms:available Date when the document was completed
	\li \c dcterms:issued: Date of the version of the document
	\li \c librevenge:abstract Abstract of the document's contents
	\li \c librevenge:account Account
	\li \c librevenge:address Address
	\li \c librevenge:attachments
	\li \c librevenge:authorization
	\li \c librevenge:bill-to
	\li \c librevenge:blind-copy
	\li \c librevenge:carbon-copy
	\li \c librevenge:checked-by
	\li \c librevenge:client
	\li \c librevenge:comments
	\li \c librevenge:department
	\li \c librevenge:descriptive-name The descriptive name for the document
	\li \c librevenge:descriptive-type The descriptive type for the document
	\li \c librevenge:destination
	\li \c librevenge:disposition
	\li \c librevenge:division
	\li \c librevenge:document-number
	\li \c librevenge:editor
	\li \c librevenge:forward-to
	\li \c librevenge:group
	\li \c librevenge:mail-stop
	\li \c librevenge:matter
	\li \c librevenge:office
	\li \c librevenge:owner
	\li \c librevenge:project
	\li \c librevenge:purpose
	\li \c librevenge:received-from
	\li \c librevenge:recorded-by
	\li \c librevenge:recorded-date Date when the document was recorded
	\li \c librevenge:reference
	\li \c librevenge:revision-notes
	\li \c librevenge:revision-number
	\li \c librevenge:section
	\li \c librevenge:security
	\li \c librevenge:status
	\li \c librevenge:telephone-number
	\li \c librevenge:version-notes
	\li \c librevenge:version-number
	\li \c meta:creation-date Document creation date
	\li \c meta:initial-creator The document's author
	\li \c meta:keyword The document's keywords
	\li \c
	*/
	virtual void setDocumentMetaData(const RVNGPropertyList &propList) = 0;

	virtual void startSlide(const RVNGPropertyList &propList) = 0;

	virtual void endSlide() = 0;

	virtual void setStyle(const RVNGPropertyList &propList, const RVNGPropertyListVector &gradient) = 0;

	virtual void startLayer(const RVNGPropertyList &propList) = 0;

	virtual void endLayer() = 0;

	virtual void startEmbeddedGraphics(const RVNGPropertyList &propList) = 0;

	virtual void endEmbeddedGraphics() = 0;

	virtual void startGroup(const RVNGPropertyList &propList) = 0;

	virtual void endGroup() = 0;

	// Different primitive shapes
	virtual void drawRectangle(const RVNGPropertyList &propList) = 0;

	virtual void drawEllipse(const RVNGPropertyList &propList) = 0;

	virtual void drawPolygon(const RVNGPropertyListVector &vertices) = 0;

	virtual void drawPolyline(const RVNGPropertyListVector &vertices) = 0;

	virtual void drawPath(const RVNGPropertyListVector &path) = 0;

	// Embedded binary/raster data
	virtual void drawGraphicObject(const RVNGPropertyList &propList) = 0;

	/** Draw a connector between two objects.
	  */
	virtual void drawConnector(const RVNGPropertyList &propList, const RVNGPropertyListVector &path) = 0;

	/** Start a text object.
	  */
	virtual void startTextObject(const RVNGPropertyList &propList, const RVNGPropertyListVector &path) = 0;

	/** End a text object.
	  */
	virtual void endTextObject() = 0;

	/**
	Called when a TAB character should be inserted
	*/
	virtual void insertTab() = 0;

	/**
	Called when an explicit space should be inserted
	*/
	virtual void insertSpace() = 0;

	/**
	Called when a string of text should be inserted
	\param text A textbuffer encoded as a UTF8 string
	*/
	virtual void insertText(const RVNGString &text) = 0;

	/**
	Called when a line break should be inserted
	*/
	virtual void insertLineBreak() = 0;

	/**
	Called when a field should be inserted. Field types may include:
	\li \c text:page-number Current page number
	\li \c text:page-count Total # of pages in document
	\param propList Defines a set of properties for the field. May contain:
	\li \c style:num-format Type of page number (for page number)
	*/
	virtual void insertField(const RVNGString &type, const RVNGPropertyList &propList) = 0;

	/**
	Called when a new ordered list level should be opened
	\param propList Defines a set of properties for the list. May contain:
	\li \c librevenge:level The level of the list in the hierarchy
	\li \c style:num-format Type of list
	\li \c style:num-prefix Text that comes before the number in the list
	\li \c style:num-suffix Text that comes after the number in the list
	\li \c text:start-value The starting number of the list
	\li \c text:min-label-width The distance between the list label and the actual text, stored in inches
	\li \c text:space-before The indentation level of the lists, stored in inches
	*/
	virtual void openOrderedListLevel(const RVNGPropertyList &propList) = 0;

	/**
	Called when a new unordered list level should be opened
	\param propList Defines a set of properties for the list level. May contain:
	\li \c librevenge:level The level of the list in the hierarchy
	\li \c text:bullet-char The string that should be used as a bullet
	\li \c text:min-label-width The distance between the bullet and the actual text, stored in inches
	\li \c text:space-before The indentation level of the lists, stored in inches
	*/
	virtual void openUnorderedListLevel(const RVNGPropertyList &propList) = 0;

	/**
	Called when an unordered list level should be closed
	*/
	virtual void closeOrderedListLevel() = 0;

	/**
	Called when an ununordered list level should be closed
	*/
	virtual void closeUnorderedListLevel() = 0;

	/**
	Called when a list element should be opened
	\param propList Property list for the paragraph. May contain:
	\li \c fo:text-align The justification of this paragraph (left, center, end, full, or justify)
	\li \c fo:margin-left The left indentation of this paragraph, in inches
	\li \c fo:margin-right The right indentation of this paragraph, in inches
	\li \c fo:margin-top The amount of extra spacing to be placed before the paragraph, in inches
	\li \c fo:margin-bottom The amount of extra spacing to be placed after the paragraph, in inches
	\li \c fo:text-indent The indentation of first line, in inches (difference relative to margin-left)
	\li \c fo:line-height The amount of spacing between lines, in number of lines (1.0 is single spacing)
	\li \c fo:break-before Whether this paragraph should be placed in a new column or page (the value is set to column or page if so)
	\param tabStops List of tabstop definitions for the paragraph. If the list is empty, default tabstop definition should be used. Each tab stop may contain:
	\li \c style:type Type of tab (left, right, center, or char)
	\li \c style:char Alingnment character for char aligned tabs
	\li \c style:leader-text The leader character
	\li \c style:position Position of the tab
	*/
	virtual void openListElement(const RVNGPropertyList &propList, const RVNGPropertyListVector &tabStops) = 0;

	/**
	Called when a list element should be closed
	*/
	virtual void closeListElement() = 0;

	/**
	Called when a new paragraph is opened. This (or openListElement) will always be called before any text or span is placed into the document.
	\param propList Property list for the paragraph. May contain:
	\li \c fo:text-align The justification of this paragraph (left, center, end, full, or justify)
	\li \c fo:margin-left The left indentation of this paragraph, in inches
	\li \c fo:margin-right The right indentation of this paragraph, in inches
	\li \c fo:margin-top The amount of extra spacing to be placed before the paragraph, in inches
	\li \c fo:margin-bottom The amount of extra spacing to be placed after the paragraph, in inches
	\li \c fo:text-indent The indentation of first line, in inches (difference relative to margin-left)
	\li \c fo:line-height The amount of spacing between lines, in number of lines (1.0 is single spacing)
	\li \c fo:break-before Whether this paragraph should be placed in a new column or page (the value is set to column or page if so)
	\param tabStops List of tabstop definitions for the paragraph. If the list is empty, default tabstop definition should be used. Each tab stop may contain:
	\li \c style:type Type of tab (left, right, center, or char)
	\li \c style:char Alingnment character for char aligned tabs
	\li \c style:leader-text The leader character
	\li \c style:position Position of the tab
	*/
	virtual void openParagraph(const RVNGPropertyList &propList, const RVNGPropertyListVector &tabStops) = 0;

	/**
	Called when a paragraph is closed.
	*/
	virtual void closeParagraph() = 0;

	/**
	Called when a text span is opened
	\param propList Property list for the span. May contain:
	\li \c fo:font-style Font style (italic or normal)
	\li \c fo:font-weight Font style (bold or normal)
	\li \c style:text-line-through-type (double or single, if present)
	\li \c style:text-underline-type (double or single, if present)
	\li \c style:text-outline (true or false)
	\li \c fo:font-variant (small-caps, if present)
	\li \c style:font-name The name of the font used in the span, a text string in ascii
	\li \c fo:font-size The size of the font used in the span, in points (72 points per inch)
	\li \c fo:color The color of the font used in the span (encoded in hex: \#RRGGBB)
	\li \c fo:background-color The background color of the text in the span (encoded in hex: \#RRGGBB)
	\li \c style:text-blinking Whether the text should blink (true or false)
	\li \c fo:text-shadow
	*/
	virtual void openSpan(const RVNGPropertyList &propList) = 0;

	/**
	Called when a text span is closed
	*/
	virtual void closeSpan() = 0;

	/**
	Called when a table should be opened
	\param propList Defines a set of properties for the table. May contain:
	\li \c table:align The alignment (left, right, center, or margins)
	\li \c fo:margin-left The left indentation of the table, in inches
	\li \c fo:margin-right The right indentation of the table, in inches
	\li \c style:width Total width of the table, in inches
	\li \c fo:break-before Whether this table should be placed in a new column or page (the value is set to column or page if so)
	\param columns Column definitions for the table. May contain
	\li \c style:column-width Width of a column, in inches
	*/
	virtual void openTable(const RVNGPropertyList &propList, const RVNGPropertyListVector &columns) = 0;
	/**
	Called when a new table row is opened
	\param propList Defines a set of properties for the table row. May contain:
	\li \c style:row-height The row's height, in inches
	\li \c style:min-row-height The row's minimum height, in inches
	\li \c librevenge:is-header-row This row contains headings of columns and should repeat at every page (for tables that span several pages)
	*/
	virtual void openTableRow(const RVNGPropertyList &propList) = 0;
	/**
	Called when the current table row is closed
	*/
	virtual void closeTableRow() = 0;
	/**
	Called when a new table cell is opened
	\param propList Property list for the table cell. May contain:
	\li \c librevenge:column Number of the column in which the cell is positioned
	\li \c librevenge:row Number of the row in which the cell is positioned
	\li \c table:number-columns-spanned Number of columns that the cell spans
	\li \c table:number-rows-spanned Number of rows that the cell spans
	\li \c fo:border-left Properties of the left border of the cell
	\li \c fo:border-right Properties of the right border of the cell
	\li \c fo:border-top Properties of the top border of the cell
	\li \c fo:border-bottom Properties of the bottom border of the cell
	\li \c fo:background-color Color of the cell (encoded in hex: \#RRGGBB)
	\li \c style:vertical-align Vertical alignment of the content in the cell (top, middle, or bottom)
	*/
	virtual void openTableCell(const RVNGPropertyList &propList) = 0;
	/**
	Called when the current table cell is closed
	*/
	virtual void closeTableCell() = 0;
	/**
	Called when a covered (spanned by another cell in the table) table cell is opened
	\param propList Property list for the table cell. May contain:
	\li \c librevenge:column Number of the column in which the cell is positioned
	\li \c librevenge:row Number of the row in which the cell is positioned
	*/
	virtual void insertCoveredTableCell(const RVNGPropertyList &propList) = 0;
	/**
	Called when the current table is closed
	*/
	virtual void closeTable() = 0;

	/** Start a comment.
	  */
	virtual void startComment(const RVNGPropertyList &propList) = 0;

	/** End a comment.
	  */
	virtual void endComment() = 0;

	/** Start slide notes.
	  */
	virtual void startNotes(const RVNGPropertyList &propList) = 0;

	/** End slide notes.
	  */
	virtual void endNotes() = 0;
};

}

#endif // RVNGPRESENTATIONINTERFACE_H

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
