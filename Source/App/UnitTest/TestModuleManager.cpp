//
// Created by WeslyChen on 2024/1/19.
//

#include "gtest/gtest.h"
#include "Module/ModuleSingleton.h"

static int gStackCount = 0;

class TestModule01 final : public Module::IModule
{
    SINGLETON_MODULE(TestModule01)

public:
    void StartupModule() override { EXPECT_TRUE(gStackCount++ == 2); }
    void ShutdownModule() override { EXPECT_TRUE(--gStackCount == 2); }
};
class TestModule02 final : public Module::IModule
{
    SINGLETON_MODULE(TestModule02)

public:
    void StartupModule() override { EXPECT_TRUE(gStackCount++ == 1); }
    void ShutdownModule() override { EXPECT_TRUE(--gStackCount == 1); }

public:
    void Get01() { TestModule01::instance(); }
};
class TestModule03 final : public Module::IModule
{
    SINGLETON_MODULE(TestModule03)

public:
    void StartupModule() override { EXPECT_TRUE(gStackCount++ == 3); }
    void ShutdownModule() override { EXPECT_TRUE(--gStackCount == 3); }

public:
    void Get01() { TestModule01::instance(); }
};
class TestModule04 final : public Module::IModule
{
    SINGLETON_MODULE(TestModule04)

public:
    void StartupModule() override { EXPECT_TRUE(gStackCount++ == 0); }
    void ShutdownModule() override { EXPECT_TRUE(--gStackCount == 0); }

public:
    void Get0203()
    {
        TestModule02::instance()->Get01();
        TestModule03::instance()->Get01();
    }
};

TEST(ModuleManager, Register)
{
    TestModule04::instance()->Get0203();
    Module::GetManager()->UnregisterAll();
}