#include "stack.h"

#include "../gtest/gtest.h"

TEST(TStack, can_create_steck_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> bf(3));
}

