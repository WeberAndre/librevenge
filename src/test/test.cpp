/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2006 Andrew Ziem
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>

#include "librevenge_internal.h"
#include "RVNGMemoryStream.h"


#define TMP_FILENAME "librevenge-unittest.tmp"

class Test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Test);
	CPPUNIT_TEST(testStream);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testStream(void);

};

void Test::setUp(void)
{
	FILE *f = fopen(TMP_FILENAME, "w");
	fprintf(f, "%c%c%c%c",1,2,3,4);
	fprintf(f, "%c%c%c%c",0,5,6,7);
	fclose(f);
}

void Test::tearDown(void)
{
	unlink(TMP_FILENAME);
}

void Test::testStream(void)
{
	unsigned long numBytesRead;

	/**********************
	 * Test RVNGFileStream *
	 **********************/
	RVNGInputStream *input = new RVNGFileStream(TMP_FILENAME);

	CPPUNIT_ASSERT_EQUAL ( false, input->isStructured() );
	CPPUNIT_ASSERT_EQUAL ( (RVNGInputStream *) NULL, input->getSubStreamByName("foo") );

	// test read()
	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT ( NULL == input->read(0, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (unsigned long)0, numBytesRead );
	CPPUNIT_ASSERT_EQUAL ( (long) 0 , input->tell() );
	CPPUNIT_ASSERT ( NULL != input->read(1, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (long) 1 , input->tell() );

	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT ( NULL != input->read(50, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (long) 8 , input->tell() );

	// test seek(), tell(), isEnd()
	input->seek(1, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 1 , input->tell() );

	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 0 , input->tell() );

	input->seek(8, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 8 , input->tell() );

	input->seek(-1, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 0, input->tell() );

	input->seek(8, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( true, input->isEnd() );

	input->seek(10000, RVNG_SEEK_SET);
	CPPUNIT_ASSERT( 10000 != input->tell() );
	CPPUNIT_ASSERT( input->isEnd() );

	delete input;

	/************************
	 * Test RVNGStringStream *
	 ************************/
	input = new RVNGStringStream((const unsigned char *)"\1\2\3\4\0\5\6\7", 8);

	CPPUNIT_ASSERT_EQUAL ( false, input->isStructured() );
	CPPUNIT_ASSERT_EQUAL ( (RVNGInputStream *) NULL, input->getSubStreamByName("foo") );

	// test read()
	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT ( NULL == input->read(0, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (unsigned long) 0, numBytesRead );
	CPPUNIT_ASSERT_EQUAL ( (long) 0 , input->tell() );
	CPPUNIT_ASSERT ( NULL != input->read(1, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (long) 1 , input->tell() );

	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT ( NULL != input->read(50, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (long) 8 , input->tell() );

	// test seek(), tell(), isEnd()
	input->seek(1, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 1 , input->tell() );

	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 0 , input->tell() );

	input->seek(8, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 8 , input->tell() );

	input->seek(-1, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 0, input->tell() );

	input->seek(8, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( true, input->isEnd() );

	input->seek(10000, RVNG_SEEK_SET);
	CPPUNIT_ASSERT( 10000 != input->tell() );
	CPPUNIT_ASSERT( input->isEnd() );

	delete input;


	/************************
	 * Test RVNGMemoryInputStream *
	 ************************/
	input = new RVNGMemoryInputStream((unsigned char *)("\1\2\3\4\0\5\6\7"), 8);

	CPPUNIT_ASSERT_EQUAL ( false, input->isStructured() );
	CPPUNIT_ASSERT_EQUAL ( (RVNGInputStream *) NULL, input->getSubStreamByName("foo") );

	// test read()
	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT ( NULL == input->read(0, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (unsigned long) 0, numBytesRead );
	CPPUNIT_ASSERT_EQUAL ( (long) 0 , input->tell() );
	CPPUNIT_ASSERT ( NULL != input->read(1, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (long) 1 , input->tell() );

	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT ( NULL != input->read(50, numBytesRead)  );
	CPPUNIT_ASSERT_EQUAL ( (long) 8 , input->tell() );

	// test seek(), tell(), isEnd()
	input->seek(1, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 1 , input->tell() );

	input->seek(0, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 0 , input->tell() );

	input->seek(8, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 8 , input->tell() );

	input->seek(-1, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( (long) 0, input->tell() );

	input->seek(8, RVNG_SEEK_SET);
	CPPUNIT_ASSERT_EQUAL ( true, input->isEnd() );

	input->seek(10000, RVNG_SEEK_SET);
	CPPUNIT_ASSERT( 10000 != input->tell() );
	CPPUNIT_ASSERT( input->isEnd() );

	delete input;


}

CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main()
{
	// Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;

	// Add a listener that colllects test result
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );

	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener( &progress );

	// Add the top suite to the test runner
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	// output
	CPPUNIT_NS::CompilerOutputter outputter( &result, std::cerr );
	outputter.write();

	// return status code
	return result.wasSuccessful() ? 0 : 1;
}
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
