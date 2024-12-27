#include <gtest/gtest.h>
#include "../src/Editor.cpp"

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
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}