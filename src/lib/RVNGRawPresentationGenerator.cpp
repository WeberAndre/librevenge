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

#include <stdio.h>

#include <librevenge-generators/librevenge-generators.h>

#include "RVNGRawGeneratorBase.h"

namespace librevenge
{

namespace
{

enum Callback
{
    CALLBACK_START_DOCUMENT = 0,
    CALLBACK_START_SLIDE,
    CALLBACK_START_LAYER,
    CALLBACK_START_EMBEDDED_GRAPHICS,
    CALLBACK_START_GROUP,
    CALLBACK_START_TEXT_OBJECT,
    CALLBACK_OPEN_PARAGRAPH,
    CALLBACK_OPEN_SPAN,
    CALLBACK_OPEN_ORDERED_LIST_LEVEL,
    CALLBACK_OPEN_UNORDERED_LIST_LEVEL,
    CALLBACK_OPEN_LIST_ELEMENT,
    CALLBACK_OPEN_TABLE,
    CALLBACK_OPEN_TABLE_ROW,
    CALLBACK_OPEN_TABLE_CELL,
    CALLBACK_START_COMMENT,
    CALLBACK_START_NOTES
};

}

struct RVNGRawPresentationGeneratorImpl : RVNGRawGeneratorBase
{
	explicit RVNGRawPresentationGeneratorImpl(bool printCallgraphScore);
};

RVNGRawPresentationGeneratorImpl::RVNGRawPresentationGeneratorImpl(bool printCallgraphScore)
	: RVNGRawGeneratorBase(printCallgraphScore)
{
}

RVNGRawPresentationGenerator::RVNGRawPresentationGenerator(const bool printCallgraphScore)
	: m_impl(new RVNGRawPresentationGeneratorImpl(printCallgraphScore))
{
}

RVNGRawPresentationGenerator::~RVNGRawPresentationGenerator()
{
	delete m_impl;
}

void RVNGRawPresentationGenerator::startDocument(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startDocument(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_START_DOCUMENT);
}

void RVNGRawPresentationGenerator::endDocument()
{
	RVNG_CALLGRAPH_LEAVE(("endDocument\n"), CALLBACK_START_DOCUMENT);
}

void RVNGRawPresentationGenerator::setDocumentMetaData(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::setDocumentMetaData(%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::startSlide(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startSlide(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_START_SLIDE);
}

void RVNGRawPresentationGenerator::endSlide()
{
	RVNG_CALLGRAPH_LEAVE(("endSlide\n"), CALLBACK_START_SLIDE);
}

void RVNGRawPresentationGenerator::startLayer(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startLayer (%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_START_LAYER);
}

void RVNGRawPresentationGenerator::endLayer()
{
	RVNG_CALLGRAPH_LEAVE(("endLayer\n"), CALLBACK_START_LAYER);
}

void RVNGRawPresentationGenerator::startEmbeddedGraphics(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startEmbeddedGraphics (%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_START_EMBEDDED_GRAPHICS);
}

void RVNGRawPresentationGenerator::endEmbeddedGraphics()
{
	RVNG_CALLGRAPH_LEAVE(("endEmbeddedGraphics \n"), CALLBACK_START_EMBEDDED_GRAPHICS);
}

void RVNGRawPresentationGenerator::startGroup(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startGroup(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_START_GROUP);
}

void RVNGRawPresentationGenerator::endGroup()
{
	RVNG_CALLGRAPH_LEAVE(("endGroup\n"), CALLBACK_START_GROUP);
}

void RVNGRawPresentationGenerator::setStyle(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::setStyle(%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::drawRectangle(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::drawRectangle (%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::drawEllipse(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::drawEllipse (%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::drawPolyline(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::drawPolyline (%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::drawPolygon(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::drawPolygon (%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::drawPath(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::drawPath (%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::drawGraphicObject(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::drawGraphicObject (%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::drawConnector(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::drawConnector(%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::startTextObject(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startTextObject (%s)\n", propList.getPropString().cstr()), CALLBACK_START_TEXT_OBJECT);
}

void RVNGRawPresentationGenerator::endTextObject()
{
	RVNG_CALLGRAPH_LEAVE(("endTextObject\n"), CALLBACK_START_TEXT_OBJECT);
}

void RVNGRawPresentationGenerator::openParagraph(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openParagraph (%s)\n", propList.getPropString().cstr()), CALLBACK_OPEN_PARAGRAPH);
}

void RVNGRawPresentationGenerator::closeParagraph()
{
	RVNG_CALLGRAPH_LEAVE(("closeParagraph\n"), CALLBACK_OPEN_PARAGRAPH);
}

void RVNGRawPresentationGenerator::openSpan(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openSpan (%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_OPEN_SPAN);
}

void RVNGRawPresentationGenerator::closeSpan()
{
	RVNG_CALLGRAPH_LEAVE(("closeSpan\n"), CALLBACK_OPEN_SPAN);
}

void RVNGRawPresentationGenerator::insertText(const RVNGString &str)
{
	printf("RVNGRawPresentationGenerator::insertText (%s)\n", str.cstr());
}

void RVNGRawPresentationGenerator::insertTab()
{
	printf("RVNGRawPresentationGenerator::insertTab\n");
}

void RVNGRawPresentationGenerator::insertSpace()
{
	printf("RVNGRawPresentationGenerator::insertSpace\n");
}

void RVNGRawPresentationGenerator::insertLineBreak()
{
	printf("RVNGRawPresentationGenerator::insertLineBreak\n");
}

void RVNGRawPresentationGenerator::insertField(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::insertField(%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::openOrderedListLevel(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openOrderedListLevel(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_OPEN_ORDERED_LIST_LEVEL);
}

void RVNGRawPresentationGenerator::openUnorderedListLevel(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openUnorderedListLevel(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_OPEN_UNORDERED_LIST_LEVEL);
}

void RVNGRawPresentationGenerator::closeOrderedListLevel()
{
	RVNG_CALLGRAPH_LEAVE(("closeOrderedListLevel\n"),
	                     CALLBACK_OPEN_ORDERED_LIST_LEVEL);
}

void RVNGRawPresentationGenerator::closeUnorderedListLevel()
{
	RVNG_CALLGRAPH_LEAVE(("closeUnorderedListLevel\n"),
	                     CALLBACK_OPEN_UNORDERED_LIST_LEVEL);
}

void RVNGRawPresentationGenerator::openListElement(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openListElement(%s)\n", propList.getPropString().cstr()), CALLBACK_OPEN_LIST_ELEMENT);
}

void RVNGRawPresentationGenerator::closeListElement()
{
	RVNG_CALLGRAPH_LEAVE(("closeListElement\n"), CALLBACK_OPEN_LIST_ELEMENT);
}

void RVNGRawPresentationGenerator::openTable(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openTable(%s)\n", propList.getPropString().cstr()), CALLBACK_OPEN_TABLE);
}

void RVNGRawPresentationGenerator::openTableRow(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openTableRow(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_OPEN_TABLE_ROW);
}

void RVNGRawPresentationGenerator::closeTableRow()
{
	RVNG_CALLGRAPH_LEAVE(("closeTableRow\n"), CALLBACK_OPEN_TABLE_ROW);
}

void RVNGRawPresentationGenerator::openTableCell(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("openTableCell(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_OPEN_TABLE_CELL);
}

void RVNGRawPresentationGenerator::closeTableCell()
{
	RVNG_CALLGRAPH_LEAVE(("closeTableCell\n"), CALLBACK_OPEN_TABLE_CELL);
}

void RVNGRawPresentationGenerator::insertCoveredTableCell(const RVNGPropertyList &propList)
{
	printf("RVNGRawPresentationGenerator::insertCoveredTableCell(%s)\n", propList.getPropString().cstr());
}

void RVNGRawPresentationGenerator::closeTable()
{
	RVNG_CALLGRAPH_LEAVE(("closeTable\n"), CALLBACK_OPEN_TABLE);
}

void RVNGRawPresentationGenerator::startComment(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startComment(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_START_COMMENT);
}

void RVNGRawPresentationGenerator::endComment()
{
	RVNG_CALLGRAPH_LEAVE(("endComment\n"), CALLBACK_START_COMMENT);
}

void RVNGRawPresentationGenerator::startNotes(const RVNGPropertyList &propList)
{
	RVNG_CALLGRAPH_ENTER(("startNotes(%s)\n", propList.getPropString().cstr()),
	                     CALLBACK_START_NOTES);
}

void RVNGRawPresentationGenerator::endNotes()
{
	RVNG_CALLGRAPH_LEAVE(("endNotes\n"), CALLBACK_START_NOTES);
}

}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
