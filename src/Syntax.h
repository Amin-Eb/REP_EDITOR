using namespace std;
using json = nlohmann::json; 


class Syntax{
    public:
        TSParser* parser;
        TSTree* tree;
        TSNode RootNode;
        const int TwoDigits = 10;
        const int ThreeDigits = 100;
        uint32_t Ps[1000];
        map<string, int> ColorMap;
        Syntax(){
            void* handle = dlopen("./libtree-sitter-cpp.so", RTLD_NOW);
            TSLanguage* (*tree_sitter_cpp)() = (TSLanguage* (*)())dlsym(handle, "tree_sitter_cpp");
            parser = ts_parser_new();
            ts_parser_set_language(parser, tree_sitter_cpp());
            for(int i = 0 ; i < 1000; i ++)
                Ps[i] = 0;
        }
        void Build(string Str[],int LN);
        void DfsLine(TSNode Node,int CurrentLine,int ScreenLine,string SourceCode[]);
        void DfsScr(TSNode Node,int TheStart,int TheEnd,string SourceCode[]);
        void PrintLine(int CurrentLine,int ScreenLine, string SourceCode[]);
        void PrintScr(int TheStart,int TheEnd, string SourceCode[]);

};

void Syntax::Build(string Str[], int LN){
    string Temp = "";
    for (int i = 0 ; i < LN; i ++) {
        Temp += Str[i] + '\n';
        Ps[i+1] = Temp.size();
    }   
    tree = ts_parser_parse_string(parser, nullptr, Temp.c_str(), Temp.size());
    RootNode = ts_tree_root_node(tree);
}
void Syntax::DfsLine(TSNode Node,int CurrentLine,int ScreenLine,string SourceCode[]){
    if (ts_node_is_null(Node))
        return;
	const char* Type = ts_node_type(Node);
    uint32_t StartByte = ts_node_start_byte(Node);
    uint32_t EndByte = ts_node_end_byte(Node);
    uint32_t StartRow = ts_node_start_point(Node).row;
    uint32_t StartCol = ts_node_start_point(Node).column;
    uint32_t EndRow = ts_node_end_point(Node).row; 
    if(StartRow != EndRow || StartRow != CurrentLine || ts_node_child_count(Node) != 0){
        uint32_t child_count = ts_node_child_count(Node);
        for (uint32_t i = 0; i < child_count; ++i) {
            TSNode child = ts_node_child(Node, i);
            DfsLine(child, CurrentLine,ScreenLine,SourceCode);
        }
        return;
    }
    if (ColorMap.find(Type) != ColorMap.end()) {
        attron(COLOR_PAIR(ColorMap[Type]));
    }
    
	string rep = ""; 
	for(int i = StartByte; i < EndByte; i ++) rep += SourceCode[CurrentLine][i - Ps[CurrentLine]];
    move(ScreenLine, StartCol + 4);
    printw("%s", rep.c_str());
    if (ColorMap.find(Type) != ColorMap.end()) {
        attroff(COLOR_PAIR(ColorMap[Type]));
    }

    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; ++i) {
        TSNode child = ts_node_child(Node, i);
        DfsLine(child, CurrentLine, ScreenLine, SourceCode);
    }
}

void Syntax::PrintLine(int LineNumber,int ScreenLine,string SourceCode[]){
    TSPoint StartPoint = {LineNumber, 0}; 
    TSPoint EndPoint = {LineNumber + 1,0};
    TSNode Node = ts_node_named_descendant_for_point_range(RootNode, StartPoint, EndPoint);
    move(ScreenLine, 0);
    attron(COLOR_PAIR(1));
    if (LineNumber + 1 < TwoDigits)
        printw("%c", ' ');
    if (LineNumber + 1 < ThreeDigits)
        printw("%c", ' ');
    printw("%d ", LineNumber + 1);
    attroff(COLOR_PAIR(1));
    DfsLine(RootNode, LineNumber, ScreenLine, SourceCode);
    refresh();
}
void Syntax::DfsScr(TSNode Node,int TheStart,int TheEnd, string SourceCode[]){
    if (ts_node_is_null(Node))
        return;
	const char* Type = ts_node_type(Node);
    uint32_t StartByte = ts_node_start_byte(Node);
    uint32_t EndByte = ts_node_end_byte(Node);
    uint32_t StartRow = ts_node_start_point(Node).row;
    uint32_t StartCol = ts_node_start_point(Node).column;
    uint32_t EndRow = ts_node_end_point(Node).row; 
    if(StartRow > TheEnd || EndRow < TheStart || ts_node_child_count(Node) != 0){
        uint32_t child_count = ts_node_child_count(Node);
        for (uint32_t i = 0; i < child_count; ++i) {
            TSNode child = ts_node_child(Node, i);
            DfsScr(child, TheStart, TheEnd, SourceCode);
        }
        return;
    }

    if (ColorMap.find(Type) != ColorMap.end()) {
        attron(COLOR_PAIR(ColorMap[Type]));
    }
	string rep = ""; 
	for(int i = StartByte; i < EndByte; i ++) rep += SourceCode[StartRow][i - Ps[StartRow]];
    move(StartRow - TheStart, StartCol + 4);
    printw("%s", rep.c_str());
    if (ColorMap.find(Type) != ColorMap.end()) {
        attroff(COLOR_PAIR(ColorMap[Type]));
    }

    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; ++i) {
        TSNode child = ts_node_child(Node, i);
        DfsScr(child, TheStart, TheEnd, SourceCode);
    }
}
void Syntax::PrintScr(int TheStart,int TheEnd,string SourceCode[]){
    for (int i = TheStart, j = 0; i <= TheEnd; i++, j++) {
        move(j, 0);
        attron(COLOR_PAIR(1));
        if (i + 1 < TwoDigits)
            printw("%c", ' ');
        if (i + 1 < ThreeDigits)
            printw("%c", ' ');
        printw("%d ", i + 1);
        attroff(COLOR_PAIR(1));
    }
    TSPoint StartPoint = {TheStart, 0}; 
    TSPoint EndPoint = {TheEnd + 1,0};
    TSNode Node = ts_node_named_descendant_for_point_range(RootNode, StartPoint, EndPoint); 
    DfsScr(Node, TheStart, TheEnd, SourceCode);
    refresh();
}