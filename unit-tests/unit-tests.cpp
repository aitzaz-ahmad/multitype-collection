#include "pch.h"
#include "CppUnitTest.h"
#include "configurations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{

	TEST_CLASS(unittests_property) {

		TEST_CLASS_INITIALIZE(initialize)
		{
			Logger::WriteMessage("unittests_property initialize()");
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			Logger::WriteMessage("unittests_property cleanup()");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(empty_property)
			TEST_OWNER(L"Aitzaz Ahmad")
			TEST_DESCRIPTION(L"Default constructed property must be empty")
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(empty_property)
		{
			Logger::WriteMessage("Running unittests_property - empty_property");
			const auto config_property = property{};

			Assert::IsTrue(config_property.hash_key().empty(),
						   L"config_property.hash_key() is not empty");
			
			const auto optional = config_property.get_as<std::string>();
			Assert::IsFalse(optional.has_value(),
							L"config_property.get_as<std::string>() is not std::optional<std::string>{}");
		}
		
		BEGIN_TEST_METHOD_ATTRIBUTE(property_with_boolean_value)
			TEST_OWNER(L"Aitzaz Ahmad")
			TEST_DESCRIPTION(L"Construct a property with a bool value")
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(property_with_boolean_value)
		{
			Logger::WriteMessage("Running unittests_property - property_with_boolean_value");
			const auto config_property = property{"attribute", true};

			Assert::IsFalse(config_property.hash_key().empty(),
							L"config_property.hash_key() is empty");

			const auto optional = config_property.get_as<bool>();
			Assert::IsTrue(optional.has_value(),
						   L"config_property.get_as<bool>() is std::optional<bool>{}");

			Assert::IsTrue(typeid(optional.value()) == typeid(bool),
						   L"optional.value() is not a bool");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(property_with_double_value)
			TEST_OWNER(L"Aitzaz Ahmad")
			TEST_DESCRIPTION(L"Construct a property with a double value")
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(property_with_double_value)
		{
			Logger::WriteMessage("Running unittests_property - property_with_double_value");
			const auto config_property = property{ "attribute", double{ 12 } };

			Assert::IsFalse(config_property.hash_key().empty(),
							L"config_property.hash_key() is empty");

			const auto optional = config_property.get_as<double>();
			Assert::IsTrue(optional.has_value(),
						   L"config_property.get_as<double>() is std::optional<double>{}");

			Assert::IsTrue(typeid(optional.value()) == typeid(double),
						   L"optional.value() is not a double");

			Assert::AreEqual(optional.value(),
							 double{ 12 },
							 0.002, //tolerance
							 L"optional.value() != double{ 12 }");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(property_with_int32_value)
			TEST_OWNER(L"Aitzaz Ahmad")
			TEST_DESCRIPTION(L"Construct a property with a int32 value")
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(property_with_int32_value)
		{
			Logger::WriteMessage("Running unittests_property - property_with_int32_value");
			const auto config_property = property{ "attribute", int32_t{ INT32_MAX } };

			Assert::IsFalse(config_property.hash_key().empty(),
							L"config_property.hash_key() is empty");

			const auto optional = config_property.get_as<int32_t>();
			Assert::IsTrue(optional.has_value(),
						   L"config_property.get_as<int32_t>() is std::optional<int32_t>{}");

			Assert::IsTrue(typeid(optional.value()) == typeid(int32_t),
						   L"optional.value() is not a int32_t");

			Assert::AreEqual(optional.value(),
							 INT32_MAX,
							 L"optional.value() != INT32_MAX");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(property_with_string_value)
			TEST_OWNER(L"Aitzaz Ahmad")
			TEST_DESCRIPTION(L"Construct a property with a string value")
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(property_with_string_value)
		{
			Logger::WriteMessage("Running unittests_property - property_with_string_value");
			const auto config_property = property{ "attribute", std::string{ "hello world!" }};

			Assert::IsFalse(config_property.hash_key().empty(),
							L"config_property.hash_key() is empty");

			const auto optional = config_property.get_as<std::string>();
			Assert::IsTrue(optional.has_value(),
						   L"config_property.get_as<std::string>() is std::optional<std::string>{}");

			Assert::IsTrue(typeid(optional.value()) == typeid(std::string),
						   L"optional.value() is not a std::string");

			Assert::AreEqual(optional.value(),
							 std::string{ "hello world!" },
							 L"optional.value() != std::string{ \"hello world!\" }");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(property_with_user_defined_type_as_value)
			TEST_OWNER(L"Aitzaz Ahmad")
			TEST_DESCRIPTION(L"Construct a property with a user-defined type as value")
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(property_with_user_defined_type_as_value)
		{
			Logger::WriteMessage("Running unittests_property - property_with_user_defined_type_as_value");

			struct employee {

				int id{};
				std::string last_name{};
			};

			const auto config_property = property{ "attribute", employee{ 612, "Smith" } };

			Assert::IsFalse(config_property.hash_key().empty(),
							L"config_property.hash_key() is empty");

			const auto optional = config_property.get_as<employee>();
			Assert::IsTrue(optional.has_value(),
						   L"config_property.get_as<employee>() is std::optional<employee>{}");

			Assert::IsTrue(typeid(optional.value()) == typeid(employee),
						   L"optional.value() is not an employee");

			const auto& emp1 = optional.value();
			Assert::AreEqual(emp1.id,
							 612,
							 L"emp.id != 612");
			Assert::AreEqual(emp1.last_name,
							 std::string{ "Smith" },
							 L"emp.last_name != \"Smith\"");
		}
	};
}
