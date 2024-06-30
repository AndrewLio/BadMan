#include "ClientSpoofer.h"

#include <combaseapi.h>

#include <Windows.h>
#include <iostream>

#include <iphlpapi.h>

#include <WS2tcpip.h>

#pragma comment(lib, "IPHLPAPI.lib")

ClientSpoofer::ClientSpoofer() : IModule(0, Category::CLIENT, "spoofes") {
}

const char* ClientSpoofer::getModuleName() {
	return "Spoofer";
}

void ClientSpoofer::GetIP() {
	const char* newIpAddress = "maybe doesnt work :(";

	PIP_ADAPTER_INFO adapterInfo = new IP_ADAPTER_INFO;
	ULONG bufferSize = sizeof(IP_ADAPTER_INFO);
	if (GetAdaptersInfo(adapterInfo, &bufferSize) == ERROR_BUFFER_OVERFLOW) {
		delete[] adapterInfo;
		adapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(new char[bufferSize]);
	}
	if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR) {
		for (PIP_ADAPTER_INFO adapter = adapterInfo; adapter; adapter = adapter->Next) {
			if (adapter->Type == MIB_IF_TYPE_ETHERNET && adapter->AddressLength == 6) {
				DWORD dwRetVal;
				MIB_IPNETROW ipNetRow;
				if ((dwRetVal = SendARP(INT(newIpAddress), 0, &ipNetRow, nullptr)) == NO_ERROR) {
					memcpy(ipNetRow.bPhysAddr, adapter->Address, adapter->AddressLength);  // Spoofing
					ipNetRow.dwType = MIB_IPNET_TYPE_DYNAMIC;

					if (CreateIpNetEntry(&ipNetRow) != NO_ERROR) {
					} else {
					}
				} else {
				}
			}
		}
	} else {
		std::cout << "Error getting adapter information." << std::endl;
	}

	delete[] adapterInfo;
}

std::string ClientSpoofer::GetGUID() {
	constexpr size_t GUID_LEN = 64;
	char buffer[GUID_LEN];

	GUID guid;
	if (bool(CoCreateGuid(&guid)))
		return std::string();

	_snprintf(buffer, GUID_LEN,
			  "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			  guid.Data1, guid.Data2, guid.Data3,
			  guid.Data4[0], guid.Data4[1], guid.Data4[2],
			  guid.Data4[3], guid.Data4[4], guid.Data4[5],
			  guid.Data4[6], guid.Data4[7]);
	return buffer;
}

void ClientSpoofer::onEnable() {
}

void ClientSpoofer::onTick(GameMode* gm) {
	if (guidSpf) {
		GetGUID();
	}
	if (ipSpf) {
		GetIP();
	}
}

void ClientSpoofer::onDisable() {
}