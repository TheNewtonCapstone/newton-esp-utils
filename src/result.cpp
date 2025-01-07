#include "newton/result.h"

using namespace newton;

Result<void> Result<void>::success()
{
    return Result<void>("");
}