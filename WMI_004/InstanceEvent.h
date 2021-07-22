#ifndef CINSTANCEEVENT_H
#define CINSTANCEEVENT_H

#include "Sink.h"

class CInstanceEvent : public CSink {
    public:
        CInstanceEvent(void);
        ~CInstanceEvent(void);

    private:
        HRESULT DealWithSingleItem( CComBSTR bstrName, CComVariant Value, CIMTYPE type, LONG lFlavor );
        HRESULT DealWithUnknownTypeItem( CComBSTR bstrName, CComVariant Value, CIMTYPE type, LONG lFlavor );
        VOID PrintfItem( CComBSTR bstrName, CComVariant Value, CIMTYPE type, LONG lFlavor );
};

#endif
