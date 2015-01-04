#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "react_render.h"

check_path(const char *path, const char *expected) {
        char *buf;

        buf = render_path(path);
        ck_assert_msg(buf, "Expected <%s> to return a valid buffer");
        ck_assert_msg(strstr(buf, expected),
                      "Expected <%s> to contain %s, actually returned %s",
                      path, expected, buf);
        free(buf);
}

START_TEST(test_render_404)
{
        check_path("/notfound", "404 :(");
}
END_TEST

START_TEST(test_render_root)
{
        check_path("/", "Hello Isomorphic React!");
}
END_TEST

Suite * react_render_suite()
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("React Rendering");

        tc_core = tcase_create("Core");
        tcase_add_test(tc_core, test_render_404);
        tcase_add_test(tc_core, test_render_root);

        suite_add_tcase(s, tc_core);

        return s;
}

int main(void) {
        int number_failed;
        Suite *s;
        SRunner *sr;

        s = react_render_suite();
        sr = srunner_create(s);

        render_set_debug(1);
        render_init("../bundle.js");

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
