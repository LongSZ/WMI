#ifndef CSYNQUERY_H
#define CSYNQUERY_H

#include "WMI.h"
#include <string>
using namespace std;

class CSynQuery : public CWMI {
    public:
        CSynQuery(const wstring& wszNamespace, const wstring& wszWQLQuery);
        ~CSynQuery(void);
    
    private:
        HRESULT Excute(CComPtr<IWbemServices> pSvc);
        HRESULT DealWithIWbemClassObject(CComPtr<IWbemClassObject> pclsObj);
        virtual HRESULT DealWithSingleItem(CComBSTR bstrName, CComVariant Value, CIMTYPE type, LONG lFlavor);
    
         wstring m_wszWQLQuery;
};

#endif
