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

TEST(EditorTest, InsertText) {
    Editor editor;
    editor.AddLine(0,"salam");
    EXPECT_EQ(editor.Matn[0], "salam");
    editor.AddCharacter(0, 1, 'c');
    EXPECT_EQ(editor.Matn[0], "scalam");
}
TEST(EditorTest, DeleteText) {
    Editor editor;
    editor.AddLine(0,"salam");
    editor.DeleteCharacter(0,2);
    EXPECT_EQ(editor.Matn[0],"saam");
    editor.DeleteLine(0);
    EXPECT_EQ(editor.Matn[0], "");
}
TEST(ScreenTest, MoveCursor) {
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}