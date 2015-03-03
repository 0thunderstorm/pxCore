// rtCore CopyRight 2007-2015 John Robinson
// rtString.h
// A simple utf8 string class

#include "rtString.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include "rtLog.h"
extern "C" {
#include "utf8.h"
}

static char* STRDUP(const char* s)
{
  if (!s)
    return NULL;

#ifdef _WIN32
  return _strdup(s);
#else
  return strdup(s);
#endif
}

rtString::rtString(): mData(0)  {
  //  printf("default constructor\n");
}

rtString::rtString(char* s)
{
  mData = STRDUP(s);
}

rtString::rtString(const char* s)
{
  mData = STRDUP(s);
}

rtString::rtString(const rtString& s)
{
  mData = STRDUP(s.mData);
}

rtString& rtString::operator=(const rtString& s)
{
  mData = STRDUP(s.mData);
  return *this;
}

rtString& rtString::operator=(const char* s)
{
  mData = STRDUP(s);
  return *this;
}

bool rtString::isEmpty()
{
  return (!mData || !(*mData));
}

rtString::~rtString() { term(); }

void rtString::term() {
  if (mData)
      free(mData);
  mData = 0;
}

void rtString::append(const char* s) {
  int sl = strlen(s);
  int dl = strlen(mData);
  mData = (char*)realloc((void*)mData, dl+sl+1);
    strcpy(mData+dl, s);
}

int rtString::compare(const char* s) const {
  u_int32_t c1, c2;
  int i1 = 0, i2 = 0;
  
  do {
    c1 = u8_nextchar((char*)s, &i1);
    c2 = u8_nextchar((char*)mData, &i2);
  } while (c1 == c2 && c1 && c2);
  
  return c1-c2;
}


char* rtString::cString() const {
  return mData;
}

//HACK: missing symbol. Is this utf8?
int32_t rtString::length() const {
  return mData ? strlen(mData) : 0;
}

