/*
 * tfile.c
 *
 * Tests for low-level file APIs (open/read/write/lseek/close/stat).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "../src/file/_fcb.h"
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

#define FILE_A "TFILEA.TMP"
#define FILE_B "TFILEB.TMP"
#define FILE_C "TFILEC.TMP"

TEST(fcb_name_uppercase_and_padding) {
    char dst[8];
    _to_fcb_name(dst, "ab1", 8);
    EXPECT_EQ_INT('A', dst[0]);
    EXPECT_EQ_INT('B', dst[1]);
    EXPECT_EQ_INT('1', dst[2]);
    EXPECT_EQ_INT(' ', dst[3]);
    EXPECT_EQ_INT(' ', dst[7]);
}

TEST(creat_write_read_roundtrip) {
    int fd;
    int rc;
    ssize_t n;
    char wbuf[8] = { 'A', 'B', 'C', 'D', '1', '2', '3', '4' };
    char rbuf[8];

    fd = creat(FILE_A);
    ASSERT_TRUE(fd >= 3);
    n = write(fd, wbuf, sizeof(wbuf));
    EXPECT_EQ_INT((int)sizeof(wbuf), (int)n);
    EXPECT_EQ_INT(0, fsync(fd));
    EXPECT_EQ_INT(0, close(fd));

    fd = open(FILE_A, O_RDONLY);
    ASSERT_TRUE(fd >= 3);
    EXPECT_EQ_LONG(0L, (long)lseek(fd, 0L, SEEK_SET));
    memset(rbuf, 0, sizeof(rbuf));
    n = read(fd, rbuf, sizeof(rbuf));
    EXPECT_EQ_INT((int)sizeof(rbuf), (int)n);
    EXPECT_EQ_INT(0, memcmp(wbuf, rbuf, sizeof(rbuf)));
    rc = close(fd);
    EXPECT_EQ_INT(0, rc);
}

TEST(open_with_create_flag) {
    int fd = open(FILE_B, O_WRONLY | O_CREAT);
    ASSERT_TRUE(fd >= 3);
    EXPECT_EQ_INT(0, close(fd));
}

TEST(open_invalid_path_sets_enoent) {
    int fd;
    errno = 0;
    fd = open("ABCDEFGHI.TMP", O_RDONLY);
    EXPECT_EQ_INT(-1, fd);
    EXPECT_EQ_INT(ENOENT, errno);
}

TEST(open_missing_file_without_create_fails) {
    int fd;
    errno = 0;
    fd = open("MISSING.TMP", O_RDONLY);
    EXPECT_EQ_INT(-1, fd);
    EXPECT_EQ_INT(EIO, errno);
}

TEST(lseek_invalid_cases) {
    int fd = creat(FILE_C);
    ASSERT_TRUE(fd >= 3);

    errno = 0;
    EXPECT_EQ_LONG(-1L, (long)lseek(fd, -1L, SEEK_SET));
    EXPECT_EQ_INT(EINVAL, errno);

    errno = 0;
    EXPECT_EQ_LONG(-1L, (long)lseek(fd, 0L, SEEK_END));
    EXPECT_EQ_INT(EINVAL, errno);

    EXPECT_EQ_INT(0, close(fd));
}

TEST(stat_existing_file) {
    int fd;
    char payload[] = "xyz";
    struct stat st;
    int rc;

    fd = creat(FILE_A);
    ASSERT_TRUE(fd >= 3);
    EXPECT_EQ_INT(3, (int)write(fd, payload, 3));
    EXPECT_EQ_INT(0, close(fd));

    rc = stat(FILE_A, &st);
    EXPECT_EQ_INT(0, rc);
    EXPECT_TRUE(st.st_size >= 3);
    EXPECT_TRUE(st.st_blksize > 0);
}

TEST(stat_missing_file_fails) {
    struct stat st;
    errno = 0;
    EXPECT_EQ_INT(-1, stat("NOFILE.TMP", &st));
    EXPECT_EQ_INT(EIO, errno);
}

TEST(invalid_fd_errors) {
    char ch;
    errno = 0;
    EXPECT_EQ_INT(-1, close(2));
    EXPECT_EQ_INT(EBADF, errno);

    errno = 0;
    EXPECT_EQ_INT(-1, fsync(2));
    EXPECT_EQ_INT(EBADF, errno);

    errno = 0;
    EXPECT_EQ_INT(-1, (int)read(2, &ch, 1));
    EXPECT_EQ_INT(EBADF, errno);

    errno = 0;
    EXPECT_EQ_INT(-1, (int)write(2, "z", 1));
    EXPECT_EQ_INT(EBADF, errno);
}

TEST(remove_and_unlink) {
    int fd;
    struct stat st;

    fd = creat("TDEL1.TMP");
    ASSERT_TRUE(fd >= 3);
    EXPECT_EQ_INT(0, close(fd));
    EXPECT_EQ_INT(0, remove("TDEL1.TMP"));
    EXPECT_EQ_INT(-1, stat("TDEL1.TMP", &st));

    fd = creat("TDEL2.TMP");
    ASSERT_TRUE(fd >= 3);
    EXPECT_EQ_INT(0, close(fd));
    EXPECT_EQ_INT(0, unlink("TDEL2.TMP"));
    EXPECT_EQ_INT(-1, stat("TDEL2.TMP", &st));
}

TEST(dirent_lists_matching_files) {
    int fd;
    DIR *dir;
    struct dirent *ent;
    int found_a = 0;
    int found_b = 0;

    fd = creat("DIRENTA.TMP");
    ASSERT_TRUE(fd >= 3);
    EXPECT_EQ_INT(0, close(fd));

    fd = creat("DIRENTB.TMP");
    ASSERT_TRUE(fd >= 3);
    EXPECT_EQ_INT(0, close(fd));

    dir = opendir("DIRENT*.TMP");
    ASSERT_TRUE(dir != NULL);

    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, "DIRENTA.TMP") == 0)
            found_a = 1;
        if (strcmp(ent->d_name, "DIRENTB.TMP") == 0)
            found_b = 1;
    }

    EXPECT_EQ_INT(0, closedir(dir));
    EXPECT_TRUE(found_a);
    EXPECT_TRUE(found_b);
}

int main(void) {
    printf("TFILE: file API tests\r\n");
    RUN_TEST(fcb_name_uppercase_and_padding);
    RUN_TEST(creat_write_read_roundtrip);
    RUN_TEST(open_with_create_flag);
    RUN_TEST(open_invalid_path_sets_enoent);
    RUN_TEST(open_missing_file_without_create_fails);
    RUN_TEST(lseek_invalid_cases);
    RUN_TEST(stat_existing_file);
    RUN_TEST(stat_missing_file_fails);
    RUN_TEST(invalid_fd_errors);
    RUN_TEST(remove_and_unlink);
    RUN_TEST(dirent_lists_matching_files);
    if (g_failures == 0) {
        printf("PASS all %d tests\r\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\r\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
