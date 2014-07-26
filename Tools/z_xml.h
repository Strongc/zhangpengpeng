/* z_xml
 * zhangpengpeng (rocflyhi@gmail.com)
 * xml tool
 */

typedef struct z_xml_node_ {
	char *name;
	char *value;

	struct z_xml_node_ *next;
	struct z_xml_node_ *child;
	struct z_xml_node_ *last_child;
	struct z_xml_node_ *parent;

	char *origin_content;
	struct z_xml_node_ *handle_next;
}z_xml_node;

typedef struct z_xml_ {
	z_xml_node *root;
	z_xml_node *pos;
	int pos_type;	// 0 node, 1 node's child which is null

	z_xml_node *unhandle_list;
	z_xml_node *unhandle_list_tail;
	z_xml_node *handle_list;
	z_xml_node *handle_list_tail;
}z_xml;

int z_xml_init(z_xml *xml);
int z_xml_uninit(z_xml *xml);
int z_xml_set_string(z_xml *xml, const char *xml_string);
int z_xml_get_string(z_xml *xml, char *xml_string);
int z_xml_add_node(z_xml *xml, const char *name, const char *value);
int z_xml_find_node(z_xml *xml, const char *name);
const char *z_xml_get_name(z_xml *xml);
const char *z_xml_get_value(z_xml *xml);
int z_xml_move_in(z_xml *xml);
int z_xml_move_out(z_xml *xml);
