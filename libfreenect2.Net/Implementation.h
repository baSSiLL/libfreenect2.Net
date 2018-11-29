#pragma once

#define CAST_TO_MANAGED(ClassName, instance) ((instance) == nullptr ? nullptr : gcnew ClassName(instance))
