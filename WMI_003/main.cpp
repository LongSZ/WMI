#include <QCoreApplication>

#include "SynQueryData.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    //1. 查询网络适配器
    CSynQueryData recvnotify(L"root\\cimv2", 
        L"select Name, GUID, DeviceID, PNPDeviceID, PhysicalAdapter, \
              NetConnectionID, NetConnectionStatus, MACAddress from Win32_NetworkAdapter where PhysicalAdapter = True");
    recvnotify.ExcuteFun();
    
    //2.1 正在运行的进程的进程名
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT Caption FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.2 正在运行的进程的进程ID
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT ProcessId FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.3 正在运行的进程的父进程ID
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT ParentProcessId FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.4 正在运行的进程在启动时的命令
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT CommandLine FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.5 正在运行的进程是何时启动的
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT CreationDate FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.6 正在运行的进程的文件路径
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT ExecutablePath FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.7 正在运行的进程的用户时间和内核时间
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT UserModeTime,KernelModeTime FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.8 正在运行的进程的线程数
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT ThreadCount FROM Win32_Process");
    //recvnotify.ExcuteFun();
    
    //2.9 获取指定进程ID的进程的优先级
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT Name, Priority FROM Win32_Process Where ProcessId = 0 or ProcessID = 4");
    //recvnotify.ExcuteFun();
    
    //3.1 枚举所有线程的所有信息
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_Thread");
    //recvnotify.ExcuteFun();
    
    //4.1 枚举所有的桌面
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_Desktop");
    //recvnotify.ExcuteFun();
    
    //5.1 枚举所有环境变量的信息
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_Environment");
    //recvnotify.ExcuteFun();
    
    //6.1 查询所有驱动信息
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_SystemDriver");
    //recvnotify.ExcuteFun();
    
    //7.1 获取指定文件夹的访问属性
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT AccessMask FROM Win32_Directory WHERE Name = 'c:\\\\Program Files'");
    //recvnotify.ExcuteFun();
    
    //8.1 获取指定文件夹的访问属性
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_DiskPartition");
    //recvnotify.ExcuteFun();
    
    //8.6 枚举所有逻辑磁盘信息
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_LogicalDisk");
    //recvnotify.ExcuteFun();
    
    //9.1 枚举电脑上所有快捷方式
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_ShortcutFile");
    //recvnotify.ExcuteFun();
    
    //9.3 枚举所有映射的磁盘信息
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_MappedLogicalDisk");
    //recvnotify.ExcuteFun();
    
    //9.6 枚举系统中所有分页文件信息
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_PageFile");
    //recvnotify.ExcuteFun();
    
    //10.1 查询是否开启了系统硬件安全设置密码
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT AdminPasswordStatus FROM Win32_ComputerSystem");
    //recvnotify.ExcuteFun();
    
    //11.1 获取系统UUID
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT UUID FROM Win32_ComputerSystemProduct");
    //recvnotify.ExcuteFun();
    
    //12.1 获取本地时间
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT Year, Month, Day, Hour, Minute, Second FROM Win32_LocalTime");
    //recvnotify.ExcuteFun();
    
    //13.1 枚举系统中的服务
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_Service");
    //recvnotify.ExcuteFun();
    
    //14. 查询本地用户和组
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_Group");
    //recvnotify.ExcuteFun();
    
    //15.7 查询内存信息
    //CSynQueryData recvnotify(L"root\\CIMV2", L"SELECT * FROM Win32_MemoryDevice");
    //recvnotify.ExcuteFun();
    
    return a.exec();
}
