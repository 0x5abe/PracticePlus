#pragma once
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

#ifdef PP_DEBUG
    static char l_testSeparator[] = { 'T', 'E', 'S', 'T' };
    static char l_vecSeparator[] = { 'V', 'E', 'C', 'T' };
    #define SEPARATOR_O o_stream.write(l_testSeparator, 4);
    #define VEC_SEPARATOR_O o_stream.write(l_vecSeparator, 4);
    #define SEPARATOR_I i_stream.ignore(4);
    #define VEC_SEPARATOR_I i_stream.ignore(4);
#endif