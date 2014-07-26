/* zml
 * zhangpengpeng (rocflyhi@gmail.com)
 * zml tool
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zml.h"

int zml_mcopy_string(char **ptr, const char *string, int len)
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

#define zml_safe_delete(ptr)	\
	if (ptr != NULL)	\
	{	\
		free(ptr);		\
		ptr = NULL;	\
	}


zml_node *zml_create_node()
{
	int len = sizeof(zml_node);
	zml_node *node = (zml_node*)malloc(len);
	if (node != NULL)
	{
		node->name = NULL;
		node->value = NULL;
		node->level = 0;

		node->next = NULL;
		node->child = NULL;
		node->last_child = NULL;
		node->parent = NULL;
	}
	return node;
}
void zml_delete_node(zml_node *node)
{
	if (node != NULL)	
	{
		zml_safe_delete(node->name);
		zml_safe_delete(node->value);
		zml_safe_delete(node);
	}
}
void zml_delete_node_r(zml_node *node)
{
	if (node == NULL)
		return ;
	if (node->child != NULL)
		zml_delete_node_r(node->child);
	if (node->next != NULL)
		zml_delete_node_r(node->next);
	zml_delete_node(node);
}


int zml_init(zml *z)
{
	if (z == NULL)
		return -1;

	z->root = NULL;
	z->pos = NULL;
	z->pos_type = 0;
	return 0;
}
int zml_uninit(zml *z)
{
	if (z == NULL)
		return -1;

	zml_delete_node_r(z->root);
	return 0;
}

int zml_add_child(zml_node *child, zml_node *parent)
{
	if (parent->child == NULL)
		parent->child = child;
	else
		parent->last_child->next = child;
	parent->last_child = child;
	child->parent = parent;
	child->level = parent->level + 1;
	return 0;
}
int zml_add_sibling(zml_node *sibling, zml_node *node)
{
	sibling->next = node->next;
	sibling->parent = node->parent;
	sibling->level = node->level;
	node->next = sibling;
	if (node->parent != NULL)
		if (node->parent->last_child == node)
			node->parent->last_child = sibling;
	return 0;
}

#define zml_is_return(p) \
	(*p == '\r' && (p + 1) != NULL && *(p + 1) == '\n')
#define zml_is_nul_char(p) \
	(*p == '\0' || *p == ' ' || *p == '\t' || (*p == '\\' && (p + 1) != NULL && *(p + 1) == '\\') || (zml_is_return(p)))

const char *zml_find_colon(const char *start, const char *end)
{
	while (start < end)
	{
		if (*start == ':')
			return start;
		start++;
	}
	return NULL;
}
int zml_count_tab_move(const char **p)
{
	int sum = 0;
	while (*p != NULL && **p== '\t')
	{
		sum++;
		(*p)++;
	}
	return sum;
}

zml_node *zml_handle_oneline(const char **pos_string)
{
	zml_node *node = NULL;
	const char *pos_start = *pos_string;
	const char *pos_end = pos_start;
	const char *pos_colon = NULL;

	if (pos_string == NULL || *pos_string == NULL || **pos_string == '\0')
		return NULL;

	while (*pos_end!= '\0')			// find return or string end
	{
		if (zml_is_return(pos_end))
		{
			*pos_string = pos_end + 2;
			break;
		}
		pos_end++;
	}
	if (*pos_end == '\0')
	{
		*pos_string = pos_end;
	}

	while (pos_end > pos_start)		// find nul-char end
	{
		if (!zml_is_nul_char(pos_end))
			break;
		pos_end--;
	}
	if (pos_end <= pos_start)		// nothing to handle
		return NULL;

	if (*pos_start == '!')
	{
		// todo: handle configure
		return NULL;
	}

	node = zml_create_node();
	node->level = zml_count_tab_move(&pos_start);

	pos_colon = zml_find_colon(pos_start, pos_end);
	if (pos_colon == NULL)
		zml_mcopy_string(&node->name, pos_start, pos_end - pos_start + 1);
	else
	{
		zml_mcopy_string(&node->name, pos_start, pos_colon - pos_start);
		zml_mcopy_string(&node->value, pos_colon + 1, pos_end - pos_colon);
	}
	return node;
}

int zml_set_string(zml *z, const char *z_string)
{
	const char *newline = z_string;
	int level = 0;

	if (z == NULL || z_string == NULL)
		return -1;
	if (z->root != NULL)
		return -2;

	while (newline != NULL && *newline != '\0')
	{
		zml_node *node = zml_handle_oneline(&newline);
		if (node == NULL)
			continue;

		if (z->root == NULL)
		{
			z->root = node;
		}
		else if (node->level == level)		// add sibling
		{
			zml_add_sibling(node, z->pos);
		}
		else if (node->level == level + 1)		// add child
		{
			zml_add_child(node, z->pos);
		}
		else if (node->level == level - 1)		// add parent
		{
			zml_add_sibling(node, z->pos->parent);
		}
		else	// error relation
		{
			return -3;
		}

		level = node->level;
		z->pos = node;
	}

	z->pos = z->root;
	return 0;
}

int zml_get_string_r(zml_node *node, char *z_string)
{
	int ret = 0;
	int level = node->level;
	if (node == NULL || z_string == NULL)
		return -1;

	// return and add \t
	strcat(z_string, "\r\n");
	while (level-- > 0)
		strcat(z_string, "\t");

	strcat(z_string, node->name);
	if (node->child == NULL)
	{
		if (node->value != NULL && strlen(node->value) != 0)
		{
			strcat(z_string, ":");
			strcat(z_string, node->value);
		}
	}
	else
		ret = zml_get_string_r(node->child, z_string);

	if (node->next != NULL)
	{
		ret = zml_get_string_r(node->next, z_string);
	}
	return ret;
}

int zml_get_string(zml *z, char *z_string)
{
	if (z_string == NULL || z == NULL)
		return -1;

	strcat(z_string,
		"!zml\r\n"
		"!version:1.0");
	return zml_get_string_r(z->root, z_string);
}

int zml_add_node(zml *z, const char *name, const char *value)
{
	zml_node *node = NULL;

	if (z == NULL || name == NULL || value == NULL)
		return -1;

	node = zml_create_node();
	zml_mcopy_string(&node->name, name, strlen(name));
	zml_mcopy_string(&node->value, value, strlen(value));

	if (z->root == NULL)		// add root
	{
		node->level = 0;
		z->root = node;
	}
	else if (z->pos_type == 0)	// add sibling
	{
		zml_add_sibling(node, z->pos);
	}
	else		// add first child
	{
		zml_add_child(node, z->pos);
	}
	z->pos = node;
	z->pos_type = 0;
	return 0;
}

int zml_find_node(zml *z, const char *name)
{
	if (z == NULL || name == NULL)
		return -1;
	if (z->root == NULL || z->pos == NULL)
		return -2;
	if (z->pos_type != 0)
		return -3;

	while (z->pos != NULL)
	{
		if (strcmp(z->pos->name, name) == 0)
			return 0;
		z->pos = z->pos->next;
	}
	return -4;
}

const char *zml_get_name(zml *z)
{
	if (z != NULL && z->pos != NULL && z->pos_type == 0)
		return z->pos->name;
	else
		return NULL;
}

const char *zml_get_value(zml *z)
{
	if (z != NULL && z->pos != NULL && z->pos_type == 0)
		return z->pos->value;
	else
		return NULL;
}

int zml_move_in(zml *z)
{
	if (z == NULL)
		return -1;
	if (z->pos_type != 0)
		return -2;

	if (z->pos->child != NULL)
	{
		z->pos = z->pos->child;
	}
	else
	{
		z->pos_type = 1;
	}
	return 0;
}

int zml_move_out(zml *z)
{
	if (z == NULL)
		return -1;
	if (z->pos == NULL)
		return -2;

	if (z->pos_type != 0)
		z->pos_type = 0;
	else if (z->pos->parent != NULL)
		z->pos = z->pos->parent;
	else
		return -3;

	return 0;
}
