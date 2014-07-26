/* a global mgr class  '(zhangpengpeng 20101022)
 * some infos and some funs
 */
class SysInfo
{
private:
        char sysName[100];
        int parameters;
        enum enum_state{READY, RUN, OVER} state;
        //...other parameters

        bool bRuning;
        static SysInfo *pSysInfo;
        bool privateFuns(); //...some private functions

public:
        SysInfo();
        virtual ~SysInfo();
        static SysInfo *instance(); //get its instance

        void changeStateFuns();
        void writeLog();
        void alert();
        //other functions
};

//SysInfo::instance()->alert();

