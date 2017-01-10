#include "stdafx.h"
#include "txtDataManager.h"


txtDataManager::txtDataManager()
{
}


txtDataManager::~txtDataManager()
{
}

HRESULT txtDataManager::init()
{
	return S_OK;
}

void txtDataManager::release()
{

}

//세이브
void txtDataManager::save(const char* fileName, vector<string> vStr)
{
	HANDLE file;
	char str[SAVEBUFFER];
	DWORD write;

	strcpy(str, vectorArrayCombine(vStr));

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}

char* txtDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[SAVEBUFFER];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); ++i)
	{
		strcat(str, vArray[i].c_str());
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}

//로드
vector<string> txtDataManager::load(const char* fileName)
{
	HANDLE file;
	char str[LOADBUFFER];
	DWORD read;

	memset(str, 0, LOADBUFFER);
	file = CreateFile(fileName, GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, LOADBUFFER, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtDataManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);

	if (token == NULL)
	{
		vArray.clear();
		return vArray;
	}

	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}
	return vArray;

}
