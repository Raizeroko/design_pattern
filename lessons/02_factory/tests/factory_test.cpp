#include "lessons/02_factory/after/notification.hpp"
#include "lessons/02_factory/before/notification.hpp"
#include "tests/test_framework.hpp"

void factory_tests() {
    EXPECT_EQ(factory::before::send_notification("email", "hello"), "email:hello");
    auto notifier = factory::after::make_notifier("push");
    EXPECT_EQ(notifier->send("release"), "push:release");
}

int main() {
    return labtest::run("factory", factory_tests);
}
