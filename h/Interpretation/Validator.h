#pragma once

#include "../MemoryManagement/Object.h"
#include "../NodeTypes/LeafNode.h"

namespace Doer {

	class Validator {
	public:
		bool IsVariable(const Node* node) const
		{
			const HasValue* has_value;
			const LeafNode* leaf_node;
			
			if (has_value = dynamic_cast<const HasValue*>(node))
			{
				if (leaf_node = dynamic_cast<const LeafNode*>(node))
				{
					if (leaf_node->GetValue().GetType() == Token::IDENTIFIER)
					{
						return true;
					}

					auto& token = leaf_node->GetValue();
					error.ReportAt("Can't assign anything to " + token.GetText(), ErrorPriority::SOURCE_ERROR, token.Line, token.Column);
					return false;
				}

				auto& token = has_value->GetValue();
				error.ReportAt("Are you invalid? What is this", ErrorPriority::SOURCE_ERROR, token.Line, token.Column);
				return false;
			}

			error.Report("WTF is even that", ErrorPriority::SOURCE_ERROR);
			return false;
		}
	};
}
