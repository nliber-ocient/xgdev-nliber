#ifndef DEBUG_H
#define DEBUG_H
/***********************************************************************
 * Provide "dout" for debug output.  If DEBUG is defined, map it to
 * std::cout, otherwise send output to a null buffer
 * Shamelessly Taken from 
 * https://stackoverflow.com/questions/11826554/standard-no-op-output-stream
 ***********************************************************************/
#include <iostream>
#include <sstream>

#ifdef DEBUG
static auto &dout = std::cout;
#else
class NullBuffer : public std::stringstream
{
public:
  int overflow(int c) { return c; }
};

static NullBuffer dout;
#endif


#endif /* DEBUG_H */
