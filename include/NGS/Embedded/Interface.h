#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/extend.h"

NGS_BEGIN

using pin_t = ngs::uint32;

class EmbeddedObject : public DeleteCopy {
public:
	virtual ~EmbeddedObject(){}

	virtual bool IsOpened()const = 0;
	virtual void Close() = 0;

private:

protected:
	ngs::void_ptr _data = nullptr;
};

NGS_END
