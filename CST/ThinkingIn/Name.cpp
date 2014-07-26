/* zpp's style about struct, enum, etc. */
typedef struct _st_structureName{
        enum _em_stateName{ /*..status..*/ }state;
        //..other members
}StructureName;
class ClassName;
// type's name which is used directly begins with uppercase;

/*
私有的，不想给外部使用的函数（回调、线程调用等）以小写字母卡口，给外部使用的函数以大写字母开头。
*/

