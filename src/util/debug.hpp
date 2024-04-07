#pragma once
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

#ifdef PP_DEBUG
    static char l_testSeparator[] = { 'T', 'E', 'S', 'T' };
    static char l_vecSeparator[] = { 'V', 'E', 'C', 'T' };
    static char l_endSeparator[] = { 'E', 'N', 'D', 'E' };
    static char l_arrSeparator[] = { 'A', 'R', 'R', 'Y' };
    static char l_uMapSeparator[] = { 'M', 'A', 'P', 'U' };

    void writeSeparator(std::string i_string, OutputStream& o_stream);

    void readSeparator(std::string o_string, InputStream& i_stream);

    #define SEPARATOR_O o_stream.write(l_testSeparator, 4);
    #define SEPARATOR_O_C(s) writeSeparator(#s, o_stream);
    #define VEC_SEPARATOR_O o_stream.write(l_vecSeparator, 4);
    #define ARR_SEPARATOR_O o_stream.write(l_arrSeparator, 4);
    #define UMAP_SEPARATOR_O o_stream.write(l_uMapSeparator, 4);
    #define SEPARATOR_O_END o_stream.write(l_endSeparator, 4);
    #define SEPARATOR_I i_stream.ignore(4);
    #define SEPARATOR_I_C(s) readSeparator(#s, i_stream);
    #define VEC_SEPARATOR_I i_stream.ignore(4);
    #define ARR_SEPARATOR_I i_stream.ignore(4);
    #define UMAP_SEPARATOR_I i_stream.ignore(4);
    #define SEPARATOR_I_END i_stream.ignore(4);
#else
    #define SEPARATOR_O
    #define SEPARATOR_O_C(s)
    #define VEC_SEPARATOR_O
    #define ARR_SEPARATOR_O
    #define UMAP_SEPARATOR_O
    #define SEPARATOR_O_END
    #define SEPARATOR_I
    #define SEPARATOR_I_C(s)
    #define VEC_SEPARATOR_I
    #define ARR_SEPARATOR_I
    #define UMAP_SEPARATOR_I
    #define SEPARATOR_I_END
#endif