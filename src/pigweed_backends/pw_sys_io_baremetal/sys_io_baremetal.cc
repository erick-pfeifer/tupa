#include <cstddef>

#include "pw_status/status.h"
#include "pw_status/status_with_size.h"
#include "pw_sys_io/sys_io.h"
#include "sercom/usart/plib_sercom2_usart.h"

namespace pw::sys_io {

Status ReadByte(std::byte* dest) {
  while (true) {
    if (TryReadByte(dest).ok()) {
      return OkStatus();
    }
  }
}

Status TryReadByte(std::byte* /* dest */) { return Status::Unimplemented(); }

Status WriteByte(std::byte /* b */) { return Status::Unimplemented(); }

StatusWithSize WriteLine(const std::string_view& s) {
  while (SERCOM2_USART_WriteIsBusy()) {
  }

  SERCOM2_USART_Write(const_cast<char*>(s.data()), s.size());

  while (SERCOM2_USART_WriteIsBusy()) {
  }

  SERCOM2_USART_Write(const_cast<char*>("\n"), 1);

  return StatusWithSize(OkStatus(), s.size() + 1);
}

}  // namespace pw::sys_io
