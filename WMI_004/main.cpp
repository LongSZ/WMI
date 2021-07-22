#include <QCoreApplication>

#include "AsynNotifyQuery.h"
#include "AsynNotifyQuery.cpp"          //模板类要包含cpp?
#include "InstanceEvent.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    //1. 监控进程创建和死亡
//    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//    CAsynNotifyQuery<CInstanceEvent> recvnotify(L"root\\CIMV2", 
//        L"SELECT * FROM __InstanceModificationEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process'", hEvent);
//    recvnotify.ExcuteFun();
    
    //2. 监控USB设备插拔 
//    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//    CAsynNotifyQuery<CInstanceEvent> recvnotify(L"root\\CIMV2", 
//        L"SELECT * FROM __InstanceCreationEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_USBCOntrollerDevice'", hEvent);
//    recvnotify.ExcuteFun();
    
    //3. 监控某个进程
//    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//    CAsynNotifyQuery<CInstanceEvent> recvnotify(L"root\\CIMV2", 
//        L"SELECT * FROM __InstanceModificationEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process' And TargetInstance.Name = 'Notepad.exe'", hEvent);
//    recvnotify.ExcuteFun();
    
    //4. 监控电量 -- 等到笔记本上再试
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    CAsynNotifyQuery<CInstanceEvent> recvnotify(L"root\\CIMV2", 
        L"SELECT * FROM __InstanceModificationEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Battery'", hEvent);
    recvnotify.ExcuteFun();
    
    return a.exec();
}
