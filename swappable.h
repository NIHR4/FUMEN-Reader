#pragma once
//Benjamin, https://stackoverflow.com/a/24761663/10999204
template<typename T>
T bswap(T val) {
	T retVal;
	char* pVal = (char*)& val;
	char* pRetVal = (char*)& retVal;
	int size = sizeof(T);
	for (int i = 0; i < size; i++) pRetVal[size - 1 - i] = pVal[i];

	return retVal;
}

