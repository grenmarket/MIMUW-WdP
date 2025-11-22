CC = gcc

CFLAGS = -std=c23 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond -Wfloat-equal -Wshadow -Wconversion -Wjump-misses-init -Wlogical-not-parentheses -Wnull-dereference -Wvla -Werror -fstack-protector-strong -fsanitize=undefined -fno-sanitize-recover -g -fno-omit-frame-pointer -O1

TARGET = algorytm_x

$(TARGET): algorytm_x.c
	$(CC) $(CFLAGS) algorytm_x.c -o $(TARGET)

clean:
	rm -f $(TARGET)
