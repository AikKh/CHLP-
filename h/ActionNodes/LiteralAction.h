#pragma once

#include "../ActionNode.h"
#include "../MemoryManagement/ObjectGenerator.h"

namespace Doer {

	class LiteralAction : public ActionNode {
	public:
		LiteralAction(const string& text, bool is_boolean) : m_text{ text }, m_type{ Type::INT }
		{
			if (is_boolean)
			{
				m_type = Type::BOOL;
			}
			else
			{
				// Deducing literal type, string is yet missing
				for (char c : text)
				{
					if (c == '.') 
					{
						m_type = Type::FLOAT;
					}
				}
			}
		}

		shared_ptr<Object> Execute() const override 
		{
			bool is_true{};

			try 
			{
				switch (m_type)
				{
				case Doer::Type::INT:
					return ObjectGenerator::GenerateInt(std::stoi(m_text));

				case Doer::Type::FLOAT:
					return ObjectGenerator::GenerateFloat(std::stof(m_text));

				case Doer::Type::BOOL:
					is_true = (m_text == "true");
					return ObjectGenerator::GenerateBool(is_true);

				case Doer::Type::NONE:
				default:
					throw;
				}
			}
			catch (...)
			{
				error.Report("Invalid literal value " + m_text, ErrorPriority::SOURCE_ERROR);
				return nullptr;
			}
		}

	private:
		const string& m_text;
		Type m_type;
	};
}
