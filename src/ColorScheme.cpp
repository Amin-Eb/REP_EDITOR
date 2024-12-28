#include "ColorScheme.h"
using namespace std;
using json = nlohmann::json;

void ColorScheme::InitColor(int Number, string HexaColor){
    int r, g, b;
    stringstream ss;
    ss << std::hex << HexaColor.substr(1, 2); // Red
    ss >> r;
    ss.clear();
    ss << std::hex << HexaColor.substr(3, 2); // Green
    ss >> g;
    ss.clear();
    ss << std::hex << HexaColor.substr(5, 2); // Blue
    ss >> b;    
    init_color(Number + 10, r * 4, g * 4, b * 4);
}

map<string, int> ColorScheme::Build(string FileName){
    std::fstream JsonFile{};
    map<string,int> ColorMap;
    try{
        JsonFile.open(FileName);
    }catch(const std::ios_base::failure& e){
        return ColorMap;
    }
    json ColorData;
    JsonFile >> ColorData; 
    InitColor(0, (string)ColorData["colors"]["editor.background"]);
    InitColor(1, (string)ColorData["colors"]["editor.foreground"]);
    InitColor(2, (string)ColorData["colors"]["editor.selectionHighlightBackground"]);
    int i = 0, ted = 5;
    for(auto x : ColorData["tokenColors"]){
        cout << ColorData["tokenColors"][i] << endl;
        int j = 0;
        for(auto y : ColorData["tokenColors"][i]["scope"]){
            if(y == "string"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["string_content"] = ted;
                ColorMap["character"] = ted;
                ColorMap["'"] = ted;
                ColorMap["\""] = ted;
                ted ++;
            }else if(y == "comment"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["comment"] = ted;
                ted ++;
            }else if(y == "keyword.control"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["if"] = ted;
                ColorMap["while"] = ted;
                ColorMap["for"] = ted;
                ColorMap["do"] = ted;
                ColorMap["return"] = ted;
                ColorMap["continue"] = ted;
                ColorMap["else"] = ted;
                ColorMap["using"] = ted;
                ColorMap["#include"] = ted;
                ColorMap["#define"] = ted;
                ColorMap["#endif"] = ted;
                ColorMap["#ifndef"] = ted;
                ColorMap["#ifdef"] = ted;
                ted ++;
            }else if(y == "constant.numeric"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["number_literal"] = ted;
                ted ++;
            }else if(y == "storage.type"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["primitive_type"] = ted;
                ColorMap["namespace"] = ted;
                ted ++;
            }
            else if(y == "variable.other.constant"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["const"] = ted;
                ColorMap["static"] = ted;
                ColorMap["auto"] = ted;
                ColorMap["class"] = ted;
                ted ++;   
            }
            else if(y == "entity.name.function"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["field_identifier"] = ted;
                ColorMap["func"] = ted;
                ted ++;   
            }else if(y == "meta.preprocessor.string"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["system_libstring"] = ted;
                ted ++;
            }else if(y == "entity.name.namespace"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["namespace_identifier"] = ted;
                ted ++;
            }
            j++;
        } 
        i++;
    }
    return ColorMap;
}