﻿#include "ResourceManager.h"
#include "rapidxml-1.13\rapidxml.hpp"
#include <fstream>
#include <vector>
#include "../MegaMan/MegaManUtilities.h"

#include <iostream>
#include <cstdio>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;
using namespace std;
using namespace rapidxml;
using namespace s_framework;

ResourceManager* ResourceManager::m_instance = NULL;

ResourceManager::ResourceManager()
{
	
}


ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance(){
	if (m_instance == NULL)
		m_instance = new ResourceManager();
	return m_instance;
}

void ResourceManager::resetResourceManager(){
	delete m_instance;
	m_instance = NULL;
}

void ResourceManager::parseAnimationXML(Texture* texture,string xmlFile)
{
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile(xmlFile);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node();
	// Iterate over the brewerys

	SpriteSpec* t_spriteSpec = NULL;
	vector<SpriteSpec*> t_listSpriteSpec;

	ObjectState t_objectState;
	int objectType = 0;
	int stateID = 0;
	int frameID = 0;
	int delayTime = 0;
	for (xml_node<> * character_node = root_node->first_node(); character_node; character_node = character_node->next_sibling())
	{
		//t_spriteSpec = new SpriteSpec();

		objectType = stoi(character_node->first_attribute("objectID")->value());

		for (xml_node<>* state_node = character_node->first_node(); state_node; state_node = state_node->next_sibling()){
			stateID = stoi(state_node->first_attribute("stateID")->value());
			delayTime = stoi(state_node->first_attribute("delayTime")->value());

			// gán characterID và stateID vào lớp CharacterState
			t_objectState.m_character = objectType;
			t_objectState.m_state = stateID;

			AnimationSpec* t_animationSpec = new AnimationSpec();
			t_animationSpec->setDelayTime(delayTime);
			//// biến tạm chứa list SpriteSpec
			vector<SpriteSpec*> t_listSpriteSpec;

			for (xml_node<>* frame_node = state_node->first_node(); frame_node; frame_node = frame_node->next_sibling()){

				frameID = stoi(frame_node->value());

				t_spriteSpec = texture->getSpriteSpecById(frameID);
				t_listSpriteSpec.push_back(t_spriteSpec);
			}
			t_animationSpec->setSpriteSpecs(t_listSpriteSpec);

			m_mapStateToAnimation[t_objectState] = t_animationSpec;
		}
	}
}

void ResourceManager::parseAnimationJSON(Texture* texture,string jsonFile){
	FILE* pFile = fopen(jsonFile.c_str(), "rb");
	char buffer[65536];
	FileReadStream is(pFile, buffer, sizeof(buffer));
	Document document;
	//document.ParseStream<0, UTF8<>, FileReadStream>(is);
	document.ParseStream(is);
	Value& animation_list = document["animation"];

	SpriteSpec* t_spriteSpec = NULL;
	vector<SpriteSpec*> t_listSpriteSpec;

	ObjectState t_objectState;
	int objectType = 0;
	int stateID = 0;
	int frameID = 0;
	int delayTime = 0;
	for (SizeType i = 0; i < animation_list.Size(); i++)
	{
		//t_spriteSpec = new SpriteSpec();
		Value& animation = animation_list[i];
		objectType = animation["objectID"].GetInt();
		Value& state = animation["state"];
		for (SizeType j = 0; j < state.Size(); j++){
			stateID = state[j]["stateID"].GetInt();
			delayTime = state[j]["delayTime"].GetInt();

			// gán characterID và stateID vào lớp CharacterState
			t_objectState.m_character = objectType;
			t_objectState.m_state = stateID;

			AnimationSpec* t_animationSpec = new AnimationSpec();
			t_animationSpec->setDelayTime(delayTime);
			//// biến tạm chứa list SpriteSpec
			vector<SpriteSpec*> t_listSpriteSpec;

			Value& frame = state[j]["frame"];
			for (SizeType f = 0; f < frame.Size(); f++){

				frameID = frame[f].GetInt();
				t_spriteSpec = texture->getSpriteSpecById(frameID);
				t_listSpriteSpec.push_back(t_spriteSpec);
			}
			t_animationSpec->setSpriteSpecs(t_listSpriteSpec);

			m_mapStateToAnimation[t_objectState] = t_animationSpec;
		}
	}
	
}

AnimationSpec* ResourceManager::getAnimationSprites(int character, int state)
{
	ObjectState t;
	t.m_character = character;
	t.m_state = state;

	return m_mapStateToAnimation[t];
}