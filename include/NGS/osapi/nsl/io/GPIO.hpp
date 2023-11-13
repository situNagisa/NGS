#pragma once

#include "NGS/nsl/depend.h"
#include "NGS/nsl/defined.h"
#include "NGS/nsl/file/device_file.h"
#include "NGS/nsl/io/MultiplexIO.h"

NSL_BEGIN
static const std::string GPIO_DIR = "/sys/class/gpio/";

struct GPIO_Data {
	ngs::pin_t pin;
	std::string directory;
	nsl::DeviceFile
		direction{"direction"},
		active_low{ "active_low" },
		value{ "value" },
		edge{ "edge" }
	;
};

NSL_END


static bool _Export(ngs::pin_t pin) {
	auto pin_s = std::to_string(pin);
	std::string dir = nsl::GPIO_DIR + "gpio" + pin_s;

	if (!nsl::File::Access(dir)) {
		nsl::File exp("export");

		if (!exp.OpenDirectory(nsl::GPIO_DIR, nsl::File::F_OPEN_WRITE_ONLY)) {
			NGS_LOGFL(warning, "注册gpio %s 失败！\n", pin_s.c_str());
			return false;
		}

		int ret = exp.Write(pin_s);
		NGS_LOGFL(debug, "ret:%d size:%d\n", ret, pin_s.size());
		if (pin_s.size() != ret) {
			exp.Close();
			NGS_LOGFL(warning, "注册gpio %s 失败！\n", pin_s.c_str());
			return false;
		}
		exp.Close();
	}
	return true;
}

static bool _UnExport(ngs::pin_t pin) {
	auto pin_s = std::to_string(pin);
	std::string dir = nsl::GPIO_DIR + "gpio" + pin_s;

	if (!nsl::File::Access(dir)) {
		nsl::File unExp("unexport");

		if (!unExp.OpenDirectory(nsl::GPIO_DIR, nsl::File::F_OPEN_WRITE_ONLY)) {
			NGS_LOGFL(warning, "注销gpio %s 失败！\n", pin_s.c_str());
			return false;
		}
		int ret = unExp.Write(pin_s);
		NGS_LOGFL(debug, "ret:%d size:%d\n", ret, pin_s.size());
		if (pin_s.size() != ret) {
			unExp.Close();
			NGS_LOGFL(warning, "注销gpio %s 失败！\n", pin_s.c_str());
			return false;
		}
		unExp.Close();
	}
	return true;
}

NGS_HPP_INLINE bool ngs::GPIO::Open(ngs::pin_t pin, Mode mode) {
	using nsl::GPIO_Data;
	using nsl::GPIO_DIR;

	if (!_Export(pin)) return false;
	NGS_NEW(_data, nsl::GPIO_Data)();
	nsl::GPIO_Data& data = *reinterpret_cast<nsl::GPIO_Data*>(_data);

	//初始化设备文件
	data.directory = GPIO_DIR + "gpio" + std::to_string(pin);
	data.pin = pin;

	if (!data.direction.OpenDirectory(data.directory, nsl::File::F_OPEN_READ_WRITE))goto err;
	if (!data.edge.OpenDirectory(data.directory, nsl::File::F_OPEN_READ_WRITE))goto err;

	if (!data.active_low.OpenDirectory(data.directory, nsl::File::F_OPEN_WRITE_ONLY))goto err;
	data.active_low.Write("0");

	SetMode(mode);
	if (!data.value.IsOpened())goto err;

	NGS_LOGFL(debug, "pin:%d successfully!\n", pin);

	return true;
err:;
	if (data.direction.IsOpened())data.direction.Close();
	if (data.active_low.IsOpened())data.active_low.Close();
	if (data.value.IsOpened())data.value.Close();
	if (data.edge.IsOpened())data.edge.Close();

	_UnExport(data.pin);

	ngs::delete_(&data);
	_data = nullptr;
	return false;
}

NGS_HPP_INLINE bool ngs::GPIO::IsOpened()const {
	return _data;
}

NGS_HPP_INLINE void ngs::GPIO::Close() {
	nsl::GPIO_Data& data = *reinterpret_cast<nsl::GPIO_Data*>(_data);

	if (data.direction.IsOpened())data.direction.Close();
	if (data.active_low.IsOpened())data.active_low.Close();
	if (data.value.IsOpened())data.value.Close();
	if (data.edge.IsOpened())data.edge.Close();

	_UnExport(data.pin);

	NGS_DELETE(&data);
	_data = nullptr;
}

NGS_HPP_INLINE void ngs::GPIO::SetInterrupt(bool enable) {
	if (enable)return;
	nsl::GPIO_Data& data = *reinterpret_cast<nsl::GPIO_Data*>(_data);
	data.edge.Write("none");
}
NGS_HPP_INLINE void ngs::GPIO::SetInterrupt(Interrupt type) {
	nsl::GPIO_Data& data = *reinterpret_cast<nsl::GPIO_Data*>(_data);

	switch (type)
	{
	case ngs::GPIO::Interrupt::disable:
		data.edge.Write("none");
		break;
	case ngs::GPIO::Interrupt::positive:
		data.edge.Write("rising");
		break;
	case ngs::GPIO::Interrupt::nagative:
		data.edge.Write("falling");
		break;
	case ngs::GPIO::Interrupt::any:
		data.edge.Write("both");
		break;
	case ngs::GPIO::Interrupt::low:

		break;
	case ngs::GPIO::Interrupt::high:

		break;
	case ngs::GPIO::Interrupt::max:
	default:
		return;
	}
}

NGS_HPP_INLINE void ngs::GPIO::SetMode(Mode mode) {
	nsl::GPIO_Data& data = *reinterpret_cast<nsl::GPIO_Data*>(_data);

	nsl::File::OpenMode open_mode = {};
	switch (mode)
	{
	case ngs::GPIO::Mode::disable:
		return;
		break;
	case ngs::GPIO::Mode::input:
		open_mode = nsl::File::F_OPEN_READ_ONLY;
		data.direction.Write("in");
		break;
	case ngs::GPIO::Mode::output:
	case ngs::GPIO::Mode::output_open_drain:
		open_mode = nsl::File::F_OPEN_WRITE_ONLY;
		data.direction.Write("out");
		break;
	case ngs::GPIO::Mode::input_output_open_drain:
	case ngs::GPIO::Mode::input_output:
		open_mode = nsl::File::F_OPEN_READ_WRITE;
		break;
	default:
		break;
	}
	if (data.value.IsOpened())data.value.Close();
	data.value.OpenDirectory(data.directory, open_mode);
}

NGS_HPP_INLINE bool ngs::GPIO::Get()const {
	nsl::GPIO_Data& data = *reinterpret_cast<nsl::GPIO_Data*>(_data);
	char level = '0';
	data.value.OffsetHead();
	data.value.Read((ngs::byte_ptr)&level, 1);
	//ngs::nos.Log("GPIO::Get", "level:%c\n", level);

	return level == '1';
}
NGS_HPP_INLINE void ngs::GPIO::Set(bool level) {
	nsl::GPIO_Data& data = *reinterpret_cast<nsl::GPIO_Data*>(_data);

	if (level)
		data.value.Write("1");
	else
		data.value.Write("0");
}