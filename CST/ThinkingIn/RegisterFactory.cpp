// Factory::Register

class interface()
{
	// static bool init();
	// static interface *CreateInstace();
};

typedef string KEY_ID;
typedef interface* (*CREATEINSTANCE)();

class factory
{
private:
	static map<KEY_ID, CREATEINSTANCE> RegisterMap;
public:
	static int Register(KEY_ID keyword, CREATEINSTANCE func);
	static interface *CreateInstace(KEY_ID keyword);
};

int factory::Register(KEY_ID keyword, CREATEINSTANCE func)
{
	RegisterMap[keyword] = func;
	// 注册时还可调用库的初始化函数
}

interface *factory::CreateInstace(KEY_ID keyword)
{
	return RegisterMap[keyword]();
}

class product1 : public interface
{
public:
	static interface *CreateInstace()
	{
		return new product1;
	}
};

int main()
{
	factory::Register("prod1", product1::CreateInstace);
	interface *instance = factory::CreateInstace("prod1");
	return 0;
}


/*************************************************/
// 根据实际情况选择相应的处理函数 
// 结构体数组：根据数字、名称或者其他标识来判断选用相应的函数
typedef struct        // 通过结构体建立关联
{
    int cmd;
    char *cmd;
    FUNCPTRINT func;
}CMD_TABLE;
CMD_TABLE HikSdkCmd[] = 
{
    { 1, "GetServerInfo",            (FUNCPTRINT)GetServerInfo },
    { 2, "GetServerInfoPara",        (FUNCPTRINT)GetServerInfoPara },
    { 3, "GetNetPara",               (FUNCPTRINT)GetNetPara }
};


/* 多个动态库采用同样的接口函数，
 * 上层根据实际情况选择对应的动态库，
 * 采用一样的调用方式
 */

