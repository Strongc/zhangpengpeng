/* z_xml
 * zhangpengpeng (rocflyhi@gmail.com)
 * xml tool
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z_xml.h"

int z_xml_mcopy_string(char **ptr, const char *string, int len)
{
	*ptr = (char*)malloc(len + 1);
	memset(*ptr, 0, len + 1);
	if (*ptr != NULL)
	{
		memcpy(*ptr, string, len);
		return 0;
	}
	return -1;
}

#define z_xml_safe_delete(ptr)	\
	if (ptr != NULL)	\
	{	\
		free(ptr);		\
		ptr = NULL;	\
	}


z_xml_node *z_xml_create_node()
{
	int len = sizeof(z_xml_node);
	z_xml_node *node = (z_xml_node*)malloc(len);
	if (node != NULL)
	{
		node->name = NULL;
		node->value = NULL;

		node->next = NULL;
		node->child = NULL;
		node->last_child = NULL;
		node->parent = NULL;

		node->origin_content = NULL;
		node->handle_next = NULL;
	}
	return node;
}
void z_xml_delete_node(z_xml_node *node)
{
	if (node != NULL)	
	{
		z_xml_safe_delete(node->name);
		z_xml_safe_delete(node->value);
		z_xml_safe_delete(node->origin_content);
		z_xml_safe_delete(node);
	}
}


int z_xml_init(z_xml *xml)
{
	if (xml == NULL)
		return -1;

	xml->root = NULL;
	xml->pos = NULL;
	xml->pos_type = 0;
	xml->handle_list = NULL;
	xml->handle_list_tail = NULL;
	xml->unhandle_list = NULL;
	xml->unhandle_list_tail = NULL;
	return 0;
}
int z_xml_uninit(z_xml *xml)
{
	z_xml_node *for_delete = NULL;
	z_xml_node *next_delete = NULL;

	if (xml == NULL)
		return -1;

	for_delete = xml->unhandle_list;
	xml->unhandle_list = NULL;
	while (for_delete != NULL)
	{
		next_delete = for_delete->handle_next;
		z_xml_delete_node(for_delete);
		for_delete = next_delete;
	}
	for_delete = xml->handle_list;
	xml->handle_list = NULL;
	while (for_delete != NULL)
	{
		next_delete = for_delete->handle_next;
		z_xml_delete_node(for_delete);
		for_delete = next_delete;
	}

	return 0;
}

char *z_xml_find_next_lt(char *begin)
{
	char *ptr = begin;
	while (ptr != NULL)
	{
		if (*ptr == '<')
			break;
		ptr++;
	}
	return ptr;
}
char *z_xml_find_next_gt(char *begin)
{
	char *ptr = begin;
	while (ptr != NULL)
	{
		if (*ptr == '>')
			break;
		ptr++;
	}
	return ptr;
}

char *z_xml_find_name_end(char *string, char *name)
{
	char *name_end_string = NULL;
	char * pos_name_end_lt = NULL;

	name_end_string = (char*)malloc(strlen(name) + 4);
	sprintf(name_end_string, "</%s>", name);
	pos_name_end_lt = strstr(string, name_end_string);
	z_xml_safe_delete(name_end_string);
	return pos_name_end_lt;
}

int z_xml_add_child(z_xml_node *child, z_xml_node *parent)
{
	if (parent->child == NULL)
		parent->child = child;
	else
		parent->last_child->next = child;
	parent->last_child = child;
	child->parent = parent;
	return 0;
}
int z_xml_add_sibling(z_xml_node *sibling, z_xml_node *node)
{
	sibling->next = node->next;
	sibling->parent = node->parent;
	node->next = sibling;
	if (node->parent != NULL)
		if (node->parent->last_child == node)
			node->parent->last_child = sibling;
	return 0;
}

int z_xml_parse_node(z_xml *xml)
{
	z_xml_node *node_parsing = NULL;
	char *pos_name_lt = NULL;
	char *pos_name_gt = NULL;

	node_parsing = xml->unhandle_list;
	if (node_parsing == NULL)
		return -1;

	/* remove this node from unhandle list */
	xml->unhandle_list = node_parsing->handle_next; 

	pos_name_lt = z_xml_find_next_lt(node_parsing->origin_content);
	if (pos_name_lt == NULL)
		return -100;
	pos_name_gt = z_xml_find_next_gt(pos_name_lt);
	if (pos_name_gt == NULL)
		return -101;
	if ((pos_name_gt - pos_name_lt) < 2)
		return -102;

	if (*(pos_name_gt - 1) == '/')	/* e.g. <name/> */
	{
		if ((pos_name_gt - pos_name_lt) < 3)
			return -103;
		z_xml_mcopy_string(&node_parsing->name, pos_name_lt + 1, pos_name_gt - pos_name_lt - 2);
		z_xml_mcopy_string(&node_parsing->value, "", 1);
	}
	else
	{
		char *pos_name_2lt = NULL;
		char *pos_name_end_lt = NULL;

		z_xml_mcopy_string(&node_parsing->name, pos_name_lt + 1, pos_name_gt - pos_name_lt - 1);

		pos_name_2lt = z_xml_find_next_lt(pos_name_gt + 1);
		if (pos_name_2lt == NULL)
			return -104;

		pos_name_end_lt = z_xml_find_name_end(pos_name_gt + 1, node_parsing->name);
		if (pos_name_end_lt == NULL)
			return -105;

		if (pos_name_2lt == pos_name_end_lt)	/* e.g. <name>aa</name> */
		{
			z_xml_mcopy_string(&node_parsing->value, pos_name_gt + 1, pos_name_2lt - pos_name_gt - 1);
		}
		else	/* e.g. <name><a>aa</a><b/></name> */
		{
			while (pos_name_2lt < pos_name_end_lt)
			{
				z_xml_node *sub_node = z_xml_create_node();
				char *pos_sub_name_lt = pos_name_2lt;
				char *pos_sub_name_gt = z_xml_find_next_gt(pos_sub_name_lt);
				char *pos_sub_end = pos_name_2lt;
				if (*(pos_sub_name_gt - 1) == '/')	/* e.g. <b/> */
				{
					z_xml_mcopy_string(&sub_node->origin_content, pos_sub_name_lt, pos_sub_name_gt - pos_sub_name_lt + 1);
					pos_sub_end = pos_sub_name_gt;
				}
				else	/* e.g. <a>aa</a> */
				{
					char *pos_sub_name_end_lt = NULL;
					char *sub_name = NULL;

					z_xml_mcopy_string(&sub_name, pos_sub_name_lt + 1, pos_sub_name_gt - pos_sub_name_lt - 1);
					pos_sub_name_end_lt = z_xml_find_name_end(pos_sub_name_gt + 1, sub_name);
					pos_sub_end = pos_sub_name_end_lt + strlen(sub_name) + 2;
					z_xml_safe_delete(sub_name);
					z_xml_mcopy_string(&sub_node->origin_content, pos_sub_name_lt, pos_sub_end - pos_sub_name_lt + 1);
				}

				z_xml_add_child(sub_node, node_parsing);
				pos_name_2lt = z_xml_find_next_lt(pos_sub_end + 1);

				/* add new node to unhandle list */
				if (xml->unhandle_list == NULL)
					xml->unhandle_list = sub_node;
				else
					xml->unhandle_list_tail->handle_next = sub_node;
				xml->unhandle_list_tail = sub_node;
			}
		}
	}
	z_xml_safe_delete(node_parsing->origin_content);

	/* add this node to handle list */
	if (xml->handle_list == NULL)
		xml->handle_list = node_parsing;
	else
		xml->handle_list_tail->handle_next = node_parsing;
	xml->handle_list_tail = node_parsing;
	return 0;
}

