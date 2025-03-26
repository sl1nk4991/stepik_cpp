// filepath: /home/admin-1/Documents/src/cpp/stepik/sharedptr/test_main.cpp
#include <cassert>
#include "../sharedptr/main.cpp"

void test_reset_with_nullptr() {
    SharedPtr ptr(new Number(10));
    assert(ptr.get() != nullptr); // Initially, ptr manages an object

    ptr.reset(); // Reset to nullptr
    assert(ptr.get() == nullptr); // ptr should now manage no object
}

void test_reset_with_new_object() {
    SharedPtr ptr(new Number(10));
    assert(ptr.get() != nullptr); // Initially, ptr manages an object
    assert(ptr->evaluate() == 10); // Verify the value

    ptr.reset(new Number(20)); // Reset with a new object
    assert(ptr.get() != nullptr); // ptr should now manage the new object
    assert(ptr->evaluate() == 20); // Verify the new value
}

void test_reset_on_empty_sharedptr() {
    SharedPtr ptr; // Empty SharedPtr
    assert(ptr.get() == nullptr); // Initially, ptr manages no object

    ptr.reset(); // Reset to nullptr (no-op)
    assert(ptr.get() == nullptr); // ptr should still manage no object
}

void test_reset_with_reference_counting() {
    SharedPtr ptr1(new Number(10));
    SharedPtr ptr2 = ptr1; // Shared ownership
    assert(ptr1.get() == ptr2.get()); // Both should manage the same object

    ptr1.reset(new Number(20)); // Reset ptr1 with a new object
    assert(ptr1.get() != nullptr); // ptr1 should manage the new object
    assert(ptr1->evaluate() == 20); // Verify the new value
    assert(ptr2.get() != nullptr); // ptr2 should still manage the old object
    assert(ptr2->evaluate() == 10); // Verify the old value
}

void test_reference_counting_multiple_sharedptrs() {
    SharedPtr ptr1(new Number(42)); // Create a new SharedPtr managing an object
    assert(ptr1.get() != nullptr); // ptr1 should manage the object
    assert(ptr1->evaluate() == 42); // Verify the value

    {
        SharedPtr ptr2 = ptr1; // Shared ownership
        SharedPtr ptr3 = ptr2; // Another shared ownership
        assert(ptr1.get() == ptr2.get()); // All should manage the same object
        assert(ptr2.get() == ptr3.get()); // All should manage the same object
        assert(ptr3->evaluate() == 42); // Verify the value

        ptr2.reset(new Number(100)); // Reset ptr2 with a new object
        assert(ptr2.get() != nullptr); // ptr2 should manage the new object
        assert(ptr2->evaluate() == 100); // Verify the new value
        assert(ptr1.get() == ptr3.get()); // ptr1 and ptr3 should still manage the old object
        assert(ptr1->evaluate() == 42); // Verify the old value
    }

    // After ptr2 and ptr3 go out of scope, ptr1 should still manage the object
    assert(ptr1.get() != nullptr); // ptr1 should still manage the object
    assert(ptr1->evaluate() == 42); // Verify the value
}

int main() {
    test_reset_with_nullptr();
    test_reset_with_new_object();
    test_reset_on_empty_sharedptr();
    test_reset_with_reference_counting();
    test_reference_counting_multiple_sharedptrs();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}