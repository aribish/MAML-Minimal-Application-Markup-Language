#include "errFormatter.h"

void ab::fileNotFoundErr(std::string snippet)
{
  std::cout << "\x1b[38;2;200;50;0mERR\x1b[0m | \x1b[38;2;200;150;25mFile Not Found\x1b[0m | \x1b[38;2;200;50;0mError Source Attempted to be Ignored\x1b[0m | Snippet: " << snippet << '\n';
}
void ab::fileNotSuppliedErr(std::string snippet)
{
  std::cout << "\x1b[38;2;200;50;0mCMD ERR\x1b[0m | \x1b[38;2;200;150;25mFile Not Supplied\x1b[0m | \x1b[38;2;200;50;0mParser Termininated\x1b[0m | Snippet: " << snippet << '\n';
}
void ab::tooManyFilesErr(std::string snippet)
{
  std::cout << "\x1b[38;2;200;50;0mCMD ERR\x1b[0m | \x1b[38;2;200;150;25mToo Many files Supplied\x1b[0m | \x1b[38;2;200;50;0mParser Termininated\x1b[0m | Snippet: " << snippet << '\n';
}
void ab::internalErr(int lineNum)
{
  std::cout << "\x1b[38;2;200;50;0mINTERNAL ERR\x1b[0m | \x1b[38;2;200;150;25mAn Unknown Internal Error Has Occured at Parser Line: " << lineNum << "\x1b[0m | Please contact the Air Boigus at: [airboigus@gmail.com] or on the MAML Github page";
}
void ab::noAttributeParameterSuppliedErr(std::string snippet)
{
  std::cout << "\x1b[38;2;200;50;0mDOC ERR\x1b[0m | \x1b[38;2;200;150;25No Attribute Parameter Supplied\x1b[0m | \x1b[38;2;200;50;0mError Source Ignored\x1b[0m | Snippet: " << snippet << '\n';
}
void ab::invalidAttributeParameterErr(std::string snippet)
{
  std::cout << "\x1b[38;2;200;50;0mDOC ERR\x1b[0m | \x1b[38;2;200;150;25mInvalid Attribute Parameter\x1b[0m | \x1b[38;2;200;50;0mError Source Ignored\x1b[0m | Snippet: " << snippet << '\n';
}
void ab::unrecognizedObjectErr(std::string snippet)
{
  std::cout << "\x1b[38;2;200;50;0mDOC ERR\x1b[0m | \x1b[38;2;200;150;25mUnrecognized Object\x1b[0m | \x1b[38;2;200;50;0mError Source Ignored\x1b[0m | Snippet: " << snippet << '\n';
}
void ab::missingClosingTagErr(std::string snippet)
{
  std::cout << "\x1b[38;2;200;50;0mDOC ERR\x1b[0m | \x1b[38;2;200;150;25mMissing Closing Tag\x1b[0m | \x1b[38;2;200;50;0mError Source Ignored\x1b[0m | Snippet: " << snippet << '\n';
}
void ab::tooManyDefaultScenesErr()
{
  std::cout << "\x1b[38;2;200;50;0mDOC ERR\x1b[0m | \x1b[38;2;200;150;25mMore Than One Default Scene\x1b[0m | \x1b[38;2;200;50;0mError Source Ignored\x1b[0m | Snippet: No Snippet Available\n";
}
