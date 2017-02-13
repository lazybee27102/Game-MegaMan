#include <iostream>
#include <cstdio>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h""

using namespace rapidjson;
using namespace std;

void main(){
	cout << "Hello\n";
	FILE* pFile = fopen("texture.json", "rb");
	char buffer[65536];
	FileReadStream is(pFile, buffer, sizeof(buffer));
	Document document;
	//document.ParseStream<0, UTF8<>, FileReadStream>(is);
	document.ParseStream(is);

	Value& imagePath = document["imagePath"];
	cout << imagePath.GetString() << "\n" << document["sprites"].GetArray()[1]["x"].GetFloat();
	std::getchar();
}