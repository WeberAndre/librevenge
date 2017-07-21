/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2002-2004 Marc Maurer (uwog@uwog.net)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGCSVSPREADSHEETGENERATOR_H
#define RVNGCSVSPREADSHEETGENERATOR_H

#include "librevenge-generators-api.h"

#include <librevenge/librevenge.h>
#include <librevenge-stream/librevenge-stream.h>

namespace librevenge
{

struct RVNGCSVSpreadsheetGeneratorImpl;
/** A CSV generator for spreadsheet documents.
  *
  * See \c ::librevenge::RVNGSpreadsheetInterface for documentation of the basic interface.
  */
class REVENGE_GENERATORS_API RVNGCSVSpreadsheetGenerator : public RVNGSpreadsheetInterface
{
	//! unimplemented copy constructor to prevent copy
	RVNGCSVSpreadsheetGenerator(const RVNGCSVSpreadsheetGenerator &other);
	//! unimplemented copy operator to prevent copy
	RVNGCSVSpreadsheetGenerator &operator=(const RVNGCSVSpreadsheetGenerator &other);

public:
	/** constructor given:
		\li \c sheets a vector of string to fill
		\li \c generateFormula a flag to known if we need to generate the formula or not

		\note if generateFormula is true, the formula will be
		generated with english name, so a localized version of Excel,
		... will not recognize them
	*/
	explicit RVNGCSVSpreadsheetGenerator(RVNGStringVector &sheets, bool generateFormula=false);
	//! destructor
	~RVNGCSVSpreadsheetGenerator() override;
	/** set the separators:
		- \c fieldSep the field separator, default: ,
		- \c textSep the text separator, default: "
		- \c decimalSep the decimal separator, default: .
	 */
	void setSeparators(char fieldSep=',', char textSep='"', char decimalSep='.');
	//! defines the format used to export the date and the time (see strftime)
	void setDTFormats(RVNGString const &date="%m/%d/%y", RVNGString const &time="%H:%M:%S");
	void setDocumentMetaData(const RVNGPropertyList &propList) override;
	void defineEmbeddedFont(const RVNGPropertyList &propList) override;

	void startDocument(const RVNGPropertyList &propList) override;
	void endDocument() override;

	// sheet
	void defineSheetNumberingStyle(const RVNGPropertyList &propList) override;
	void openSheet(const RVNGPropertyList &propList) override;
	void closeSheet() override;
	void openSheetRow(const RVNGPropertyList &propList) override;
	void closeSheetRow() override;
	void openSheetCell(const RVNGPropertyList &propList) override;
	void closeSheetCell() override;

	// chart
	void defineChartStyle(const RVNGPropertyList &propList) override;
	void openChart(const RVNGPropertyList &propList) override;
	void closeChart() override;
	void openChartTextObject(const RVNGPropertyList &propList) override;
	void closeChartTextObject() override;
	void openChartPlotArea(const RVNGPropertyList &propList) override;
	void closeChartPlotArea() override;
	void insertChartAxis(const RVNGPropertyList &axis) override;
	void openChartSerie(const librevenge::RVNGPropertyList &series) override;
	void closeChartSerie() override;

	void definePageStyle(const RVNGPropertyList &propList) override;
	void openPageSpan(const RVNGPropertyList &propList) override;
	void closePageSpan() override;
	void openHeader(const RVNGPropertyList &propList) override;
	void closeHeader() override;
	void openFooter(const RVNGPropertyList &propList) override;
	void closeFooter() override;

	void defineParagraphStyle(const RVNGPropertyList &propList) override;
	void openParagraph(const RVNGPropertyList &propList) override;
	void closeParagraph() override;

	void defineCharacterStyle(const RVNGPropertyList &propList) override;
	void openSpan(const RVNGPropertyList &propList) override;
	void closeSpan() override;

	void openLink(const RVNGPropertyList &propList) override;
	void closeLink() override;

	void defineSectionStyle(const RVNGPropertyList &propList) override;
	void openSection(const RVNGPropertyList &propList) override;
	void closeSection() override;

	void insertTab() override;
	void insertSpace() override;
	void insertText(const RVNGString &text) override;
	void insertLineBreak() override;
	void insertField(const RVNGPropertyList &propList) override;

	void openOrderedListLevel(const RVNGPropertyList &propList) override;
	void openUnorderedListLevel(const RVNGPropertyList &propList) override;
	void closeOrderedListLevel() override;
	void closeUnorderedListLevel() override;
	void openListElement(const RVNGPropertyList &propList) override;
	void closeListElement() override;

	void openFootnote(const RVNGPropertyList &propList) override;
	void closeFootnote() override;
	void openEndnote(const RVNGPropertyList &propList);
	void closeEndnote();
	void openComment(const RVNGPropertyList &propList) override;
	void closeComment() override;

	void openTextBox(const RVNGPropertyList &propList) override;
	void closeTextBox() override;

	void openTable(const RVNGPropertyList &propList) override;
	void openTableRow(const RVNGPropertyList &propList) override;
	void closeTableRow() override;
	void openTableCell(const RVNGPropertyList &propList) override;
	void closeTableCell() override;
	void insertCoveredTableCell(const RVNGPropertyList &propList) override;
	void closeTable() override;

	void openFrame(const RVNGPropertyList &propList) override;
	void closeFrame() override;

	void insertBinaryObject(const RVNGPropertyList &propList) override;

	// drawing function
	void openGroup(const RVNGPropertyList &propList) override;
	void closeGroup() override;

	void defineGraphicStyle(const RVNGPropertyList &propList) override;
	void drawRectangle(const RVNGPropertyList &propList) override;
	void drawEllipse(const RVNGPropertyList &propList) override;
	void drawPolygon(const RVNGPropertyList &propList) override;
	void drawPolyline(const RVNGPropertyList &propList) override;
	void drawPath(const RVNGPropertyList &propList) override;
	void drawConnector(const RVNGPropertyList &propList) override;

	void insertEquation(const RVNGPropertyList &propList) override;

private:
	//! the internal storage data
	RVNGCSVSpreadsheetGeneratorImpl *m_impl;
};

}

#endif /* RVNGCSVSPREADSHEETGENERATOR_H */

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
