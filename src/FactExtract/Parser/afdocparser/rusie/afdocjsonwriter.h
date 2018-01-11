#pragma once
#include "afdocplaintextwriter.h"

//---avikulin----------------------------------------
//---модифицированный вывод фактов в формате JSON
//---------------------------------------------------

class CAfDocJSONWriter: public CAfDocPlainTextWriter {
public:
    CAfDocJSONWriter(const Stroka& strFileName, ECharset encoding, const CParserOptions::COutputOptions& OutputOptions);
    
    ~CAfDocJSONWriter();

    virtual void AddDocument(CTextProcessor* pText, TOutputStream* out);

private:
    virtual Stroka AddWS(CWordSequence* pWS, CSentence* _pSent);
};