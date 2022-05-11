// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 11/05/2022

#ifndef __AK_KILA_NODE_PARSER__
#define __AK_KILA_NODE_PARSER__

#include <Core/core.h>
#include "types.h"

namespace Ak::Kl
{
	using node_ptr = unique_ptr_w<class Node>;
	node_ptr parse_nodes_tree(class compiler_context& context, class tk_iterator& it, type_handle type_id, bool allow_comma);
}

#endif // __AK_KILA_NODE_PARSER__
