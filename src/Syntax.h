using namespace std;

class Syntax{
    public:
        TSParser* parser;
        TSTree* tree;
        TSNode RootNode;
        uint32_t Ps[2000];
        Syntax(){
            void* handle = dlopen("/home/aebov/Desktop/REP_EDITOR/tree-sitter-cpp.so", RTLD_NOW);
            TSLanguage* (*tree_sitter_cpp)() = (TSLanguage* (*)())dlsym(handle, "tree_sitter_cpp");
            parser = ts_parser_new();
            ts_parser_set_language(parser, tree_sitter_cpp());
            for(int i = 0 ; i < 2000; i ++)
                Ps[i] = 0;
        }
        void Build(string Str[],int LN);
        void DfsLine(TSNode Node,int CurrentLine,string source_code[]);
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
void Syntax::DfsLine(TSNode Node,int CurrentLine,string source_code[]){
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
            DfsLine(child, CurrentLine, source_code);
        }
        return;
    }
    if (strcmp(Type, "declaration_unit") == 0) {
        attron(COLOR_PAIR(1));
    } else if (strcmp(Type, "identifier") == 0) {
        attron(COLOR_PAIR(2));
    } else if (strcmp(Type, "primitive_type") == 0) {
        attron(COLOR_PAIR(3));
    }
	string rep = ""; 
	for(int i = StartByte; i < EndByte; i ++) rep += source_code[CurrentLine][i - Ps[CurrentLine]];
    move(StartRow, StartCol);
    printw("%s", rep.c_str());
	refresh();
    attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
    uint32_t child_count = ts_node_child_count(Node);
    for (uint32_t i = 0; i < child_count; ++i) {
        TSNode child = ts_node_child(Node, i);
        DfsLine(child, CurrentLine, source_code);
    }
}