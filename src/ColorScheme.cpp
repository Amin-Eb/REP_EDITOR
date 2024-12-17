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
    init_color(Number + 10, r * 1000 / 255, g * 1000 / 255, b * 1000 / 255);
}

map<string, int> ColorScheme::Build(string FileName){
    std::fstream JsonFile{};
    JsonFile.open(FileName);
    map<string,int> ColorMap;
    if (!JsonFile.is_open()) {
        return ColorMap;
    }      
    json ColorData;
    JsonFile >> ColorData; 
    InitColor(0, (string)ColorData["colors"]["editor.background"]);
    InitColor(1, (string)ColorData["colors"]["editor.foreground"]);
    InitColor(2, (string)ColorData["colors"]["editor.lineHighlightBackground"]);
    int i = 0, ted = 5;
    for(auto x : ColorData["tokenColors"]){
        cout << ColorData["tokenColors"][i] << endl;
        int j = 0;
        for(auto y : ColorData["tokenColors"][i]["scope"]){
            if(y == "string"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["string_content"] = ted;
                ColorMap["char_literal"] = ted;
                ColorMap["'"] = ted;
                ColorMap["\""] = ted;
                ted ++;
            }else if(y == "comment"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["comment"] = ted;
                ted ++;
            }else if(y == "keyword"){
                InitColor(ted, ColorData["tokenColors"][i]["settings"]["foreground"]);
                init_pair(ted, ted + 10, 10);
                ColorMap["if"] = ted;
                ColorMap["while"] = ted;
                ColorMap["for"] = ted;
                ColorMap["do"] = ted;
                ColorMap["return"] = ted;
                ColorMap["continue"] = ted;
                ColorMap["else"] = ted;
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
                ColorMap["identifier"] = ted;
                ted ++;   
            }
            j ++;
        } 
        i++;
    }
    return ColorMap;
}