#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cpp_free_mock.h>

using namespace ::std;
using namespace ::testing;

struct OriginalClass {
    string func0Parameter() {
        return "Non mocked.";
    }

    string func0Parameter2() {
        return "Non mocked.";
    }

    //non-implemented function
    string non_implementedFunc();

    //virtial function
    virtual string non_implementedFunc2();
};

//Mocking class
struct TestMockStruct: public OriginalClass {

    //Mock non-implemented function
    MOCK_METHOD(string, non_implementedFunc, ());
    //Mock virtual non-implemented function
    MOCK_METHOD(string, non_implementedFunc2, (), (override));

};

//Test fixture used to configure the test suites
struct TestMemberFunction : public ::testing::Test {
    virtual void SetUp() { }
    virtual void TearDown() {
        CLEAR_MOCKER();
    }
};

//Test case to test CppFreeMock::RestoreToReal()
TEST_F(TestMemberFunction, RestoreToReal) {
    TestMockStruct mockStruct;
    auto mocker = MOCKER(&TestMockStruct::func0Parameter);
    EXPECT_CALL(*mocker, MOCK_FUNCTION(&mockStruct))
        .Times(Exactly(1))
        .WillOnce(Return("Hello world."));
    EXPECT_EQ("Hello world.", mockStruct.func0Parameter());
    mocker->RestoreToReal();
    EXPECT_EQ("Non mocked.", mockStruct.func0Parameter());
}

//Test case to test mocking of non-implemented functions
TEST_F(TestMemberFunction, NonImplemented) {
    TestMockStruct mockStruct;
    auto mocker = MOCKER(&TestMockStruct::non_implementedFunc);
    EXPECT_CALL(*mocker, MOCK_FUNCTION(&mockStruct))
        .Times(Exactly(1))
        .WillOnce(Return("Test 123"));

    auto result = mockStruct.non_implementedFunc();

    EXPECT_EQ(result, "Test 123");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
