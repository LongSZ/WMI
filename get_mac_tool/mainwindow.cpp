#include "mainwindow.h"
#include "ui_mainwindow.h"

static const char* s_sql_netcard = "Select Name, NetConnectionID, NetConnectionStatus, MACAddress from Win32_NetworkAdapter Where PhysicalAdapter = True and NetEnabled = True";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    get_mac();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_mac()
{
    CDnpService cService;
    if (!cService.IsServiceRunning(_T("Winmgmt"))) {
        if (!cService.EasyStart(_T("Winmgmt"))) {
            ui->lineEdit_mac->setText(QStringLiteral("启动WMI服务失败!"));
        }
    }
    
    string mac_addr;
    if (GetMacAddr(mac_addr) && !mac_addr.empty()) {
        ui->lineEdit_mac->setText(mac_addr.c_str());
    }
    else {
        ui->lineEdit_mac->setText(QStringLiteral("获取MAC地址失败"));
    }
}


void MainWindow::on_pushButton_refresh_clicked()
{
    get_mac();
}

int MainWindow::GetWMIInformationBySQL(const char *sql, const char *pszClass, vector<map<string, string> > &vecMapOut)
{
    IWbemLocator* pIWbemLocator = NULL;
    IWbemServices* pWbemServices = NULL;
    IEnumWbemClassObject* pEnumObject = NULL;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (CoInitializeSecurity(NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_PKT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        0
    ) != S_OK)
        return -1;

    BSTR bstrNamespace = _com_util::ConvertStringToBSTR("root\\cimv2");
    BSTR bstrQuery = _com_util::ConvertStringToBSTR(sql);

    if (CoCreateInstance(
        CLSID_WbemAdministrativeLocator,
        NULL,
        CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
        IID_IUnknown,
        (void**)&pIWbemLocator
    ) != S_OK)
        return -1;

    if (pIWbemLocator->ConnectServer(
        bstrNamespace,  // Namespace
        NULL,          // Userid
        NULL,           // PW
        NULL,           // Locale
        0,              // flags
        NULL,           // Authority
        NULL,           // Context
        &pWbemServices
    ) != S_OK)
    {
        OutputDebugString(L"CoConnectServer Fail\n");
        pIWbemLocator->Release();
        return -2;
    }

    if (S_OK != CoSetProxyBlanket(pWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE,
        NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE))
    {
        OutputDebugString(L"CoSetProxyBlanket Fail\n");
        pIWbemLocator->Release();
        pWbemServices->Release();
        return -2;
    }

    HRESULT hRes;
    BSTR bstrQL = _com_util::ConvertStringToBSTR("WQL");
    hRes = pWbemServices->ExecQuery(bstrQL, bstrQuery, WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumObject);
    if (hRes != S_OK)
    {
        pIWbemLocator->Release();
        pWbemServices->Release();
        return -2;
    }       

    ULONG uCount = 1, uReturned;
    IWbemClassObject* pClassObject = NULL;
    while (pEnumObject)
    {
        map<string, string> mapOut;

        HRESULT hr = pEnumObject->Next(WBEM_INFINITE, 1, &pClassObject, &uReturned);
        if (!uReturned)
        {
            break;
        }

        VARIANT vtProp;
        VariantInit(&vtProp);
        pClassObject->BeginEnumeration(WBEM_FLAG_NONSYSTEM_ONLY);
        {
            CIMTYPE pvtType;
            VARIANT     pVal;
            BSTR        pstrName;
            VARIANT v;

            BSTR strClassProp = _com_util::ConvertStringToBSTR(pszClass);
            hRes = pClassObject->Get(strClassProp, 0, &v, 0, 0);
            if (hRes != S_OK)
            {
                continue;
            }
            SysFreeString(strClassProp);

            //get properties
            while (pClassObject->Next(0, &pstrName, &pVal, &pvtType, NULL) == WBEM_S_NO_ERROR)
            {
                if ((pVal.vt == VT_NULL) || (pVal.vt == VT_EMPTY))
                    continue;

                //for property value
                BOOL b = pVal.vt & VT_VARIANT;
                if (pVal.vt & VT_ARRAY)
                {
                    DWORD dwBytes = 0;
                    SAFEARRAY* pArrayVal = NULL;
                    pArrayVal = pVal.parray;
                    dwBytes = pArrayVal->rgsabound[0].cElements;

                    if (pVal.vt & VT_BSTR)
                    {
                        string sInfo;
                        BSTR* pArr = (BSTR*)(pArrayVal->pvData);
                        for (long i = 0; i < dwBytes; i++)
                        {
                            _bstr_t bstrVal = pArr[i];
                            char* strVal = (char*)bstrVal;
                            //strVlaueOfArray.Format("%s", strVal);
                            sInfo.append(strVal);
                            if (i < dwBytes - 1)
                                sInfo.append("|||");
                        }

                        char* p = _com_util::ConvertBSTRToString(pstrName);
                        mapOut.insert(make_pair(p, sInfo));
                        delete[] p;
                    }
                    continue;
                }

                _bstr_t bstrVal = &pVal;
                char* strVal = (char*)bstrVal;

                char* p = _com_util::ConvertBSTRToString(pstrName);
                mapOut.insert(make_pair(p, strVal));

                delete[] p;
                p = NULL;
                SysFreeString(pstrName);
                VariantClear(&pVal);
            }
        }

        if (mapOut.size() > 0)
            vecMapOut.push_back(mapOut);
    }

    if (pIWbemLocator != NULL)
        pIWbemLocator->Release();
    if (pWbemServices != NULL)
        pWbemServices->Release();
    if (pEnumObject != NULL)
        pEnumObject->Release();
    if (pClassObject != NULL)
        pClassObject->Release();

    SysFreeString(bstrQuery);
    CoUninitialize();
    return 0;
}

bool MainWindow::GetMacAddr(string &sMac)
{
    string sWlanMac;
    bool bFindEthnet = false;
    vector<map<string, string>> vecMapInfo;
    GetWMIInformationBySQL(s_sql_netcard, "Name", vecMapInfo);
    for (auto it : vecMapInfo) {
        string sNetType = it["NetConnectionID"];
        std::transform(sNetType.begin(), sNetType.end(), sNetType.begin(), ::toupper);
        cout << "sNetType = " << sNetType << ", and mac = " << it["MACAddress"] << endl;
        
        bool bEthernet = (int)sNetType.find("以太网") >= 0 || (int)sNetType.find("ETHERNET") >= 0;
        if (bEthernet) {
            sMac = it["MACAddress"];
            return true;
        }
        
        bool bBlueTooth = ((int)sNetType.find("蓝牙") >= 0 || (int)sNetType.find("BLUETOOTH") >= 0);
        bool bLoopAdapter = (int)sNetType.find("LOOPBACK") >= 0;
        bool bWLan = (int)sNetType.find("WLAN") >= 0;
        if (bWLan) {
            sWlanMac = it["MACAddress"];
        }

        if (!bBlueTooth && !bLoopAdapter && !bWLan)
        {
            sMac = it["MACAddress"];
            bFindEthnet = true;
        } 
    }

    if (!bFindEthnet|| sMac.empty())
    {
        sMac = sWlanMac;
    }

    return sMac.empty() ? -1 : 0;
}
