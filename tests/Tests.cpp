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
using json = nlohmann::json;

class MockScreenHandler : public Screen {
public:
    MOCK_METHOD(void, Init, (), ());
    MOCK_METHOD(void, Move, (int y, int x), ());
    MOCK_METHOD(void, PrintScr,(Editor Edit),());
};

class MockEditorHandler : public Editor {
public:
    MOCK_METHOD(void, AddLine, (int Line, std::string Str), (override));
	MOCK_METHOD(void, AddCharacter, (int Line, int Position, char Character), (override));
	MOCK_METHOD(void, DeleteLine, (int Line), (override));
    MOCK_METHOD(void, DeleteCharacter, (int Line, int Position), (override));
};

class MockNormalModeHandler : public Normal {
public:
    MOCK_METHOD(void, LineUp, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override)); 
    MOCK_METHOD(void , LineDown, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override));
    MOCK_METHOD(void , Right, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override));
    MOCK_METHOD(void, Left, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override)); 
    MOCK_METHOD(void , Home, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override));
    MOCK_METHOD(void , PageUp, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override));   
    MOCK_METHOD(void, PageDown, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override)); 
    MOCK_METHOD(void , EndPage, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override));
    MOCK_METHOD(void , Enter, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
                Editor& Rep), (override));      
};

class MockInsertModeHandler : public Insert {
public:
    MOCK_METHOD(void, LineDown, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep), (override));
    MOCK_METHOD(void, Enter, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep), (override));
    MOCK_METHOD(void, BackSpace, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep), (override));
    MOCK_METHOD(void, NewChar, (char ch,int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep), (override));

    MOCK_METHOD(void, LineUp, (int& CurrentLine, int& x, int& y, Screen& RepScreen,
				Editor& Rep), (override));
};

MockScreenHandler RepScreen;

TEST(MouseTest, Click) {
    int x = 4, y = 0, x2 , y2, CurrentLine = 0, mode = 1;
    Mouse RepMouse;
    Normal RepNormal;
    Editor Rep;
    RepMouse.Press(x, y, x2, y2, CurrentLine, RepScreen,Rep, mode, RepNormal, 1);
}
TEST(FileTest, OpenNotExisted) {
    Editor Rep;
    File RepFile("color.json2");
    if (RepFile.Open("color.json2", Rep) == false) {
        Rep.AddLine(0, "");
    }
}
TEST(FileTest, OpenExisted){
    Editor Rep;
    File RepFile("color.json");
    if (RepFile.Open("color.json", Rep) == false) {
        Rep.AddLine(0, "");
    }
    EXPECT_EQ(Rep.Matn[0], "{");
}
TEST(EditorTest, InsertText) {
    Editor Rep;
    Rep.AddLine(0,"salam");
    EXPECT_EQ(Rep.Matn[0], "salam");
    Rep.AddCharacter(0, 1, 'c');
    EXPECT_EQ(Rep.Matn[0], "scalam");
}

TEST(EditorTest, DeleteText) {
    Editor Rep;
    Rep.AddLine(0,"salam");
    Rep.AddCharacter(0, 1, 'c');
    Rep.DeleteCharacter(0,2);
    EXPECT_EQ(Rep.Matn[0],"sclam");
    Rep.DeleteLine(0);
    EXPECT_EQ(Rep.Matn[0], "");
}

TEST(NormalModeTest, SendKeyFunctionality) {
    MockNormalModeHandler RepNormal;
    int CurrentLine = 0, y = 0, x = 4;
    Editor Rep;
    EXPECT_CALL(RepNormal, LineUp(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, LineDown(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, Right(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, Left(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, Home(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, PageUp(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, PageDown(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, EndPage(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepNormal, Enter(_,_,_,_,_)).Times(1);

    RepNormal.SendKey(1, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(2, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(3, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(4, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(5, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(6, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(7, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(8, CurrentLine, x, y, RepScreen, Rep);
    RepNormal.SendKey(9, CurrentLine, x, y, RepScreen, Rep);   
}

TEST(NormalMode, LineUp){
    Editor Rep;
    int CurrentLine = 0, x = 4, y = 0;
    Normal RepNormal;
    RepNormal.LineUp(CurrentLine, x, y, RepScreen, Rep);
    EXPECT_EQ(CurrentLine, 0);
    EXPECT_EQ(y, 0);
}
TEST(InsertModeTest, SendKeyFunctionality) {
    Editor Rep;
    MockInsertModeHandler RepInsert;
    int CurrentLine, x, y;

    EXPECT_CALL(RepInsert, Enter(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepInsert, BackSpace(_,_,_,_,_)).Times(1);
    EXPECT_CALL(RepInsert, NewChar(_,_,_,_,_,_)).Times(1);

    CurrentLine = 0, x = 4, y = 0;
    RepInsert.SendKey(10, CurrentLine, x, y, RepScreen, Rep);
    CurrentLine = 1, x = 4, y = 1;
    RepInsert.SendKey(0, CurrentLine, CurrentLine, y, RepScreen, Rep);
    CurrentLine = 0, x = 4, y = 0;
    RepInsert.SendKey('a', CurrentLine, x, y, RepScreen, Rep);
}
TEST(InsertModeTest, Enter) {
    MockEditorHandler Rep;
    Insert RepInsert;
    int CurrentLine = 0, x = 4, y = 0;
    RepInsert.Enter(CurrentLine, x, y, RepScreen, Rep);
    EXPECT_EQ(CurrentLine, 1);
    EXPECT_EQ(y, 1);
}
TEST(InsertModeTest, BackSpace) {
    MockEditorHandler Rep;
    Insert RepInsert;
    int CurrentLine = 1, x = 4, y = 1;
    RepInsert.BackSpace(CurrentLine, x, y, RepScreen, Rep);
    EXPECT_EQ(CurrentLine, 0);
    EXPECT_EQ(y, 0);
}
TEST(InsertModeTest, LineUp) {
    MockEditorHandler Rep;
    Insert RepInsert;
    int CurrentLine = 0, x = 5, y = 6;
    RepInsert.LineDown(CurrentLine, x, y, RepScreen, Rep);
    EXPECT_EQ(CurrentLine, 1);
    EXPECT_EQ(y, 7);
    EXPECT_EQ(x, 5);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    endwin();
    return RUN_ALL_TESTS();
}