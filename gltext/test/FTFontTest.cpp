#include "FTFontTest.h"
#include <string>
using namespace gltext;

CPPUNIT_TEST_SUITE_REGISTRATION( FTFontTest );

void
FTFontTest::testConstructor()
{
   try
   {
      const char* fontName = "arial.ttf";
      FTFont f1(fontName, 12);
      CPPUNIT_ASSERT(std::string(f1.getName()) == fontName);
      CPPUNIT_ASSERT(f1.getSize() == 12);
   }
   catch (std::runtime_error& error)
   {
      // we should not have thrown an exception!
      CPPUNIT_FAIL(error.what());
   }
}

void
FTFontTest::testConstructorThrows()
{
   // should throw an exception
   FTFont f1("notvalid.ttf", 12);
}
