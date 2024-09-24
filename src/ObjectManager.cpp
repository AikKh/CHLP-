#include "../h/Interpretation/ObjectManager.h"
#include "../h/MemoryManagement/ObjectGenerator.h"

namespace Doer
{
    std::unique_ptr<ObjectManager::OperationMap> Doer::ObjectManager::InitializeMap()
    {
        auto map = std::make_unique<OperationMap>();

        // Int Int
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::ADD)] = &Operation<int, int, int, MethodType::ADD>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::SUB)] = &Operation<int, int, int, MethodType::SUB>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::MUL)] = &Operation<int, int, int, MethodType::MUL>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::DIV)] = &Operation<int, int, float, MethodType::DIV>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::MOD)] = &Operation<int, int, int, MethodType::MOD>;

        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::EQUAL)] =         &Operation<int, int, bool, MethodType::EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::NOT_EQUAL)] =     &Operation<int, int, bool, MethodType::NOT_EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::GREATER_EQUAL)] = &Operation<int, int, bool, MethodType::GREATER_EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::GREATER_THEN)] =  &Operation<int, int, bool, MethodType::GREATER_THEN>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::LESS_EQUAL)] =    &Operation<int, int, bool, MethodType::LESS_EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::LESS_THEN)] =     &Operation<int, int, bool, MethodType::LESS_THEN>;

        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::OR)] =  &Operation<int, int, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::INT, Type::INT, MethodType::AND)] = &Operation<int, int, bool, MethodType::AND>;

        // Float Float
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::ADD)] =   &Operation<float, float, float, MethodType::ADD>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::SUB)] =   &Operation<float, float, float, MethodType::SUB>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::MUL)] =   &Operation<float, float, float, MethodType::MUL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::DIV)] =   &Operation<float, float, float, MethodType::DIV>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::MOD)] =   &Operation<float, float, float, MethodType::MOD>;

        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::EQUAL)] =         &Operation<float, float, bool, MethodType::EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::NOT_EQUAL)] =     &Operation<float, float, bool, MethodType::NOT_EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::GREATER_EQUAL)] = &Operation<float, float, bool, MethodType::GREATER_EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::GREATER_THEN)] =  &Operation<float, float, bool, MethodType::GREATER_THEN>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::LESS_EQUAL)] =    &Operation<float, float, bool, MethodType::LESS_EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::LESS_THEN)] =     &Operation<float, float, bool, MethodType::LESS_THEN>;

        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::OR)] =  &Operation<float, float, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::FLOAT, Type::FLOAT, MethodType::AND)] = &Operation<float, float, bool, MethodType::AND>;

        // Float Int
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::ADD)] = &Operation<float, int, float, MethodType::ADD>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::SUB)] = &Operation<float, int, float, MethodType::SUB>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::MUL)] = &Operation<float, int, float, MethodType::MUL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::DIV)] = &Operation<float, int, float, MethodType::DIV>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::MOD)] = &Operation<float, int, float, MethodType::MOD>;

        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::EQUAL)] =         &Operation<float, int, bool, MethodType::EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::NOT_EQUAL)] =     &Operation<float, int, bool, MethodType::NOT_EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::GREATER_EQUAL)] = &Operation<float, int, bool, MethodType::GREATER_EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::GREATER_THEN)] =  &Operation<float, int, bool, MethodType::GREATER_THEN>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::LESS_EQUAL)] =    &Operation<float, int, bool, MethodType::LESS_EQUAL>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::LESS_THEN)] =     &Operation<float, int, bool, MethodType::LESS_THEN>;

        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::OR)] =  &Operation<float, int, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::FLOAT, Type::INT, MethodType::AND)] = &Operation<float, int, bool, MethodType::AND>;

        // Int Float
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::ADD)] = &Operation<int, float, float, MethodType::ADD>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::SUB)] = &Operation<int, float, float, MethodType::SUB>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::MUL)] = &Operation<int, float, float, MethodType::MUL>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::DIV)] = &Operation<int, float, float, MethodType::DIV>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::MOD)] = &Operation<int, float, float, MethodType::MOD>;

        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::EQUAL)] =         &Operation<int, float, bool, MethodType::EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::NOT_EQUAL)] =     &Operation<int, float, bool, MethodType::NOT_EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::GREATER_EQUAL)] = &Operation<int, float, bool, MethodType::GREATER_EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::GREATER_THEN)] =  &Operation<int, float, bool, MethodType::GREATER_THEN>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::LESS_EQUAL)] =    &Operation<int, float, bool, MethodType::LESS_EQUAL>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::LESS_THEN)] =     &Operation<int, float, bool, MethodType::LESS_THEN>;

        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::OR)] =  &Operation<int, float, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::INT, Type::FLOAT, MethodType::AND)] = &Operation<int, float, bool, MethodType::AND>;

        // Int Bool
        (*map)[std::make_tuple(Type::INT, Type::BOOL, MethodType::OR)] =  &Operation<int, bool, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::INT, Type::BOOL, MethodType::AND)] = &Operation<int, bool, bool, MethodType::AND>;

        // Bool Int
        (*map)[std::make_tuple(Type::BOOL, Type::INT, MethodType::OR)] =  &Operation<bool, int, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::BOOL, Type::INT, MethodType::AND)] = &Operation<bool, int, bool, MethodType::AND>;

        // FLoat Bool
        (*map)[std::make_tuple(Type::FLOAT, Type::BOOL, MethodType::OR)] =  &Operation<float, bool, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::FLOAT, Type::BOOL, MethodType::AND)] = &Operation<float, bool, bool, MethodType::AND>;

        // Bool Float
        (*map)[std::make_tuple(Type::BOOL, Type::FLOAT, MethodType::OR)] =  &Operation<bool, float, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::BOOL, Type::FLOAT, MethodType::AND)] = &Operation<bool, float, bool, MethodType::AND>;

        // Bool Bool
        (*map)[std::make_tuple(Type::BOOL, Type::BOOL, MethodType::OR)] =        &Operation<bool, bool, bool, MethodType::OR>;
        (*map)[std::make_tuple(Type::BOOL, Type::BOOL, MethodType::AND)] =       &Operation<bool, bool, bool, MethodType::AND>;
        (*map)[std::make_tuple(Type::BOOL, Type::BOOL, MethodType::EQUAL)] =     &Operation<bool, bool, bool, MethodType::EQUAL>;
        (*map)[std::make_tuple(Type::BOOL, Type::BOOL, MethodType::NOT_EQUAL)] = &Operation<bool, bool, bool, MethodType::NOT_EQUAL>;

        return map;
    }

    ObjectManager::OperationFunction ObjectManager::Lookup(Type t1, Type t2, MethodType mt)
    {
        static auto operationMap = InitializeMap();

        OperationMap::iterator entry = operationMap->find({ t1, t2, mt });

        if (entry == operationMap->end())
            return nullptr;
        return (*entry).second;
    }

    template<typename T1, typename T2, typename T3, MethodType method>
    inline Doer::Object::ObjectPtr Doer::ObjectManager::Operation(Doer::Object::ObjectPtr a, Doer::Object::ObjectPtr b)
    {
        T3 value;
        
        if constexpr (method == MethodType::ADD)
        {
            value = *((T1*)a->GetPtr()) + *((T2*)b->GetPtr());
        }
        else if constexpr (method == MethodType::SUB)
        {
            value = *((T1*)a->GetPtr()) - *((T2*)b->GetPtr());
        }
        else if constexpr (method == MethodType::MUL)
        {
            value = *((T1*)a->GetPtr()) * *((T2*)b->GetPtr());
        }
        else if constexpr (method == MethodType::DIV)
        {
            T2 divisor = *((T2*)b->GetPtr());
            if (!divisor)
            {
                error.Report("Division by zero", ErrorPriority::RUNTIME_ERROR);
                return nullptr;
            }
            float float_divisor = divisor;
            value = *((T1*)a->GetPtr()) / float_divisor;
        }
        else if constexpr (method == MethodType::MOD)
        {
            T2 divisor = *((T2*)b->GetPtr());
            if (!divisor)
            {
                error.Report("Modulus by zero", ErrorPriority::RUNTIME_ERROR);
                return nullptr;
            }
            value = std::fmod(static_cast<decltype(value)>(*((T1*)a->GetPtr())), divisor);
        }
        else if constexpr (method == MethodType::EQUAL)
        {
            value = (*((T1*)a->GetPtr()) == *((T2*)b->GetPtr()));
        }
        else if constexpr (method == MethodType::NOT_EQUAL)
        {
            value = (*((T1*)a->GetPtr()) != *((T2*)b->GetPtr()));
        }
        else if constexpr (method == MethodType::GREATER_EQUAL)
        {
            value = (*((T1*)a->GetPtr()) >= *((T2*)b->GetPtr()));
        }
        else if constexpr (method == MethodType::GREATER_THEN)
        {
            value = (*((T1*)a->GetPtr()) > *((T2*)b->GetPtr()));
        }
        else if constexpr (method == MethodType::LESS_EQUAL)
        {
            value = (*((T1*)a->GetPtr()) <= *((T2*)b->GetPtr()));
        }
        else if constexpr (method == MethodType::LESS_THEN)
        {
            value = (*((T1*)a->GetPtr()) < *((T2*)b->GetPtr()));
        }
        else if constexpr (method == MethodType::OR)
        {
            value = (*((T1*)a->GetPtr()) || *((T2*)b->GetPtr()));
        }
        else if constexpr (method == MethodType::AND)
        {
            value = (*((T1*)a->GetPtr()) && *((T2*)b->GetPtr()));
        }
        else 
        {
            throw std::logic_error("Object manager failed to perform operation");
        }
            

        if constexpr (std::is_same_v<T3, float>)
        {
            return ObjectGenerator::GenerateFloat(value);
        }
        else if constexpr (std::is_same_v<T3, int>)
        {
            return ObjectGenerator::GenerateInt(value);
        }
        else if constexpr (std::is_same_v<T3, bool>)
        {
            return ObjectGenerator::GenerateBool(value);
        }
        else
        {
            throw std::logic_error("Object manager failed to deduce type");
        }
    }


}