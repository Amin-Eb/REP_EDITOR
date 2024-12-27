#include <gtest/gtest.h>
#include "../src/Editor.cpp"

TEST(EditorTest, InsertText) {
    Editor editor;
    editor.AddLine(0,"salam");
    EXPECT_EQ(editor.Matn[0], "salam");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
