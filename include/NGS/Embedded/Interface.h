#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_Setting.h"

NGS_BEGIN

using pin_t = ngs::uint32;

class EmbeddedObject : public DeleteCopy {
public:
	virtual ~EmbeddedObject() {
		if (_data) {
			ngs::Delete(_data);
			_data = nullptr;
		}
	}

	virtual bool IsOpened()const = 0;
	virtual void Close() = 0;

private:

protected:
	ngs::void_ptr _data = nullptr;
};

NGS_END
