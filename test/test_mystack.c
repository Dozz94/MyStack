#include "vendor/unity.h"
#include "../src/mystack.h"
#include <stdlib.h>

MyStack* stack;

void setUp(void) {
    stack = stack_create();
}

void tearDown(void) {
    stack_delete(stack);
}

void test_stack_create(void)
{
  TEST_ASSERT_NOT_NULL(stack);
  TEST_ASSERT_EQUAL_INT(-1, stack->top);

  for (size_t i = 0; i < MAX_STACK_SIZE; i++) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, stack->data[i], "data should be 0");
  }
}

void test_stack_push_onStackWithOneElement(void) {
	//given an empty stack
	stack->data[0] = 1;
	stack->top = 0;

	//when
	bool result= stack_push(stack, 2);


	//then
	TEST_ASSERT_EQUAL_INT(1, stack->top);
	TEST_ASSERT_EQUAL_INT(2, stack->data[1]);

	TEST_ASSERT_EQUAL_INT(1, stack->data[0]);
	for (int i = 2; i < MAX_STACK_SIZE; i++)
	{
		TEST_ASSERT_EQUAL_INT(0, stack->data[i]);
	}

	TEST_ASSERT_TRUE(result);

}

void test_stack_push_stackIsFull(void) {
	//given a full stack
	stack->top = MAX_STACK_SIZE - 1;

	//when
	bool result = stack_push(stack, 5);


	//then
	TEST_ASSERT_FALSE_MESSAGE(result, "stack_push returned true for full stack");
	TEST_ASSERT_EQUAL_INT(MAX_STACK_SIZE - 1, stack->top);
	TEST_ASSERT_NOT_EQUAL(5, stack->data[MAX_STACK_SIZE - 1]);
}

int main(void)
{
   UnityBegin("MyStack");

   RUN_TEST(test_stack_create);
   RUN_TEST(test_stack_push_onStackWithOneElement);
   RUN_TEST(test_stack_push_stackIsFull);

   UnityEnd();
   return 0;
}
