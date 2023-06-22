#include "NGL/gl/vertex_array.h"

NGLGL_BEGIN

void VertexArray::Enable(int index) { glEnableVertexAttribArray(index); }
void VertexArray::SetAttribPointer(size_t index, size_t size, void_ptr_cst offset, int type, int step, bool normalized) { glVertexAttribPointer(index, size, type, normalized, step, offset); }
void VertexArray::_SET_CURRENT_CONTEXT(context_type::handle_type context) { glBindVertexArray(context); }

NGLGL_END


