#pragma once

#include "NGS/nsw/depend.h"
#include "NGS/nsw/defined.h"

NSW_BEGIN

struct _WindowsSerialPortData {
	HANDLE com = INVALID_HANDLE_VALUE;
	pin_t port = 0;
};

NSW_END

NGS_BEGIN

bool SerialPort::Open(pin_t port) {
	_data = NGS_NEW(new nsw::_WindowsSerialPortData);
	auto& data = *reinterpret_cast<nsw::_WindowsSerialPortData*>(_data);
	std::string portname = "\\\\.\\COM";
	DCB dcbSerialParams = {};

	data.port = port;
	portname += std::to_string(port);

	data.com = CreateFileA(portname.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (data.com == INVALID_HANDLE_VALUE) {
		ngs::nos.Error("opening %s - %d \n", portname.c_str(), GetLastError());
		goto err_create;
	}

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(data.com, &dcbSerialParams)) {
		ngs::nos.Error("getting state of %s - %d \n", portname.c_str(), GetLastError());
		goto err_state;
	}

	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(data.com, &dcbSerialParams)) {
		ngs::nos.Error("setting state of %s - %d \n", portname.c_str(), GetLastError());
		goto err_state;
	}

	return true;
err_state:;
	CloseHandle(data.com);

err_create:;
	NGS_DELETE(&data);
	_data = nullptr;
	return false;
}

inline bool SerialPort::IsOpened() const
{
	return _data;
}

inline void SerialPort::Close()
{
	auto& data = *reinterpret_cast<nsw::_WindowsSerialPortData*>(_data);
	CloseHandle(data.com);
	ngs::Delete(&data);
	_data = nullptr;
}

inline size_t SerialPort::Write(ngs::byte_ptr_cst buffer, size_t size)
{
	auto& data = *reinterpret_cast<nsw::_WindowsSerialPortData*>(_data);
	DWORD bytesWritten;
	if (!WriteFile(data.com, buffer, size, &bytesWritten, NULL)) {
		ngs::nos.Error("writing to port %d - %d \n", data.port, GetLastError());
		return 0;
	}

	return bytesWritten;
}

inline size_t SerialPort::Read(ngs::byte_ptr buffer, size_t size)
{
	auto& data = *reinterpret_cast<nsw::_WindowsSerialPortData*>(_data);
	DWORD bytesRead;
	if (!ReadFile(data.com, buffer, size, &bytesRead, NULL)) {
		ngs::nos.Error("reading from port %d - %d \n", data.port, GetLastError());
		return 0;
	}

	return bytesRead;
}

NGS_END
