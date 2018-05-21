/*
	Name:	ConfigTool.cpp
	Author:	Tvde1
*/

#include "ConfigTool.h";
#include "FS.h";
#include "ArduinoJson.h"

void ConfigTool::load() {
	SPIFFS.begin();
	File f = SPIFFS.open("/config.json", "r");
	if (!f) {
		return;
	}

	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(f.readStringUntil('\n'));

	for (auto item : variables_) {
		item->deserialize(&root);
	}

	f.close();
}

void ConfigTool::save() {
	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	for (auto item : variables_) {
		item->serialize(&root);
	}

	SPIFFS.begin();
	File f = SPIFFS.open("/config.json", "w");
	
	String output = "";
	root.printTo(f);

	f.close();
}

void ConfigTool::getWebPortal() {
	//TODO: This
}

void ConfigTool::reset() {
	SPIFFS.begin();
	SPIFFS.remove("/config.json");

	for (auto item : variables_) {
		item->reset();
	}
}