int z_xml_set_string(z_xml *xml, const char *xml_string)
{
	if (xml == NULL || xml_string == NULL)
		return -1;
	if (xml->root != NULL)
		return -2;

	xml->root = z_xml_create_node();
	z_xml_mcopy_string(&xml->root->origin_content, xml_string, strlen(xml_string));
	xml->pos = xml->root;
	xml->unhandle_list = xml->root;
	xml->unhandle_list_tail = xml->unhandle_list;
	while (xml->unhandle_list != NULL)
		z_xml_parse_node(xml);

	return 0;
}

int z_xml_get_string_r(z_xml_node *node, char *xml_string)
{
	int ret = 0;
	if (node == NULL || xml_string == NULL)
		return -1;

	strcat(xml_string, "<");
	strcat(xml_string, node->name);
	if ((node->value == NULL || strlen(node->value) == 0) && node->child == NULL)
	{
		strcat(xml_string, "/>");
	}
	else 
	{
		strcat(xml_string, ">");

		if (node->child == NULL)
			strcat(xml_string, node->value);
		else
			ret = z_xml_get_string_r(node->child, xml_string);

		strcat(xml_string, "</");
		strcat(xml_string, node->name);
		strcat(xml_string, ">");
	}

	if (node->next != NULL)
	{
		ret = z_xml_get_string_r(node->next, xml_string);
	}
	return ret;
}

int z_xml_get_string(z_xml *xml, char *xml_string)
{
	if (xml_string == NULL || xml == NULL)
		return -1;

	return z_xml_get_string_r(xml->root, xml_string);
}

int z_xml_add_node(z_xml *xml, const char *name, const char *value)
{
	z_xml_node *node = NULL;

	if (xml == NULL || name == NULL || value == NULL)
		return -1;

	node = z_xml_create_node();
	z_xml_mcopy_string(&node->name, name, strlen(name));
	z_xml_mcopy_string(&node->value, value, strlen(value));

	if (xml->root == NULL)		// add root
	{
		xml->root = node;
	}
	else if (xml->pos_type == 0)	// add sibling
	{
		z_xml_add_sibling(node, xml->pos);
	}
	else		// add first child
	{
		z_xml_add_child(node, xml->pos);
	}
	xml->pos = node;
	xml->pos_type = 0;
	return 0;
}

int z_xml_find_node(z_xml *xml, const char *name)
{
	if (xml == NULL || name == NULL)
		return -1;
	if (xml->root == NULL || xml->pos == NULL)
		return -2;
	if (xml->pos_type != 0)
		return -3;

	while (xml->pos != NULL)
	{
		if (strcmp(xml->pos->name, name) == 0)
			return 0;
		xml->pos = xml->pos->next;
	}
	return -4;
}

const char *z_xml_get_name(z_xml *xml)
{
	if (xml != NULL && xml->pos != NULL && xml->pos_type == 0)
		return xml->pos->name;
	else
		return NULL;
}

const char *z_xml_get_value(z_xml *xml)
{
	if (xml != NULL && xml->pos != NULL && xml->pos_type == 0)
		return xml->pos->value;
	else
		return NULL;
}

int z_xml_move_in(z_xml *xml)
{
	if (xml == NULL)
		return -1;
	if (xml->pos_type != 0)
		return -2;

	if (xml->pos->child != NULL)
	{
		xml->pos = xml->pos->child;
	}
	else
	{
		xml->pos_type = 1;
	}
	return 0;
}

int z_xml_move_out(z_xml *xml)
{
	if (xml == NULL)
		return -1;
	if (xml->pos == NULL)
		return -2;

	if (xml->pos_type != 0)
		xml->pos_type = 0;
	else if (xml->pos->parent != NULL)
		xml->pos = xml->pos->parent;
	else
		return -3;

	return 0;
}
