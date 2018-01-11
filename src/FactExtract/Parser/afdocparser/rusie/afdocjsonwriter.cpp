#include "afdocjsonwriter.h"

//--конструктор + вызов конструктора базового класса
CAfDocJSONWriter::CAfDocJSONWriter(const Stroka& strFileName, ECharset encoding, const CParserOptions::COutputOptions& OutputOptions)
:CAfDocPlainTextWriter(strFileName, encoding, OutputOptions)
{
    //---ничего не делаем. Все что нужно инициализируется в базовом классе.
}

//--деструктор (по умолчанию)
CAfDocJSONWriter::~CAfDocJSONWriter()
{
    //---ничего не делаем. Вызывается деструктор базового класса.
}

//--формирование основной JSON-структуры выходных данных:
//---{"original_text":"...",
//---facts:[
//---        {"fact_id":"f1", 
//---            "data":{"key1.1":"value1.1"}, "key1.2":"value1.2","key...":"value..."}
//---        },
//---        {"fact_id":"f2", 
//---         "data":{"key2.1":"value2.1"}, "key2.2":"value2.2","key...":"value..."}
//---        }
//---        ....
//---        {"fact_id":"f...", 
//---         "data":{"key...1":"value...1"}, "key...2":"value...2","key...":"value..."}
//---        }
//---      ] 
//---}
void CAfDocJSONWriter::AddDocument(CTextProcessor* pText, TOutputStream* out){
    
    for (size_t i = 0; i < pText->GetSentenceCount(); i++) {
        CSentence* pSent = pText->GetSentence(i);
        
        Stroka factString;

        for (size_t j = 0; j < pSent->GetWordSequences().size(); j++)
            factString += AddWS(pSent->GetWordSequences()[j].Get(), pSent);

        //---строка в со структурой исходного предложения ("original_text":"...")
        Stroka SentStr = "\"original_text\":\"";
        for (size_t j = 0; j < pSent->getWordsCount(); ++j) {
            SentStr += EncodeText(pSent->getWord(j)->GetOriginalText());
            SentStr += ' ';
        }
        SentStr += "\"";

        Stroka result = "{"+SentStr;
        if (!factString.empty()){
            result+=",\"facts\":["+factString+"]";
        }
        
        result += "}";

        //---запись полной структуры фактов по предложению в выходной файловый поток.
        out->Write(~result, +result);
  }
}

//--построение JSON-структуры с фактами
Stroka CAfDocJSONWriter::AddWS(CWordSequence* pWS, CSentence* _pSent)
{
    CSentenceRusProcessor* pSent = dynamic_cast<CSentenceRusProcessor*>(_pSent);
    const CDictsHolder* pDict = GlobalDictsHolder;

    if (pSent == NULL)
        ythrow yexception() << "Base subclass of CSentence in \"CAfDocJSONWriter::AddWS\"";

    CFactsWS* pFactsWS = dynamic_cast<CFactsWS*>(pWS);
    if (pFactsWS == NULL)
        return Stroka();
    //---основная строка вывода: "
    //---[{"fact_id":"...", "data":{"key":"...", "value":"..."}}]
    Stroka result;

    for (int j = 0; j < pFactsWS->GetFactsCount(); j++) {
        const CFactFields& fact = pFactsWS->GetFact(j);

        if (!OutputOptions.HasFactToShow(fact.GetFactName()))
            continue;

        const fact_type_t* pFactType = &pDict->RequireFactType(fact.GetFactName());

        if (pFactType == NULL)
            ythrow yexception() << "Unknown FactType " << fact.GetFactName();
        
        //--- строка вывода информации о факте:
        //--- "{"fact_id":"...", "data":{"key":"...", "value":"..."}}
        Stroka strFact = "{\"fact_id\":\"" + fact.GetFactName() +"\", \"data\":{";

        bool bAddFact = true;
        for (size_t i = 0; i < pFactType->m_Fields.size(); i++) {
            const fact_field_descr_t& field = pFactType->m_Fields[i];
            if (!fact.HasValue(field.m_strFieldName))
                continue;

            strFact += "\"" + field.m_strFieldName + "\":\"";
            
            switch (field.m_Field_type) {
                case FioField: strFact += EncodeText(fact.GetFioValue(field.m_strFieldName)->GetLemma()); break;
                case TextField: {
                    Stroka ss = EncodeText(fact.GetTextValue(field.m_strFieldName)->GetCapitalizedLemma());
                    //если это обязательное поле со значением empty - не печатаем этот факт
                    if (field.m_bNecessary && stroka(ss) == "empty" && !OutputOptions.ShowFactsWithEmptyField())
                        bAddFact = false;
                    strFact += ss;
                    break;
                }
                case BoolField: fact.GetBoolValue(field.m_strFieldName) ? strFact += "true" : strFact += "false"; break;
                case DateField: {
                    strFact += EncodeText(fact.GetDateValue(field.m_strFieldName)->ToString());
                    break;
                }
                case FactFieldTypesCount:
                    /* nothing to do? */
                    break;
            }
            
            //---если это НЕ последняя итерация цикла, то добавляем ( ", ) , в противном случае - ( "} )
            if(i== pFactType->m_Fields.size() - 1){
                strFact += "\"}";
            } else {
                 strFact += "\",";
            }
        }

        strFact += "}";
        if (bAddFact)
            result += strFact;
    };
    return result;

}
