#include <cstdint>
#include <string>
#include <typeinfo>

#include <gtest/gtest.h>

#include "configurations.h"

namespace {

class PropertyTest : public ::testing::Test {
  protected:
    static void SetUpTestSuite() {
        std::cout << "PropertyTest SetUpTestSuite()\n";
    }

    static void TearDownTestSuite() {
        std::cout << "PropertyTest TearDownTestSuite()\n";
    }
};

TEST_F(PropertyTest, EmptyProperty) {
    SCOPED_TRACE("Default constructed property must be empty");

    const auto config_property = property{};

    EXPECT_TRUE(config_property.hash_key().empty()) << "config_property.hash_key() is not empty";

    const auto optional = config_property.get_as<std::string>();
    EXPECT_FALSE(optional.has_value()) << "config_property.get_as<std::string>() is not std::optional<std::string>{}";
}

TEST_F(PropertyTest, PropertyWithBooleanValue) {
    SCOPED_TRACE("Construct a property with a bool value");

    const auto config_property = property{"attribute", true};

    EXPECT_FALSE(config_property.hash_key().empty()) << "config_property.hash_key() is empty";

    const auto optional = config_property.get_as<bool>();
    ASSERT_TRUE(optional.has_value()) << "config_property.get_as<bool>() is std::optional<bool>{}";

    EXPECT_TRUE(typeid(optional.value()) == typeid(bool)) << "optional.value() is not a bool";
}

TEST_F(PropertyTest, PropertyWithDoubleValue) {
    SCOPED_TRACE("Construct a property with a double value");

    const auto config_property = property{"attribute", double{12}};

    EXPECT_FALSE(config_property.hash_key().empty()) << "config_property.hash_key() is empty";

    const auto optional = config_property.get_as<double>();
    ASSERT_TRUE(optional.has_value()) << "config_property.get_as<double>() is std::optional<double>{}";

    EXPECT_TRUE(typeid(optional.value()) == typeid(double)) << "optional.value() is not a double";

    EXPECT_NEAR(optional.value(), double{12}, 0.002) << "optional.value() != double{ 12 }";
}

TEST_F(PropertyTest, PropertyWithInt32Value) {
    SCOPED_TRACE("Construct a property with an int32 value");

    const auto config_property = property{"attribute", int32_t{INT32_MAX}};

    EXPECT_FALSE(config_property.hash_key().empty()) << "config_property.hash_key() is empty";

    const auto optional = config_property.get_as<int32_t>();
    ASSERT_TRUE(optional.has_value()) << "config_property.get_as<int32_t>() is std::optional<int32_t>{}";

    EXPECT_TRUE(typeid(optional.value()) == typeid(int32_t)) << "optional.value() is not an int32_t";

    EXPECT_EQ(optional.value(), INT32_MAX) << "optional.value() != INT32_MAX";
}

TEST_F(PropertyTest, PropertyWithStringValue) {
    SCOPED_TRACE("Construct a property with a string value");

    const auto config_property = property{"attribute", std::string{"hello world!"}};

    EXPECT_FALSE(config_property.hash_key().empty()) << "config_property.hash_key() is empty";

    const auto optional = config_property.get_as<std::string>();
    ASSERT_TRUE(optional.has_value()) << "config_property.get_as<std::string>() is std::optional<std::string>{}";

    EXPECT_TRUE(typeid(optional.value()) == typeid(std::string)) << "optional.value() is not a std::string";

    EXPECT_EQ(optional.value(), std::string{"hello world!"}) << "optional.value() != std::string{ \"hello world!\" }";
}

TEST_F(PropertyTest, PropertyWithUserDefinedTypeAsValue) {
    SCOPED_TRACE("Construct a property with a user-defined type as value");

    struct employee {
        int id{};
        std::string last_name{};
    };

    const auto config_property = property{"attribute", employee{612, "Smith"}};

    EXPECT_FALSE(config_property.hash_key().empty()) << "config_property.hash_key() is empty";

    const auto optional = config_property.get_as<employee>();
    ASSERT_TRUE(optional.has_value()) << "config_property.get_as<employee>() is std::optional<employee>{}";

    EXPECT_TRUE(typeid(optional.value()) == typeid(employee)) << "optional.value() is not an employee";

    const auto& emp1 = optional.value();
    EXPECT_EQ(emp1.id, 612) << "emp.id != 612";
    EXPECT_EQ(emp1.last_name, std::string{"Smith"}) << "emp.last_name != \"Smith\"";
}

class ConfigurationsTest : public ::testing::Test {
  protected:
    static void SetUpTestSuite() {
        std::cout << "ConfigurationsTest SetUpTestSuite()\n";
    }

    static void TearDownTestSuite() {
        std::cout << "ConfigurationsTest TearDownTestSuite()\n";
    }
};

TEST_F(ConfigurationsTest, InsertPropertyIfUnique) {
    SCOPED_TRACE("Only unique properties can be inserted to configurations object");

    auto app_config = configurations{};
    EXPECT_FALSE(app_config.exists("version"));

    app_config.insert(property{"version", std::string{"0.1.0"}});
    EXPECT_TRUE(app_config.exists("version")) << "app_config does not contain any property against the key \"version\"";

    auto version1 = app_config.get_value<std::string>("version");
    ASSERT_TRUE(version1.has_value()) << "app_config.get_value<std::string>(\"version\") has no value";
    EXPECT_EQ(version1.value(), "0.1.0")
        << "version mismatch: app_config.get_value<std::string>(\"version\").value() != \"0.1.0\"";

    app_config.insert(property{"version", std::string{"0.1.1"}});
    const auto version2 = app_config.get_value<std::string>("version");
    ASSERT_TRUE(version2.has_value()) << "app_config.get_value<std::string>(\"version\") has no value";

    EXPECT_NE(version2.value(), "0.1.1") << "the \"version\" property was overwritten in app_config";
    EXPECT_EQ(version2.value(), version1.value()) << "the \"version\" property was overwritten in app_config";
}

TEST_F(ConfigurationsTest, DoNotInsertEmptyProperty) {
    SCOPED_TRACE("do_not_insert_empty_property");

    auto app_config = configurations{};
    const auto empty = property{};
    app_config.insert(empty);

    EXPECT_FALSE(app_config.exists(empty.hash_key()))
        << "configurations must not allow the insertion of a default-constructed property";
}

TEST_F(ConfigurationsTest, DoNotInsertPropertyWithEmptyKey) {
    SCOPED_TRACE("do_not_insert_property_with_empty_key");

    auto app_config = configurations{};
    app_config.insert(property{"", std::string{"orphan"}});

    EXPECT_FALSE(app_config.exists(""))
        << "configurations must not allow the insertion of a property with an empty key";
}

} // namespace
