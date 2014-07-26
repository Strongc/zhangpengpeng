/* '(zhangpengpeng 2014/03/17) */
#include <map>

static std::map<int, void*> commhandle2data;
static int common_handle_next = 0;

int common_handle_add(void *data)
{
    int this_handle = common_handle_next++;
    commhandle2data.insert(make_pair(this_handle, data));
    return this_handle;
}

void common_handle_del(int handle)
{
    commhandle2data.erase(handle);
}

void* common_handle_get(int handle)
{
	std::map<int, void*>::const_iterator iter = commhandle2data.find(handle);
	if (iter != commhandle2data.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

/**************************************************/
HANDLE_TYPE Handles_Mgt::Add(Handle_Base *data)
{
	if (data == NULL)
		return -1;

	HANDLE_TYPE this_handle = next_handle++;
	data->handle = this_handle;
	handle_map.insert(std::make_pair(this_handle, data));
	return this_handle;
}

void Handles_Mgt::Del(HANDLE_TYPE handle)
{
	handle_map.erase(handle);
}

Handle_Base* Handles_Mgt::Get(HANDLE_TYPE handle)
{
	std::map<HANDLE_TYPE, Handle_Base*>::const_iterator iter = handle_map.find(handle);
	if (iter != handle_map.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

Handles_Mgt handle_XXX_mgt;


