/* zml
 * zhangpengpeng (rocflyhi@gmail.com)
 * zml tool
 */

typedef struct zml_node_ {
	char *name;
	char *value;
	int level;

	struct zml_node_ *next;
	struct zml_node_ *child;
	struct zml_node_ *last_child;
	struct zml_node_ *parent;
}zml_node;

typedef struct zml_ {
	zml_node *root;
	zml_node *pos;
	int pos_type;	// 0 node, 1 node's child which is null
}zml;

int zml_init(zml *z);
int zml_uninit(zml *z);
int zml_set_string(zml *z, const char *z_string);
int zml_get_string(zml *z, char *z_string);
int zml_add_node(zml *z, const char *name, const char *value);
int zml_find_node(zml *z, const char *name);
const char *zml_get_name(zml *z);
const char *zml_get_value(zml *z);
int zml_move_in(zml *z);
int zml_move_out(zml *z);
