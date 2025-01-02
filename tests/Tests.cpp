#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../src/coreinc.h"
#include "../src/ColorScheme.h"
#include "../src/Syntax.h"
#include "../src/Editor.h"
#include "../src/Screen.h"
#include "../src/NormalMode.h"
#include "../src/Mouse.h"
#include "../src/File.h"
#include "../src/InsertMode.h"

using namespace std;
using ::testing::_;

class MockScreenHandler : public Screen {
public:
    MOCK_METHOD(void, Init, (), ());
    MOCK_METHOD(void, Move, (int y, int x), ());
    MOCK_METHOD(void, PrintScr,(Editor Edit),());
};

class MockNormalModeHandler : public Normal {
public:
    MOCK_METHOD(void, LineUp, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override));    
};

Editor Rep;

TEST(EditorTest, InsertText) {
    Rep.AddLine(0,"salam");
    EXPECT_EQ(Rep.Matn[0], "salam");
    Rep.AddCharacter(0, 1, 'c');
    EXPECT_EQ(Rep.Matn[0], "scalam");
}
TEST(EditorTest, DeleteText) {
    Rep.DeleteCharacter(0,2);
    EXPECT_EQ(Rep.Matn[0],"sclam");
    Rep.DeleteLine(0);
    EXPECT_EQ(Rep.Matn[0], "");
}
TEST(NormalModeTest, LineUp) {
    Editor Rep;
    MockScreenHandler RepScreen;
    MockNormalModeHandler RepNormal;
    for(int i = 0; i < 40; i ++) Rep.AddLine(i,to_string(i));
    int CurrentLine = 0, y = 0, x = 4;
    EXPECT_CALL(RepNormal, LineUp(_,_,_,_,_)).Times(1);
    RepNormal.SendKey(1, CurrentLine, x, y, RepScreen, Rep);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    endwin();
    return RUN_ALL_TESTS();
}