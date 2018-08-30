WORK_PATH=$(shell pwd)
BIN=httpd
SRC=httpd.c
CC=gcc
LDFLAGS=-lpthread -DDEBUG
#gcc -D  编译时指定我们的宏       

.PHONY:all
all:$(BIN) cgi

$(BIN):$(SRC)
	@$(CC) -o $@ $^ $(LDFLAGS)
cgi:
	@cd wwwroot/cgi; make clean;make; cd -
.PHONY:output
output:
	@mkdir -p output/wwwroot/cgi
	@cp $(BIN) output
	@cp start.sh output
	@cp wwwroot/*.html output/wwwroot
	@cp -rf wwwroot/imag output/wwwroot
	@cp wwwroot/cgi/math_cgi output/wwwroot/cgi

.PHONY:clean
clean:
	@rm -f $(BIN)
	@rm -rf output
	@cd wwwroot/cgi; make clean; cd -
	

















